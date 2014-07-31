/*
* File: Artist.cpp
* Author: Tyson Manning, Nick Smith, Jess Zielinski, Chris Porto, Audra Agajanian
* Member: FinalProject.sln
* 
* Due: 24 July 2014
*/

#include "stdafx.h"
#include "Artist.h"

Artist::Artist(string n){
	name = n;
	numberOfAlbums = 0;
	size = 5; // Default size is 5 Albums
	albums = new Album*[size]; // Create an albums array of default size
}

Artist::Artist(string n, int nOA){
	name = n;
	numberOfAlbums = nOA;
	size = numberOfAlbums; // Create an array just long enough for all Albums
	albums = new Album*[size];
}

Artist::Artist(ifstream *inFile){
	char str[100];
	
	// Read in and assign Artist Name
	(*inFile).getline(str, 100, '\t');
	name = str;

	// Read in number of Albums by this artist
	(*inFile) >> numberOfAlbums;

	// Eat up the newline character
	(*inFile).get();

	// Create a vector of NULL pointers
	size = numberOfAlbums;
	albums = new Album*[size];

	// Read in all albums by this artist
	for (int i = 0; i < numberOfAlbums; i++){
		albums[i] = new Album(inFile);
	}
}

int Artist::getNumberAlbums(){
	return numberOfAlbums;
}

string Artist::getName(){
	return name;
}

Album* Artist::getAlbum(int index){
	return albums[index];
}

bool Artist::add(Album *newAlbum){
	bool added = false, found = false;
	int i=0;
	while(i < numberOfAlbums && (!found || !added)){
		cout << (*albums[i]).getTitle() << endl;
		if ((*newAlbum).getTitle() == (*albums[i]).getTitle()){
			found = true;
			//need to copy over all Songs in newAlbum. 
			for (int j=0; j < (*newAlbum).getNumberOfSongs(); j++)
			{
				added = (added || (*albums[i]).add((*newAlbum).getSong(j)));
			}

		}
		i++;
	}
	if (!found){
		albums[numberOfAlbums] = newAlbum;
		numberOfAlbums++;
		added = true;
	}
	return added;
}

bool Artist::remove(int index){
	if(index >= 0 && index < numberOfAlbums) {
		for (int i = index; i<(numberOfAlbums-1); i++){
			albums[i]=albums[i+1];
		}
		numberOfAlbums--;
		return true;
	} else {
		return false;
	}
}

bool Artist::search(string name){
	bool retval = false;
	for(int i=0; i<numberOfAlbums; i++) {
		if(name == (*albums[i]).getTitle()) {
			(*albums[i]).print();
			retval = true;
		}
		retval = (*albums[i]).search(name) || retval;
	}
	return retval;
}

bool Artist::searchPart(string part, int *foundNumber){
	string name;
	bool match = false;
	for (int i = 0; i < numberOfAlbums; i++){
		if((*albums[i]).getTitle().find(part) != string::npos) {
			cout << (*foundNumber)++ << '\t' << (*albums[i]).getTitle() << endl;
			match = true;
		}
		match = (*albums[i]).searchPart(part, foundNumber) || match;
	}
	return match;
}

void Artist::print(){
	cout << "Artist: " << name << endl << endl;
	for (int i = 0; i < numberOfAlbums; i++){
		(*albums[i]).print();
	}
	cout << "\n\n";
}

void Artist::saveArtist(ofstream *outFile){
	*outFile << name << '\t' << numberOfAlbums << endl;

	// Output each albums's information
	for (int i = 0; i < numberOfAlbums; i++){
		(*albums[i]).saveAlbum(outFile);
	}
}

void Artist::deleteArtist(){
	for (int i = numberOfAlbums - 1; i >= 0; i--){
		delete albums[i];
	}
	size = 0;
}

bool Artist::resize(int newSize){
	if(newSize > numberOfAlbums){
		Album **newAlbums = new Album*[newSize];
		for(int i=0; i<numberOfAlbums; i++){
			newAlbums[i]=albums[i];
		}
		delete albums;
		albums = newAlbums;
		size = newSize;
		return true;
	}
	return false;
}

bool Artist::resize(){
	return resize(numberOfAlbums+2);
}