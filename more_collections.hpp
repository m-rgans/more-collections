#pragma once
#include <vector>
#include <optional>
#include <map>

#ifdef UNIT_TESTS
#define DEBUG_PRINT(MESG) std::cerr << "[          ] [INFO] " << MESG << '\n'
#else

#endif

#include "subheaders/glossary.hpp"
#include "subheaders/id_pool.hpp"
    
// todo: option to just add to std instead
// of having our own namespace