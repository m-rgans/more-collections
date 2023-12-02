#include <iostream>
#include <map>

#include <random>
#include <time.h>

#define UNIT_TESTS
#include "ntree.hpp"

const char* FORMAT_BEGIN = "\e[";
const char* FORMAT_END = "m";

#define SECTION_ANNOUNCE(SECT_NAME) std::cout << "Section: " << SECT_NAME << '\n'
#define TEST_ANNOUNCE(TEST_NAME) std::cout << "\tTest:" << TEST_NAME << "\n"

#define SUCCESS_ANNOUNCE std::cout << "\t\tSuccess!\n"
#define FAILURE_ANNOUNCE std::cout << "\t\tFailed.\n"

#define TEST_ASSERT(V) if (V) {SUCCESS_ANNOUNCE;} else {FAILURE_ANNOUNCE; return false;}

bool test_id_pool() {
    SECTION_ANNOUNCE("ID Pool");
    {
        TEST_ANNOUNCE("Basic get/set");
        IdPool<int> a;
        const int TEST_VALUE_1 = 65;
        auto token = a.add(TEST_VALUE_1);
        TEST_ASSERT(*a.get(token) == TEST_VALUE_1);
    }
    {
        IdPool<int> a;
        const int VALUE = 76;
        auto token = a.add(VALUE);
        TEST_ANNOUNCE("Erasing");
        TEST_ASSERT(a.remove(token));
        TEST_ANNOUNCE("Erased value is not present.");
        TEST_ASSERT(!a.get(token));
    }
    {
        TEST_ANNOUNCE("Stress test");
        IdPool<int> a;
        //generate values
        std::map<IdPool<int>::Token, int> validation_list;
        const int STRESS_SAMPLE_SIZE = 40000;
        for (int i = 0; i < STRESS_SAMPLE_SIZE; i++) {
            int v = rand();
            auto token = a.add(v);
            validation_list.insert({token,v});
        }
        // todo: delete and re add 15k at random
        for (const auto key : validation_list) {
            if (!(*a.get(key.first) == key.second)) {
                FAILURE_ANNOUNCE;
            }
        }
        SUCCESS_ANNOUNCE;
    }
    return true;
}

void tests() {
    test_id_pool();
}

int main(void) {
    srand(time(nullptr));
    tests();
    return 0;
}