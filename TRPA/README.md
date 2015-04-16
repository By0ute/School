# TRPA - Signatures Recognition

## Coded with
* C++
* CMake

## Configuration
* Tested on Ubuntu 12.04
* Not tested on Debian

## How to Compile ?
```
cd TRPA/
mkdir build
cd build/
cmake ..
make
```

## Launch **TEST SUITE**
```
cd TRPA/
cd build/
./LEARNING ../samples/<train.txt>
./TEST ../samples/<test.txt>
cat score.txt
```
