#include "stdafx.h"
#include "Album.h"

class Artist {
	string name;
	int numberOfAlbums;
	Album **albums;
public:
	Artist(string name);
	Artist(string name, int numberOfAlbums);
	Artist(ifstream*);
	bool addAlbum(Album*);
	void print();
	void saveArtist(ofstream*);
	void deleteArtist();
};