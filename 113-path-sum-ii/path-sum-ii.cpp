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
    void solve(TreeNode* root, int targetSum, vector<vector<int>>& vt,
               vector<int> demo, int sum) {
        if (root == NULL) {
            return;
        }
        sum = sum + root->val;
        demo.push_back(root->val);
        if (root->left == NULL && root->right == NULL) {
            if (sum == targetSum) {
                vt.push_back(demo);
                return;
            } else
                return;
        }
        solve(root->left, targetSum, vt, demo, sum);
        solve(root->right, targetSum, vt, demo, sum);
        return;
    }
    vector<vector<int>> pathSum(TreeNode* root, int targetSum) {
        vector<vector<int>> vt;
        solve(root, targetSum, vt, {}, 0);
        return vt;
    }
};