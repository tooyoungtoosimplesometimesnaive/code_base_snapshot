
clang++ -Wall -std=c++14 -I /usr/local/boost-1.66.0/include -L /usr/local/boost-1.66.0/lib test_snapshot.cpp snapshot.cpp -o test_snapshot -lboost_system -lboost_filesystem

