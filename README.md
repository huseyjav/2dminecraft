# Introduction
This is a minimalistic 2d minecraft clone made in c++ without the use of any game libraries. Only library used was SDL as the multimedia library and rest of the logic, game loop etc was made from scratch.  
The project makes use of OOP features, making it easy to implement different components such as new world generation, new mobs, new weapons etc.
[Game Preview](https://www.youtube.com/watch?v=CiOQaXGbNrY)
# How to save and load words
Launch the executable with save file name as input, if the save file already exists in the executable directory game is gonna be leader from that file.

# Dependencies

SDL2
```
sudo apt install libsdl2-dev
```
SDL2-Image
```
sudo apt install libsdl2-image-dev
```

# Building
`make` will compile the game(compiling has only been tested on debian based linux distributions). 

`make doxygen` will generate doxygen documentation of the project.
