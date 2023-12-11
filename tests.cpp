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
    ASSERT_EQ(*pool.get(token), test_value);
}

using more_collections::Glossary;

int main(void) {
    testing::InitGoogleTest();
    return RUN_ALL_TESTS();
}