#include "../include/SongNode.h"

// Constructor to initialize a song with its ID, title, artist, and initial play
// count
SongNode::SongNode(const int &id, const std::string &title,
                   const std::string &artist)
    : id(id), title(title), artist(artist), playCount(0), next(nullptr),
      prev(nullptr) {}
