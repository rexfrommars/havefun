
CXX=clang++
CXX_FLAGS=-g -O0 -Wall -Werror

all: clean move98 move11 move2

move98: move.cc
	$(CXX) -o move98 move.cc $(CXX_FLAGS) -std=c++98

move11: move.cc
	$(CXX) -o move11 move.cc $(CXX_FLAGS) -std=c++11

move2: move2.cc
	$(CXX) -o move2 move2.cc $(CXX_FLAGS) -std=c++17

values: values.cc
	$(CXX) -o values values.cc $(CXX_FLAGS) -std=c++11

values-w: values.cc
	$(CXX) -o values values.cc $(CXX_FLAGS) -std=c++11 -DWITH_W

clean:
	rm -rf *.dSYM move98 move11 move2 values

# "otool -L move98", this is the Mac alternative of Linux ldd

