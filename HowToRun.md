## Install apps
```bash
sudo apt install g++
sudo apt install gcc-10 g++-10
sudo apt install cmake
sudo apt install build-essential
```

## Build
```bash
cd <path>/miniSQL-master
rm -rf build
mkdir build
cd build
cmake ..
make
```

## Run binaries
```bash
cd <path>/miniSQL-master
./bin/MyminiSQL  database/input.sql database/output.csv
```
