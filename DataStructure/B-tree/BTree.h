#ifndef BTREE_H
#define BTREE_H
#include <iostream>
class TreeNode {
private:
    int *keys;  // An array of keys
    int t; // Minimum degree
    TreeNode **C;    // An array of child pointers
    int n; // Current number of keys
    bool leaf; // Is true when node is lead. Otherwise false
public:
    TreeNode(int temp, bool bool_leaf);
    // A function to traverse all nodes in a subtree rooted with this node
    void traverse();

    //Function to search key k in subtree rooted with this node
    TreeNode * search(int k); //returns NULL if k is not present

    // A function that returns the index of the first key that is greater or
    // equal to k
    int findKey(int k);

    // A utility funtion to insert a new key in this node
    // The assumption is, the node must be non-full when
    // this funciton is called
    void insertNonFull(int k);

    // A utility function to split the child y of this node
    // Note that y must be full when this function is called
    void splitChild(int i, TreeNode *y);

    // A wrapper function to remove the key k in subtree rooted with this node.
    void remove(int k);

    // A function to remove the key persent in idx-th postion in this node
    // this node which is a leaf
    void removeFromLeaf(int idx);

    // A function to remove the key present in idx-th position in this node which is
    // a non-leaf node
    void removeFromNonLeaf(int idx);

    // A function to get the predecessor of the key where the key is
    // present in the idx-th positon in the node
    int getPred(int idx);

    // A function to get the successor of the key where the key is present
    // in the idx-th position in the node
    int getSucc(int idx);

    // A funtion to fill up the child node present in the idx-th position
    // in the C[] array if that child has less than t-1 keys
    void fill(int idx);

    // A function to borrow a key from the C[idx-1]-th node and place it
    // in C[idx]th node
    void borrowFromPrev(int idx);

    // A function to borrow a key from the C[idx+1]-th node and place it
    // in C[idx]th node
    void borrowFromNext(int idx);

    // A function to merge idx-th child of the node with (idx+1)th child
    // of the node
    void merge(int idx);


    // Make the BTree friend of this so that we can access private members of this
    // class in BTree functions
    friend class BTree;
};

class BTree {
private:
    TreeNode *root;
    int t;
public:
    BTree(int temp) {
        root = nullptr;
        t = temp;
    }

    void traverse() {
        if (root != nullptr) {
            root->traverse();
        }
    }

    TreeNode *search(int k) {
        return (root == nullptr) ? nullptr : root->search(k);
    }

    //The main function that inserts a new key in this B-Tree
    void insert(int k);
};

#endif
