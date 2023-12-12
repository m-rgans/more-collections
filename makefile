
SUBHEADER_DIRECTORY = subheaders

SUBHEADERS=$(ls $(SUBHEADER_DIRECTORY))
_SUBHEADERS=$(patsubst %, $(SUBHEADERS)/%, $(SUBHEADERS))

tests:tests.cpp more-collections.hpp $(_SUBHEADERS)
	g++ $< -o $@ -std=c++17 -Wall -Wextra -lgtest -g

test: tests
	./$<