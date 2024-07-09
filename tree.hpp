#ifndef TREE_HPP
#define TREE_HPP

#include "node.hpp"
#include "complex.hpp"
#include <iterator>
#include <queue>
#include <stack>

template <typename T, size_t K = 2>     // default to binary tree (2 max children) if not specified
class Tree {

private:        // by default
    Node<T>* root;

public:
    // ------------------------ Constructors & Destructors ------------------------
    Tree();
    ~Tree();

    // NOTE: We are overloading a lot of functions to allow working with both Node objects and values.

    // ------------------------ add_root() ------------------------

    /*
     * Add a root node to the tree.
     * If a root already exists, delete it and add the new root.
     * Gets a Node object.
    */
    void add_root(const Node<T>& node);

    /*
     * Add a root node to the tree.
     * If a root already exists, delete it and add the new root.
     * Gets a value to create a new Node object.
    */
    void add_root(const T& value);

    // ------------------------ add_sub_node() ------------------------

    /*
     * Add a child node to a parent node.
     * If the parent node does not exist, throw exception.
     * If the parent node has maxChildren children, throw exception.
     * Gets a parent node and a child node.
    */
    void add_sub_node(const Node<T>& parentNode, const Node<T>& childNode);

    /*
     * Add a child node to a parent node.
     * If the parent node does not exist, throw exception.
     * If the parent node has maxChildren children, throw exception.
     * Gets a parent value and a child value.
    */
    void add_sub_node(const T& parentValue, const T& childValue);

    /*
     * Add a child node to a parent node.
     * If the parent node does not exist, throw exception.
     * If the parent node has maxChildren children, throw exception.
     * Gets a parent node and a value to create a new Node object.
    */
    void add_sub_node(const Node<T>& parentNode, const T& childValue);

    /*
     * Add a child node to a parent node.
     * If the parent node does not exist, throw exception.
     * If the parent node has maxChildren children, throw exception.
     * Gets a parent value and a child node.
    */
    void add_sub_node(const T& parentValue, const Node<T>& childNode);
    
    // NOTE: All iterators, including their classes and implementations,
    // are writen in the Tree.hpp file to avoid annoying template stuff and shorten the code.
    // TODO MAKE CLASSES PRIVATE AND ADD DECLARATIONS IN THE PUBLIC SECTION
    
    // ------------------------ PreOrderIterator ------------------------
    class PreOrderIterator {
        private:    // by default
            Node<T>* current;
            std::stack<Node<T>*> stack;

            void advance(){
                // As required in the assignment:
                // for K == 2, this is a simple PreOrder traversal
                // for K > 2, this is a DFS traversal (also PreOrder)
                // No need to implement both separately
                if (stack.empty()){
                    current = nullptr;
                } else {
                    current = stack.top();
                    stack.pop();
                    // goes over children in reverse order (right to left)
                    for (auto it = current->get_children().rbegin(); it != current->get_children().rend(); ++it){
                        stack.push(*it);
                    }
                }
            }
        public:
            PreOrderIterator(Node<T>* root){
                stack.push(root);
                advance();
            }
            PreOrderIterator& operator++(){
                advance();
                return *this;
            }
            PreOrderIterator operator++(int){
                PreOrderIterator temp = *this;
                advance();
                return temp;
            }
            bool operator==(const PreOrderIterator& other) const{
                return current == other.current && stack == other.stack;
            }
            bool operator!=(const PreOrderIterator& other) const{
                return !(*this == other);
            }
            Node<T>& operator*(){
                return *current;
            }
            Node<T>* operator->(){
                return current;
            }
    };

    PreOrderIterator begin_pre_order(){
        return PreOrderIterator(root);
    }
    PreOrderIterator end_pre_order(){
        return PreOrderIterator(nullptr);
    }

    // ------------------------ PostOrderIterator ------------------------
    class PostOrderIterator {
        private:    // by default
            Node<T>* current;
            std::stack<Node<T>*> stack;

            void advance(){
                if (stack.empty()){
                    current = nullptr;
                } else {
                    // for K == 2, the stack is already set, we just pop the top each advance call
                    current = stack.top();
                    stack.pop();
                    // for K > 2, we need to push the children in reverse order (right to left), same as PreOrder (DFS for K > 2)
                    if (K > 2) {
                        for (auto it = current->get_children().rbegin(); it != current->get_children().rend(); ++it){
                            stack.push(*it);
                        }
                    }
                }
            }

            // Used for K == 2 only
            void initPostOrder(Node<T>* root){
                /* From geeks4geeks:
                https://www.geeksforgeeks.org/iterative-postorder-traversal-using-stack/
                    1. Right child of 1 exists. 
                Push 3 to stack. Push 1 to stack. Move to left child.
                        Stack: 3, 1
                2. Right child of 2 exists. 
                Push 5 to stack. Push 2 to stack. Move to left child.
                        Stack: 3, 1, 5, 2
                3. Right child of 4 doesn't exist. '
                Push 4 to stack. Move to left child.
                        Stack: 3, 1, 5, 2, 4
                4. Current node is NULL. 
                Pop 4 from stack. Right child of 4 doesn't exist. 
                */

            // Because we use a stack, the concept is to always push the latest node we wanted to visit

            if (root != nullptr){
                    stack.push(root);
                    vector<Node<T>*> children = root->get_children();
                    for (auto it = children.rbegin(); it != children.rend(); ++it){
                        initPostOrder(*it);
                    }
                }
            }
        public:
            PostOrderIterator(Node<T>* root){
                if (root != nullptr){
                    if (K == 2){
                        initPostOrder(root);
                    }
                    else {      // Same at PreOrderIterator (DFS for K > 2)
                        stack.push(root);
                    }
                }
                advance();  // sets current to the first node (top of stack)
            }
            PostOrderIterator& operator++(){
                advance();
                return *this;
            }
            PostOrderIterator operator++(int){
                PostOrderIterator temp = *this;
                advance();
                return temp;
            }
            bool operator==(const PostOrderIterator& other) const{
                return current == other.current && stack == other.stack;
            }
            bool operator!=(const PostOrderIterator& other) const{
                return !(*this == other);
            }
            Node<T>& operator*(){
                return *current;
            }
            Node<T>* operator->(){
                return current;
            }
    };
    
    PostOrderIterator begin_post_order(){
        return PostOrderIterator(root);
    }
    PostOrderIterator end_post_order(){
        return PostOrderIterator(nullptr);
    }

    // ------------------------ InOrderIterator ------------------------
    class InOrderIterator {
        // TODO CONTINUE HERE
    };


    InOrderIterator begin_in_order();
    InOrderIterator end_in_order();

    BFSIterator begin_bfs_scan();
    BFSIterator end_bfs_scan();

    DFSIterator begin_dfs_scan();
    DFSIterator end_dfs_scan();

    void myHeap();

    void print_tree(); // GUI function

private:
    /*
     * Find a node with a specific value in the tree.
     * Gets a node and a value to search for under him.
     * Returns the node with the value or nullptr if not found.
    */
    Node<T>* find_node(Node<T>* node, const T& value);

    /*
     * Print the tree in a GUI format?
     * Gets a node and a depth to print the node at.
    */
    void print_node(Node<T>* node, int depth);
};

#endif // TREE_HPP