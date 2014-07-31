/*
* File: FinalProject.cpp
* Author: Tyson Manning, Nick Smith, Jess Zielinski, Chris Porto, Audra Agajanian
* Member: FinalProject.sln
* 
* Due: 24 July 2014
*/

#include "stdafx.h"
#include <iostream>
#include "Library.h"

using namespace std;

Artist* addMenu();
string searchMenu();
void helpMenu();
void normalize(string*);	//change all underscores to spaces
string getResponse();

int _tmain(int argc, _TCHAR* argv[])
{
	cout << "Use underscore for space in all entries" << endl;
	/*
	Menu Commands:
	Add - Adds album to the Library
	Search - Finds all Artists, Albums, and Songs that match the specified value
	SearchPart - Finds all Artists, Albums and Songs that have the specified value in them
	PrintLib - Print the entire library to the screen
	Help - Print help menu
	LoadLib - Load Library from a file
	SaveLib - Save Library to a file
	Quit - Exit

	Use underscore instead of space for all entries

	// Not implemented
	Delete - Removed specified Artist, Album, or Song
	Print - Print specifed Artist, Album, or Song
	*/

	Library *lib = new Library();

	string command = "";
	while(command != "Quit"){
		cout << "Enter Command: ";
		cin >> command;
		if (command == "Add") {
			Artist *newArtist = addMenu();
			if ((*lib).add(newArtist)){
				cout << "Added Successfully";
			} else {
				cout << "Not Added Successfully";
			}
		} else if (command =="SearchPart") {
			string searchVal = searchMenu();
			if(!(*lib).searchPart(searchVal)){
				cout << "Nothing Found";
			}
		} else if (command == "Search"){
			string searchVal = searchMenu();
			cout << endl;
			if(!(*lib).search(searchVal)){
				cout << "Nothing Found";
			}
		} else if (command == "Delete") {
			cout << "Delete Menu";
		} else if (command == "Print") {
			cout << "Print Search results Menu";
		} else if (command == "PrintLib") {
			(*lib).print();
		} else if (command == "Help") {
			helpMenu();
		} else if (command == "LoadLib") {
			if((*lib).loadLibrary()){
				cout << "Library loaded from the file.";
			} else {
				cout << "Error loading library";
			}
		} else if (command == "SaveLib") {
			(*lib).saveLibrary();
			cout << "Library saved to the file.";
		} else {
			cout << "Unrecognized Command.";
		}
		cout << endl;
	}

	(*lib).deleteLibrary();

	return 0;
}

void helpMenu(){
	cout << endl << "Menu Commands:" << endl << endl;
	cout << "Add - Adds album to the Library" << endl;
	cout << "Search - Finds all Artists, Albums, and Songs that match the specified value"  << endl;
	cout << "SearchPart - Finds all Artists, Albums and Songs that have the specified value in them"  << endl;
	cout << "PrintLib - Print the entire library to the screen"  << endl;
	cout << "Help - Print help menu"  << endl;
	cout << "LoadLib - Load Library from a file (removes any other Artists in File)"  << endl;
	cout << "SaveLib - Save Library to a file"  << endl;
	cout << "Quit - Exit"  << endl << endl;
	cout << "Use underscore instead of space for all entries" << endl;
}

string getResponse(){
	string response;
	cin >> response;
	normalize(&response);
	return response;
}

string searchMenu(){
	string searchVal;
	cout << "Search Value: (use _ as space) ";
	searchVal = getResponse();
	return searchVal;
}


void normalize(string *input){
	for(int i = 0; i < (*input).length(); i++){
		if ((*input)[i] == '_')
			(*input)[i] = ' ';
	}
}

Artist* addMenu(){
	Artist *newArtist;
	string artist, album;
	cout << "Please enter an artist:" << endl;
    artist = getResponse();
	newArtist = new Artist(artist);
    cout << "Please enter album name" << endl;
    album = getResponse();
    cout << "How many songs do you want to add?" << endl;
    int numSongs;
    cin >> numSongs;
    Song **songs = new Song*[numSongs]; //songs name

    for (int i = 0; i < numSongs; i++) {
        cout << "enter song length: " << i+1 << endl;
        int length;
        cin >> length;
        cout << "enter song name: " << i+1 << endl;
        string name = getResponse();
        songs[i] = new Song(name, length);
    }

    (*newArtist).add(new Album(album, numSongs, songs));

	
    //while (album.compare("N") != 0) {
        //cout << "Please enter next album name or N if done" << endl;	//typing "N" breaks the library
        //cin >> album;
   // }

	return newArtist;
}
