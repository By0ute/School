# TRPA - Signatures Recognition

## Coded with
* C++
* [**CMake**](http://www.cmake.org/)

## Configuration
* Tested on [**Ubuntu 12.04**](http://www.ubuntu.com/)
* Not tested on [**Debian**](https://www.debian.org/)

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
