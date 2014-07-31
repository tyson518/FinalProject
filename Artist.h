/*
* File: Artist.h
* Author: Tyson Manning, Nick Smith, Jess Zielinski, Chris Porto, Audra Agajanian
* Member: FinalProject.sln
* 
* Due: 24 July 2014
*/

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
	int getNumberAlbums();
	string getName();//to get the name 
	Album* getAlbum(int index);
	bool add(Album*);
	bool remove(int index);
	bool search(string name);// to print out any albums and songs that match name. 
	bool searchPart(string part, int *foundNumber); // prints out any albums or songs that contain part
	void print();
	void saveArtist(ofstream*);
	void deleteArtist();
};