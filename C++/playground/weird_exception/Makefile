
CXX=g++
CXX_FLAGS=-g -Wall -Werror -std=c++17

lib.o: lib.hh lib.cc
	$(CXX) -c -o lib.o lib.cc $(CXX_FLAGS)

main.o: lib.hh main.cc
	$(CXX) -c -o main.o main.cc $(CXX_FLAGS)

main: main.o lib.o
	$(CXX) -o main main.o lib.o $(CXX_FLAGS)

