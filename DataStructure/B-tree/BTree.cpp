#include "BTree.h"
TreeNode::TreeNode(int t1, bool leaf1) {
    t = t1;
    leaf = leaf1;

    keys = new int [2 * t -1];
    C = new TreeNode*[2 * t];

    n = 0;
}

void TreeNode::traverse() {
    // There are n keys and n+1 children, travers througn n keys
    // and first n children
    int i;
    for (i = 0; i < n; ++i) {
        // If this is not leaf, then before printing key[i],
        // traverse the subtree rooted with child C[i]
        if (leaf == false) {
            C[i]->traverse();
        }
        std::cout << " " << keys[i];
    }
    // Print the subtree rooted with last child
    if (leaf == false) {
        C[i]->traverse();
    }
}

TreeNode *TreeNode::search(int k) {
    // Find the first key greater than or equal to k
    int i = 0;
    while (i < n && k > keys[i]) {
        i++;
    }
    // If the found key os equal to k, return this node
    if (keys[i] == k) {
        return this;
    }

    // If key is not found here and this is a leaf node
    if (leaf == true)
        return nullptr;

    // Go to the appropriate child
    return C[i]->search(k);
}

int TreeNode::findKey(int k)
{
    int idx = 0;
    while (idx < n && keys[idx] < k) {
        ++idx;
    }
    return idx;
}

void BTree::insert(int k) {

    // If tree is empty
    if (root == nullptr) {
        // Allocate memory for root
        root = new TreeNode(t, true);
        root->keys[0] = k;
        root->n = 1;
    } else { // If tree is not empty
        if (root->n == 2 * t -1) { // If root is full, then tree grows in height
            // Allocate memory for new root
            TreeNode *s = new TreeNode(t, false);

            // Make old root as child of new root
            s->C[0] = root;

            // Split the old root and move 1 key to the new root
            s->splitChild(0, root);

            // New root has two children now. Decide which of the two children
            // is going to have new key
            int i = 0;
            if (s->keys[0] < k) {
                i++;
            }
            s->C[i]->insertNonFull(k);

            // Change root
            root = s;
        } else { // If root is not full, call insertNonFull for root
            root->insertNonFull(k);
        }
    }
}

void TreeNode::insertNonFull(int k) {
    // Initialize index as index of rightmost element
    int i = n - 1;

    // If this is a leaf node
    if (leaf == true) {
        // The following loop does two things
        // a) Finds the location of new key to be inserted
        // b) Moves all greater keys to one place ahead
        while (i >= 0 && keys[i] > k) {
            keys[i + 1] = keys[i];
            i--;
        }
        // Insert the new key at found location
        keys[i + 1] = k;
        n = n + 1;
    } else { // If this node is not leaf

        // Find the child which is going to have the new key
        while (i >= 0 && keys[i] > k) {
            i--;
        }

        // See if the found child is full
        if (C[i + 1]->n == 2 * t -1) {
            // If the child is full, then split it
            splitChild(i + 1, C[i + 1]);

            // After split, the middle key of C[i] goes up and C[i]
            // is splitted into two. See which of the two is going to
            // have the new key
            if (keys[i + 1] < k) {
                i++;
            }
        }
        C[i + 1]->insertNonFull(k);
    }
}

void TreeNode::splitChild(int i, TreeNode *y) {
    // Create a new node which is going to store (t-1) keys of y
    TreeNode *z = new TreeNode(y->t, y->leaf);
    z->n = t - 1;

    // Copy the last (t-1) keys of y to z
    for (int j = 0; j < t - 1; ++j) {
        z->keys[j] = y->keys[j + t];
    }

    //Copy ths last t children of y to z
    if (y->leaf == false) {
        for (int j = 0; j < t; ++j) {
            z->C[j] = y->C[j + t];
        }
    }

    // Reduce the number of keys in y
    y->n = t - 1;

    // Since this node is going to have a new child, create space of new child
    for (int j = n; j >= i + 1; --j) {
        C[j + 1] = C[j];
    }

    // Link the new child to this node
    C[i + 1] = z;

    // A key of y will move to this node. Find the location of new kye
    // and move all greater keys one space ahead
    for (int j = n - 1; j >= i; --j) {
        keys[j + 1] = keys[j];
    }

    // Copy the middle key of y to this node
    keys[i] = y->keys[t - 1];

    // Increment count of keys in this node
    n = n + 1;
}

void TreeNode::remove(int k)
{
    int idx = findKey(k);

    // The key to be removed is present in this node
    if (idx < n && keys[idx] == k) {
        // If the node is a leaf node - removeFromLeaf is called
        // Otherwise, removeFromNonLeaf function is called
        if (leaf) {
            removeFromLeaf(idx);
        } else {
            removeFromNonLeaf(idx);
        }
    } else {
        // If this node is a leaf node, then the key is not present in tree
        if (leaf) {
            std::cout << "The key" << k <<" is does not exist in the tree" << std::endl;
            return;
        }

        // The key to be removed is present in the sub-tree rooted with this node
        // The flag indicates whether the key is persent in the sub-tree rooted with the last
        // child of this node
        bool flag = ( (idx == n) ? true : false);

        // If the child where the key is supposed to exist has less that t keys,
        // we fill that child
        if (C[idx]->n < t) {
            fill(idx);
        }

        // If the last child has been merged, it must have merged with the previoud
        // child and so we recurse on the (idx - 1)th child. Else, we recurse on the
        // (idx)th child which now has atleast t keys
        if (flag && idx > n) {
            C[idx - 1]->remove(k);
        } else {
            C[idx]->remove(k);
        }
    }
    return;
}

void TreeNode::removeFromLeaf(int idx)
{
    // Move all the keys after idx-th pos one place backward
    for (int i = idx + 1; i < n; ++i) {
        keys[i - 1] = keys[i];
    }
    // Reduce the count of keys
    n--;
    return;
}
