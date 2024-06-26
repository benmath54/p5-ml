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
    ASSERT_TRUE(tree.find(19) == tree.min_greater_than(19));
    ASSERT_TRUE(tree.find(8) == tree.max_element());

    tree.insert(19);
    ASSERT_TRUE(tree.find(19) != tree.end());
    ASSERT_TRUE(tree.find(8) != tree.max_element());

    ASSERT_TRUE(tree.find(5) == tree.min_element());

    BinarySearchTree<int>::Iterator it1 = tree.find(6);
    BinarySearchTree<int>::Iterator it2 = tree.min_greater_than(5);
    cout << *it1 << endl;

    ASSERT_TRUE(it2 == it1);

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

TEST(test_check_sorting){
    BinarySearchTree<int> tree;
    tree.insert(5);
    tree.insert(6);
    ASSERT_TRUE(tree.check_sorting_invariant()); 
    BinarySearchTree<int>::Iterator it1 = tree.find(6);
    *it1 = 5;
    ASSERT_FALSE(tree.check_sorting_invariant()); 

    *it1 = 1;
    ASSERT_FALSE(tree.check_sorting_invariant()); 
    *it1 = 8;
    tree.insert(0);
    it1 = tree.find(0);
    *it1 = 100;
    ASSERT_FALSE(tree.check_sorting_invariant()); 
    *it1 = 0;

    BinarySearchTree<int> tree2;
    it1 = tree2.insert(6);
    BinarySearchTree<int>::Iterator it2 = tree2.begin();
    ASSERT_TRUE(it1 == it2);
    *it1 = 100;
    ASSERT_TRUE(tree.check_sorting_invariant());
}

TEST(test_trav_in_order){
    BinarySearchTree<char> tree;
    tree.insert('f');
    tree.insert('b');
    tree.insert('g');
    tree.insert('a');
    tree.insert('d');
    tree.insert('c');
    tree.insert('e');
    tree.insert('i');
    tree.insert('h');

    cout << tree.to_string();
    ostringstream oss_inorder;
    tree.traverse_inorder(oss_inorder);
    ASSERT_TRUE(oss_inorder.str() == "a b c d e f g h i ");
}

TEST(test_trav_preorder){
    BinarySearchTree<char> tree;
    tree.insert('f');
    tree.insert('b');
    tree.insert('g');
    tree.insert('a');
    tree.insert('d');
    tree.insert('c');
    tree.insert('e');
    tree.insert('i');
    tree.insert('h');

    cout << tree.to_string();
    ostringstream oss_preorder;
    tree.traverse_preorder(oss_preorder);
    ASSERT_TRUE(oss_preorder.str() == "f b a d c e g i h ");
}

TEST(test_min_gt_map){
    BinarySearchTree<string> tree;
    tree.insert("hello");
    tree.insert("pi");
    tree.insert("world");
    BinarySearchTree<string>::Iterator it1 = tree.find("hello");
    ASSERT_EQUAL(*it1,"hello");
    it1++;
    ASSERT_EQUAL(*it1,"pi");
    it1++;
    ASSERT_EQUAL(*it1,"world");

    cout << tree << endl;
}

TEST(test_empty_bst){
    BinarySearchTree<int> tree;
    ostringstream oss_preorder;
    tree.traverse_preorder(oss_preorder);
    string pre = oss_preorder.str();
    ASSERT_TRUE(pre.empty());
    ostringstream oss_inorder;
    tree.traverse_inorder(oss_inorder);
    pre = oss_inorder.str();
    ASSERT_TRUE(pre.empty());

    ASSERT_TRUE(tree.check_sorting_invariant());
    ASSERT_TRUE(tree.max_element() == tree.end());
    ASSERT_TRUE(tree.min_element() == tree.end());
    ASSERT_TRUE(tree.min_greater_than(5) == tree.end());
    ASSERT_TRUE(tree.find(4) == tree.end());
    ASSERT_TRUE(tree.begin() == tree.end());
}

TEST(test_pp){
    BinarySearchTree<char> tree;
    tree.insert('f');
    tree.insert('b');
    tree.insert('g');
    tree.insert('a');
    tree.insert('d');
    tree.insert('c');
    tree.insert('e');
    tree.insert('i');
    tree.insert('h');
    BinarySearchTree<char>::Iterator it1 = tree.begin();
    for(char c = 'a'; c <= 'f'; c++){
        cout << *it1 << " ";
        ASSERT_TRUE(c == *it1);
        it1++;
    }
}

TEST(test_assignment_error16){
    BinarySearchTree<int> tree;
    BinarySearchTree<int> tree2(tree);

    BinarySearchTree<int>::Iterator it1 = tree2.begin();
    BinarySearchTree<int>::Iterator it2 = tree.begin();
    ASSERT_EQUAL(it1,it2);

    ASSERT_EQUAL(tree.begin(),tree2.begin());

    tree2.insert(5);
    tree2.insert(8);
    tree2.insert(6);
    tree2.insert(9);

    it1 = tree2.begin();
    ASSERT_EQUAL(*it1,5);

    tree.insert(5);
    it2 = tree.begin();

    ASSERT_NOT_EQUAL(it1,it2);
    ASSERT_EQUAL(*it1,*it2);

    BinarySearchTree<int> tree3(tree);

    it1 = tree3.begin();

    ASSERT_EQUAL(*it1,*it2);

    BinarySearchTree<int> tree4;

    ostringstream oss_preorder;
    tree4.traverse_preorder(oss_preorder);
    string pre = oss_preorder.str();    

    cout << pre << endl;
    ASSERT_TRUE(pre.empty());

    tree4.traverse_inorder(oss_preorder);
    string trav = oss_preorder.str();

    cout << pre << endl;
    ASSERT_TRUE(pre.empty());
}

TEST(haha_imlosing_it){
    BinarySearchTree<string> tree;
    tree.insert("I");
    tree.insert("Will");
    tree.insert("Be");
    tree.insert("There");
    tree.insert("Coding");
    tree.insert("Sucks");
    tree.insert("This");
    tree.insert("Doesnt");
    tree.insert("Look");
    tree.insert("Right");
    tree.insert("This Will be on my public Github");
    cout << tree.to_string() << endl;

    ASSERT_EQUAL(tree.size(),11);
    ASSERT_EQUAL(tree.height(),6);
    ostringstream oss_preorder;
    tree.traverse_preorder(oss_preorder);
    string pre = oss_preorder.str();
    string correct = "I Be Coding Doesnt Will There Sucks Look Right"
    " This This Will be on my public Github ";
    ASSERT_EQUAL(pre,correct);

    ostringstream oss_inorder;
    tree.traverse_inorder(oss_inorder);
    string ino = oss_inorder.str();
    string ino_correct = "Be Coding Doesnt I Look Right Sucks "
    "There This This Will be on my public Github Will ";
    ASSERT_EQUAL(ino,ino_correct);

    
}

TEST_MAIN()
