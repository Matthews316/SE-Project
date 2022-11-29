//
// Created by cgm81 on 11/3/2022.
//
#define CATCH_CONFIG_MAIN
#include "./catch.hpp"
#include "AVLTree.h"

TEST_CASE("Check that AVLTree works", "[AVLTree]") {
    AVLTree<int> testTree;

    SECTION("contains and insert") {
        REQUIRE(testTree.contains(1) == false);
        testTree.insert(1);
        REQUIRE(testTree.contains(1) == true);
        REQUIRE(testTree.contains(2) == false);
        testTree.insert(2);
        REQUIRE(testTree.contains(2) == true);
    }

    SECTION("clear") {
        testTree.insert(1);
        testTree.insert(2);
        REQUIRE(testTree.isEmpty() == false);
        testTree.clear();
        REQUIRE(testTree.isEmpty() == true);
    }

    SECTION("isEmpty") {
        REQUIRE(testTree.isEmpty() == true);
        testTree.insert(1);
        REQUIRE(testTree.isEmpty() == false);
        testTree.clear();
        REQUIRE(testTree.isEmpty() == true);
    }

    SECTION("remove") {
        testTree.insert(1);
        testTree.insert(2);
        testTree.insert(3);
        REQUIRE(testTree.contains(1) == true);
        REQUIRE(testTree.contains(2) == true);
        REQUIRE(testTree.contains(3) == true);
        testTree.remove(1);
        REQUIRE(testTree.contains(1) == false);
        testTree.remove(2);
        REQUIRE(testTree.contains(2) == false);
        testTree.remove(3);
        REQUIRE(testTree.contains(3) == false);
    }

    SECTION("findMin") {
        testTree.insert(1);
        testTree.insert(3);
        testTree.insert(9);
        testTree.insert(2);
        testTree.insert(4);
        testTree.insert(8);
        testTree.insert(12);
        REQUIRE(testTree.findMinVal() == 1);
    }

    SECTION("findVal") {
        testTree.insert(1);
        testTree.insert(2);
        testTree.insert(3);
        testTree.insert(4);
        REQUIRE(testTree.findVal(1) == 1);
        REQUIRE(testTree.findVal(2) == 2);
        REQUIRE(testTree.findVal(3) == 3);
        REQUIRE(testTree.findVal(4) == 4);
    }

    SECTION("Copy Constructor") {
        testTree.insert(1);
        testTree.insert(2);
        testTree.insert(3);
        AVLTree<int> testTree2 = testTree;
        REQUIRE(testTree2.contains(1) == true);
        REQUIRE(testTree2.contains(2) == true);
        REQUIRE(testTree2.contains(3) == true);
        testTree.remove(1);
        REQUIRE(testTree.contains(1) == false);
        REQUIRE(testTree2.contains(1) == true);
    }

    SECTION("Copy Assignment Operator") {
        AVLTree<int> testTree2;
        testTree.insert(1);
        testTree.insert(2);
        testTree.insert(3);
        testTree2 = testTree;
        REQUIRE(testTree2.contains(1) == true);
        REQUIRE(testTree2.contains(2) == true);
        REQUIRE(testTree2.contains(3) == true);
        testTree.remove(1);
        REQUIRE(testTree.contains(1) == false);
        REQUIRE(testTree2.contains(1) == true);
    }
}

