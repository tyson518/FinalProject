/*
* File: Library.cpp
* Author: Tyson Manning, Nick Smith, Jess Zielinski, Chris Porto, Audra Agajanian
* Member: FinalProject.sln
* 
* Due: 24 July 2014
*/

#include "stdafx.h"
#include "Library.h"

Library::Library(){
	size = 20; // Default size of 20 Artists
	artists = new Artist*[size]; // Create empty array of default size
	numberOfArtists = 0;
}

bool Library::add(Artist *newArtist){
	bool added = false, found = false;
	int i=0; 
	while (i < numberOfArtists && (!added || !found)) {
		if ((*newArtist).getName() == (*artists[i]).getName()){
			found = true;

			//need to copy over all albums in newArtist
			for (int j = 0; j < (*newArtist).getNumberAlbums(); j++){
				added = (added || (*artists[i]).add((*newArtist).getAlbum(j)));
			}

			
		}
		i++;
	}
	if (!found){
		// add newArtist to artists array
		if (numberOfArtists < size || resize()){
			artists[numberOfArtists] = newArtist;
			numberOfArtists++;
			added = true;
		}
	}
	return added;
}

bool Library::search(string name){
	bool retval = false;
	for (int i = 0; i < numberOfArtists; i++){
		if(name == (*artists[i]).getName()){
			(*artists[i]).print();
			retval = true;
		}
		retval = (*artists[i]).search(name) || retval;
	}
	return retval;
}

bool Library::searchPart(string part){
	string name;
	int foundNumber = 1;
	bool match = false;
	for (int i = 0; i < numberOfArtists; i++){
		if((*artists[i]).getName().find(part) != string::npos) {
			cout << foundNumber++ << '\t' << (*artists[i]).getName() << endl;
			match = true;
		}
		match = (*artists[i]).searchPart(part, &foundNumber) || match;
	}
	return match;
}

void Library::print(){
	cout << "Library:" << endl << endl;
	for (int i = 0; i < numberOfArtists; i++){
		(*artists[i]).print();
	}
}

bool Library::loadLibrary(){
	ifstream inFile;

	// Open the file
	inFile.open("Library.txt");

	if(inFile.fail()){
		return false;
	}

	// Read in how many artists are in file
	inFile >> numberOfArtists;

	// Create the Artists array of the correct size
	size = numberOfArtists;
	artists = new Artist*[size];

	// Eat up the newline character
	inFile.get();

	// Read in all the Artists in the Library
	for (int i = 0; i < numberOfArtists; i++){
		artists[i] = new Artist(&inFile);
	}

	inFile.close();

	return true;
}

bool Library::saveLibrary(){
	ofstream outFile;

	// Open the file
	outFile.open("Library.txt");

	if(outFile.fail()){
		return false;
	}

	// Output to a file just like is expected when loading the library
	outFile << numberOfArtists << endl;

	// Output each artist's information
	for (int i = 0; i < numberOfArtists; i++){
		(*artists[i]).saveArtist(&outFile);
	}

	outFile.close();
	return true;
}

void Library::deleteLibrary(){
	for (int i = numberOfArtists - 1; i >= 0; i--){
		delete artists[i];
	}
	size = 0;
}

bool Library::resize(int newSize){
	if(newSize > numberOfArtists){
		Artist **newArtist = new Artist*[newSize];
		for(int i=0; i<numberOfArtists; i++){
			newArtist[i]=artists[i];
		}
		delete artists;
		artists = newArtist;
		size = newSize;
		return true;
	}
	return false;
}

bool Library::resize(){
	return resize(numberOfArtists+2);
}