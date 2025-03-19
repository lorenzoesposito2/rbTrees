#ifndef NODE_H
#define NODE_H

class node {
public:
    enum color { RED, BLACK };

    node(int key, color col) : key(key), col(col), left(nullptr), right(nullptr), parent(nullptr) {}

    int getKey() const { return key; }
    color getColor() const { return col; }
    void setColor(color c) { col = c; }
    node* getLeft() const { return left; }
    void setLeft(node* l) { left = l; }
    node* getRight() const { return right; }
    void setRight(node* r) { right = r; }
    node* getParent() const { return parent; }
    void setParent(node* p) { parent = p; }

    bool isLeftChild() const { return parent->getLeft() == this; }
    bool isRightChild() const { return parent->getRight() == this; }
    bool isParent(node *n) const { return parent == n; }

private:
    int key;
    color col;
    node* left;
    node* right;
    node* parent;
};

#endif // NODE_H