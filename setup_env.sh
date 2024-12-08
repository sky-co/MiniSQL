#!/usr/bin/env bash

set -eu

echo "Setup required apps for MiniSQL ..."

sudo apt install g++ -y
sudo apt install gcc-10 g++-10 -y
sudo apt install cmake -y
sudo apt install build-essential -y
