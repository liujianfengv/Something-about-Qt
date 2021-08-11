#include <iostream>
#include <vector>
using namespace std;
class TreeNode {
    friend class BSTree;
public:
    TreeNode(int val) {
        _data = val;
        _left = _right = nullptr;
    }
    void insert(int val) {
        if (val == _data) {
            return;
        } else if (val > _data) {
            if (_right) {
                _right->insert(val);
            } else {
                _right = new TreeNode(val);
            }
        } else {
            if (_left) {
                _left->insert(val);
            } else {
                _left = new TreeNode(val);
            }
        }
    }
    void inOrder() {
        if (_left) {
            _left->inOrder();
        }
        cout<<_data<<endl;
        if (_right) {
            _right->inOrder();
        }
        return;
    }
    TreeNode* findMin() {
        TreeNode* tmp = this;
        while (tmp->_left != nullptr) {
            tmp = tmp->_left;
        }
        return tmp;
    }
private:
    int _data;
    TreeNode *_left;
    TreeNode *_right;
};

class BSTree {
public:
    BSTree();
    void insertNode(int val);
    void inOrder();
    void deleteNode(int val);
private:
    TreeNode* deleteNodeImp(TreeNode *root, int key);
private:
    TreeNode *_root;
};
BSTree::BSTree()
{
    _root = nullptr;
}
void BSTree::insertNode(int val)
{
    if (!_root) {
        _root = new TreeNode(val);
    }
    _root->insert(val);
}

void BSTree::inOrder()
{
    _root->inOrder();
}

void BSTree::deleteNode(int val)
{
    _root = deleteNodeImp(_root, val);
}

TreeNode *BSTree::deleteNodeImp(TreeNode *root, int key)
{
    if (root == nullptr) {
        return root;
    }
    if (key < root->_data) {
        root->_left = deleteNodeImp(root->_left, key);
    } else if (key > root->_data) {
        root->_right = deleteNodeImp(root->_right, key);
    } else {
        TreeNode *res;
        if (root->_left == nullptr) {
            res = root->_right;
            delete root;
            return res;
        } else if (root->_right == nullptr){
            res = root->_left;
            delete root;
            return res;
        }
        TreeNode *min = root->_right->findMin();
        root->_data = min->_data;
        root->_right = deleteNodeImp(root->_right, root->_data);
    }
    return root;
}
int main()
{
    BSTree tree;
    vector<int> data = {6, 5, 8, 4, 7, 9, 2, 1, 3};
    for (auto & i : data) {
        tree.insertNode(i);
    }
    tree.deleteNode(3);
    tree.inOrder();
    return 0;
}
