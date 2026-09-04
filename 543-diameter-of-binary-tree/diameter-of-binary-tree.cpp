/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode() : val(0), left(nullptr), right(nullptr) {}
 *     TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
 *     TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left),
 * right(right) {}
 * };
 */
class Solution {
public:
    int diameter(TreeNode* root, int& maxiAns) {
        if (root == NULL) {
            return 0;
        }
        int lh = diameter(root->left, maxiAns);
        int rh = diameter(root->right, maxiAns);

        maxiAns = max(maxiAns, lh + rh);
        return 1 + max(lh, rh);
    }
    int diameterOfBinaryTree(TreeNode* root) {
        int maxiAns = INT_MIN;
        diameter(root, maxiAns);
        return maxiAns;
    }
};