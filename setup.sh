#!/bin/bash


#compile mainmake
gcc mm.c -o mm

#make the executable runable without need for "./"
chmod +rwx mm

#make link to standard execution path