#include "stdafx.h"
#include "Artist.h"

Artist::Artist(string n){
	name = n;
	numberOfAlbums = 0;
	albums = new Album*[5]; // Create an albums array of default size
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

string Artist::getName(){
	return name;
}

bool Artist::search(string name){
	return false;
}

bool Artist::add(Album *newAlbum){
	bool retval = false, added = false;
	for (int i=0; i < numberOfAlbums; i++){
		if ((*newAlbum).getTitle().compare((*albums[i]).getTitle()) == 0){
			//need to copy over all Songs in newAlbum. 
			
		}
	}
	if (!added){
		// add newAlbum to albums array
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