#pragma once
#ifndef SONG_H
#define SONG_H

#include <string>

class SongNode {
public:
  int id;             // Unique ID for the song
  std::string title;  // Title of the song
  std::string artist; // Artist of the song
  int playCount;      // Number of times the song has been played
  SongNode *
      next; // Pointer to the next song in the playlist (for doubly linked list)
  SongNode *prev; // Pointer to the previous song in the playlist (for doubly
                  // linked list)

  // Constructor to initialize a song with its ID, title, and artist
  SongNode(const int &id, const std::string &title, const std::string &artist);
};

#endif
