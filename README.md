# Code base snapshot

This repo is still undergoing.

Goal: run a command then get the 'snapshot' of a code base. (Including how many lines are comments, what is the percentage of different languages, etc.)

# Using Boost to have the filesystem API

Steps: (I'm on Mac OS)

1, Download Boost library. http://www.boost.org/users/download/

2, Unzip and cd to the root directory, do `./bootstrap.sh --prefix=/usr/local/boost-<your_boost_version>`

3, Do `sudo ./b2 cxxflags=-std=c++14 install`. This may take quit a while.

4, Do `export DYLD_LIBRARY_PATH=/usr/local/boost-1.60.0/lib:$DYLD_LIBRARY_PATH` or add that to your bash profile.

5, Compile your source file using:
```
clang++ -std=c++14 -I /usr/local/boost-<your_boost_version>/include -L /usr/local/boost-<your_boost_version>/lib test.cpp -o test -lboost_system -lboost_filesystem
```
because the only boost library I used is filesystem.

