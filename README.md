# Chess 2
A variant of the game Chess with a randomization aspect, made in C++17.

## Installation
To play the game, extract the Chess2-release zip-file and run the .exe file.

## Game Rules
The movement rules are the same as in the origianl Chess, but when a piece is clicked, it moves to a random legal square. The king must be captured to win the game, and the "check" mechanic does not exist in this game for this reason.

## Work In Progress
To make the game more balanced, the rules will be changed so that pieces with too many possible moves will have a higher chance to capture a piece.

## Build and Dependencies
The project is compiled and built with Meson using the gcc compiler. SDL2 is used for the graphical elementents of the game and is dynamically linked in the release. Some other C++ libraries like libstdc++.dll are dynamically linked too at the moment but may be statically linked in a later release. The current release only supports Windows and the release zip-folder only contains an .exe binary as a result.