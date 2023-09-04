------------------------


HOW TO COMPILE AND RUN


------------------------


Compile: g++ -std=c++17 dungeon.cpp Items.cpp Map.cpp Player.cpp Sorcerer.cpp Party.cpp 


proj2


Run: ./a.out


------------------------


DEPENDENCIES


------------------------


Items.h, Map.h Sorcerer.h, Player.h, Party.h, monsters.txt, riddles.txt, and results.txt
must be in the same directory to compile.


------------------------


SUBMISSION INFORMATION


------------------------


CSCI1300 Fall 2022 Project 3


Author: Chris Delisle


Recitation: 104 - Christopher Ojukwu


Date: Dec 1, 2022


------------------------


ABOUT THIS PROJECT


------------------------


This project is a game, played on a 12 by 12 2d map. The entire game is 2d, and allows 
for a multitude of actions for players to choose. They are faced with monsters, riddles,
misfortunes, and more. This is the dungeon game option as presented by the course.
It combines loops, conditionals, arrays, reading and writing to a file, and more. 
The player wins by surviving with at least one companion, and killing the sorcerer
boss after clearing all of the rooms. The player can die by losing party members,
starving to death, or not escaping by the time the Sorcerer destroys the dungeon.