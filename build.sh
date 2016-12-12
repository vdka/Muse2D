#!/bin/bash

set -e

SEARCHPATHS="-L/usr/local/lib -I/usr/local/include -I$(pwd)/src/lib"
DEPENDENCIES="-framework OpenGL -lglfw3"

clang src/*.c src/lib/*.c $SEARCHPATHS $DEPENDENCIES -std=gnu99 -fgnu89-inline -o main

if [[ $1 == "run" ]]; then
    ./main
fi
