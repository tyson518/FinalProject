/*
* File: Album.cpp
* Author: Tyson Manning, Nick Smith, Jess Zielinski, Chris Porto, Audra Agajanian
* Member: FinalProject.sln
* 
* Due: 24 July 2014
*/

#include "stdafx.h"
#include <iostream>
#include "Album.h"

Album::Album(string titleP, int numSongsP, Song **songsP){
	title = titleP;
	numSongs = numSongsP;
	size = numSongs; // Songs array passed is as big as the number of songs in the album
	songs = songsP;
}

Album::Album(ifstream *inFile){
	char str[100];

	// Read in and assign Album title
	(*inFile).getline(str, 100, '\t');
	title = str;

	// Read in number of songs in album
	(*inFile) >> numSongs;

	// Eat up the newline character
	(*inFile).get();

	// Create a vector of NULL pointers
	size = numSongs;
	songs = new Song*[size];

	
	// Read in all songs from this album
	for (int i = 0; i < numSongs; i++){
		songs[i] = new Song(inFile);
	}
}

string Album::getTitle(){
	return title;       
}

void Album::setTitle(string newTitle){
	title = newTitle;   
}

Song* Album::getSong(int index){
     if(index >= 0 && index < numSongs)
         return songs[index];
     return NULL;                 //not sure if this will work or break the program
}

int Album::getNumberOfSongs(){
    return numSongs;
}

bool Album::editSong(Song *newSong, int index){
    if(index > 0 && index < numSongs)
	{
		songs[index] = newSong;
		return true;
	}
	else
		return false;
}

bool Album::insertSong(Song *newSong, int index)
{
    if(index > 0 && index < numSongs && size>numSongs) //needs to be an initialized index and have room to slide down
	{
		for(int i=numSongs; i>index; i--) //start at the end and go backward, shifting songs up
		{
			songs[i+1] = songs[i];
		}
		songs[index] = newSong; //add the new song
		numSongs++;
		return true;
	}
	else if(index>0 && index<numSongs && size<=numSongs)	//if array is too small to slide down
	{
		resize();	//make array larger
		for(int i=numSongs; i>index; i--)
		{
			songs[i+1] = songs[i];
		}
		songs[index] = newSong;
		numSongs++;
		return true;
	}
	else
		return false;
}

bool Album::add(Song *newSong){
	bool added = false, found = false;
	int i=0; 
	while (i < numSongs && (!added || !found)) {
		if ((*newSong).getTitle() == (*songs[i]).getTitle()){
			found = true;
		}
		i++;
	}
	if (!found){
		// add newSong to songs array
		
		if (numSongs < size || resize()){
			songs[numSongs] = newSong;
			numSongs++;
			added = true;
		}
	}
	return added;

}

bool Album::search(string searchSong)
{
	bool retval = false;
	for(int i=0; i<numSongs; i++) {
		if(searchSong == (*songs[i]).getTitle()) {
			(*songs[i]).print();
			retval = true;
		}
	}
	return retval;
}

int Album::getIndex(string searchSong)
{
	int retval = -1;
	for(int i=0; i<numSongs; i++) 
	{
		if(searchSong == (*songs[i]).getTitle()) 
		{
			retval = i;
		}
	}
	return retval;
}

bool Album::searchPart(string part, int *foundNumber){
	string name;
	bool match = false;
	for (int i = 0; i < numSongs; i++){
		if((*songs[i]).getTitle().find(part) != string::npos) {
			cout << (*foundNumber)++ << '\t' << (*songs[i]).getTitle() << endl;
			match = true;
		}
	}
	return match;
}

bool Album::removeSong(int index){
	if(index >= 0 && index < numSongs) {
		for (int i = index; i<(numSongs-1); i++){
			songs[i]=songs[i+1];
		}
		numSongs--;
		return true;
	} else {
		return false;
	}
}

void Album::saveAlbum(ofstream *outFile){
	*outFile << title << '\t' << numSongs << endl;

	// Output each albums's information
	for (int i = 0; i < numSongs; i++){
		(*songs[i]).saveSong(outFile);
	}
}

void Album::print(){
	cout << "Album Name:\t" << title << "\tAlbum Length:\t";
	printLength();
	cout << endl << "\t#\tTime\tPlays\tName\n";
	for (int i = 0; i < numSongs; i++){
		cout << "\t" << i + 1 << "\t";
		(*songs[i]).print();
	}
	cout << endl;
}

void Album::deleteAlbum(){
	for (int i = numSongs - 1; i >= 0; i--){
		delete songs[i];
	}
	size = 0;
	numSongs = 0;
}

bool Album::resize(int newSize){
	if(newSize > numSongs){
		Song **newSongs = new Song*[newSize];
		for(int i=0; i<numSongs; i++){
			newSongs[i]=songs[i];
		}
		delete songs;
		songs = newSongs;
		size = newSize;
		return true;
	}
	return false;
}

bool Album::resize(){
	return resize(numSongs*2);
}

unsigned long Album::calculateLength(){
	unsigned long retval = 0;
	
	for(int i=0; i<numSongs; i++)          //calculate album length
		retval += (*songs[i]).getLength();

	return retval;
}

void Album::printLength(){
	unsigned long length = calculateLength();
	cout << length/60 << ":";  //convert to minutes and seconds. Unnecessary, but looks nice
	if(length%60 < 10)
		cout << "0" << length%60;   //cout "0:04" instead of "0:4"
	else
		cout << length%60;
}