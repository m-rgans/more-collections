
tests:tests.cpp ntree.hpp
	g++ $< -o $@ -std=c++17 -Wall -Wextra -lgtest

test: tests
	./$<