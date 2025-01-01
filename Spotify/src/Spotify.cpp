#include "../include/Spotify.h"
#include <fstream>
#include <iostream>

// Constructor for initializing Spotify instance
Spotify::Spotify() {}

// Destructor to clean up dynamically allocated songs and playlists
Spotify::~Spotify() {
  for (auto song : songs)
    delete song; // Delete song objects

  for (auto playlist : playlists)
    delete playlist; // Delete playlist objects
}

// Retrieve a song by its ID
SongNode *Spotify::getSong(int id) {
  for (auto song : songs)
    if (song->id == id)
      return song; // Return song if found

  return nullptr; // Return nullptr if song is not found
}

// Add a new song to the library
void Spotify::addSongToLibrary(const int &id, const std::string &title,
                               const std::string &artist) {
  songs.push_back(new SongNode(
      id, title, artist)); // Add new song object to the songs vector
}

// Play a song from a specific playlist
void Spotify::playSongFromPlaylist(const std::string &name, const int &id) {
  for (Playlist *playlist : playlists) {
    if (playlist->getName() == name) {
      playlist->playSong(id); // Call playSong on the matching playlist
      return;
    }
  }
  std::cout << "Invalid playlist name."
            << std::endl; // Handle invalid playlist name
}

// Create a new playlist
void Spotify::createPlaylist(const std::string &name) {
  if (playlistExists(name)) {
    std::cout << "Playlist already exists.\n";
    return;
  }
  Playlist *newPlaylist =
      new Playlist(name, this); // Create new playlist object
  playlists.push_back(
      newPlaylist); // Add the new playlist to the playlists vector
}

// Checks if the the playlist exists
bool Spotify::playlistExists(const std::string &name) {
  for (Playlist *playlist : playlists)
    if (playlist->getName() == name)
      return true;
  return false;
};

// Add a song to a playlist
void Spotify::addSongToPlaylist(const std::string &name, const int &id) {
  for (Playlist *playlist : playlists) {
    if (playlist->getName() == name) {
      playlist->addSong(id); // Add song to the playlist
      return;
    }
  }
  std::cout << "Playlist not found: " << name
            << std::endl; // Handle invalid playlist name
}

// Delete a song from a playlist
void Spotify::deleteSongFromPlaylist(const std::string &name, const int &id) {
  for (Playlist *playlist : playlists) {
    if (playlist->getName() == name) {
      playlist->deleteSong(id); // Delete song from the playlist
      return;
    }
  }
  std::cout << "Invalid playlist name."
            << std::endl; // Handle invalid playlist name
}

// Display all songs in the library
void Spotify::displaySongs() {
  for (const auto &song : songs)
    std::cout << song->id << " : " << song->title << " by " << song->artist
              << std::endl; // Print song details
}

// Display all playlists
void Spotify::displayPlaylists() {
  for (const auto &playlist : playlists)
    playlist->display(); // Display the playlist's details
}

// Display a specific playlist by name
void Spotify::displayPlaylist(const std::string &name) {
  for (Playlist *playlist : playlists) {
    if (playlist->getName() == name) {
      playlist->display(); // Display the playlist's details
      return;
    }
  }
  std::cout << "Invalid playlist name."
            << std::endl; // Handle invalid playlist name
}

// Get the total number of songs in a playlist
int Spotify::getPlaylistTotalSongsCount(const std::string &name) {
  for (Playlist *playlist : playlists)
    if (playlist->getName() == name)
      return playlist
          ->totalSongs(); // Return the number of songs in the playlist

  std::cout << "Invalid playlist name."
            << std::endl; // Handle invalid playlist name
  return -1;              // Return -1 if playlist is not found
}

// Shuffle a playlist based on a specific order
void Spotify::shufflePlaylist(const std::string &name, const int &order) {
  for (Playlist *playlist : playlists) {
    if (playlist->getName() == name) {
      switch (order) {
      case SHUFFLE_PRE_ORDER:
        playlist->shufflePreOrder(); // Shuffle playlist in pre-order
        break;
      case SHUFFLE_POST_ORDER:
        playlist->shufflePostOrder(); // Shuffle playlist in post-order
        break;
      case SHUFFLE_IN_ORDER:
        playlist->shuffleInOrder(); // Shuffle playlist in in-order
        break;
      default:
        std::cout << "Invalid shuffle order. Use 1, 2, or 3." << std::endl;
      }
      return;
    }
  }
  std::cout << "Invalid playlist name."
            << std::endl; // Handle invalid playlist name
}

// Sort a playlist by a specific criterion
void Spotify::sortPlaylist(const std::string &name, int sortType,
                           bool reverse) {
  for (Playlist *playlist : playlists) {
    if (playlist->getName() == name) {
      switch (sortType) {
      case SORT_BY_PLAY_COUNT:
      case (3 - SORT_BY_PLAY_COUNT):        // Nice Hack
        playlist->sortByPlayCount(reverse); // Sort by play count
        break;
      case SORT_BY_RECENTLY_PLAYED:
        playlist->sortByRecentlyPlayed(); // Sort by recently played
        break;
      default:
        std::cout << "Invalid sort type."
                  << std::endl; // Handle invalid sort type
      }
      return;
    }
  }
  std::cout << "Playlist not found: " << name
            << std::endl; // Handle invalid playlist name
}

// Search for a song by its title and track the search
void Spotify::searchSongByTitle(const std::string &title) {
  trackSearchHistory(title); // Track the search in history
  for (const auto &song : songs) {
    if (song->title == title) {
      std::cout << song->title << " is found.\n"; // Print found song details
      return;
    }
  }
  std::cout << "A song with the title: " << title
            << " is not found.\n"; // Handle no song found
}

// Search for songs by an artist and track the search
void Spotify::searchSongByArtist(const std::string &artist) {
  trackSearchHistory(artist); // Track the search in history
  std::cout << "Songs by " << artist << ":" << std::endl;
  for (const auto &song : songs)
    if (song->artist == artist)
      std::cout << song->title << std::endl; // Print song titles by the artist
}

// Display the last played song in a playlist
void Spotify::displayLastPlayed(const std::string &playlistName) {
  for (Playlist *playlist : playlists) {
    if (playlist->getName() == playlistName) {
      playlist->displayLastPlayed(); // Display last played song details
      return;
    }
  }
  std::cout << "Playlist not found: " << playlistName
            << std::endl; // Handle invalid playlist name
}

// Track search history for a given key (title or artist)
void Spotify::trackSearchHistory(const std::string &key) {
  if ((int)searchHistory.size() >= maxSearchHistory)
    searchHistory.pop(); // Remove the oldest search if history exceeds max size

  searchHistory.push(key); // Add new search to the history queue
}

// Display the search history
void Spotify::displaySearchHistory() {
  if (searchHistory.empty()) {
    std::cout << "No search history." << std::endl;
    return;
  }

  std::cout << "\n--- Search History (most recent first) ---\n";
  std::queue<std::string> temp =
      searchHistory; // Copy search history to a temporary queue
  std::vector<std::string> history;

  while (!temp.empty())
    history.push_back(temp.front()), // Store search history in a vector
        temp.pop();

  for (auto it = history.rbegin(); it != history.rend(); ++it)
    std::cout << *it << std::endl; // Print search history in reverse order
}

// Save playlists to a file
void Spotify::savePlaylistsToFile(const std::string &filename) const {
  std::ofstream file(filename);
  if (!file.is_open()) {
    std::cerr << "Error opening file for saving playlists: " << filename
              << std::endl;
    return;
  }

  // Save playlist count
  file << playlists.size() << "\n";

  for (const auto &playlist : playlists) {
    // Save playlist name
    file << playlist->getName() << "\n";

    // Save songs in playlist
    file << playlist->totalSongs() << "\n";
    for (const auto &song : playlist->getSongs()) {
      file << song->id << "\n";        // Save song ID
      file << song->title << "\n";     // Save song title
      file << song->artist << "\n";    // Save song artist
      file << song->playCount << "\n"; // Save song play count
    }

    // Save the ID of the last played song
    file << playlist->getLastPlayedID() << "\n"; // Save last played song ID
  }

  file.close(); // Close the file after writing
}

// Load playlists from a file
void Spotify::loadPlaylistsFromFile(const std::string &filename) {
  std::ifstream file(filename);
  if (!file.is_open()) {
    std::cerr << "Error opening file for loading playlists: " << filename
              << std::endl;
    return;
  }

  size_t playlistCount = 0;
  file >> playlistCount;
  file.ignore(); // Ignore the newline character

  // Clear existing playlists
  for (auto playlist : playlists)
    delete playlist;

  playlists.clear();

  for (size_t i = 0; i < playlistCount; ++i) {
    // Load playlist name
    std::string name;
    std::getline(file, name);

    createPlaylist(name); // Create the playlist

    size_t songCount = 0;
    file >> songCount;
    file.ignore(); // Ignore the newline character

    for (size_t j = 0; j < songCount; ++j) {
      // Load song details and add to the playlist
      int songID;
      file >> songID;
      file.ignore(); // Ignore the newline character

      std::string songTitle;
      std::getline(file, songTitle);

      std::string artist;
      std::getline(file, artist);

      int playCount;
      file >> playCount;
      file.ignore(); // Ignore the newline character

      // Find the song by ID and set its play count
      auto song = getSong(songID);
      if (song != nullptr)
        song->playCount = playCount; // Set the play count of the song

      addSongToPlaylist(name, songID); // Add the song to the playlist
    }

    // Load and set the last played song ID
    int lastPlayedSongID;
    file >> lastPlayedSongID;
    file.ignore(); // Ignore the newline character

    for (auto p : playlists) {
      if (p->getName() == name) {
        p->setLastPlayedID(lastPlayedSongID);
        break;
      }
    }
  }

  file.close(); // Close the file after reading
}
