# SDL-2D-Platformer-Engine
Learning C++ and SDL 


This project began as an attempt to create a 2D platformer game. However, during the initial exploration, I found that most existing game engines were either overly bloated, lacked native C++ support, or did not offer a true 2D environment—instead relying on workarounds to simulate 2D space.

As development progressed, the project naturally evolved into a game engine in its own right. While it originated as a game, it has since shifted focus toward providing a lightweight, C++-based 2D engine. Some basic assets and character demos are included to showcase the engine's current capabilities.

🛠️ Building the Project

You can compile the project using the following make commands:

make all — builds the project  
make clean all — cleans previous builds and then compiles the project

Ensure that your system has a proper C++ build environment and SDL2 installed  
    
g++, SDL/SDL2

⚠️ Windows Notes

Texture loading paths on Windows require manual adjustment.

Due to path differences across operating systems, texture loading paths need to be updated manually when compiling on Windows. These can be found in main.cpp, starting around line 70.

This is a temporary limitation and will be addressed in a future update for better cross-platform compatibility.
