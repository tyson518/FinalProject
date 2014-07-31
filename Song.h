/*
* File: Song.h
* Author: Tyson Manning, Nick Smith, Jess Zielinski, Chris Porto, Audra Agajanian
* Member: FinalProject.sln
* 
* Due: 24 July 2014
*/

#include "stdafx.h"
#include <string>
#include <iostream>
#include <fstream>

using namespace std;

class Song {
	string title;
	unsigned long length; //in seconds
	int playCount;
	void printLength();
public:
	Song(string t); // Create song with given name, and a default length and play count of 0
	Song(string t, unsigned long l); // Create song with given name and length and a default play count of 0
	Song(string t, unsigned long l, int p); // Create song with given name, length and play count
	Song(ifstream*);
	void saveSong(ofstream*);
	string getTitle();
	void print();
	int getLength();
	void incrementPlayCount();
	int getPlayCount();
};