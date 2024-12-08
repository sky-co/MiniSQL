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

## Run
```bash
cd <path>/MiniSQL-master
# Run bin
./bin/MyMiniSQL  database/input.sql database/output.csv
# Run bin and output txt
./bin/MyMiniSQL  database/input.sql database/output.csv > ./record_log.txt
```

## Notice
- `build.sh` is used to build release version
- `build_debug.sh` is used to build debug version
