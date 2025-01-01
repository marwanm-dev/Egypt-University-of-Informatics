# Spotify-inspired Music Player Application

This project implements a Spotify-inspired music player application, providing features like creating and managing playlists, shuffling songs, sorting playlists, and tracking search history. The application uses various data structures and adheres to modular design principles.

## Features

- **Playlists Management**

  - Create and delete playlists.
  - Add and remove songs from playlists.
  - Display playlists and their contents.

- **Song Library**

  - Add songs to the library with details like title and artist.
  - Search songs by title or artist.

- **Sorting and Shuffling**

  - Sort playlists by play count or recently played songs.
  - Shuffle playlists in different orders: in-order, pre-order, post-order.

- **Playback**

  - Play songs from playlists.
  - Track and display the most recently played songs.

- **Search History**

  - Track and display the history of song searches.

- **File Management**
  - Save and load playlists to/from files.

## Code Structure

### Core Classes

1. **`BST`**

   - Manages song IDs using a Binary Search Tree.
   - Supports operations like insertion, deletion, and traversal (in-order, pre-order, post-order).

2. **`BSTNode`**

   - Represents a node in the binary search tree, holding a song ID and pointers to child nodes.

3. **`Playlist`**

   - Represents a playlist of songs.
   - Supports song addition, deletion, playback, sorting, and shuffling.

4. **`SongNode`**

   - Represents a song with attributes like ID, title, artist, and play count.
   - Used in doubly linked lists for managing playlist songs.

5. **`Spotify`**

   - Main application class.
   - Manages the song library, playlists, and user interactions.

6. **Constants**
   - Defines key constants like shuffle order types, sort types, and file paths.

### Helper Functions (`Spotify_Helpers`)

- Provides utilities like menu display, user input validation, and high-level operations for interacting with the application.

## Things to Add

- **Actual Database of MP3 Files**  
  Integrate a real database of MP3 files to play the songs, enabling full-fledged music playback functionality.

- **Playback Controls**  
  Implement the ability to pause songs and replay them, enhancing the playback experience.

- **Enhanced User Interface**  
  Provide a graphical or command-line interface to simplify user interactions with the application.

- **Music Recommendations**  
  Add a feature to recommend songs or playlists based on user preferences and play history.
