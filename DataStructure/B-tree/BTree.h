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
    void insertNonFull(int k);
    void splitChild(int i, TreeNode *y);

    // A function to traverse all nodes in a subtree rooted with this node
    void traverse();

    // A function to traverse all nodes in a subtree rooted with this node
    TreeNode * search(int k); //returns NULL if k is not present

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

    void insert(int k);
};

#endif
