#pragma once
#ifndef BSTNode_H
#define BSTNode_H

// A node in the binary search tree
class BSTNode {
public:
  int id;         // The ID of the node
  BSTNode *left;  // Pointer to the left child
  BSTNode *right; // Pointer to the right child

  BSTNode(const int &id); // Constructor to initialize the node with an ID
};

#endif
