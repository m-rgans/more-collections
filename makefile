
SUBHEADERS=id_pool.hpp glossary.hpp
_SUBHEADERS=$(patsubst %, subheaders/%, $(SUBHEADERS))

tests:tests.cpp more-collections.hpp $(_SUBHEADERS)
	g++ $< -o $@ -std=c++17 -Wall -Wextra -lgtest -g

test: tests
	./$<