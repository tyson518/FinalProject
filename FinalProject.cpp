// FinalProj'ect.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include "Library.h"

using namespace std;

Artist* addMenu();
string searchMenu();
void helpMenu();

int _tmain(int argc, _TCHAR* argv[])
{
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
				cout << "Added";
			} else {
				cout << "Not Added";
			}
		} else if (command =="SearchPart") {
			string searchVal = searchMenu();
			if(!(*lib).searchPart(searchVal)){
				cout << "Nothing Found";
			}
		} else if (command == "Search"){
			string searchVal = searchMenu();
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
			(*lib).loadLibrary();
			cout << "Library loaded from the file.";
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
	cout << "LoadLib - Load Library from a file"  << endl;
	cout << "SaveLib - Save Library to a file"  << endl;
	cout << "Quit - Exit"  << endl;
}

string searchMenu(){
	string searchVal;
	cout << "Search Value: (use _ as space) ";
	cin >> searchVal;

	for(int i = 0; i < searchVal.length(); i++){
		if (searchVal[i] == '_')
			searchVal[i] = ' ';
	}

	return searchVal;
}

Artist* addMenu(){
	Artist *newArtist;
	string artist, album;
	cout << "Please enter an artist: " << endl;
    cin >> artist;
	newArtist = new Artist(artist);
    cout << "Please enter first album name" << endl;
    cin >> album;
    while (album.compare("N") != 0) {
        cout << "How many songs on this album?" << endl;
        int numSongs;
        cin >> numSongs;
        Song **songs;
		songs = new Song*[numSongs]; //songs name

        for (int i = 0; i < numSongs; i++) {
            cout << "enter song length: " << i << endl;
            int length;
            cin >> length;
            cout << "enter song name: " << i << endl;
            string name;
            cin >> name;
            songs[i] = new Song(name, length);
        }
        (*newArtist).add(new Album(album, numSongs, songs));

        cout << "Please enter next album name or N if done" << endl;
        cin >> album;
    }

	return newArtist;
}
