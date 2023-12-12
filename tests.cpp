/*

    todo:
    > change over test format
    > change to using m-collections namespace
    > finish collections

*/


#include <gtest/gtest.h>

#include <iostream>
#include <map>

#include <random>
#include <time.h>

#define UNIT_TESTS 1

#include "more-collections.hpp"
using more_collections::IdPool;

TEST(IdPool, add_and_retrieve) {
    IdPool<int> pool;
    int test_value = 32;
    auto token = pool.add(test_value);
    ASSERT_EQ(pool.get(token), test_value);
}

TEST(IdPool, add_remove_retrieve) {
    IdPool<int> pool;
    int test_value = 32;
    auto token = pool.add(test_value);
    ASSERT_TRUE(pool.remove(token));
    ASSERT_THROW(pool.get(token), std::out_of_range);
}

TEST(IdPool, add_remove_many) {
    IdPool<int> pool;
    const unsigned int testv_length = 500;

    int test_values[testv_length];
    for (unsigned int i; i < testv_length;i++) {
        test_values[i] = rand();
    }

    IdPool<int>::Token tokens[testv_length] = { 0 };

    DEBUG_PRINT("Setting up testing pool");
    for (unsigned i = 0; i < testv_length; i++) {
        tokens[i] = pool.add(test_values[i]);
        ASSERT_TRUE(pool.is_valid_token(tokens[i]));
        ASSERT_EQ(pool.get(tokens[i]), test_values[i]);
    }

    const int VALUE_REMOVED = -1; // rand doesnt return negative values
    DEBUG_PRINT("Removing ~1/2 from test pool\n");
    for (unsigned i = 0; i < testv_length; i++) {
        if (rand() % 2) {
            pool.remove(tokens[i]);
            test_values[i] = VALUE_REMOVED;
        }
    }

    DEBUG_PRINT("Re checking test pool.\n");
    for (unsigned i = 0; i < testv_length; i++) {
        if (test_values[i] == VALUE_REMOVED) {
            ASSERT_THROW(pool.get(tokens[i]), std::out_of_range);
        }
        else {
            ASSERT_EQ(pool.get(tokens[i]), test_values[i]);
        }
    }

}

using more_collections::Glossary;
TEST(glossary, add_and_retrieve) {
    Glossary<std::string, int> glossary;
    auto token = glossary.insert("one", 1);
    ASSERT_EQ(glossary.get(token), 1);
    ASSERT_EQ(glossary.get("one"), 1);
}

using more_collections::Glossary;

int main(void) {
    // use a constant seed so that tests are consistent
    const int RAND_SEED = 240;

    srand(RAND_SEED);

    testing::InitGoogleTest();
    return RUN_ALL_TESTS();
}