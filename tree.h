#ifndef TREE_H
#define TREE_H

#include "node.h"
#include <fstream>
#include <stdexcept>

/* this is the tree class that will be used to create the red-black tree.
the main functions were implemented starting from the pseudocode in the book:
"Introduction to Algorithms" by Thomas H. Cormen, Charles E. Leiserson, Ronald L. Rivest, and Clifford Stein */

class tree {
public:
    tree() : nil(new node(-1, node::BLACK)), root(nil) {}
    tree(const std::string& filename); // constructor that reads the tree from a file

    void insertNode(int key);
    void deleteNode(int key);
    void inOrderTraversal(node* n);
    bool isKeyInside(int key);
    node *search(int key);

    node* getRoot() const { return root; }

    void printTree(node* n, int indent);

private:
    node* nil;
    node* root;

    void insertFixup(node* z);
    void deleteFixup(node* x);
    void leftRotate(node* x);
    void rightRotate(node* x);
    void transplant(node* u, node* v);
    node* treeMinimum(node* x);
};

#endif // TREE_H