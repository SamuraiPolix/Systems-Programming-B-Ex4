#include "node.hpp"

using std::vector, std::size_t;

template <typename T>
Node<T>::Node(const T& value) : value(value) {}

template <typename T>
Node<T>::Node(const Node<T>& other) : value(other.get_value()) {
    Node<T>* otherChildren = other.get_children();
    for (auto child : otherChildren) {
        children.push_back(new Node<T>(*child));
    }
}

template <typename T>
Node<T>::Node(const T& value, size_t numChildren) : Node<T>(value) {
    children.reserve(numChildren);      // reserve space for children to avoid resizing vector
}

template <typename T>
Node<T>::Node(const Node<T>& other, size_t numChildren) : children.reserve(numChildren), Node<T>(other) {}

template <typename T>
Node<T>::~Node() {
    for (auto child : children) {
        if (child != nullptr){      // should really be null in practice but just in case
            delete child;
        }
    }
}

template <typename T>
T Node<T>::get_value() const {
    return data;
}

template <typename T>
vector<Node<T>*>& Node<T>::get_children() const {
    return children;
}

template <typename T>
size_t Node<T>::getChildrenSize() const {
    return children.size();
}

template <typename T>
void Node<T>::add_child(Node<T>& child) {
    // check many things to make sure the child is valid before adding
    if (child == this) {
        throw runtime_error("Cannot add node as child to itself");
    }
    if (child == nullptr) {
        throw runtime_error("Node is null, cannot add as child node");
    }
    if (typeid(child) != typeid(Node<T>)) {
        throw runtime_error("Types do not match, cannot add child node");
    }
    // check if child already exists
    for (auto c : children) {
        if (c == child) {
            throw runtime_error("Node already exists as child node, cannot add again");
        }
    }

    // all good, add child
    children.push_back(&child);
}

template <typename T>
void Node<T>::remove_child(Node<T>& child) {
    for (auto it = children.begin(); it != children.end(); ++it) {
        if (*it == child) {     // add reference before child???
            children.erase(it);
            return;     // no need to continue
        }
    }
}

// Explicit template instantiation
template class Node<int>;
template class Node<Complex>;
