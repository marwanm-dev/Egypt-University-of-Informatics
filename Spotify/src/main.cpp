#include "../include/CONSTANTS.h"
#include "../include/Spotify.h"
#include "../include/SpotifyHelpers.h"
#include <fstream>
#include <iostream>
#include <limits>

int main() {
  Spotify app;
  std::ifstream file(MUSIC_DB_NAME);

  if (!file.is_open()) {
    std::cerr << "Error opening " << MUSIC_DB_NAME << std::endl;
    return 1;
  }

  int id;
  std::string song, artist;
  while (file >> id) {
    file.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::getline(file, song);
    std::getline(file, artist);

    if (!song.empty() && !artist.empty())
      app.addSongToLibrary(id, song, artist);
  }
  file.close();

  int choice;
  do {
    displayMenu();
    choice = getValidChoice(1, 15);

    switch (choice) {
    case 1:
      createPlaylist(app);
      break;
    case 2:
      addSongToPlaylist(app);
      break;
    case 3:
      deleteSongFromPlaylist(app);
      break;
    case 4:
      showPlaylist(app);
      break;
    case 5:
      showPlaylists(app);
      break;
    case 6:
      displayTotalSongs(app);
      break;
    case 7:
      playSong(app);
      break;
    case 8:
      shufflePlaylist(app);
      break;
    case 9:
      searchSong(app);
      break;
    case 10:
      showSearchHistory(app);
      break;
    case 11:
      displayLastPlayed(app);
      break;
    case 12:
      sortPlaylist(app);
      break;
    case 13:
      load(app);
      break;
    case 14:
      save(app);
      break;
    case 15:
      std::cout << "Exiting Spotify. Goodbye!\n";
      break;
    }
  } while (choice != 15);

  return 0;
}
