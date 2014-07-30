#include "stdafx.h"
#include "Library.h"

Library::Library(){
	size = 20; // Default size of 20 Artists
	artists = new Artist*[size]; // Create empty array of default size
}

bool Library::search(string name){
	bool retval = false;
	for (int i = 0; i < numberOfArtists; i++){
		if( name.compare((*artists[i]).getName()) == 0){
			(*artists[i]).print();
			retval = true;
		}
		retval = (*artists[i]).search(name) || retval;
	}
	return retval;
}

bool Library::add(Artist *newArtist){
	bool added = false, found = false;
	int i=0; 
	while (i < numberOfArtists && (!added || !found)) {
		if ((*newArtist).getName().compare((*artists[i]).getName()) == 0){
			//need to copy over all albums in newArtist
			found = true;
			//for (int j = 0; j < (*newArtist).getn
			//added = (*artists[i]).add((*newArtist).getAlbums());
		}
		i++;
	}
	if (!found){
		// add newArtist to artists array
		if (numberOfArtists < size || resize()){
			artists[numberOfArtists]= newArtist;
			numberOfArtists++;
			added = true;
		}
	}
	return added;
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

void Library::print(){
	cout << "Library:" << endl << endl;
	for (int i = 0; i < numberOfArtists; i++){
		(*artists[i]).print();
	}
}

void Library::loadLibrary(){
	ifstream inFile;

	// Open the file
	inFile.open("TempLibrary.txt");

	if(inFile.fail()){
		cout << "Failed to open File";
		return;
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
}

void Library::saveLibrary(){
	ofstream outFile;

	// Open the file
	outFile.open("TempLibrary.txt");

	if(outFile.fail()){
		cout << "Failed to open File";
		return;
	}

	// Output to a file just like is expected when loading the library
	outFile << numberOfArtists << endl;

	// Output each artist's information
	for (int i = 0; i < numberOfArtists; i++){
		(*artists[i]).saveArtist(&outFile);
	}

	outFile.close();
}

void Library::deleteLibrary(){
	for (int i = numberOfArtists - 1; i >= 0; i--){
		delete artists[i];
	}
	size = 0;
}