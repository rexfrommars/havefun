

CXX=g++-7
CXX_FLAGS=-g -Wall -Werror

TARGET=flagstaff

SRCS= \
	main.cc \
	flagstaff.cc \
	task.cc \


all: $(TARGET)

$(TARGET): $(SRCS)
	$(CXX) -o flagstaff --std=c++14 -Wall -Werror -g --debug -O0 \
		main.cc \
		flagstaff.cc \
		task.cc
		
clean:
	rm -f $(TARGET)

