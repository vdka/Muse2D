#!/bin/bash

set -e

SEARCHPATHS="-L/usr/local/lib -I/usr/local/include -I$(pwd)/include"
DEPENDENCIES="-framework OpenGL -lglfw3"

clang src/*.c $SEARCHPATHS $DEPENDENCIES -std=gnu99 -fgnu89-inline -o main

if [[ $1 == "run" ]]; then
    ./main
fi

