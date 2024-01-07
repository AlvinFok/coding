#include<iostream>

using namespace std;




// Definition for a binary tree node.
struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
};


TreeNode* invertTree(TreeNode* root) {
    if(root == NULL)return root;
    invertTree(root->left);
    invertTree(root->right);
    TreeNode *tmp = root->right;
    root->right = root->left;
    root->left = tmp;
    return root;
}


int main(){
    return 0;
}

