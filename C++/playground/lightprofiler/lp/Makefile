
CXX=g++-7
CXX_FLAGS=-g -Wall -Werror -std=c++17

HEADERS = \
	lpcommon.hh \
	lpclient.hh \


all: profiler lib client

profiler: profiler.cc $(HEADERS)
	@echo "profiler"
	$(CXX) -o profiler profiler.cc $(CXX_FLAGS)

lib: lpclient.cc $(HEADERS)
	$(CXX) -c lpclient.cc -o lpclient.cc.o $(CXX_FLAGS)

client: lib client.cc $(HEADERS)
	$(CXX) -c client.cc -o client.cc.o $(CXX_FLAGS)
	$(CXX) -o client client.cc.o lpclient.cc.o -pthread

clean:
	rm -f *.o profiler client
