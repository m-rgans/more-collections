
tests:tests.cpp more-collections.hpp subheaders/id_pool.hpp
	g++ $< -o $@ -std=c++17 -Wall -Wextra -lgtest -g

test: tests
	./$<