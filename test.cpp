#include <gtest/gtest.h>
#include "tree.h"

TEST(RBTreeTest, InsertNode) {
  tree rbTree;
  rbTree.insertNode(10);
  rbTree.insertNode(20);
  rbTree.insertNode(30);

  EXPECT_TRUE(rbTree.isKeyInside(30));
  EXPECT_TRUE(rbTree.isKeyInside(20));
  EXPECT_TRUE(rbTree.isKeyInside(10));
  EXPECT_TRUE(!rbTree.isKeyInside(25));
}

TEST(RBTreeTest, DeleteNode) {
  tree rbTree;
  rbTree.insertNode(10);
  rbTree.insertNode(20);
  rbTree.insertNode(30);
  rbTree.deleteNode(20);

  EXPECT_TRUE(rbTree.isKeyInside(30));
  EXPECT_TRUE(!rbTree.isKeyInside(20));
  EXPECT_TRUE(rbTree.isKeyInside(10));

  EXPECT_TRUE(!rbTree.isKeyInside(25));
  rbTree.insertNode(25);
  EXPECT_TRUE(rbTree.isKeyInside(25));
  rbTree.deleteNode(25);
  EXPECT_TRUE(!rbTree.isKeyInside(25));

}
/*
 for 10,20 30 tree will look like this
        20(B)
       /   \
    10(R)  30(R)
 */
TEST(RBTreeTest, isLeftChild) {
  tree rbTree;
  rbTree.insertNode(10);
  rbTree.insertNode(20);
  rbTree.insertNode(30);

  node* n = rbTree.search(20);
  EXPECT_TRUE(!n->isLeftChild());
  n = rbTree.search(30);
  EXPECT_TRUE(n->isRightChild());
  EXPECT_TRUE(n->isParent(rbTree.search(20)));
}

TEST(RBTreeTest, InsertDuplicateNode) {
    tree rbTree;
    rbTree.insertNode(10);
    rbTree.insertNode(10); // Insert duplicate

    EXPECT_TRUE(rbTree.isKeyInside(10));
    EXPECT_EQ(rbTree.getRoot()->getKey(), 10);
}

TEST(RBTreeTest, DeleteNonExistentNode) {
    tree rbTree;
    rbTree.insertNode(10);
    rbTree.insertNode(20);
    rbTree.insertNode(30);

    rbTree.deleteNode(40); // Delete non-existent node

    EXPECT_TRUE(rbTree.isKeyInside(10));
    EXPECT_TRUE(rbTree.isKeyInside(20));
    EXPECT_TRUE(rbTree.isKeyInside(30));
}

TEST(RBTreeTest, TreeStructureAfterInsertions) {
    tree rbTree;
    rbTree.insertNode(10);
    rbTree.insertNode(20);
    rbTree.insertNode(30);
    rbTree.insertNode(15);

    node* root = rbTree.getRoot();
    EXPECT_EQ(root->getKey(), 20);
    EXPECT_EQ(root->getLeft()->getKey(), 10);
    EXPECT_EQ(root->getRight()->getKey(), 30);
    EXPECT_EQ(root->getLeft()->getRight()->getKey(), 15);
}

TEST(RBTreeTest, TreeStructureAfterDeletions) {
    tree rbTree;
    rbTree.insertNode(10);
    rbTree.insertNode(20);
    rbTree.insertNode(30);
    rbTree.insertNode(15);

    rbTree.deleteNode(20);

    node* root = rbTree.getRoot();
    EXPECT_EQ(root->getKey(), 15);
    EXPECT_EQ(root->getLeft()->getKey(), 10);
    EXPECT_EQ(root->getRight()->getKey(), 30);
}


int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
