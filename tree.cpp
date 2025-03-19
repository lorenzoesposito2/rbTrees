#include "tree.h"
#include <iostream>
#include <iomanip>
#include <cmath>
#include <queue>

// constructor that reads keys from a file
tree::tree(const std::string& filename) : nil(new node(-1, node::BLACK)), root(nil) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        throw std::runtime_error("Could not open file " + filename);
    }
    int key;
    while (file >> key) {
        insertNode(key);
    }
    file.close();
}

// Perform a left rotation on the node x
void tree::leftRotate(node* x) {
    node* y = x->getRight();
    x->setRight(y->getLeft());
    if (y->getLeft() != nil) {
        y->getLeft()->setParent(x);
    }
    y->setParent(x->getParent());
    if (x->getParent() == nil) {
        root = y;
    } else if (x == x->getParent()->getLeft()) {
        x->getParent()->setLeft(y);
    } else {
        x->getParent()->setRight(y);
    }
    y->setLeft(x);
    x->setParent(y);
}

// Perform a right rotation on the node x
void tree::rightRotate(node* x) {
    node* y = x->getLeft();
    x->setLeft(y->getRight());
    if (y->getRight() != nil) {
        y->getRight()->setParent(x);
    }
    y->setParent(x->getParent());
    if (x->getParent() == nil) {
        root = y;
    } else if (x == x->getParent()->getRight()) {
        x->getParent()->setRight(y);
    } else {
        x->getParent()->setLeft(y);
    }
    y->setRight(x);
    x->setParent(y);
}

// Insert a node with the given key into the tree
void tree::insertNode(int key) {
    node* z = new node(key, node::RED);
    node* y = nil;
    node* x = root;

    while (x != nil) {
        y = x;
        if (z->getKey() < x->getKey()) {
            x = x->getLeft();
        } else {
            x = x->getRight();
        }
    }
    z->setParent(y);
    if (y == nil) {
        root = z;
    } else if (z->getKey() < y->getKey()) {
        y->setLeft(z);
    } else {
        y->setRight(z);
    }
    z->setLeft(nil);
    z->setRight(nil);
    z->setColor(node::RED);
    // up to here, the code is the same as the binary search tree insertion
    insertFixup(z); // fix the red-black tree properties
}

// Fix the red-black tree properties after inserting a node
void tree::insertFixup(node* z) {
    while (z->getParent()->getColor() == node::RED) {
        // z parent is a left child
        if (z->getParent() == z->getParent()->getParent()->getLeft()) {
            node* y = z->getParent()->getParent()->getRight();
            // case 1
            if (y->getColor() == node::RED) {
                z->getParent()->setColor(node::BLACK);
                y->setColor(node::BLACK);
                z->getParent()->getParent()->setColor(node::RED);
                z = z->getParent()->getParent();
            } else {
                // case 2
                if (z == z->getParent()->getRight()) {
                    z = z->getParent();
                    leftRotate(z);
                }
                // case 3
                z->getParent()->setColor(node::BLACK);
                z->getParent()->getParent()->setColor(node::RED);
                rightRotate(z->getParent()->getParent());
            }
        // simmetrical case but with left and right swapped (z parent is a right child)
        } else {
            node* y = z->getParent()->getParent()->getLeft();
            // case 1
            if (y->getColor() == node::RED) {
                z->getParent()->setColor(node::BLACK);
                y->setColor(node::BLACK);
                z->getParent()->getParent()->setColor(node::RED);
                z = z->getParent()->getParent();
            } else {
                // case 2
                if (z == z->getParent()->getLeft()) {
                    z = z->getParent();
                    rightRotate(z);
                }
                // case 3
                z->getParent()->setColor(node::BLACK);
                z->getParent()->getParent()->setColor(node::RED);
                leftRotate(z->getParent()->getParent());
            }
        }
    }
    root->setColor(node::BLACK);
}




// Replace the subtree rooted at node u with the subtree rooted at node v
void tree::transplant(node* u, node* v) {
    // if u is the root
    if (u->getParent() == nil) {
        root = v;
    } else if (u == u->getParent()->getLeft()) {
        u->getParent()->setLeft(v);
    } else {
        u->getParent()->setRight(v);
    }
    v->setParent(u->getParent());
}

/* Returns the node with the minimum key in the subtree rooted at x
it's important to call on the right child of the node which will be deleted */
node* tree::treeMinimum(node* x) {
    while (x->getLeft() != nil) {
        x = x->getLeft();
    }
    return x;
}

// Delete the node with the given key from the tree
void tree::deleteNode(int key) {
    // search for the node with the given key
    node* z = root;
    while (z != nil && z->getKey() != key) {
        if (key < z->getKey()) {
            z = z->getLeft();
        } else {
            z = z->getRight();
        }
    }

    // node not found
    if (z == nil) {
        std::cout << "Node not found in the tree.\n";
        return;
    }

    // deletion routine
    node* y = z;
    node::color yOriginalColor = y->getColor();
    node* x;

    // if z has only one child
    if (z->getLeft() == nil) {
        x = z->getRight();
        transplant(z, z->getRight());
    } else if (z->getRight() == nil) {
        x = z->getLeft();
        transplant(z, z->getLeft());
    } else {
        // if z has two children
        y = treeMinimum(z->getRight());
        yOriginalColor = y->getColor();
        x = y->getRight();
        if (y->getParent() != z) {
            transplant(y, y->getRight());
            y->setRight(z->getRight());
            y->getRight()->setParent(y);
        } else {
            x->setParent(y);
        }
        transplant(z, y);
        y->setLeft(z->getLeft());
        y->getLeft()->setParent(y);
        y->setColor(z->getColor());
    }
    // if the node deleted was black, fix the red-black tree properties
    if (yOriginalColor == node::BLACK) {
        deleteFixup(x);
    }

    // delete the node effectively
    delete z;
}

// Fix the red-black tree properties after deleting a node
void tree::deleteFixup(node* x) {
    while (x != root && x->getColor() == node::BLACK) {
        // x is a left child
        if (x == x->getParent()->getLeft()) {
            node* w = x->getParent()->getRight();
            // case 1
            if (w->getColor() == node::RED) {
                w->setColor(node::BLACK);
                x->getParent()->setColor(node::RED);
                leftRotate(x->getParent());
                w = x->getParent()->getRight();
            }
            // case 2
            if (w->getLeft()->getColor() == node::BLACK && w->getRight()->getColor() == node::BLACK) {
                w->setColor(node::RED);
                x = x->getParent();
            } else {
                // case 3
                if (w->getRight()->getColor() == node::BLACK) {
                    w->getLeft()->setColor(node::BLACK);
                    w->setColor(node::RED);
                    rightRotate(w);
                    w = x->getParent()->getRight();
                }
                // case 4
                w->setColor(x->getParent()->getColor());
                x->getParent()->setColor(node::BLACK);
                w->getRight()->setColor(node::BLACK);
                leftRotate(x->getParent());
                x = root;
            }
        // simmetrical case but with left and right swapped
        } else {
            // x is a right child
            node* w = x->getParent()->getLeft();
            // case 1
            if (w->getColor() == node::RED) {
                w->setColor(node::BLACK);
                x->getParent()->setColor(node::RED);
                rightRotate(x->getParent());
                w = x->getParent()->getLeft();
            }
            // case 2
            if (w->getRight()->getColor() == node::BLACK && w->getLeft()->getColor() == node::BLACK) {
                w->setColor(node::RED);
                x = x->getParent();
            } else {
                // case 3
                if (w->getLeft()->getColor() == node::BLACK) {
                    w->getRight()->setColor(node::BLACK);
                    w->setColor(node::RED);
                    leftRotate(w);
                    w = x->getParent()->getLeft();
                }
                // case 4
                w->setColor(x->getParent()->getColor());
                x->getParent()->setColor(node::BLACK);
                w->getLeft()->setColor(node::BLACK);
                rightRotate(x->getParent());
                x = root;
            }
        }
    }
    x->setColor(node::BLACK);
}


// Perform an in-order traversal of the tree and print the keys
void tree::inOrderTraversal(node* n) {
    if (n != nil) {
        inOrderTraversal(n->getLeft());
        std::cout << n->getKey() << " ";
        inOrderTraversal(n->getRight());
    }
}

// Check if the tree contains a node with the given key
int tree::isKeyInside(int key) {
    node* n = root;
    int comparisons = 0;
    while (n != nil) {
        comparisons++;
        if (n->getKey() == key) {
            return comparisons;
        } else if (key < n->getKey()) {
            n = n->getLeft();
        } else {
            n = n->getRight();
        }
    }
    return comparisons;
}

// Search for a node with the given key, return the node if found, throw an exception otherwise
node* tree::search(int key) {
    node* n = root;
    while (n != nil) {
        if (n->getKey() == key) {
            return n;
        } else if (key < n->getKey()) {
            n = n->getLeft();
        } else {
            n = n->getRight();
        }
    }
    throw std::runtime_error("Key not found in the tree.");
}

// Print the tree structure NOT STABLE
void tree::printTree(node* n, int indent) {
    if (n == nil) {
        std::cout << "Tree is empty.\n";
        return;
    }

    std::queue<node*> q;
    q.push(n);
    int level = 0;
    int maxLevel = 0;
    std::vector<std::vector<std::string>> levels;

    while (!q.empty()) {
        int size = q.size();
        std::vector<std::string> currentLevel;
        for (int i = 0; i < size; ++i) {
            node* current = q.front();
            q.pop();
            if (current == nil) {
                currentLevel.push_back(" ");
                q.push(nil);
                q.push(nil);
            } else {
                std::string key = "(" + std::to_string(current->getKey()) + ")";
                if (current->getColor() == node::RED) {
                    key = "\033[31m" + key + "\033[0m"; // Red color
                } else {
                    key = "\033[30m" + key + "\033[0m"; // Black color
                }
                currentLevel.push_back(key);
                q.push(current->getLeft());
                q.push(current->getRight());
            }
        }
        levels.push_back(currentLevel);
        ++level;
        if (std::all_of(currentLevel.begin(), currentLevel.end(), [](const std::string& s) { return s == " "; })) {
            break;
        }
    }

    maxLevel = levels.size();
    for (int i = 0; i < maxLevel; ++i) {
        int indent = std::pow(2, maxLevel - i - 1) - 1;
        int between = std::pow(2, maxLevel - i) - 1;
        for (int j = 0; j < levels[i].size(); ++j) {
            if (j == 0) {
                std::cout << std::setw(indent) << ' ';
            } else {
                std::cout << std::setw(between) << ' ';
            }
            std::cout << levels[i][j];
        }
        std::cout << "\n";
    }
}
