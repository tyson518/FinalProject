// FinalProj'ect.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include "Library.h"

using namespace std;

Artist* addMenu();

int _tmain(int argc, _TCHAR* argv[])
{
	/*
	Menu Commands:
	Add - Adds album to the Library
	Search - Finds all Artists, Albums, and Songs that match the specified value
	Delete - Removed specified Artist, Album, or Song
	Print - Print specifed Artist, Album, or Song
	PrintLib - Print the entire library to the screen
	Help - Print help menu
	LoadLib - Load Library from a file
	SaveLib - Save Library to a file
	Quit - Exit
	*/

	Library *lib = new Library();

	string command = "";
	while(command.compare("Quit") != 0){
		cout << "Enter Command: ";
		cin >> command;
		if (command.compare("Add") == 0){
			Artist *newArtist = addMenu();
			if ((*lib).add(newArtist)){
				cout << "Added";
			} else {
				cout << "Not Added";
			}
		} else if (command.compare("Search") == 0){
			string searchVal;
			cout << "Search Value: (use _ as space) ";
			cin >> searchVal;

			for(int i = 0; i < searchVal.length(); i++){
				if (searchVal[i] == '_')
					searchVal[i] = ' ';
			}

			if(!(*lib).search(searchVal)){
				cout << "Nothing Found";
			}
		} else if (command.compare("Delete") == 0){
			cout << "Delete Menu";
		} else if (command.compare("Print") == 0){
			cout << "Print Search results Menu";
		} else if (command.compare("PrintLib") == 0){
			(*lib).print();
		} else if (command.compare("Help") == 0){
			cout << "Add Menu";
		} else if (command.compare("LoadLib") == 0){
			(*lib).loadLibrary();
			cout << "Library loaded from the file.";
		} else if (command.compare("SaveLib") == 0){
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
        (*newArtist).addAlbum(new Album(album, numSongs, songs));

        cout << "Please enter next album name or N if done" << endl;
        cin >> album;
    }

	return newArtist;
}
