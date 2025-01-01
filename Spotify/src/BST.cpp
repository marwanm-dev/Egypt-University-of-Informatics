#include "../include/BST.h"

// Constructor to initialize the BST with an empty tree (root is nullptr)
BST::BST() : root(nullptr) {}

// Destructor to clear the tree by calling the clear function
BST::~BST() { clear(root); }

// Clears the tree, starting from the root node
void BST::clear() { clear(root); }

// Inserts a new node with the given ID into the BST
void BST::insert(const int &id) {
  BSTNode *newNode = new BSTNode(id); // Create a new node
  if (!root) { // If the tree is empty, the new node becomes the root
    root = newNode;
    return;
  }

  BSTNode *current = root;
  BSTNode *parent = nullptr;
  // Traverse the tree to find the correct position for the new node
  while (current) {
    parent = current;
    if (id < current->id) // Move to the left subtree if the ID is smaller
      current = current->left;
    else // Move to the right subtree if the ID is larger or equal
      current = current->right;
  }
  // Insert the new node as a left or right child based on the ID
  if (id < parent->id)
    parent->left = newNode;
  else
    parent->right = newNode;
}

// Removes the node with the specified ID from the BST
void BST::remove(const int &id) {
  BSTNode *del = root, *tmp = nullptr;

  // Traverse the tree to find the node to delete
  while (del) {
    if (del->id == id)
      break;
    else if (id > del->id) // Move to the right if the ID is greater
      tmp = del, del = del->right;
    else // Move to the left if the ID is smaller
      tmp = del, del = del->left;
  }

  // If the node doesn't exist, return without making changes
  if (!del)
    return;

  // Case 1: Node is a leaf (no children)
  if (!del->left && !del->right) {
    if (tmp) {
      if (tmp->left == del)
        tmp->left = nullptr;
      else
        tmp->right = nullptr;
    } else
      root = nullptr; // Root is being deleted
    delete del;
  }
  // Case 2: Node has one child (either left or right)
  else if (!del->left) {
    if (tmp) {
      if (tmp->left == del)
        tmp->left = del->right;
      else
        tmp->right = del->right;
    } else
      root =
          del->right; // If root is being deleted, update it to the right child
    delete del;
  } else if (!del->right) {
    if (tmp) {
      if (tmp->left == del)
        tmp->left = del->left;
      else
        tmp->right = del->left;
    } else
      root = del->left; // If root is being deleted, update it to the left child
    delete del;
  }
  // Case 3: Node has two children
  else {
    // Find the in-order successor (smallest node in the right subtree)
    BSTNode *sml = del->right;
    while (sml->left)
      sml = sml->left; // Go to the leftmost node in the right subtree
    // Replace the node's ID with the in-order successor's ID
    del->id = sml->id;
    remove(sml->id); // Remove the in-order successor from the tree
  }
}

// Retrieves the IDs in in-order traversal (left, root, right)
void BST::getInOrder(std::queue<int> &ids) const {
  inOrderTraversal(root, ids);
}

// Retrieves the IDs in pre-order traversal (root, left, right)
void BST::getPreOrder(std::queue<int> &ids) const {
  preOrderTraversal(root, ids);
}

// Retrieves the IDs in post-order traversal (left, right, root)
void BST::getPostOrder(std::queue<int> &ids) const {
  postOrderTraversal(root, ids);
}

// Recursively clears the tree starting from the given node
void BST::clear(BSTNode *node) {
  if (!node)
    return;           // Base case: if the node is null, return
  clear(node->left);  // Clear the left subtree
  clear(node->right); // Clear the right subtree
  delete node;        // Delete the current node
}

// Recursively performs an in-order traversal and adds IDs to the queue
void BST::inOrderTraversal(const BSTNode *node, std::queue<int> &ids) const {
  if (!node)
    return;                           // Base case: if the node is null, return
  inOrderTraversal(node->left, ids);  // Traverse left subtree
  ids.push(node->id);                 // Add the node's ID to the queue
  inOrderTraversal(node->right, ids); // Traverse right subtree
}

// Recursively performs a pre-order traversal and adds IDs to the queue
void BST::preOrderTraversal(const BSTNode *node, std::queue<int> &ids) const {
  if (!node)
    return;                            // Base case: if the node is null, return
  ids.push(node->id);                  // Add the node's ID to the queue
  preOrderTraversal(node->left, ids);  // Traverse left subtree
  preOrderTraversal(node->right, ids); // Traverse right subtree
}

// Recursively performs a post-order traversal and adds IDs to the queue
void BST::postOrderTraversal(const BSTNode *node, std::queue<int> &ids) const {
  if (!node)
    return;                            // Base case: if the node is null, return
  postOrderTraversal(node->left, ids); // Traverse left subtree
  postOrderTraversal(node->right, ids); // Traverse right subtree
  ids.push(node->id);                   // Add the node's ID to the queue
}
