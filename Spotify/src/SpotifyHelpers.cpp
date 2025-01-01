#include "../include/SpotifyHelpers.h"
#include "../include/CONSTANTS.h"
#include <iostream>
#include <limits>

void displayMenu() {
  std::cout << "\nSpotify Menu:\n"
            << "1. Create Playlist\n"
            << "2. Add Song to Playlist\n"
            << "3. Delete Song from Playlist\n"
            << "4. Display Playlist\n"
            << "5. Display All Playlists\n"
            << "6. Display Total Songs in a Playlist\n"
            << "7. Play a song\n"
            << "8. Shuffle Playlist\n"
            << "9. Search a Song\n"
            << "10. Display Search History\n"
            << "11. Display Last Played Song\n"
            << "12. Sort Playlist\n"
            << "13. Load Playlists\n"
            << "14. Save and Continue\n"
            << "15. Exit\n";
}

int getValidChoice(int min, int max) {
  int choice;
  while (true) {
    std::cout << "Enter your choice: ";
    std::cin >> choice;
    if (std::cin.fail() || choice < min || choice > max) {
      std::cin.clear();
      std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
      std::cout << "Invalid choice. Please enter a number between " << min
                << " and " << max << ".\n";
    } else
      break;
  }
  return choice;
}

void createPlaylist(Spotify &app) {
  std::string name;
  std::cout << "Enter playlist name: ";
  std::cin.ignore();
  std::getline(std::cin, name);

  app.createPlaylist(name);
  std::cout << "Playlist '" << name << "' created successfully!\n";

  char addSongsChoice;
  std::cout << "Add songs to the playlist (type 'a') or "
               "any other key to skip: ";
  std::cin >> addSongsChoice;

  std::cout << "Available Songs:\n";
  app.displaySongs();

  if (addSongsChoice == 'a' || addSongsChoice == 'A') {
    int songId;
    while (true) {
      std::cout << "Enter song ID to add (or '0' to finish): ";
      std::cin >> songId;

      if (songId == 0) {
        std::cout << "Finished adding songs to '" << name
                  << "' with a total of "
                  << app.getPlaylistTotalSongsCount(name) << " songs.\n";
        break;
      }
      app.addSongToPlaylist(name, songId);
    }
  }
}

void addSongToPlaylist(Spotify &app) {
  std::string playlistName;
  int songId;
  std::cout << "Enter playlist name: ";
  std::cin.ignore();
  std::getline(std::cin, playlistName);
  if (!app.playlistExists(playlistName)) {
    std::cout << "Playlist does not exist.\n";
    return;
  }

  std::cout << "\nAvailable songs:\n";
  app.displaySongs();

  while (true) {
    std::cout << "Enter song ID to add (or '0' to finish): ";
    std::cin >> songId;

    if (songId == 0) {
      std::cout << "Finished adding songs to '" << playlistName
                << " with a total of "
                << app.getPlaylistTotalSongsCount(playlistName) << " songs.\n";
      break;
    }

    app.addSongToPlaylist(playlistName, songId);
  }
}

void searchSong(Spotify &app) {
  std::string option, key;
  std::cout << "Search all songs by title (press 't') or by artist "
               "(press 'a')\n";
  std::cin >> option;

  if (option == "t" || option == "T") {
    std::cout << "Enter song title to search for: ";
    std::cin.ignore();
    std::getline(std::cin, key);
    app.searchSongByTitle(key);
  } else if (option == "a" || option == "A") {
    std::cout << "Enter song artist to search by: ";
    std::cin.ignore();
    std::getline(std::cin, key);
    app.searchSongByArtist(key);
  } else
    std::cout << "Invalid option.\n";
}

void load(Spotify &app) { app.loadPlaylistsFromFile(PLAYLISTS_DB_NAME); }

void save(Spotify &app) {
  std::cout << "Saved sucessfully!\n";
  app.savePlaylistsToFile(PLAYLISTS_DB_NAME);
}

void showPlaylist(Spotify &app) {
  std::string name;
  std::cout << "Enter playlist name: ";
  std::cin.ignore();
  std::getline(std::cin, name);
  app.displayPlaylist(name);
}

void showPlaylists(Spotify &app) { app.displayPlaylists(); }

void showSearchHistory(Spotify &app) { app.displaySearchHistory(); }

void displayTotalSongs(Spotify &app) {
  std::string playlistName;
  std::cout << "Enter playlist name: ";
  std::cin.ignore();
  std::getline(std::cin, playlistName);
  std::cout << "Total songs in the playlist: "
            << app.getPlaylistTotalSongsCount(playlistName) << "\n";
}

void playSong(Spotify &app) {
  std::string playlistName;
  std::cout << "Enter playlist name: ";
  std::cin.ignore();
  std::getline(std::cin, playlistName);
  app.displayPlaylist(playlistName);
  int songID;
  while (true) {
    std::cout << "Enter the song ID to play (or '0' to finish): ";
    std::cin >> songID;
    if (songID == 0) {
      std::cout << "Finished playing songs from " << playlistName << std::endl;
      break;
    }
    app.playSongFromPlaylist(playlistName, songID);
  }
  app.displayPlaylist(playlistName);
}

void shufflePlaylist(Spotify &app) {
  std::string playlistName;
  int type;
  std::cout << "Enter playlist name: ";
  std::cin.ignore();
  std::getline(std::cin, playlistName);
  std::cout << "Shuffle options:\n1. Pre-order\n2. Post-order\n3. In-order\n";
  std::cout << "Enter shuffle type: ";
  std::cin >> type;
  app.shufflePlaylist(playlistName, type);
  std::cout << "Playlist shuffled!\n";
}

void displayLastPlayed(Spotify &app) {
  std::string name;
  std::cout << "Enter playlist name: ";
  std::cin.ignore();
  std::getline(std::cin, name);
  app.displayLastPlayed(name);
}

void sortPlaylist(Spotify &app) {
  std::string playlistName;
  int sortType;
  bool reverse = false;
  std::cout << "Enter playlist name: ";
  std::cin.ignore();
  std::getline(std::cin, playlistName);
  std::cout << "Sort options:\n1. Most played to least played\n2. Least "
               "played to most played\n";
  std::cout << "3. Recently played songs\nEnter sort type: ";
  std::cin >> sortType;
  if (sortType == 2)
    reverse = true;
  app.sortPlaylist(playlistName, sortType, reverse);
  std::cout << "Playlist sorted!\nNew order:\n";
  app.displayPlaylist(playlistName);
}

void deleteSongFromPlaylist(Spotify &app) {
  std::string playlistName;
  int songId;
  std::cout << "Enter playlist name: ";
  std::cin.ignore();
  std::getline(std::cin, playlistName);
  if (!app.playlistExists(playlistName)) {
    std::cout << "Playlist does not exist.\n";
    return;
  }

  std::cout << "Songs in playlist:\n";
  app.displayPlaylist(playlistName);

  std::cout << "Enter song ID to delete: ";
  std::cin >> songId;

  app.deleteSongFromPlaylist(playlistName, songId);
}
