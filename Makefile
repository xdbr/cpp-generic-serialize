CXXFLAGS += -std=c++17 -fconcepts -Wall -Wextra -Wpedantic -Weffc++ -Wc++14-compat -Iinclude

vpath %.hpp include/

default: test clean

test: CXXFLAGS += -Wsuggest-final-types -Wsuggest-final-methods -Wsuggest-override -Wsuggest-attribute=pure -Wsuggest-attribute=const -Wsuggest-attribute=noreturn -Wunused-macros -Wno-endif-labels -Wundef -Wconversion -Wdangling-else	
test: test_binary
	./$<

test_binary: test_binary.cpp

test_binary.cpp: save.hpp load.hpp concepts.hpp

clean:
	rm -f a.out test_binary *.bin