#include "stdafx.h"
#include "Library.h"

Library::Library(){
	artists = new Artist*[20];
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
	artists = new Artist*[numberOfArtists];

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
}