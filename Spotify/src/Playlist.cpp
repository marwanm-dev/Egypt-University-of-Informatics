#include "../include/Playlist.h"
#include "../include/Spotify.h"
#include <algorithm>
#include <iostream>

Playlist::Playlist(const std::string &n, Spotify *app)
    : name(n), head(nullptr), tail(nullptr), lastPlayed(0), app(app) {}

Playlist::~Playlist() {
  // Clean up the playlist by deleting all songs
  while (head) {
    SongNode *temp = head;
    head = head->next;
    delete temp;
  }
}

std::string Playlist::getName() const { return name; }

int Playlist::getLastPlayedID() const { return lastPlayed; }

void Playlist::setLastPlayedID(const int &id) { lastPlayed = id; }

std::vector<SongNode *> Playlist::getSongs() const {
  std::vector<SongNode *> songs;
  SongNode *current = head;
  while (current) {
    songs.push_back(current); // Add each song to the vector
    current = current->next;
  }
  return songs;
}

void Playlist::addSong(int id) {
  SongNode *songFromLibrary = app->getSong(id);
  if (!songFromLibrary) {
    std::cout << "Song with ID " << id << " does not exist in the library.\n";
    return;
  }

  // Check if the song is already in the playlist
  SongNode *current = head;
  while (current) {
    if (current->id == id) {
      std::cout << "Song already exists in the playlist.\n";
      return;
    }
    current = current->next;
  }

  // Add the song to the playlist
  SongNode *newSong = new SongNode(*songFromLibrary);
  newSong->next = nullptr;
  newSong->prev = tail;

  if (!head) {
    head = tail = newSong; // First song in the playlist
  } else {
    tail->next = newSong;
    tail = newSong; // Add to the end of the playlist
  }

  songTree.insert(newSong->id); // Insert into the song tree for ID management
  std::cout << newSong->title << " by " << newSong->artist << "is added to '"
            << name << "'\n";
}

void Playlist::deleteSong(const int &id) {
  // Search for the song and delete it
  SongNode *current = head;
  while (current) {
    if (current->id == id) {
      // Update pointers of adjacent songs
      if (current->prev)
        current->prev->next = current->next;
      if (current->next)
        current->next->prev = current->prev;
      if (current == head)
        head = current->next;
      if (current == tail)
        tail = current->prev;

      songTree.remove(id); // Remove from song tree
      delete current;
      std::cout << "Song deleted successfully: " << id << std::endl;
      return;
    }
    current = current->next;
  }
  std::cout << "Song with id: " << id << " does not exist.\n";
}

void Playlist::display() const {
  // Display all songs in the playlist
  std::cout << "Songs in the playlist '" << name << "':\n";
  SongNode *current = head;
  while (current) {
    std::cout << current->id << " : " << current->title << " by "
              << current->artist << " (Played " << current->playCount
              << " times)" << std::endl;
    current = current->next;
  }
}

int Playlist::totalSongs() const {
  int count = 0;
  SongNode *current = head;
  while (current) {
    count++; // Count each song in the playlist
    current = current->next;
  }
  return count;
}

void Playlist::playSong(const int &id) {
  SongNode *current = head;
  while (current) {
    if (current->id == id) {
      lastPlayed = current->id;          // Update last played song
      recentlyPlayedStack.push(current); // Push to stack for recent plays
      current->playCount++;              // Increment play count
      std::cout << "Currently playing: " << current->id << " : "
                << current->title << " by " << current->artist << std::endl;
      return;
    }
    current = current->next;
  }
  std::cout << "Song not found in the playlist.\n";
}

void Playlist::displayLastPlayed() const {
  // Display the last played song's details
  if (lastPlayed) {
    SongNode *song = app->getSong(lastPlayed);
    std::cout << "Last played: " << song->title << " by " << song->artist
              << std::endl;
  } else {
    std::cout << "No song has been played yet.\n";
  }
}

void Playlist::sortByPlayCount(bool reverse) {
  if (!head) {
    std::cout << "The playlist is empty.\n";
    return;
  }

  // Collect all songs into a vector and sort by play count
  std::vector<SongNode *> songs;
  SongNode *current = head;
  while (current) {
    songs.push_back(current);
    current = current->next;
  }

  std::sort(songs.begin(), songs.end(), [reverse](SongNode *a, SongNode *b) {
    return reverse ? a->playCount < b->playCount : a->playCount > b->playCount;
  });

  rebuildListFromVector(songs); // Rebuild the playlist from sorted vector
  std::cout << "Playlist sorted successfully by play count.\n";
}

void Playlist::sortByRecentlyPlayed() {
  if (recentlyPlayedStack.empty()) {
    std::cout << "No songs have been played recently.\n";
    return;
  }

  // Sort songs based on recently played order
  std::vector<SongNode *> sortedSongs;
  std::stack<SongNode *> tempStack = recentlyPlayedStack;

  while (!tempStack.empty()) {
    sortedSongs.push_back(tempStack.top());
    tempStack.pop();
  }

  SongNode *current = head;
  while (current) {
    if (std::find(sortedSongs.begin(), sortedSongs.end(), current) ==
        sortedSongs.end()) {
      sortedSongs.push_back(current); // Add remaining songs
    }
    current = current->next;
  }

  rebuildListFromVector(sortedSongs); // Rebuild the playlist from sorted vector
  std::cout << "Playlist sorted successfully by recently played.\n";
}

void Playlist::shuffleInOrder() {
  std::queue<int> ids;
  songTree.getInOrder(ids); // Get song IDs in in-order traversal
  while (!ids.empty()) {
    playSong(ids.front()); // Play each song in order
    ids.pop();
  }
}

void Playlist::shufflePreOrder() {
  std::queue<int> ids;
  songTree.getPreOrder(ids); // Get song IDs in pre-order traversal
  while (!ids.empty()) {
    playSong(ids.front()); // Play each song in order
    ids.pop();
  }
}

void Playlist::shufflePostOrder() {
  std::queue<int> ids;
  songTree.getPostOrder(ids); // Get song IDs in post-order traversal
  while (!ids.empty()) {
    playSong(ids.front()); // Play each song in order
    ids.pop();
  }
}

void Playlist::rebuildListFromVector(std::vector<SongNode *> &songs) {
  if (songs.empty()) {
    head = nullptr;
    tail = nullptr;
    return;
  }

  // Rebuild the doubly linked list from sorted vector
  head = songs[0];
  tail = songs.back();

  head->prev = nullptr;
  tail->next = nullptr;

  for (size_t i = 0; i < songs.size(); ++i) {
    if (i > 0)
      songs[i]->prev = songs[i - 1]; // Set previous pointer
    if (i < songs.size() - 1)
      songs[i]->next = songs[i + 1]; // Set next pointer
  }
}
