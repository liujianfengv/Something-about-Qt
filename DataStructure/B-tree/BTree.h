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

    int findKey(int k);

    // A utility funtion to insert a new key in this node
    // The assumption is, the node must be non-full when
    // this funciton is called
    void insertNonFull(int k);

    // A utility function to split the child y of this node
    // Note that y must be full when this function is called
    void splitChild(int i, TreeNode *y);

    void remove(int k);

    void removeFromLeaf(int idx);

    void removeFromNonLeaf(int idx);

    int getPred(int idx);

    int getSucc(int idx);

    void fill(int idx);

    void borrowFromPrev(int idx);

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
