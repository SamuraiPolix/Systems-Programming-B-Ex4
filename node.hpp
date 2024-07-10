#ifndef NODE_HPP
#define NODE_HPP

#include <vector>
#include "complex.hpp"

using std::vector, std::size_t;

template <typename T>
class Node {

private:    // by default
    T value;
    vector<Node<T>*> children;

public:
    // ------------------------ Constructors & Destructors ------------------------
    Node(const T& value);
    Node(const Node<T>& other);     // copy constructor
    Node(const T& value, size_t numChildren);     // constructor with number of children - to avoid resizing vector (better performance)
    Node(const Node<T>& other, size_t numChildren);     // copy constructor with number of children - to avoid resizing vector (better performance)
    ~Node();

    T get_value() const;
    vector<Node<T>*>& get_children() const;
    size_t getChildrenSize() const;

    void add_child(Node<T>& child);
    void remove_child(Node<T>& child);

    // Comparison operators to use in HeapIterator
    bool operator<(const Node<T>& other) const;
    bool operator>(const Node<T>& other) const;
    bool operator==(const Node<T>& other) const;
    bool operator!=(const Node<T>& other) const;
    bool operator<=(const Node<T>& other) const;
    bool operator>=(const Node<T>& other) const;
};

#endif // NODE_HPP
