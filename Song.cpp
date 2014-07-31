/*
* File: Song.cpp
* Author: Tyson Manning, Nick Smith, Jess Zielinski, Chris Porto, Audra Agajanian
* Member: FinalProject.sln
* 
* Due: 24 July 2014
*/

#include "stdafx.h"
#include <iostream>
#include "Song.h"

Song::Song(string t){
	title = t;
	length = 0;
	playCount = 0;
}

Song::Song(string t, unsigned long lengthP){
	title = t;
	length = lengthP;
	playCount = 0;
}

Song::Song(string t, unsigned long lengthP, int playCountP){
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
	printLength();
	cout << '\t' << playCount << '\t' << title << endl;
}

int Song::getLength(){
	return length;
}

void Song::incrementPlayCount(){
	playCount++;
}

int Song::getPlayCount(){
	return playCount;
}

void Song::printLength(){
	cout << length/60 << ":";  //convert to minutes and seconds. Unnecessary, but looks nice
	if(length%60 < 10)
		cout << "0" << length%60;   //cout "0:04" instead of "0:4"
	else
		cout << length%60;
}