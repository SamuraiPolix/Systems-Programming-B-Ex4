#include "tree.hpp"
#include <iostream>

using std::cout, std::endl;

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

// Explicit template instantiation
template class Tree<int>;
template class Tree<Complex>;

// // Iterator functions in Tree class: "typename" is added here because the compiler does not know the type of the iterator until runtime. (its used as a placeholder)
// template <typename T, size_t K>
// typename Tree<T, K>::PreOrderIterator Tree<T, K>::begin_pre_order() {
//     return PreOrderIterator(root);
// }

// template <typename T, size_t K>
// typename Tree<T, K>::PostOrderIterator Tree<T, K>::begin_post_order() {
//     return PostOrderIterator(root);
// }

// template <typename T, size_t K>
// typename Tree<T, K>::InOrderIterator Tree<T, K>::begin_in_order() {
//     return InOrderIterator(root);
// }

// template <typename T, size_t K>
// typename Tree<T, K>::BFSIterator Tree<T, K>::begin_bfs_scan() {
//     return BFSIterator(root);
// }

// template <typename T, size_t K>
// typename Tree<T, K>::DFSIterator Tree<T, K>::begin_dfs_scan() {
//     return DFSIterator(root);
// }

// template <typename T, size_t K>
// typename Tree<T, K>::PreOrderIterator Tree<T, K>::end_pre_order() {
//     return PreOrderIterator(nullptr);
// }

// template <typename T, size_t K>
// typename Tree<T, K>::PostOrderIterator Tree<T, K>::end_post_order() {
//     return PostOrderIterator(nullptr);
// }

// template <typename T, size_t K>
// typename Tree<T, K>::InOrderIterator Tree<T, K>::end_in_order() {
//     return InOrderIterator(nullptr);
// }

// template <typename T, size_t K>
// typename Tree<T, K>::BFSIterator Tree<T, K>::end_bfs_scan() {
//     return BFSIterator(nullptr);
// }

// template <typename T, size_t K>
// typename Tree<T, K>::DFSIterator Tree<T, K>::end_dfs_scan() {
//     return DFSIterator(nullptr);
// }

// // PreOrderIterator functions
// template <typename T, size_t K>
// Tree<T, K>::PreOrderIterator::PreOrderIterator(Node<T>* root) {
//     if (root != nullptr) {
//         stack.push(root);
//     }
// }

// // prefix
// template <typename T, size_t K>
// typename Tree<T, K>::PreOrderIterator& Tree<T, K>::PreOrderIterator::operator++() {
//     if (stack.empty()) {
//         return *this;       // return the same iterator - nowhere to go
//     }
//     Node<T>* node = stack.top();        // node is for sure not null, because only non-null node pointers are pushed to stack in constructor
//     stack.pop();
//     vector<Node<T>*> children = node->get_children();
//     // 'r' is used to reverse the order of children to get the correct order in the stack
//     for (auto it = children.rbegin(); it != children.rend(); ++it) {
//         stack.push(*it);
//     }
//     return *this;
// }

// // postfix
// template <typename T, size_t K>
// typename Tree<T, K>::PreOrderIterator Tree<T, K>::PreOrderIterator::operator++(int) {
//     PreOrderIterator temp = *this;
//     ++(*this);      // using the prefix operator
//     return temp;
// }

// template <typename T, size_t K>
// Node<T>& Tree<T, K>::PreOrderIterator::operator*() {
//     return *stack.top();
// }

// template <typename T, size_t K>
// Node<T>* Tree<T, K>::PreOrderIterator::operator->() {
//     return stack.top();
// }

// template <typename T, size_t K>
// bool Tree<T, K>::PreOrderIterator::operator!=(const PreOrderIterator& other) {
//     return stack != other.stack;
// }

// // PostOrderIterator functions
// template <typename T, size_t K>
// Tree<T, K>::PostOrderIterator::PostOrderIterator(Node<T>* root) {
//     if (root != nullptr) {
//         stack.push(root);
//     }
// }

// template <typename T, size_t K>
// typename Tree<T, K>::PostOrderIterator& Tree<T, K>::PostOrderIterator::operator++() {
//     if (stack.empty()) {
//         return *this;       // return the same iterator - nowhere to go
//     }
//     Node<T>* node = stack.top();        // node is for sure not null, because only non-null node pointers are pushed to stack in constructor
//     stack.pop();
//     vector<Node<T>*> children = node->get_children();
//     for (auto child : children) {
//         stack.push(child);
//     }
//     visited.push(node);
//     return *this;
// }

// template <typename T, size_t K>
// typename Tree<T, K>::PostOrderIterator Tree<T, K>::PostOrderIterator::operator++(int) {
//     PostOrderIterator temp = *this;
//     ++(*this);      // using the prefix operator
//     return temp;
// }

// template <typename T, size_t K>
// Node<T>& Tree<T, K>::PostOrderIterator::operator*() {
//     return *visited.top();
// }

// template <typename T, size_t K>
// Node<T>* Tree<T, K>::PostOrderIterator::operator->() {
//     return visited.top();
// }

// template <typename T, size_t K>
// bool Tree<T, K>::PostOrderIterator::operator!=(const PostOrderIterator& other) {
//     return stack != other.stack;
// }

// // InOrderIterator functions
// template <typename T, size_t K>
// Tree<T, K>::InOrderIterator::InOrderIterator(Node<T>* root) {
//     if (root != nullptr) {
//         stack.push(root);
//     }
// }

// template <typename T, size_t K>
// typename Tree<T, K>::InOrderIterator& Tree<T, K>::InOrderIterator::operator++() {
//     if (stack.empty()) {
//         return *this;       // return the same iterator - nowhere to go
//     }
//     Node<T>* node = stack.top();        // node is for sure not null, because only non-null node pointers are pushed to stack in constructor
//     stack.pop();
//     vector<Node<T>*> children = node->get_children();
//     // 'r' is used to reverse the order of children to get the correct order in the stack
//     for (auto it = children.rbegin(); it != children.rend(); ++it) {
//         stack.push(*it);
//     }
//     return *this;
// }

// template <typename T, size_t K>
// Node<T>& Tree<T, K>::InOrderIterator::operator*() {
//     return *stack.top();
// }

// template <typename T, size_t K>
// Node<T>* Tree<T, K>::InOrderIterator::operator->() {
//     return stack.top();
// }

// template <typename T, size_t K>
// bool Tree<T, K>::InOrderIterator::operator!=(const InOrderIterator& other) {
//     return stack != other.stack;
// }

// // BFSIterator functions
// template <typename T, size_t K>
// Tree<T, K>::BFSIterator::BFSIterator(Node<T>* root) {
//     if (root != nullptr) {
//         queue.push(root);
//     }
// }

// template <typename T, size_t K>
// typename Tree<T, K>::BFSIterator& Tree<T, K>::BFSIterator::operator++() {
//     if (queue.empty()) {
//         return *this;       // return the same iterator - nowhere to go
//     }
//     Node<T>* node = queue.front();        // node is for sure not null, because only non-null node pointers are pushed to queue in constructor
//     queue.pop();
//     vector<Node<T>*> children = node->get_children();
//     for (auto child : children) {
//         queue.push(child);
//     }
//     return *this;
// }

// template <typename T, size_t K>
// Node<T>& Tree<T, K>::BFSIterator::operator*() {
//     return *queue.front();
// }

// template <typename T, size_t K>
// Node<T>* Tree<T, K>::BFSIterator::operator->() {
//     return queue.front();
// }

// template <typename T, size_t K>
// bool Tree<T, K>::BFSIterator::operator!=(const BFSIterator& other) {
//     return queue != other.queue;
// }

// // DFSIterator functions
// template <typename T, size_t K>
// Tree<T, K>::DFSIterator::DFSIterator(Node<T>* root) {
//     if (root != nullptr) {
//         stack.push(root);
//     }
// }

// template <typename T, size_t K>
// typename Tree<T, K>::DFSIterator& Tree<T, K>::DFSIterator::operator++() {
//     if (stack.empty()) {
//         return *this;       // return the same iterator - nowhere to go
//     }
//     Node<T>* node = stack.top();        // node is for sure not null, because only non-null node pointers are pushed to stack in constructor
//     stack.pop();
//     vector<Node<T>*> children = node->get_children();
//     for (auto child : children) {
//         stack.push(child);
//     }
//     return *this;
// }

// template <typename T, size_t K>
// Node<T>& Tree<T, K>::DFSIterator::operator*() {
//     return *stack.top();
// }

// template <typename T, size_t K>
// Node<T>* Tree<T, K>::DFSIterator::operator->() {
//     return stack.top();
// }

// template <typename T, size_t K>
// bool Tree<T, K>::DFSIterator::operator!=(const DFSIterator& other) {
//     return stack != other.stack;
// }
