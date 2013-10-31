#!/bin/bash


#compile mainmake
gcc src/mm.c -o $(pwd)/mm

#make the executable runable without need for "./"
chmod +rwx mm

#make link to standard execution path