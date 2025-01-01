#pragma once
#ifndef SPOTIFY_H
#define SPOTIFY_H

#include "CONSTANTS.h"
#include "Playlist.h"
#include "SongNode.h"
#include <queue>
#include <vector>

class Playlist; // Forward declaration of the Playlist class

class Spotify {
public:
  Spotify();  // Constructor
  ~Spotify(); // Destructor

  SongNode *getSong(int id); // Retrieve a song by its ID
  void addSongToLibrary(const int &id, const std::string &title,
                        const std::string &artist); // Add a song to the library
  void playSongFromPlaylist(const std::string &name,
                            const int &id);     // Play a song from a playlist
  void createPlaylist(const std::string &name); // Create a new playlist
  bool
  playlistExists(const std::string &name); // Checks if the the playlist exists
  void addSongToPlaylist(const std::string &name,
                         const int &id); // Add a song to a playlist
  void deleteSongFromPlaylist(const std::string &name,
                              const int &id); // Delete a song from a playlist
  void displaySongs();     // Display all songs in the library
  void displayPlaylists(); // Display all playlists
  void displayPlaylist(const std::string &name); // Display a playlist by name
  int getPlaylistTotalSongsCount(
      const std::string &name); // Get the total song count in a playlist
  void shufflePlaylist(const std::string &name,
                       const int &order); // Shuffle the playlist
  void
  searchSongByTitle(const std::string &title); // Search for a song by title
  void
  searchSongByArtist(const std::string &artist); // Search for songs by artist
  void displayLastPlayed(
      const std::string
          &playlistName); // Display the last played song in a playlist
  void sortPlaylist(const std::string &name, int sortType,
                    bool reverse);                 // Sort a playlist
  void trackSearchHistory(const std::string &key); // Track search history
  void displaySearchHistory();                     // Display the search history
  void savePlaylistsToFile(
      const std::string &filename) const; // Save playlists to a file
  void loadPlaylistsFromFile(
      const std::string &filename); // Load playlists from a file

private:
  std::vector<SongNode *> songs;     // Collection of songs in the library
  std::vector<Playlist *> playlists; // Collection of playlists in the system
  std::queue<std::string> searchHistory; // Queue to track search history
  const int maxSearchHistory =
      MAX_SEARCH_HISTORY; // Max number of entries in the search history queue
};

#endif
