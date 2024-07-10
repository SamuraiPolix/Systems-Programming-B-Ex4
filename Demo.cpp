/*
 * Email: sam.lazareanu@gmail.com
 * ID: ****6281
 * @SamuraiPolix - Samuel Lazareanu
*/

/*
 * Demo app for Ex4
 */
#include <iostream>
#include <string>
#include "node.hpp"
#include "tree.hpp"

using namespace std;

int main()
{
    Node<double> root_node = Node<double>(1.1);
    Tree<double> tree; // Binary tree that contains doubles.
    tree.add_root(root_node);
    Node<double> n1 = Node<double>(1.2);        // same as Node<double> n1(1.2);
    Node<double> n2(1.3);       // same as Node<double> n2(1.3);
    Node<double> n3 = Node<double>(1.4);
    Node<double> n4 = Node<double>(1.5);
    Node<double> n5 = Node<double>(1.6);

    tree.add_sub_node(root_node, n1);
    tree.add_sub_node(root_node, n2);
    tree.add_sub_node(n1, n3);
    tree.add_sub_node(n1, n4);
    tree.add_sub_node(n2, n5);
   
    // The tree should look like:
    /**
     *       root = 1.1
     *     /       \
     *    1.2      1.3
     *   /  \      /
     *  1.4  1.5  1.6
     */

    cout << "PreOrder:" << endl;
    for (auto node = tree.begin_pre_order(); node != tree.end_pre_order(); ++node)
    {
        cout << node->get_value() << ", ";
    } // prints: 1.1, 1.2, 1.4, 1.5, 1.3, 1.6

    cout << endl;

    cout << "PostOrder:" << endl;
    for (auto node = tree.begin_post_order(); node != tree.end_post_order(); ++node)
    {
        cout << node->get_value() << ", ";
    } // prints: 1.4, 1.5, 1.2, 1.6, 1.3, 1.1

    cout << endl;

    cout << "InOrder:" << endl;
    for (auto node = tree.begin_in_order(); node != tree.end_in_order(); ++node)
    {
        cout << node->get_value() << ", ";
    } // prints: 1.4, 1.2, 1.5, 1.1, 1.6, 1.3

    cout << endl;

    cout << "BFS:" << endl;
    for (auto node = tree.begin_bfs_scan(); node != tree.end_bfs_scan(); ++node)
    {
        cout << node->get_value() << ", ";
    } // prints: 1.1, 1.2, 1.3, 1.4, 1.5, 1.6

    cout << endl;

    cout << "DFS:" << endl;
    for (auto node = tree.begin_dfs_scan(); node != tree.end_dfs_scan(); ++node)
    {
        cout << node->get_value() << ", ";
    } // prints: 1.1, 1.2, 1.4, 1.5, 1.3, 1.6

    cout << endl;

    cout << "BFS (for-each):" << endl;
    for (auto node : tree)
    {
        cout << node.get_value() << ", ";
    } // same as BFS: 1.1, 1.2, 1.3, 1.4, 1.5, 1.6

    cout << endl;

    cout << "Heap:" << endl;
    for (auto node = tree.myHeap(); node != tree.end_heap(); ++node)
    {
        cout << node->get_value() << ", ";
    } // prints: 1.6, 1.5, 1.4, 1.3, 1.2, 1.1

    cout << endl << endl;

    cout << tree << endl; // Should print the graph using GUI.

    Node<double> root_node2 = Node<double>(1.1);
    Node<double> n11 = Node<double>(1.2);
    Node<double> n22 = Node<double>(1.3);
    Node<double> n33 = Node<double>(1.4);
    Node<double> n44 = Node<double>(1.5);
    Node<double> n55 = Node<double>(1.6);

    Tree<double, 3> three_ary_tree; // 3-ary tree.
    three_ary_tree.add_root(root_node2);
    three_ary_tree.add_sub_node(root_node2, n11);
    three_ary_tree.add_sub_node(root_node2, n22);
    three_ary_tree.add_sub_node(root_node2, n33);
    three_ary_tree.add_sub_node(n11, n44);
    three_ary_tree.add_sub_node(n22, n55);

    cout << three_ary_tree << endl; // Should print the graph using GUI.

     // The tree should look like:
    /**
     *       root = 1.1
     *     /      |     \
     *    1.2    1.3    1.4
     *   /        |
     *  1.5      1.6
     */

    // Demo with Complex
    Node<Complex> root_node3 = Node<Complex>(Complex(1.1, 2.2));
    Node<Complex> n111 = Node<Complex>(Complex(1.2, 2.3));
    Node<Complex> n222 = Node<Complex>(Complex(1.3, 2.4));
    Node<Complex> n333 = Node<Complex>(Complex(1.4, 2.5));
    Node<Complex> n444 = Node<Complex>(Complex(1.5, 2.6));
    Node<Complex> n555 = Node<Complex>(Complex(1.6, 2.7));

    Tree<Complex> complex_tree; // binary by default
    complex_tree.add_root(root_node3);
    complex_tree.add_sub_node(root_node3, n111);
    complex_tree.add_sub_node(root_node3, n222);
    complex_tree.add_sub_node(n111, n333);
    complex_tree.add_sub_node(n111, n444);
    complex_tree.add_sub_node(n222, n555);

    cout << complex_tree << endl; // Should print the graph using GUI.

    return 0;   
}
