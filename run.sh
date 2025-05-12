#!/bin/bash

# Compile the project
make

# If make was successful, run the program
if [ $? -eq 0 ]; then
    ./sdl_app
else
    echo "Build failed. Exiting."
fi
