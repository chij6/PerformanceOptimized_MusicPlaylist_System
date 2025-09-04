# Music Playback System - Songlist in C
## Program Operation Introduction
The following section provides detailed instructions on how to operate this project, with explanations provided later.

1. Download ```songlist.csv``` and ```song_demo.c```, and save them in the same folder.
2. Open cmd or any compiler that can compile C programming language.
3. Execute the project.

![image](https://github.com/chij6/Songlist-in-C/blob/main/demo.png)

The function page will appear as shown above, first listing all songs, then entering the function page!

## 1. System Overview and Introduction

This is a data structure final project for school, aimed at designing a simple song playback system. The default playlist is created through a CSV file, please refer to the attachment: *songlist.csv*.

* The following are system functions:
	* Song Information
	* Function
	* Search
	* Random Playback
    * Add Favorite
	* Search Favorite


## 2.Condition Description

1. Song information must include (Song Name, Artist, Song Length (unit: minutes: seconds), My Favorite)  EX: Dynamite BTS 3:44 Y
2. Song data must be read from a CSV file for subsequent modifications.
3. After ending the program, a new personal configuration file must be written.

## 3.Function Description
### ADD
* Input the song information to be added, and display the result after addition when re-querying the playlist. EX: Please select the function Add

    1. Enter the song information to be added (Artist, Song Name, Song Length):
    2. Butter BTS 2:10
    3. Successfully added

### Delete
* Delete specified song information, and show the result after deletion when re-querying the playlist. EX: Please select the function Delete
  
    1. Enter the song name or artist to delete (all songs by the artist will be deleted)
    2. Successfully deleted

### Modify
* Input the song information to be modified, and show the modified result when re-querying the playlist. EX: Please select function Modify

1. Enter the song name to modify:
2. XXXX
3. Modify content
4. Butter BTS 2:10
5. Successfully modified
    
### Search
* From the song list, perform various searches (using artist, song name, and time range as conditions), and display the sorted results.
Ex: Please select function: Search

    1. Please enter artist
    2. BTS 
    3. BTS's songs include
    
| **no** | **Song** | **Singer** | **Time** |
|-------|:-----:|------:|------:|
| 1   |   Butter   |  BTS | 4:10 |
| 2   |  Dynamite  |  BTS | 3:57 |
| 3   |     ON     |  BTS | 3:59 |
### Add Favorite
* After searching for specific songs, add them to My Favorites list. For example: Create List A, List B (there is a default ```0628.csv playlist```)

### Search Favorite
* Search My Favorites list: Query specific favorite lists (can read from csv)
EX: Please enter function: Search Favorite

    1. Please enter the list name
    2. Eric
    3. Eric's favorite list includes
    
| **no** | **Song** | **Singer** | **Time** |
|-------|:-----:|------:|------:|
| 1   |   Butter   |  BTS | 4:10 |
| 2   |  Dynamite  |  BTS | 3:57 |
| 3   |     ON     |  BTS | 3:59 |

### Random Playbacl
* From the song list or My Favorites list, display randomly played songs.
