CXXFLAGS 	+= -std=c++17 -fconcepts -Wall -Wextra -Wpedantic -Iinclude

vpath %.hpp include/

default: test clean

test: test_binary
	./$<

test_binary: test_binary.cpp

test_binary.cpp: save.hpp load.hpp concepts.hpp

clean:
	rm -f a.out test_binary *.bin