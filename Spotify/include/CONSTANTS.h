#ifndef CONSTANTS_H
#define CONSTANTS_H

#include <string>

// Maximum search history size for the Spotify application
const int MAX_SEARCH_HISTORY = 10;

// Shuffle order types
const int SHUFFLE_PRE_ORDER = 1;
const int SHUFFLE_POST_ORDER = 2;
const int SHUFFLE_IN_ORDER = 3;

// Playlist sort types
const int SORT_BY_PLAY_COUNT = 1;
const int SORT_BY_RECENTLY_PLAYED = 3;

// Add any default file paths if needed
const std::string PLAYLISTS_DB_NAME = "data/playlists.txt";
const std::string MUSIC_DB_NAME = "data/music.txt";

#endif
