#include "BinarySearchTree.hpp"
#include "unit_test_framework.hpp"
#include <iostream>
using namespace std;


TEST(test_empty) {
    BinarySearchTree<int> tree;
    ASSERT_TRUE(tree.empty());
    tree.insert(5);
    ASSERT_FALSE(tree.empty());
}

TEST(test_size){
    BinarySearchTree<int> tree;
    ASSERT_EQUAL(tree.size(),0);
    tree.insert(5);
    tree.insert(7);
    tree.insert(6);
    tree.insert(8);
    ASSERT_EQUAL(tree.size(),4);
}

TEST(test_height){
    BinarySearchTree<int> tree;
    ASSERT_EQUAL(tree.height(),0);
    tree.insert(5);
    tree.insert(6);
    tree.insert(7);
    tree.insert(8);
    ASSERT_EQUAL(tree.height(),4);

    BinarySearchTree<int> tree2;
    tree2.insert(5);
    tree2.insert(8);
    tree2.insert(6);
    tree2.insert(9);
    ASSERT_EQUAL(tree2.height(),3);
    tree2.insert(1);
    ASSERT_EQUAL(tree2.height(),3);
    tree2.insert(7);
    ASSERT_EQUAL(tree2.height(),4);
}

TEST(test_assignment){
    BinarySearchTree<int> tree;
    ASSERT_TRUE(tree.empty());
    BinarySearchTree<int> tree2 = tree;
    ASSERT_TRUE(tree2.empty());

    tree2.insert(5);
    tree2.insert(8);
    tree2.insert(6);
    tree2.insert(9);
    ASSERT_EQUAL(tree2.height(),3);
    BinarySearchTree<int> tree3(tree2);
    ASSERT_TRUE(tree2.find(5) != tree3.find(5));
    ASSERT_TRUE(tree2.find(3) == tree3.find(3));

    tree = tree3;
    ASSERT_TRUE(tree2.find(5) != tree.find(5));
    ASSERT_TRUE(tree2.find(3) == tree.find(3));
}

TEST(test_find){
    BinarySearchTree<int> tree;
    tree.insert(5);
    tree.insert(6);
    tree.insert(7);
    tree.insert(8);

    ASSERT_TRUE(tree.find(19) == tree.end());
    ASSERT_TRUE(tree.find(8) == tree.max_element());

    tree.insert(19);
    ASSERT_TRUE(tree.find(19) != tree.end());
    ASSERT_TRUE(tree.find(8) != tree.max_element());

    ASSERT_TRUE(tree.find(5) == tree.min_element());

    ASSERT_TRUE(tree.find(6) == tree.min_greater_than(5));

    BinarySearchTree<int> tree2;

    ASSERT_TRUE(tree2.find(0) == tree2.end());
    ASSERT_TRUE(tree.find(0) == tree2.end());
}

TEST(test_insert){
    BinarySearchTree<string> tree;

    tree.insert("really cool string");
    tree.insert("not so cool string");

    ASSERT_TRUE(*tree.find("really cool string") == "really cool string");
}

/*
min
max
check sorting
traverse in order
traverse preorder
min greater than
*/

TEST_MAIN()
