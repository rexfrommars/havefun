
CXX=g++
CXX_FLAGS=-g -Wall -Werror -std=c++17

all: app profiler

app:
	$(CXX) app.cc -o app $(CXX_FLAGS) -pthread

profiler:
	$(CXX) profiler.cc -o profiler $(CXX_FLAGS)

