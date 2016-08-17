CXXFLAGS = -std=c++11 -pedantic -Wall -Wextra -Werror
CC = ${CXX}

test: test.o

test.o: test.cpp range.hpp
