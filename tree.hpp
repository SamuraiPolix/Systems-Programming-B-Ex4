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

    // ------------------------ print_tree() ------------------------
    void print_tree(); // GUI function

    friend ostream& operator<<(ostream& os, const Tree<T, K>& tree);

private:    // helpers
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

public: // Iterators
    
    // NOTE: All iterators, including their classes and implementations,
    // are writen in the Tree.hpp file to avoid annoying template stuff and shorten the code.
    // TODO MAKE CLASSES PRIVATE AND ADD DECLARATIONS IN THE PUBLIC SECTION

    // ------------------------ Iterator ------------------------
    // This is used to allow for-each loop on tree (as seen in Demo.cpp). Required by assignment to return BFS>.
    BFSIterator begin() {
        return begin_bfs_scan();
    }
    BFSIterator end() {
        return end_bfs_scan();
    }
    
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
                }
                else {
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

    // NOTE: for all begin_iter, end_iter functions:
    // Could add a check for K == 2 and K > 2,
    // create a general iterator and return it on top of PreOrderIterator or DFSIterator according to K
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
                }
                else {
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
        private:    // by default
            Node<T>* current;
            std::stack<Node<T>*> stack;

            void advance(){
                vector<Node<T>*> children = current->get_children();
                if (K == 2) { // InOrder
                    // stack was set in constructor to mostleft, here we push the right children and all his left children
                    if (children.size() > 1) {
                        push_left(children[1]);
                    }
                } else if (K > 2) { // DFS
                    // for all children in reverse order (right to left), push them and their children
                    for (auto it = children.rbegin(); it != children.rend(); ++it) {
                        stack.push(*it);
                    }
                }
                // update current to the next mostleft or DFS node
                if (!stack.empty()) {
                    current = stack.top();
                    stack.pop();
                }
                else {
                    current = nullptr;
                }
            }

            // Used for K == 2 only,
            // This simply pushes all left children until null, to set current on the leftmost node
            void push_left(Node<T>* node) {
                while (node != nullptr) {
                    stack.push(node);
                    vector<Node<T>*> children = node->get_children();
                    if (children.size() > 0) {  // push left child
                        node = children[0];
                    }
                    else {
                        node = nullptr;     // to break loop
                    }
                }
            }
        public:
            InOrderIterator(Node<T>* root){
                if (root != nullptr){
                    if (K == 2){
                        // set stack to the leftmost path to null - pushes all left children until null
                        push_left(root);
                    }
                    else {      // DFS for K > 2
                        if (node != nullptr) {
                            nodeStack.push(node);
                        }
                    }
                }
                advance();  // sets current to the first node (top of stack). if root is null, sets current to null
            }
            InOrderIterator& operator++(){
                advance();
                return *this;
            }
            InOrderIterator operator++(int){
                InOrderIterator temp = *this;
                advance();
                return temp;
            }
            bool operator==(const InOrderIterator& other) const{
                return current == other.current && stack == other.stack;
            }
            bool operator!=(const InOrderIterator& other) const{
                return !(*this == other);
            }
            Node<T>& operator*(){
                return *current;
            }
            Node<T>* operator->(){
                return current;
            }
    };

    InOrderIterator begin_in_order(){
        return InOrderIterator(root);
    }
    InOrderIterator end_in_order(){
        return InOrderIterator(nullptr);
    
    }

    // ------------------------ BFSIterator ------------------------
    class BFSIterator {
        private:    // by default
            Node<T>* current;
            // we are using a queue to access the nodes in the order they were added
            // (That way we always add all the children but access the parents first) - BFS
            std::queue<Node<T>*> queue;

            void advance(){
                if (queue.empty()){
                    current = nullptr;
                }
                else {
                    current = queue.front();
                    queue.pop();
                    vector<Node<T>*> children = current->get_children();
                    // add them from left to right, because we are using a queue so we pop them in the same order as we push them
                    for (auto it = children.begin(); it != children.end(); ++it){
                        queue.push(*it);
                    }
                }
            }
        public:
            BFSIterator(Node<T>* root){
                queue.push(root);
                advance();      // deals with root = null case, sets current to the first node
            }
            BFSIterator& operator++(){
                advance();
                return *this;
            }
            BFSIterator operator++(int){
                BFSIterator temp = *this;
                advance();
                return temp;
            }
            bool operator==(const BFSIterator& other) const{
                return current == other.current && queue == other.queue;
            }
            bool operator!=(const BFSIterator& other) const{
                return !(*this == other);
            }
            Node<T>& operator*(){
                return *current;
            }
            Node<T>* operator->(){
                return current;
            }
    };

    BFSIterator begin_bfs_scan(){
        return BFSIterator(root);
    }
    BFSIterator end_bfs_scan(){
        return BFSIterator(nullptr);
    }

    // ------------------------ DFSIterator ------------------------
    class DFSIterator {
        private:    // by default
            Node<T>* current;
            std::stack<Node<T>*> stack;

            void advance(){
                if (stack.empty()){
                    current = nullptr;
                }
                else {
                    current = stack.top();
                    stack.pop();
                    vector<Node<T>*> children = current->get_children();
                    // push all children in reverse order (right to left)
                    // same as we done in Pre Post In Order for K == 2, but now for all K
                    for (auto it = children.rbegin(); it != children.rend(); ++it){
                        stack.push(*it);
                    }
                }
            }
        public:
            DFSIterator(Node<T>* root){
                stack.push(root);
                advance();      // deals with root = null case, sets current to the first node
            }
            DFSIterator& operator++(){
                advance();
                return *this;
            }
            DFSIterator operator++(int){
                DFSIterator temp = *this;
                advance();
                return temp;
            }
            bool operator==(const DFSIterator& other) const{
                return current == other.current && stack == other.stack;
            }
            bool operator!=(const DFSIterator& other) const{
                return !(*this == other);
            }
            Node<T>& operator*(){
                return *current;
            }
            Node<T>* operator->(){
                return current;
            }
    };

    DFSIterator begin_dfs_scan(){
        return DFSIterator(root);
    }
    DFSIterator end_dfs_scan(){
        return DFSIterator(nullptr);
    }

    // ------------------------ HeapIterator ------------------------
    class HeapIterator {
        private:    // by default
            size_t index;
            vector<Node<T>*> heap;

            void advance(){
                // if there are still nodes, pop the smallest from heap and increment index
                if (index < heap.size() - 1) {
                    // pop the top node (smallest) and push the next node
                    std::pop_heap(heap.begin(), heap.end() - index, std::greater<Node<T>>());
                    index++;
                }
            }

            // Pushes all nodes to the vector
            void initHeap(Node<T>* node){
                if (node != nullptr){
                    heap.push(root);
                    vector<Node<T>*> children = node->get_children();
                    for (auto it = children.begin(); it != children.end(); ++it){
                        // push all children to the vector
                        initHeap(*it);
                    }
                }
            }
        public:
            HeapIterator(Node<T>* root) : index(0) {
                initHeap(root);
                // Using standart lib (allowed in assignment) https://www.geeksforgeeks.org/cpp-stl-heap/
                // make_help() makes our vector a heap, with the comparison we get a min heap
                // Note: We overloaded comparison operator > >= etc. for Node<T> to compare the values
                std::make_heap(heap.begin(), heap.end(), std::greater<Node<T>>());
            }
            HeapIterator& operator++(){
                advance();
                return *this;
            }
            HeapIterator operator++(int){
                HeapIterator temp = *this;
                advance();
                return temp;
            }
            bool operator==(const HeapIterator& other) const{
                return index == other.index && heap == other.heap;
            }
            bool operator!=(const HeapIterator& other) const{
                return !(*this == other);
            }
            Node<T>& operator*(){
                return heap[index];
            }
            Node<T>* operator->(){
                return &heap[index];
            }
    };

    HeapIterator myHeap(){
        return HeapIterator(root);
    }
};

#endif // TREE_HPP