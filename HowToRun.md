## Install apps
```bash
sudo apt install g++
sudo apt install gcc-10 g++-10
sudo apt install cmake
sudo apt install build-essential
```

## Build
```bash
cd <path>/MiniSQL-master
rm -rf build
mkdir build
cd build
cmake ..
make
```

## Run binaries
```bash
cd <path>/MiniSQL-master
./bin/MyMiniSQL  database/input.sql database/output.csv
```
