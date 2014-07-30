#include "stdafx.h"
#include "Artist.h"

Artist::Artist(string n){
	name = n;
	numberOfAlbums = 0;
	albums = new Album*[numberOfAlbums];
}

Artist::Artist(string n, int nOA){
	name = n;
	numberOfAlbums = nOA;
	albums = new Album*[numberOfAlbums];
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
	albums = new Album*[numberOfAlbums];

	// Read in all albums by this artist
	for (int i = 0; i < numberOfAlbums; i++){
		albums[i] = new Album(inFile);
	}
}

bool Artist::addAlbum(Album *newAlbum){
	int count = 0;
	while(albums[count] != NULL && count < numberOfAlbums){
		count ++;
	}
	if (count < numberOfAlbums){
		albums[count] = newAlbum;
		return true;
	}
	return false;
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
}