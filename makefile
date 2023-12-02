
tests:tests.cpp ntree.hpp
	g++ $< -o $@ -std=c++17

test: tests
	./$<