#ifndef AVLTREE_H
#define AVLTREE_H

#include <stdexcept>
#include <algorithm>
#include <iostream>
#include <queue>
#include <stack>
#include <cmath>


using namespace std;

template <typename Comparable>
class AVLTree {
private:

    struct AVLNode {
        Comparable element;
        AVLNode *left;
        AVLNode *right;
        int height;

        AVLNode(const Comparable &ele, AVLNode *lt, AVLNode *rt, int h = 0) {
            element = ele;
            left = lt;
            right = rt;
            height = h;
        }
    };

    AVLNode *root;

public:
//constructor
AVLTree() {
    root = nullptr;
}

//copy constructor
AVLTree(const AVLTree &rhs) {
    root = nullptr;
    root = clone(rhs.root);
}

//copy assignment operator
AVLTree &operator=(const AVLTree &rhs)
{
    clear();
    root = clone(rhs.root);
    return *this;
}

//destructor
~AVLTree(){
    clear();
}

//iterative function to find a value in the tree
bool contains( const Comparable &x) {
    if(root == nullptr){
        return false;
    }
    AVLNode *current = root;
    while( current != nullptr ) {
        if (x < current->element) {
            current = current->left;
        }
        else if (x > current->element) {
            current = current->right;
        }
        else {
            return true;    // Match
        }
    }
    return false;   // No match
}

//check if the tree is empty
bool isEmpty() {
    if (root == nullptr) {
        return true;
    }
    else {
        return false;
    }
}

//print contents of the tree
void printTreeSort(ostream &out = cout) const {
    printTreeSort(root, out);
}

//print out the tree by levels
void printTreeByLevel(ostream &out = cout) const
{
    printTreeByLevel(root, out);
}

//print the tree structure
void prettyPrintTree() const {
    prettyPrintTree("", root, false);
}

//clear tree
void clear() {
    clear(root);
}

//insert an item using iteration
void insert(const Comparable &x) {
    if (root == nullptr) {
        root = new AVLNode(x, nullptr, nullptr, 0);
        return ; // a single node is always balanced
    }

    stack<AVLNode *> alpha;  //create a stack which will used to store nodes for balancing

    AVLNode *current = root;
    AVLNode *previous = nullptr;
    while (current != nullptr) {  //iterate down the tree until nullptr is reached
        if (x < current->element) {
            previous = current;
            current = current->left;
        }
        else if (x > current->element) {
            previous = current;
            current = current->right;
        }
        alpha.push(previous); //add alpha value to the stack
    }

    current = new AVLNode(x, nullptr, nullptr, 0);  //create new node
    if (x < previous->element) {
        previous->left = current;  //set left pointer if value is less than parent
    }
    else if (x > previous->element) {
        previous->right = current;  //set right pointer if value is greater than parent
    }
    alpha.push(current); //push current in the stack for balancing

    while (!alpha.empty()) {
        balance(alpha.top()->left); //balance left node
        balance(alpha.top()->right); //balance right node
        alpha.top()->height = max(height(alpha.top()->left), height(alpha.top()->right)) + 1; //update height
        alpha.pop(); //remove value from the stack
    }
        balance(root); //balance root node
}

//iterative function to storeValue of tree in vector (in-order traversal)
void storeTree(vector<Comparable> &v) {
    if(root == nullptr) {
        throw std::runtime_error("Tree is empty!");
    }
    stack<AVLNode *> s; //create stack to store nodes
    AVLNode *current = root;
    while(current != nullptr || s.empty() == false) { //continue until nullptr or stack is empty
        while (current != nullptr) { //traverse down the left side of the tree
            s.push(current);
            current = current->left;
        }
        current = s.top();
        s.pop();
        v.push_back(current->element);
        current = current->right; //traverse right side
    }
}

//check tree balance
void check_balance() {
    this->check_balance(root);
}

//remove an item
void remove(const Comparable &x) {
    remove(x, root);
}
//find a value and return it
Comparable & findVal(const Comparable &x) {  //will only be used once contains element confirmed
    if(root == nullptr){
        throw std::runtime_error("Tree is empty!");
    }

    AVLNode *current = root;
    while( current != nullptr ) { //traverse the tree until the value is found or nullptr is reached
        if (x < current->element) {
            current = current->left;
        }
        else if (x > current->element) {
            current = current->right;
        }
        else {
            return current->element;    // Match
        }
    }
    throw std::runtime_error("Value not found!");   // No match
}

//find minimum value
Comparable findMinVal() {
    if(root == nullptr){
        throw std::runtime_error("Tree is empty!");
    }
    return findMin(root)->element;
}

private:
//recursive function for removing a node
void remove(const Comparable &x, AVLNode *&t) {
    if (root == nullptr) {
        throw std::runtime_error("Tree is empty!");
    }
    else if (x == root->element) { //calls a special function to remove root node
        removeRoot();
        balance(t);
        return;
    }

    if (t == nullptr) {
        cout << "Word not found";
        return;
    }

    if (x < t->element) {
        if (t->left->element == x) { //before moving down the tree check to see if the left element is the value
            removeNode(t, t->left, true); //pass parent, parent->left, and boolean left value (true)
        }
        else {
            remove(x, t->left); //move down left side of the tree
        }
    }
    else if (x > t->element) {
        if (t->right->element == x) { //before moving down the tree check to see if the right element is the value
            removeNode(t, t->right, false); //pass parent, parent->right, and boolean left value (false)
        }
        else {
            remove(x, t->right); //move down right side of the tree
        }
    }
        balance(t); //balance occurs after each recursive call
}
//remove a root node from the tree
void removeRoot() {
    AVLNode *t = root;
    AVLNode *small = nullptr;
    //no children
    if (t->left == nullptr && t->right == nullptr ) {
        delete t;
        root = nullptr;
    }
    //one child on the right
    else if (t->left == nullptr && t->right != nullptr) {
        root = t->right;  //sets the new root
        delete t;  //removes the old root
    }
    //one child on the left
    else if (t->left != nullptr && t->right == nullptr) {
        root = t->left;  //sets the new root
        delete t;  //removes the old root
    }
    //two children
    else {
        small = findMin(t->right); //finds the smallest value on the right
        t->element = small->element;  //sets current element equal to smallest element found
        if (small->right != nullptr) {  //check to see if small has a child on the right
            AVLNode *child = small->right; //temp equal to right child
            small->element = child->element;  //set small equal to right child
            delete child; //delete right child
        }
        else {
            delete small;  //delete the smallest element node
        }
    }
}

//remove non-root node
void removeNode(AVLNode *p, AVLNode *t, bool left) {
    AVLNode *temp = nullptr;
    AVLNode *small = nullptr;
    //no children
    if (t->left == nullptr && t->right == nullptr ) {
        temp = t;
        if (left) {
            p->left = nullptr;  //if node to be removed on the left side of the parent, left parent pointer should be null
        }
        else {
            p->right = nullptr;  //if node to be removed on the right side of the parent, right parent pointer should be null
        }
        delete temp; // delete node
    }
    //one child on the right
    else if (t->left == nullptr && t->right != nullptr) {
        temp = t;
        if (left) {
            p->left = t->right;  //if node to be removed on the left side of the parent, left parent pointer should point to right child
        } else {
            p->right = t->right;  //if node to be removed on the right side of the parent, right parent pointer should point to right child
        }
        delete temp;
    }

    //one child on the left
    else if (t->left != nullptr && t->right == nullptr) {
        temp = t;
        if (left) {
            p->left = t->left;  //if node to be removed on the left side of the parent, left parent pointer should point to left child
        } else {
            p->right = t->left;  //if node to be removed on the left side of the parent, left parent pointer should point to left child
        }
        delete temp;
    }

    //two children
    else {
        small = findMin(t->right); //find smallest value on the right side
        t->element = small->element;  //set t equal to smallest value
        if (small->right != nullptr) {  //check to see if small has a child on the right
            AVLNode *child = small->right; //temp equal to right child
            small->element = child->element;  //set small equal to right child
            delete child; //delete right child
        }
        else {
            delete small; //delete empty small node
        }
    }

}

/**
 * Internal method to find the smallest item in a subtree t.
 * Return node containing the smallest item.
 */
 //find min value
AVLNode *findMin(AVLNode *t) {
    if (t == nullptr)
        return nullptr;

    if (t->left == nullptr)
        return t;

    return findMin(t->left);
}
//clear tree
void clear(AVLNode *&t)
{
    if (t == nullptr)
        return;

    clear(t->left);
    clear(t->right);
    delete t;
    t = nullptr;
}

//copy tree
AVLNode *clone(AVLNode *t) const {
    if (t == nullptr) {
        return nullptr;
    }
    return new AVLNode{t->element, clone(t->left), clone(t->right), t->height};
}

//print and sort tree
void printTreeSort(AVLNode *t, ostream &out) const {
    if (t == nullptr)
        return;

    // recursion
    printTreeSort(t->left, out);
    out << t->element << endl;
    printTreeSort(t->right, out);
}
//print tree by level
void printTreeByLevel(AVLNode *t, ostream &out) const {
    if (t == nullptr)
        return;

    AVLNode *current;
    queue<AVLNode *> q;

    // start with the root node in the queue
    q.push(t);

    while (!q.empty())
    {
        // take the next node from the front of the queue
        current = q.front();
        q.pop();
        out << current->element << " ";

        // add children to the end of the queue
        if (current->left != nullptr)
            q.push(current->left);

        if (current->right != nullptr)
            q.push(current->right);
    }
}

void prettyPrintTree(const std::string &prefix, const AVLNode *node, bool isRight) const {
    if (node == nullptr)
        return;

    std::cout << prefix;
    std::cout << (isRight ? "├──" : "└──");
    // print the value of the node
    std::cout << node->element << std::endl;

    // enter the next tree level - left and right branch
    prettyPrintTree(prefix + (isRight ? "│   " : "    "), node->right, true);
    prettyPrintTree(prefix + (isRight ? "│   " : "    "), node->left, false);
}
//calculate height
int height(AVLNode *t) const {
    return t == nullptr ? -1 : t->height;
}
//check tree balance
int check_balance(AVLNode *node) {
    if (node == nullptr) {
        return -1;
    }

    int lHeight = check_balance(node->left) + 1;
    int rHeight = check_balance(node->right) + 1;

    if(lHeight - rHeight > 1){
        throw invalid_argument("tree is not balanced.");
    }

    int trueNodeHeight = std::max(lHeight, rHeight);

     if(trueNodeHeight != node->height){
         throw invalid_argument("node does not have correct height value.");
     }

    return trueNodeHeight;
}

static const int ALLOWED_IMBALANCE = 1;
//balance function
void balance(AVLNode *&t) {
    if (t == nullptr)
        return;

    if (height(t->left) - height(t->right) > ALLOWED_IMBALANCE)  // unbalancing insertion was left
    {
        if (height(t->left->left) >= height(t->left->right))
            rotateWithLeftChild(t); // case 1 (outside)
        else
            doubleWithLeftChild(t); // case 2 (inside)
    }
    else if (height(t->right) - height(t->left) > ALLOWED_IMBALANCE) // unbalancing insertion was right
    {
        if (height(t->right->right) >= height(t->right->left))
            rotateWithRightChild(t); // case 4 (outside)
        else
            doubleWithRightChild(t); // case 3 (inside)
    }

    // update height
    //t->height = max(height(t->left), height(t->right)) + 1;
}

int max(int lhs, int rhs) const {
    return lhs > rhs ? lhs : rhs;
}

void rotateWithLeftChild(AVLNode *&k2) {
    AVLNode *k1 = k2->left;
    k2->left = k1->right;
    k1->right = k2;
    k2->height = max(height(k2->left), height(k2->right)) + 1;
    k1->height = max(height(k1->left), k2->height) + 1;
    k2 = k1;
}

void rotateWithRightChild(AVLNode *&k1) {
    AVLNode *k2 = k1->right;
    k1->right = k2->left;
    k2->left = k1;
    k1->height = max(height(k1->left), height(k1->right)) + 1;
    k2->height = max(height(k2->right), k1->height) + 1;
    k1 = k2;
}

void doubleWithLeftChild(AVLNode *&k3) {
    rotateWithRightChild(k3->left);
    rotateWithLeftChild(k3);
}

void doubleWithRightChild(AVLNode *&k) {
    rotateWithLeftChild(k->right);
    rotateWithRightChild(k);
}

};

#endif //AVLTREE_H
