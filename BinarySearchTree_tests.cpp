#include "BinarySearchTree.hpp"
#include "unit_test_framework.hpp"


TEST(test_empty) {
    BinarySearchTree<int> tree;
    ASSERT_TRUE(tree.empty());
    tree.insert(5);
    ASSERT_FALSE(tree.empty());
}
/*
size
height
copy nodes
destroy nodes
find
insert
min
max
check sorting
traverse in order
traverse preorder
min greater than
*/

TEST_MAIN()
