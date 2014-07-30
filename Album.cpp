#include "stdafx.h"
#include <iostream>
#include "Album.h"

Album::Album(string titleP, int numSongsP, Song **songsP){
	title = titleP;
	numSongs = numSongsP;
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
	songs = new Song*[numSongs];
	
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

Song Album::getSong(int index){
     if(index > 0 && index < numSongs)
         return *songs[index];    
     else
         return NULL;                 //not sure if this will work or break the program
}

void Album::setSong(Song *newSong, int index){
     if(index > 0 && index < numSongs)
		 songs[index] = newSong;
     else
         cout << "The album does not have that many tracks" << endl;
}

bool Album::removeSong(int index){
    //Is there a song.kill() of some sort?
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

int Album::getNumberOfSongs(){
    return numSongs;
}

void Album::printLength(){
	unsigned long length = calculateLength();
	cout << length/60 << ":";  //convert to minutes and seconds. Unnecessary, but looks nice
	if(length%60 < 10)
		cout << "0" << length%60;   //cout "0:04" instead of "0:4"
	else
		cout << length%60;
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

bool Album::add(Song*){
	return false;
}

void Album::saveAlbum(ofstream *outFile){
	*outFile << title << '\t' << numSongs << endl;

	// Output each albums's information
	for (int i = 0; i < numSongs; i++){
		(*songs[i]).saveSong(outFile);
	}
}

void Album::deleteAlbum(){
	for (int i = numSongs - 1; i >= 0; i--){
		delete songs[i];
	}
}

unsigned long Album::calculateLength(){
	unsigned long retval = 0;
	
	for(int i=0; i<numSongs; i++)          //calculate album length
		retval += (*songs[i]).getLength();

	return retval;
}