
CXX=clang++
CXX_FLAGS=-g -O0 -Wall -Werror

all: clean move98 move11

move98:
	$(CXX) -o move98 move.cc $(CXX_FLAGS) -std=c++98

move11:
	$(CXX) -o move11 move.cc $(CXX_FLAGS) -std=c++11

clean:
	rm -rf move98 move11

# "otool -L move98", this is the Mac alternative of Linux ldd

