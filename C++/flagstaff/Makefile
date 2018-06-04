

CXX=g++-7
CXX_FLAGS=-g -std=c++17 -Wall -Werror

TARGET=flagstaff

SRCS= \
	log.cc \
	flagstaff.cc \
	task.cc \
	main.cc \


all: clean $(TARGET)

$(TARGET): $(SRCS)
	$(CXX) -o $(TARGET) $(CXX_FLAGS) $(SRCS)

clean:
	rm -f $(TARGET)

