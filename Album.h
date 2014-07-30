#include "stdafx.h"
#include <iostream>
#include "Song.h"

class Album {
	string title;
	Song **songs; //array of songs
	int numSongs; //number of songs

	unsigned long calculateLength();

public:
	Album(string, int, Song**); //constructor, numSong, array of songs
	Album(ifstream*); // Constructor for reading in from file

	string getTitle();
	void setTitle(string);
	Song getSong(int index);
	void setSong(Song, int); //set song at index
	bool removeSong(int); //remove song at index
	int getNumberOfSongs();
	unsigned long getLength();
	void printLength();
	void setSong(Song*, int);
	void saveAlbum(ofstream*);
	void print();
	void deleteAlbum();

	//void printAll();
	//void kill();
};