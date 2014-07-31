/*
* File: Library.h
* Author: Tyson Manning, Nick Smith, Jess Zielinski, Chris Porto, Audra Agajanian
* Member: FinalProject.sln
* 
* Due: 24 July 2014
*/

#include "stdafx.h"
#include <fstream>
#include "Artist.h"

class Library {
	int numberOfArtists;
	Artist **artists;
	int size;

	// Array Management Functions
	bool resize(int newSize); // change size to new size only works if newSize > number of songs
    bool resize(); // size = numSongs + 2
public:
	Library(); // Create library with default size of 20
	bool add(Artist *newArtist);// adds new artist, albums and songs to library.
	bool search(string name);// finds any songs, artists, or albums named name
	bool searchPart(string part); // finds any songs, artists, or album with part in their title or name
	void print();
	bool loadLibrary();// reads from a file
	bool saveLibrary();// writes the contents of library to a file
	void deleteLibrary();
};