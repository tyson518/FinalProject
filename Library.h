#include "stdafx.h"
#include <fstream>
#include "Artist.h"

class Library {
	int numberOfArtists;
	Artist **artists;
public:
	Library(); // Create library with default size of 20

	void playSong(string song);
	void playArtist(string artistName);
	void playAlbum(string albumName);
	void find(string name);//finds any songs, artists, or albums named name
	void print();
	void loadLibrary();//reads from a file
	void saveLibrary();//writes the contents of library to a file
	void deleteLibrary();
};