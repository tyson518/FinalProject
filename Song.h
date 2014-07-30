#include "stdafx.h"
#include <string>
#include <iostream>
#include <fstream>

using namespace std;

class Song {
	string title;
	unsigned long length; //in seconds
	int playCount;
public:
	Song(string name); // Create song with given name, and a default length and play count of 0
	Song(string name, int length); // Create song with given name and length and a default play count of 0
	Song(string name, int length, int playCount); // Create song with given name, length and play count
	Song(ifstream*);
	string getTitle(Song songA);
	int getLength(Song songA);
	int getPlayCount(Song songA);
	void incrementPlayCount(Song songA);
	void saveSong(ofstream*);
	void print();
	int getLength();
};