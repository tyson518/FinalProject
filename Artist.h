#include "stdafx.h"
#include "Album.h"

class Artist {
	string name;
	int numberOfAlbums;
	Album **albums;
	int size;
	
	// Array Management Functions
	bool resize(int newSize); //change size to new size only works if newSize > number of songs
    bool resize(); //size = numSongs + 2
public:
	Artist(string name);
	Artist(string name, int numberOfAlbums);
	Artist(ifstream*);
	bool add(Album*);
	bool remove(int index);
	void print();
	void saveArtist(ofstream*);
	void deleteArtist();
	Album getAlbum(int index);
	string getName();//to get the name 
	bool search(string name);// to print out any albums and songs that match name. 
	bool searchPart(string part, int *foundNumber); // prints out any albums or songs that contain part
};