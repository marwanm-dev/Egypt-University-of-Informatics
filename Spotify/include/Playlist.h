#pragma once
#ifndef PLAYLIST_H
#define PLAYLIST_H

#include "BST.h"
#include "SongNode.h"
#include "Spotify.h"
#include <stack>
#include <string>
#include <vector>

class Spotify; // Forward declaration to avoid circular dependency

class Playlist {
public:
  Playlist(const std::string &n,
           Spotify *app); // Constructor, initializes playlist with name and app
                          // reference
  ~Playlist();            // Destructor, cleans up memory used by the playlist

  std::string getName() const;         // Get the name of the playlist
  int getLastPlayedID() const;         // Get ID of the last played song
  void setLastPlayedID(const int &id); // Set the ID of the last played song
  std::vector<SongNode *>
  getSongs() const;               // Retrieve all songs in the playlist
  void addSong(int id);           // Add a song by ID
  void deleteSong(const int &id); // Remove a song by ID
  void display() const;           // Display all songs in the playlist
  int totalSongs() const;         // Get total number of songs in the playlist
  void playSong(const int &id);   // Play a specific song by ID
  void displayLastPlayed() const; // Display the most recently played song

  // Sorting and shuffling
  void sortByPlayCount(
      bool reverse = false);   // Sort songs by play count, can reverse order
  void sortByRecentlyPlayed(); // Sort songs based on recent play order
  void shuffleInOrder();       // Shuffle playlist in in-order sequence
  void shufflePreOrder();      // Shuffle playlist in pre-order sequence
  void shufflePostOrder();     // Shuffle playlist in post-order sequence

private:
  std::string name; // Playlist name
  SongNode *head;   // Head of the doubly linked list of songs
  SongNode *tail;   // Tail of the doubly linked list of songs
  int lastPlayed;   // ID of the last played song
  BST songTree;     // Binary search tree to manage song IDs
  std::stack<SongNode *>
      recentlyPlayedStack; // Stack to track songs played recently
  Spotify *app;            // Pointer to the Spotify app for fetching songs

  void rebuildListFromVector(
      std::vector<SongNode *>
          &songs); // Helper method to rebuild the linked list from a vector
};

#endif
