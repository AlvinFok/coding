#include<iostream>



// Definition for a binary tree node.
struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
};

int xlvl = -1, ylvl = -2, xParent = 0, yParent = 0;

void dfs(TreeNode* root, int x, int y, int depth, int parent){
    if(!root) return;

    if(root->val == x){
        xlvl = depth;
        xParent = parent;
    }

    else if(root->val == y){
        ylvl = depth;
        yParent = parent;
    }

    else{
        dfs(root->left, x, y, depth + 1, root->val);
        dfs(root->right, x, y, depth + 1, root->val);
    }
}

bool isCousins(TreeNode* root, int x, int y) {
    dfs(root, x, y, 0, -1);
    return (xlvl == ylvl && xParent != yParent) ? true : false;
}


int main(int argc, char const *argv[])
{
    /* code */
    return 0;
}
