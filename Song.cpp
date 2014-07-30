#include "stdafx.h"
#include <iostream>
#include "Song.h"

Song::Song(string t){
	title = t;
	length = 0;
	playCount = 0;
}

Song::Song(string t, int lengthP){
	title = t;
	length = lengthP;
	playCount = 0;
}

Song::Song(string t, int lengthP, int playCountP){
	title = t;
	length = lengthP;
	playCount = playCountP;
}

Song::Song(ifstream *inFile){
	char str[100];

	// Read in song name
	(*inFile).getline(str,100,'\t');
	title = str;

	// Read in song length
	*inFile >> length;

	// Read in song play count
	*inFile >> playCount;

	// Eat up the newline character
	(*inFile).get();
}

void Song::saveSong(ofstream *outFile){
	*outFile << title << '\t' << length << '\t' << playCount << endl;
}

string Song::getTitle(){
	return title;
}

void Song::print(){
	cout << length << '\t' << playCount << '\t' << title << endl;
}

int Song::getLength(){
	return length;
}