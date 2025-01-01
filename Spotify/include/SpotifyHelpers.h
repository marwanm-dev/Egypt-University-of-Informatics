#ifndef SPOTIFY_HELPERS_H
#define SPOTIFY_HELPERS_H

#include "Spotify.h"

// Function declarations
void displayMenu();
int getValidChoice(int min, int max);
void createPlaylist(Spotify &app);
void addSongToPlaylist(Spotify &app);
void deleteSongFromPlaylist(Spotify &app);
void showPlaylist(Spotify &app);
void showPlaylists(Spotify &app);
void showSearchHistory(Spotify &app);
void displayTotalSongs(Spotify &app);
void playSong(Spotify &app);
void shufflePlaylist(Spotify &app);
void searchSong(Spotify &app);
void displayLastPlayed(Spotify &app);
void sortPlaylist(Spotify &app);
void load(Spotify &app);
void save(Spotify &app);

#endif
