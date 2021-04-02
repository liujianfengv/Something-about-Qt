#ifndef BTREE_H
#define BTREE_H
#include <iostream>
class TreeNode {
private:
    int *keys;
    int t;
    TreeNode **C;
    int n;
    bool leaf;
public:
    TreeNode(int temp, bool bool_leaf);
    void insertNonFull(int k);
    void splitChild(int i, TreeNode *y);
    void traverse();
    TreeNode * search(int k);
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
