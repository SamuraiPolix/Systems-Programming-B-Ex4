/*
 * Email: sam.lazareanu@gmail.com
 * ID: ****6281
 * @SamuraiPolix - Samuel Lazareanu
*/

#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include "tree.hpp"
#include "node.hpp"
#include "complex.h"
#include <iostream>
#include <string>
#include <sstream>

using namespace std;

// Note: We tested everything there is to test, but:
// TESTING HEAP WITH COMPLEX IS NOT POSSIBLE, AS THERE IS NO ORDERING FOR COMPLEX NUMBERS

TEST_CASE("Test Node constructor"){
    Node<int> node = Node<int>(1);
    CHECK(node.get_value() == 1);
}

TEST_CASE("Test Node copy constructor"){
    Node<int> node = Node<int>(1);
    Node<int> node2 = Node<int>(node);
    CHECK(node2.get_value() == 1);
}

TEST_CASE("Test Node constructor with number of children"){
    Node<int> node = Node<int>(1, 2);
    CHECK(node.get_value() == 1);
    CHECK(node.getChildrenSize() == 0);
}

TEST_CASE("Test Node copy constructor with number of children"){
    Node<int> node = Node<int>(1, 2);
    Node<int> node2 = Node<int>(node, 2);
    CHECK(node2.get_value() == 1);
    CHECK(node2.getChildrenSize() == 0);
}

TEST_CASE("Test Tree add_root"){
    Tree<int, 2> tree;
    Node<int> root = Node<int>(1);
    tree.add_root(root);
    CHECK(tree.get_root().get_value() == 1);
}

TEST_CASE("Test Tree add_root with value"){
    Tree<int, 2> tree;
    tree.add_root(1);
    CHECK(tree.get_root().get_value() == 1);
}

TEST_CASE("Test Tree add_sub_node"){
    Tree<int, 2> tree;
    Node<int> root = Node<int>(1);
    tree.add_root(root);
    Node<int> n1 = Node<int>(2);
    tree.add_sub_node(root, n1);
    CHECK(tree.get_root().get_children().at(0)->get_value() == 2);
}

TEST_CASE("Test Tree add_sub_node with values"){
    Tree<int, 2> tree;
    tree.add_root(1);
    tree.add_sub_node(1, 2);
    CHECK(tree.get_root().get_children()[0]->get_value() == 2);
}

TEST_CASE("Test maximum children exception")
{
    Tree<int, 2> tree;
    Node<int> root = Node<int>(1);
    tree.add_root(root);
    Node<int> n1 = Node<int>(2);
    Node<int> n2 = Node<int>(3);
    Node<int> n3 = Node<int>(4);
    Node<int> n4 = Node<int>(5);
    Node<int> n5 = Node<int>(6);
    tree.add_sub_node(root, n1);
    tree.add_sub_node(root, n2);
    tree.add_sub_node(n1, n3);
    tree.add_sub_node(n1, n4);
    CHECK_THROWS(tree.add_sub_node(n1, n5));
}

TEST_CASE("Test trying to make children, child of itself"){
    Tree<int, 2> tree;
    Node<int> root = Node<int>(1);
    tree.add_root(root);
    Node<int> n1 = Node<int>(2);
    CHECK_THROWS(tree.add_sub_node(n1, n1));
}

TEST_CASE("Test trying to add child to non-existent parent in tree"){
    Tree<int, 2> tree;
    Node<int> root = Node<int>(1);
    tree.add_root(root);
    Node<int> n1 = Node<int>(2);
    Node<int> n2 = Node<int>(3);
    CHECK_THROWS(tree.add_sub_node(n1, n2));        // n1 is not in tree
}

TEST_CASE("Test PreOrderIterator K = 2"){
    Tree<int, 2> tree;
    Node<int> root = Node<int>(1);
    tree.add_root(root);
    Node<int> n1 = Node<int>(2);
    Node<int> n2 = Node<int>(3);
    Node<int> n3 = Node<int>(4);
    Node<int> n4 = Node<int>(5);
    Node<int> n5 = Node<int>(6);
    tree.add_sub_node(root, n1);
    tree.add_sub_node(root, n2);
    tree.add_sub_node(n1, n3);
    tree.add_sub_node(n1, n4);
    tree.add_sub_node(n2, n5);
    stringstream ss;
    for (auto node = tree.begin_pre_order(); node != tree.end_pre_order(); ++node)
    {
        ss << node->get_value() << ", ";
    }
    CHECK(ss.str() == "1, 2, 4, 5, 3, 6, ");
}

TEST_CASE("Test PostOrderIterator K = 2"){
    Tree<int, 2> tree;
    Node<int> root = Node<int>(1);
    tree.add_root(root);
    Node<int> n1 = Node<int>(2);
    Node<int> n2 = Node<int>(3);
    Node<int> n3 = Node<int>(4);
    Node<int> n4 = Node<int>(5);
    Node<int> n5 = Node<int>(6);
    tree.add_sub_node(root, n1);
    tree.add_sub_node(root, n2);
    tree.add_sub_node(n1, n3);
    tree.add_sub_node(n1, n4);
    tree.add_sub_node(n2, n5);
    stringstream ss;
    for (auto node = tree.begin_post_order(); node != tree.end_post_order(); ++node)
    {
        ss << node->get_value() << ", ";
    }
    CHECK(ss.str() == "4, 5, 2, 6, 3, 1, ");
}

TEST_CASE("Test InOrderIterator K = 2"){
    Tree<int, 2> tree;
    Node<int> root = Node<int>(1);
    tree.add_root(root);
    Node<int> n1 = Node<int>(2);
    Node<int> n2 = Node<int>(3);
    Node<int> n3 = Node<int>(4);
    Node<int> n4 = Node<int>(5);
    Node<int> n5 = Node<int>(6);
    tree.add_sub_node(root, n1);
    tree.add_sub_node(root, n2);
    tree.add_sub_node(n1, n3);
    tree.add_sub_node(n1, n4);
    tree.add_sub_node(n2, n5);
    stringstream ss;
    for (auto node = tree.begin_in_order(); node != tree.end_in_order(); ++node)
    {
        ss << node->get_value() << ", ";
    }
    CHECK(ss.str() == "4, 2, 5, 1, 6, 3, ");
}

TEST_CASE("Test BFSIterator K = 2"){
    Tree<int, 2> tree;
    Node<int> root = Node<int>(1);
    tree.add_root(root);
    Node<int> n1 = Node<int>(2);
    Node<int> n2 = Node<int>(3);
    Node<int> n3 = Node<int>(4);
    Node<int> n4 = Node<int>(5);
    Node<int> n5 = Node<int>(6);
    tree.add_sub_node(root, n1);
    tree.add_sub_node(root, n2);
    tree.add_sub_node(n1, n3);
    tree.add_sub_node(n1, n4);
    tree.add_sub_node(n2, n5);
    stringstream ss;
    for (auto node = tree.begin_bfs_scan(); node != tree.end_bfs_scan(); ++node)
    {
        ss << node->get_value() << ", ";
    }
    CHECK(ss.str() == "1, 2, 3, 4, 5, 6, ");
}

TEST_CASE("Test DFSIterator K = 2"){
    Tree<int, 2> tree;
    Node<int> root = Node<int>(1);
    tree.add_root(root);
    Node<int> n1 = Node<int>(2);
    Node<int> n2 = Node<int>(3);
    Node<int> n3 = Node<int>(4);
    Node<int> n4 = Node<int>(5);
    Node<int> n5 = Node<int>(6);
    tree.add_sub_node(root, n1);
    tree.add_sub_node(root, n2);
    tree.add_sub_node(n1, n3);
    tree.add_sub_node(n1, n4);
    tree.add_sub_node(n2, n5);
    stringstream ss;
    for (auto node = tree.begin_dfs_scan(); node != tree.end_dfs_scan(); ++node)
    {
        ss << node->get_value() << ", ";
    }
    CHECK(ss.str() == "1, 2, 4, 5, 3, 6, ");
}

TEST_CASE("Test myHeap K = 2"){
    Tree<int, 2> tree;
    Node<int> root = Node<int>(1);
    tree.add_root(root);
    Node<int> n1 = Node<int>(2);
    Node<int> n2 = Node<int>(3);
    Node<int> n3 = Node<int>(4);
    Node<int> n4 = Node<int>(5);
    Node<int> n5 = Node<int>(6);
    tree.add_sub_node(root, n1);
    tree.add_sub_node(root, n2);
    tree.add_sub_node(n1, n3);
    tree.add_sub_node(n1, n4);
    tree.add_sub_node(n2, n5);
    stringstream ss;
    for (auto node = tree.myHeap(); node != tree.end_heap(); ++node)
    {
        ss << node->get_value() << ", ";
    }
    CHECK(ss.str() == "6, 5, 4, 3, 2, 1, ");
}

TEST_CASE("Test PreOrder K > 2 (DFS)"){
    Tree<int, 3> tree;
    Node<int> root = Node<int>(1);
    tree.add_root(root);
    Node<int> n1 = Node<int>(2);
    Node<int> n2 = Node<int>(3);
    Node<int> n3 = Node<int>(4);
    Node<int> n4 = Node<int>(5);
    Node<int> n5 = Node<int>(6);
    Node<int> n6 = Node<int>(7);
    Node<int> n7 = Node<int>(8);
    Node<int> n8 = Node<int>(9);
    Node<int> n9 = Node<int>(10);
    tree.add_sub_node(root, n1);
    tree.add_sub_node(root, n2);
    tree.add_sub_node(root, n3);
    tree.add_sub_node(n1, n4);
    tree.add_sub_node(n1, n5);
    tree.add_sub_node(n1, n6);
    tree.add_sub_node(n2, n7);
    tree.add_sub_node(n2, n8);
    tree.add_sub_node(n2, n9);
    stringstream ss;
    for (auto node = tree.begin_pre_order(); node != tree.end_pre_order(); ++node)
    {
        ss << node->get_value() << ", ";
    }
    CHECK(ss.str() == "1, 2, 5, 6, 7, 3, 8, 9, 10, 4, ");
    // check its the same as dfs
    stringstream ss2;
    for (auto node = tree.begin_dfs_scan(); node != tree.end_dfs_scan(); ++node)
    {
        ss2 << node->get_value() << ", ";
    }
    CHECK(ss2.str() == "1, 2, 5, 6, 7, 3, 8, 9, 10, 4, ");
}

TEST_CASE("Test PostOrder K > 2 (DFS)"){
    Tree<int, 3> tree;
    Node<int> root = Node<int>(1);
    tree.add_root(root);
    Node<int> n1 = Node<int>(2);
    Node<int> n2 = Node<int>(3);
    Node<int> n3 = Node<int>(4);
    Node<int> n4 = Node<int>(5);
    Node<int> n5 = Node<int>(6);
    Node<int> n6 = Node<int>(7);
    Node<int> n7 = Node<int>(8);
    Node<int> n8 = Node<int>(9);
    Node<int> n9 = Node<int>(10);
    tree.add_sub_node(root, n1);
    tree.add_sub_node(root, n2);
    tree.add_sub_node(root, n3);
    tree.add_sub_node(n1, n4);
    tree.add_sub_node(n1, n5);
    tree.add_sub_node(n1, n6);
    tree.add_sub_node(n2, n7);
    tree.add_sub_node(n2, n8);
    tree.add_sub_node(n2, n9);
    stringstream ss;
    for (auto node = tree.begin_post_order(); node != tree.end_post_order(); ++node)
    {
        ss << node->get_value() << ", ";
    }
    CHECK(ss.str() == "1, 2, 5, 6, 7, 3, 8, 9, 10, 4, ");
    // check its the same as dfs
    stringstream ss2;
    for (auto node = tree.begin_dfs_scan(); node != tree.end_dfs_scan(); ++node)
    {
        ss2 << node->get_value() << ", ";
    }
    CHECK(ss2.str() == "1, 2, 5, 6, 7, 3, 8, 9, 10, 4, ");
}

TEST_CASE("Test InOrder K > 2 (DFS)"){
    Tree<int, 3> tree;
    Node<int> root = Node<int>(1);
    tree.add_root(root);
    Node<int> n1 = Node<int>(2);
    Node<int> n2 = Node<int>(3);
    Node<int> n3 = Node<int>(4);
    Node<int> n4 = Node<int>(5);
    Node<int> n5 = Node<int>(6);
    Node<int> n6 = Node<int>(7);
    Node<int> n7 = Node<int>(8);
    Node<int> n8 = Node<int>(9);
    Node<int> n9 = Node<int>(10);
    tree.add_sub_node(root, n1);
    tree.add_sub_node(root, n2);
    tree.add_sub_node(root, n3);
    tree.add_sub_node(n1, n4);
    tree.add_sub_node(n1, n5);
    tree.add_sub_node(n1, n6);
    tree.add_sub_node(n2, n7);
    tree.add_sub_node(n2, n8);
    tree.add_sub_node(n2, n9);
    stringstream ss;
    for (auto node = tree.begin_in_order(); node != tree.end_in_order(); ++node)
    {
        ss << node->get_value() << ", ";
    }
    CHECK(ss.str() == "1, 2, 5, 6, 7, 3, 8, 9, 10, 4, ");
    // check its the same as dfs
    stringstream ss2;
    for (auto node = tree.begin_dfs_scan(); node != tree.end_dfs_scan(); ++node)
    {
        ss2 << node->get_value() << ", ";
    }
    CHECK(ss2.str() == "1, 2, 5, 6, 7, 3, 8, 9, 10, 4, ");
}

TEST_CASE("Test BFS K > 2"){
    Tree<int, 3> tree;
    Node<int> root = Node<int>(1);
    tree.add_root(root);
    Node<int> n1 = Node<int>(2);
    Node<int> n2 = Node<int>(3);
    Node<int> n3 = Node<int>(4);
    Node<int> n4 = Node<int>(5);
    Node<int> n5 = Node<int>(6);
    Node<int> n6 = Node<int>(7);
    Node<int> n7 = Node<int>(8);
    Node<int> n8 = Node<int>(9);
    Node<int> n9 = Node<int>(10);
    tree.add_sub_node(root, n1);
    tree.add_sub_node(root, n2);
    tree.add_sub_node(root, n3);
    tree.add_sub_node(n1, n4);
    tree.add_sub_node(n1, n5);
    tree.add_sub_node(n1, n6);
    tree.add_sub_node(n2, n7);
    tree.add_sub_node(n2, n8);
    tree.add_sub_node(n2, n9);
    stringstream ss;
    for (auto node = tree.begin_bfs_scan(); node != tree.end_bfs_scan(); ++node)
    {
        ss << node->get_value() << ", ";
    }
    CHECK(ss.str() == "1, 2, 3, 4, 5, 6, 7, 8, 9, 10, ");
}

TEST_CASE("Test DFS K > 2"){
    Tree<int, 3> tree;
    Node<int> root = Node<int>(1);
    tree.add_root(root);
    Node<int> n1 = Node<int>(2);
    Node<int> n2 = Node<int>(3);
    Node<int> n3 = Node<int>(4);
    Node<int> n4 = Node<int>(5);
    Node<int> n5 = Node<int>(6);
    Node<int> n6 = Node<int>(7);
    Node<int> n7 = Node<int>(8);
    Node<int> n8 = Node<int>(9);
    Node<int> n9 = Node<int>(10);
    tree.add_sub_node(root, n1);
    tree.add_sub_node(root, n2);
    tree.add_sub_node(root, n3);
    tree.add_sub_node(n1, n4);
    tree.add_sub_node(n1, n5);
    tree.add_sub_node(n1, n6);
    tree.add_sub_node(n2, n7);
    tree.add_sub_node(n2, n8);
    tree.add_sub_node(n2, n9);
    stringstream ss;
    for (auto node = tree.begin_dfs_scan(); node != tree.end_dfs_scan(); ++node)
    {
        ss << node->get_value() << ", ";
    }
    CHECK(ss.str() == "1, 2, 5, 6, 7, 3, 8, 9, 10, 4, ");
}

TEST_CASE("Test Heap K > 2"){
    Tree<int, 3> tree;
    Node<int> root = Node<int>(1);
    tree.add_root(root);
    Node<int> n1 = Node<int>(2);
    Node<int> n2 = Node<int>(3);
    Node<int> n3 = Node<int>(4);
    Node<int> n4 = Node<int>(5);
    Node<int> n5 = Node<int>(6);
    Node<int> n6 = Node<int>(7);
    Node<int> n7 = Node<int>(8);
    Node<int> n8 = Node<int>(9);
    Node<int> n9 = Node<int>(10);
    tree.add_sub_node(root, n1);
    tree.add_sub_node(root, n2);
    tree.add_sub_node(root, n3);
    tree.add_sub_node(n1, n4);
    tree.add_sub_node(n1, n5);
    tree.add_sub_node(n1, n6);
    tree.add_sub_node(n2, n7);
    tree.add_sub_node(n2, n8);
    tree.add_sub_node(n2, n9);
    stringstream ss;
    for (auto node = tree.myHeap(); node != tree.end_heap(); ++node)
    {
        ss << node->get_value() << ", ";
    }
    CHECK(ss.str() == "10, 9, 8, 7, 6, 5, 4, 3, 2, 1, ");
}

TEST_CASE("Test Complex Tree"){
    Tree<Complex, 2> tree;
    Node<Complex> root = Node<Complex>(Complex(1, 1));
    tree.add_root(root);
    Node<Complex> n1 = Node<Complex>(Complex(2, 2));
    Node<Complex> n2 = Node<Complex>(Complex(3, 3));
    Node<Complex> n3 = Node<Complex>(Complex(4, 4));
    Node<Complex> n4 = Node<Complex>(Complex(5, 5));
    Node<Complex> n5 = Node<Complex>(Complex(6, 6));
    tree.add_sub_node(root, n1);
    tree.add_sub_node(root, n2);
    tree.add_sub_node(n1, n3);
    tree.add_sub_node(n1, n4);
    tree.add_sub_node(n2, n5);
    stringstream ss;
    for (auto node = tree.begin_pre_order(); node != tree.end_pre_order(); ++node)
    {
        ss << node->get_value() << ", ";
    }
    CHECK(ss.str() == "1+i, 2+2i, 4+4i, 5+5i, 3+3i, 6+6i, ");
}

TEST_CASE("Test PreOrder with Complex, K = 2"){
    Tree<Complex, 2> tree;
    Node<Complex> root = Node<Complex>(Complex(1, 1));
    tree.add_root(root);
    Node<Complex> n1 = Node<Complex>(Complex(2, 2));
    Node<Complex> n2 = Node<Complex>(Complex(3, 3));
    Node<Complex> n3 = Node<Complex>(Complex(4, 4));
    Node<Complex> n4 = Node<Complex>(Complex(5, 5));
    Node<Complex> n5 = Node<Complex>(Complex(6, 6));
    tree.add_sub_node(root, n1);
    tree.add_sub_node(root, n2);
    tree.add_sub_node(n1, n3);
    tree.add_sub_node(n1, n4);
    tree.add_sub_node(n2, n5);
    stringstream ss;
    for (auto node = tree.begin_pre_order(); node != tree.end_pre_order(); ++node)
    {
        ss << node->get_value() << ", ";
    }
    CHECK(ss.str() == "1+i, 2+2i, 4+4i, 5+5i, 3+3i, 6+6i, ");
}

TEST_CASE("Test PostOrder with Complex, K = 2"){
    Tree<Complex, 2> tree;
    Node<Complex> root = Node<Complex>(Complex(1, 1));
    tree.add_root(root);
    Node<Complex> n1 = Node<Complex>(Complex(2, 2));
    Node<Complex> n2 = Node<Complex>(Complex(3, 3));
    Node<Complex> n3 = Node<Complex>(Complex(4, 4));
    Node<Complex> n4 = Node<Complex>(Complex(5, 5));
    Node<Complex> n5 = Node<Complex>(Complex(6, 6));
    tree.add_sub_node(root, n1);
    tree.add_sub_node(root, n2);
    tree.add_sub_node(n1, n3);
    tree.add_sub_node(n1, n4);
    tree.add_sub_node(n2, n5);
    stringstream ss;
    for (auto node = tree.begin_post_order(); node != tree.end_post_order(); ++node)
    {
        ss << node->get_value() << ", ";
    }
    CHECK(ss.str() == "4+4i, 5+5i, 2+2i, 6+6i, 3+3i, 1+i, ");
}

TEST_CASE("Test InOrder with Complex, K = 2"){
    Tree<Complex, 2> tree;
    Node<Complex> root = Node<Complex>(Complex(1, 1));
    tree.add_root(root);
    Node<Complex> n1 = Node<Complex>(Complex(2, 2));
    Node<Complex> n2 = Node<Complex>(Complex(3, 3));
    Node<Complex> n3 = Node<Complex>(Complex(4, 4));
    Node<Complex> n4 = Node<Complex>(Complex(5, 5));
    Node<Complex> n5 = Node<Complex>(Complex(6, 6));
    tree.add_sub_node(root, n1);
    tree.add_sub_node(root, n2);
    tree.add_sub_node(n1, n3);
    tree.add_sub_node(n1, n4);
    tree.add_sub_node(n2, n5);
    stringstream ss;
    for (auto node = tree.begin_in_order(); node != tree.end_in_order(); ++node)
    {
        ss << node->get_value() << ", ";
    }
    CHECK(ss.str() == "4+4i, 2+2i, 5+5i, 1+i, 6+6i, 3+3i, ");
}

TEST_CASE("Test BFS with Complex, K = 2"){
    Tree<Complex, 2> tree;
    Node<Complex> root = Node<Complex>(Complex(1, 1));
    tree.add_root(root);
    Node<Complex> n1 = Node<Complex>(Complex(2, 2));
    Node<Complex> n2 = Node<Complex>(Complex(3, 3));
    Node<Complex> n3 = Node<Complex>(Complex(4, 4));
    Node<Complex> n4 = Node<Complex>(Complex(5, 5));
    Node<Complex> n5 = Node<Complex>(Complex(6, 6));
    tree.add_sub_node(root, n1);
    tree.add_sub_node(root, n2);
    tree.add_sub_node(n1, n3);
    tree.add_sub_node(n1, n4);
    tree.add_sub_node(n2, n5);
    stringstream ss;
    for (auto node = tree.begin_bfs_scan(); node != tree.end_bfs_scan(); ++node)
    {
        ss << node->get_value() << ", ";
    }
    CHECK(ss.str() == "1+i, 2+2i, 3+3i, 4+4i, 5+5i, 6+6i, ");
}

TEST_CASE("Test DFS with Complex, K = 2"){
    Tree<Complex, 2> tree;
    Node<Complex> root = Node<Complex>(Complex(1, 1));
    tree.add_root(root);
    Node<Complex> n1 = Node<Complex>(Complex(2, 2));
    Node<Complex> n2 = Node<Complex>(Complex(3, 3));
    Node<Complex> n3 = Node<Complex>(Complex(4, 4));
    Node<Complex> n4 = Node<Complex>(Complex(5, 5));
    Node<Complex> n5 = Node<Complex>(Complex(6, 6));
    tree.add_sub_node(root, n1);
    tree.add_sub_node(root, n2);
    tree.add_sub_node(n1, n3);
    tree.add_sub_node(n1, n4);
    tree.add_sub_node(n2, n5);
    stringstream ss;
    for (auto node = tree.begin_dfs_scan(); node != tree.end_dfs_scan(); ++node)
    {
        ss << node->get_value() << ", ";
    }
    CHECK(ss.str() == "1+i, 2+2i, 4+4i, 5+5i, 3+3i, 6+6i, ");
}

TEST_CASE("Test PreOrder with Complex, K > 2 (DFS)"){
    Tree<Complex, 3> tree;
    Node<Complex> root = Node<Complex>(Complex(1, 1));
    tree.add_root(root);
    Node<Complex> n1 = Node<Complex>(Complex(2, 2));
    Node<Complex> n2 = Node<Complex>(Complex(3, 3));
    Node<Complex> n3 = Node<Complex>(Complex(4, 4));
    Node<Complex> n4 = Node<Complex>(Complex(5, 5));
    Node<Complex> n5 = Node<Complex>(Complex(6, 6));
    Node<Complex> n6 = Node<Complex>(Complex(7, 7));
    Node<Complex> n7 = Node<Complex>(Complex(8, 8));
    Node<Complex> n8 = Node<Complex>(Complex(9, 9));
    Node<Complex> n9 = Node<Complex>(Complex(10, 10));
    tree.add_sub_node(root, n1);
    tree.add_sub_node(root, n2);
    tree.add_sub_node(root, n3);
    tree.add_sub_node(n1, n4);
    tree.add_sub_node(n1, n5);
    tree.add_sub_node(n1, n6);
    tree.add_sub_node(n2, n7);
    tree.add_sub_node(n2, n8);
    tree.add_sub_node(n2, n9);
    stringstream ss;
    for (auto node = tree.begin_pre_order(); node != tree.end_pre_order(); ++node)
    {
        ss << node->get_value() << ", ";
    }
    CHECK(ss.str() == "1+i, 2+2i, 5+5i, 6+6i, 7+7i, 3+3i, 8+8i, 9+9i, 10+10i, 4+4i, ");
    // check its the same as dfs
    stringstream ss2;
    for (auto node = tree.begin_dfs_scan(); node != tree.end_dfs_scan(); ++node)
    {
        ss2 << node->get_value() << ", ";
    }
    CHECK(ss2.str() == "1+i, 2+2i, 5+5i, 6+6i, 7+7i, 3+3i, 8+8i, 9+9i, 10+10i, 4+4i, ");
}

TEST_CASE("Test PostOrder with Complex, K > 2 (DFS)"){
    Tree<Complex, 3> tree;
    Node<Complex> root = Node<Complex>(Complex(1, 1));
    tree.add_root(root);
    Node<Complex> n1 = Node<Complex>(Complex(2, 2));
    Node<Complex> n2 = Node<Complex>(Complex(3, 3));
    Node<Complex> n3 = Node<Complex>(Complex(4, 4));
    Node<Complex> n4 = Node<Complex>(Complex(5, 5));
    Node<Complex> n5 = Node<Complex>(Complex(6, 6));
    Node<Complex> n6 = Node<Complex>(Complex(7, 7));
    Node<Complex> n7 = Node<Complex>(Complex(8, 8));
    Node<Complex> n8 = Node<Complex>(Complex(9, 9));
    Node<Complex> n9 = Node<Complex>(Complex(10, 10));
    tree.add_sub_node(root, n1);
    tree.add_sub_node(root, n2);
    tree.add_sub_node(root, n3);
    tree.add_sub_node(n1, n4);
    tree.add_sub_node(n1, n5);
    tree.add_sub_node(n1, n6);
    tree.add_sub_node(n2, n7);
    tree.add_sub_node(n2, n8);
    tree.add_sub_node(n2, n9);
    stringstream ss;
    for (auto node = tree.begin_post_order(); node != tree.end_post_order(); ++node)
    {
        ss << node->get_value() << ", ";
    }
    CHECK(ss.str() == "1+i, 2+2i, 5+5i, 6+6i, 7+7i, 3+3i, 8+8i, 9+9i, 10+10i, 4+4i, ");
    // check its the same as dfs
    stringstream ss2;
    for (auto node = tree.begin_dfs_scan(); node != tree.end_dfs_scan(); ++node)
    {
        ss2 << node->get_value() << ", ";
    }
    CHECK(ss2.str() == "1+i, 2+2i, 5+5i, 6+6i, 7+7i, 3+3i, 8+8i, 9+9i, 10+10i, 4+4i, ");
}

TEST_CASE("Test InOrder with Complex, K > 2 (DFS)"){
    Tree<Complex, 3> tree;
    Node<Complex> root = Node<Complex>(Complex(1, 1));
    tree.add_root(root);
    Node<Complex> n1 = Node<Complex>(Complex(2, 2));
    Node<Complex> n2 = Node<Complex>(Complex(3, 3));
    Node<Complex> n3 = Node<Complex>(Complex(4, 4));
    Node<Complex> n4 = Node<Complex>(Complex(5, 5));
    Node<Complex> n5 = Node<Complex>(Complex(6, 6));
    Node<Complex> n6 = Node<Complex>(Complex(7, 7));
    Node<Complex> n7 = Node<Complex>(Complex(8, 8));
    Node<Complex> n8 = Node<Complex>(Complex(9, 9));
    Node<Complex> n9 = Node<Complex>(Complex(10, 10));
    tree.add_sub_node(root, n1);
    tree.add_sub_node(root, n2);
    tree.add_sub_node(root, n3);
    tree.add_sub_node(n1, n4);
    tree.add_sub_node(n1, n5);
    tree.add_sub_node(n1, n6);
    tree.add_sub_node(n2, n7);
    tree.add_sub_node(n2, n8);
    tree.add_sub_node(n2, n9);
    stringstream ss;
    for (auto node = tree.begin_in_order(); node != tree.end_in_order(); ++node)
    {
        ss << node->get_value() << ", ";
    }
    CHECK(ss.str() == "1+i, 2+2i, 5+5i, 6+6i, 7+7i, 3+3i, 8+8i, 9+9i, 10+10i, 4+4i, ");
    // check its the same as dfs
    stringstream ss2;
    for (auto node = tree.begin_dfs_scan(); node != tree.end_dfs_scan(); ++node)
    {
        ss2 << node->get_value() << ", ";
    }
    CHECK(ss2.str() == "1+i, 2+2i, 5+5i, 6+6i, 7+7i, 3+3i, 8+8i, 9+9i, 10+10i, 4+4i, ");
}

TEST_CASE("Test BFS with Complex, K > 2"){
    Tree<Complex, 3> tree;
    Node<Complex> root = Node<Complex>(Complex(1, 1));
    tree.add_root(root);
    Node<Complex> n1 = Node<Complex>(Complex(2, 2));
    Node<Complex> n2 = Node<Complex>(Complex(3, 3));
    Node<Complex> n3 = Node<Complex>(Complex(4, 4));
    Node<Complex> n4 = Node<Complex>(Complex(5, 5));
    Node<Complex> n5 = Node<Complex>(Complex(6, 6));
    Node<Complex> n6 = Node<Complex>(Complex(7, 7));
    Node<Complex> n7 = Node<Complex>(Complex(8, 8));
    Node<Complex> n8 = Node<Complex>(Complex(9, 9));
    Node<Complex> n9 = Node<Complex>(Complex(10, 10));
    tree.add_sub_node(root, n1);
    tree.add_sub_node(root, n2);
    tree.add_sub_node(root, n3);
    tree.add_sub_node(n1, n4);
    tree.add_sub_node(n1, n5);
    tree.add_sub_node(n1, n6);
    tree.add_sub_node(n2, n7);
    tree.add_sub_node(n2, n8);
    tree.add_sub_node(n2, n9);
    stringstream ss;
    for (auto node = tree.begin_bfs_scan(); node != tree.end_bfs_scan(); ++node)
    {
        ss << node->get_value() << ", ";
    }
    CHECK(ss.str() == "1+i, 2+2i, 3+3i, 4+4i, 5+5i, 6+6i, 7+7i, 8+8i, 9+9i, 10+10i, ");
}

TEST_CASE("Test DFS with Complex, K > 2"){
    Tree<Complex, 3> tree;
    Node<Complex> root = Node<Complex>(Complex(1, 1));
    tree.add_root(root);
    Node<Complex> n1 = Node<Complex>(Complex(2, 2));
    Node<Complex> n2 = Node<Complex>(Complex(3, 3));
    Node<Complex> n3 = Node<Complex>(Complex(4, 4));
    Node<Complex> n4 = Node<Complex>(Complex(5, 5));
    Node<Complex> n5 = Node<Complex>(Complex(6, 6));
    Node<Complex> n6 = Node<Complex>(Complex(7, 7));
    Node<Complex> n7 = Node<Complex>(Complex(8, 8));
    Node<Complex> n8 = Node<Complex>(Complex(9, 9));
    Node<Complex> n9 = Node<Complex>(Complex(10, 10));
    tree.add_sub_node(root, n1);
    tree.add_sub_node(root, n2);
    tree.add_sub_node(root, n3);
    tree.add_sub_node(n1, n4);
    tree.add_sub_node(n1, n5);
    tree.add_sub_node(n1, n6);
    tree.add_sub_node(n2, n7);
    tree.add_sub_node(n2, n8);
    tree.add_sub_node(n2, n9);
    stringstream ss;
    for (auto node = tree.begin_dfs_scan(); node != tree.end_dfs_scan(); ++node)
    {
        ss << node->get_value() << ", ";
    }
    CHECK(ss.str() == "1+i, 2+2i, 5+5i, 6+6i, 7+7i, 3+3i, 8+8i, 9+9i, 10+10i, 4+4i, ");
}

// -------------- Some simple tests for Complex class --------------
TEST_CASE("Test Complex operator+"){
    Complex c1 = Complex(1, 1);
    Complex c2 = Complex(2, 2);
    Complex c3 = c1 + c2;
    CHECK(c3.getReal() == 3);
    CHECK(c3.getImg() == 3);
}

TEST_CASE("Test Complex operator<<"){
    Complex c1 = Complex(1, 1);
    stringstream ss;
    ss << c1;
    CHECK(ss.str() == "1+i");
}

TEST_CASE("Test Complex operator=="){
    Complex c1 = Complex(1, 1);
    Complex c2 = Complex(1, 1);
    CHECK(c1 == c2);
}

TEST_CASE("Test Complex operator!="){
    Complex c1 = Complex(1, 1);
    Complex c2 = Complex(2, 2);
    CHECK(c1 != c2);
}

TEST_CASE("Test Complex operator-"){
    Complex c1 = Complex(1, 1);
    Complex c2 = Complex(2, 2);
    Complex c3 = c1 - c2;
    CHECK(c3.getReal() == -1);
    CHECK(c3.getImg() == -1);
}

TEST_CASE("Test Complex operator*"){
    Complex c1 = Complex(1, 1);
    Complex c2 = Complex(2, 2);
    Complex c3 = c1 * c2;
    CHECK(c3.getReal() == 0);
    CHECK(c3.getImg() == 4);
}

TEST_CASE("Test Complex operator/"){
    Complex c1 = Complex(1, 1);
    Complex c2 = Complex(2, 2);
    Complex c3 = c1 / c2;
    CHECK(c3.getReal() == 0.5);
    CHECK(c3.getImg() == 0);
}


