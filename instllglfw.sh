#!/bin/bash

GSUDO="sudo"

echo "updating package lists..."
$GSUDO apt update

echo "instaling glfw3..."
$GSUDO apt install -y libglfw3 libglfw3-dev

echo "verifying installation..."
pkg-config --modversion glfw3

echo "finished"