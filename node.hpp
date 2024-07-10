#ifndef NODE_HPP
#define NODE_HPP

#include <vector>
#include "complex.hpp"
#include <stdexcept>
#include <typeinfo>

using std::vector, std::size_t, std::runtime_error;

template <typename T>
class Node {

private:    // by default
    T value;
    vector<Node<T>*> children;

public:
    // ------------------------ Constructors & Destructors ------------------------
    Node(const T& value) : value(value) {}

    // Copy constructor
    Node(const Node<T>& other) : value(other.get_value()) {
        vector<Node<T>*> otherChildren = other.get_children();
        for (auto child : otherChildren) {
            children.push_back(new Node<T>(*child));
        }
    } 

    // constructor with number of children - to avoid resizing vector (better performance)
    Node(const T& value, size_t numChildren) : Node<T>(value) {
        children.reserve(numChildren);      // reserve space for children to avoid resizing vector
    }

    // copy constructor with number of children - to avoid resizing vector (better performance)
    Node(Node<T>& other, size_t numChildren) {
        children.reserve(numChildren);
        *this = other;      // calls copy constructor
    }  

    ~Node() {
        // delete all children nodes
        for (auto child : children) {
            if (child != nullptr){      // shouldnt really be null in practice but just in case
                delete child;
            }
        }
    }

    T get_value() const {
        return value;
    }

    const vector<Node<T>*>& get_children() const {
        return children;
    }

    size_t getChildrenSize() const {
        return children.size();
    }

    void add_child(const Node<T>& child) {
        // check many things to make sure the child is valid before adding
        if (child == *this) {
            throw runtime_error("Cannot add node as child to itself");
        }
        if (typeid(child) != typeid(Node<T>)) {
            throw runtime_error("Types do not match, cannot add child node");
        }
        // check if child already exists
        for (auto c : children) {
            if (*c == child) {
                throw runtime_error("Node already exists as child node, cannot add again");
            }
        }

        // all good, add child
        children.push_back(new Node<T>(child.get_value()));
    }

    void remove_child(Node<T>& child) {
        for (auto it = children.begin(); it != children.end(); ++it) {
            if (**it == child) {     // add reference before child???
                children.erase(it);
                return;     // no need to continue
            }
        }
    }

    // Comparison operators to use in HeapIterator
    bool operator<(const Node<T>& other) const {
        return value < other.get_value();
    }

    bool operator>(const Node<T>& other) const {
        return value > other.get_value();
    }

    bool operator==(const Node<T>& other) const {
        return value == other.get_value();
    }

    bool operator!=(const Node<T>& other) const {
        return value != other.get_value();
    }

    bool operator<=(const Node<T>& other) const {
        return value <= other.get_value();
    }

    bool operator>=(const Node<T>& other) const {
        return value >= other.get_value();
    }
};

#endif // NODE_HPP
