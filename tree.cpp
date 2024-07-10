#include "tree.hpp"
#include <iostream>

using std::cout, std::endl, std::ostream;

template <typename T, size_t K>
Tree<T, K>::Tree() : root(nullptr) {}

template <typename T, size_t K>
Tree<T, K>::~Tree() {
    // This calls the destructor of Node class (which deletes all children as well)
    // So it's a sort of recursive deletion of all nodes in the tree
    if (root != nullptr) {
        delete root;        
    }
}

template <typename T, size_t K>
void Tree<T, K>::add_root(const Node<T>& node) {
    if (root != nullptr) {
        cout << "Deleting root node to set new root node" << endl;
        delete root;
    }
    root = &node;
}

template <typename T, size_t K>
void Tree<T, K>::add_root(const T& value) {
    if (root != nullptr) {
        cout << "Deleting root node to set new root node" << endl;
        delete root;
    }
    root = new Node<T>(value);
}

template <typename T, size_t K>
void Tree<T, K>::add_sub_node(const Node<T>& parentNode, const Node<T>& childNode){
    if (parentNode == nullptr) {
        throw std::runtime_error("Parent node is null, cannot add child node");
    }
    if (parentNode.children.size() >= K) {
        throw std::runtime_error("Parent node has max children, cannot add child node");
    }
    // make sure parent node is in the tree, before adding child node
    Node<T>* parentNode = find_node(root, parentNode.data);
    if (parentNode != nullptr) {
        if (parentNode->getChildrenSize() >= K) {
            throw std::runtime_error("Parent node has max children, cannot add child node");
        }
        parentNode.add_child(childNode);
    }
    else {
        throw std::runtime_error("Parent node does not exist, cannot add child node");
    }
}

template <typename T, size_t K>
void Tree<T, K>::add_sub_node(const T& parentValue, const T& childValue){
    // make sure parent node is in the tree, before adding child node
    Node<T>* parentNode = find_node(root, parentValue);
    if (parentNode != nullptr) {
        if (parentNode->getChildrenSize() >= K) {
            throw std::runtime_error("Parent node has max children, cannot add child node");
        }
        parentNode.add_child(new Node<T>(childValue));
    }
    else {
        throw std::runtime_error("Parent node does not exist, cannot add child node");
    }
}

template <typename T, size_t K>
void Tree<T, K>::add_sub_node(const Node<T>& parentNode, const T& childValue){
    if (parentNode == nullptr) {
        throw std::runtime_error("Parent node is null, cannot add child node");
    }
    if (parentNode.children.size() >= K) {
        throw std::runtime_error("Parent node has max children, cannot add child node");
    }
    // make sure parent node is in the tree, before adding child node
    Node<T>* parentNode = find_node(root, parentNode.data);
    if (parentNode != nullptr) {
        if (parentNode->getChildrenSize() >= K) {
            throw std::runtime_error("Parent node has max children, cannot add child node");
        }
        parentNode.add_child(new Node<T>(childValue));
    }
    else {
        throw std::runtime_error("Parent node does not exist, cannot add child node");
    }
}

template <typename T, size_t K>
void Tree<T, K>::add_sub_node(const T& parentValue, const Node<T>& childNode){
    // make sure parent node is in the tree, before adding child node
    Node<T>* parentNode = find_node(root, parentValue);
    if (parentNode != nullptr) {
        if (parentNode->getChildrenSize() >= K) {
            throw std::runtime_error("Parent node has max children, cannot add child node");
        }
        parentNode.add_child(childNode);
    }
    else {
        throw std::runtime_error("Parent node does not exist, cannot add child node");
    }
}

template <typename T, size_t K>
Node<T>* Tree<T, K>::find_node(Node<T>* node, const T& value) {
    if (node == nullptr) {
        return nullptr;
    }
    if (node->data == value) {      // found the node
        return node;
    }
    vector<Node<T>*> children = node->get_children();
    for (auto child : children) {
        // recursively search for the node in the children
        Node<T>* result = find_node(child, value);
        if (result != nullptr) {
            return result;
        }
    }
    // went through all children and didnt find the node
    return nullptr;
}

template <typename T, size_t K>
void Tree<T, K>::print_tree() {
    print_node(root, 0);
}

template <typename T, size_t K>
void Tree<T, K>::print_node(Node<T>* node, int depth) {
    if (node == nullptr) {
        return;
    }
    for (int i = 0; i < depth; ++i) {
        std::cout << "  ";
    }
    std::cout << node->data << std::endl;
    for (auto child : node->children) {
        print_node(child, depth + 1);
    }
}

template <typename T, size_t K>
std::ostream& operator<<(std::ostream& os, const Tree<T, K>& tree) {
    // As said in the requirements, this should print the tree in a GUI format, no usage for os
    tree.print_tree();
    return os;
}

// Explicit template instantiation
template class Tree<int>;
template class Tree<Complex>;