#pragma once
#ifndef BST_H
#define BST_H

#include "BSTNode.h"
#include <queue>

// A Binary Search Tree for managing integer IDs
class BST {
public:
  BST();        // Constructor to initialize the BST
  ~BST();       // Destructor to clean up dynamically allocated memory
  void clear(); // Clears the entire tree
  void insert(const int &id); // Inserts a new ID into the tree
  void remove(const int &id); // Removes a node with the given ID
  void getInOrder(std::queue<int> &ids) const;   // Retrieves IDs in in-order
  void getPreOrder(std::queue<int> &ids) const;  // Retrieves IDs in pre-order
  void getPostOrder(std::queue<int> &ids) const; // Retrieves IDs in post-order

private:
  BSTNode *root; // Root of the tree

  // Helper functions for recursive operations
  void clear(BSTNode *node); // Clears the tree from a given node
  void
  inOrderTraversal(const BSTNode *node,
                   std::queue<int> &ids) const; // Performs in-order traversal
  void
  preOrderTraversal(const BSTNode *node,
                    std::queue<int> &ids) const; // Performs pre-order traversal
  void postOrderTraversal(const BSTNode *node, std::queue<int> &ids)
      const; // Performs post-order traversal
};

#endif
