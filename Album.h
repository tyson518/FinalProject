/*
* File: Album.h
* Author: Tyson Manning, Nick Smith, Jess Zielinski, Chris Porto, Audra Agajanian
* Member: FinalProject.sln
* 
* Due: 24 July 2014
*/

#include "stdafx.h"
#include <iostream>
#include "Song.h"

class Album {
	string title;
	Song **songs; //array of songs
	int numSongs; //number of songs
	int size;



	// Array Management Functions
	bool resize(int newSize); //change size to new size only works if newSize > number of songs
	bool resize(); //size = numSongs * 2
	
	unsigned long calculateLength();
	void printLength();

public:
	Album(string, int, Song**); //Constructor - title, numSong, array of songs
	Album(ifstream*); // Constructor for reading in from file

	string getTitle();
	void setTitle(string);
	Song* getSong(int index);
	int getNumberOfSongs();
	unsigned long getLength();
	bool editSong(Song*, int); //change song at index, return 0 if index less than numSongs
	bool insertSong(Song*, int); //insert song at index and slide all others down
	bool add(Song*);	//tag song onto the end
	bool search(string); // Search for a song, if found, return true and print
	int getIndex(string); //search for a song, return index if found, else, return -1
	bool searchPart(string part, int *foundNumber); // Prints songs which titles contains part
	bool removeSong(int); //remove song at index
	void saveAlbum(ofstream*);
	void print();
	void deleteAlbum();
};