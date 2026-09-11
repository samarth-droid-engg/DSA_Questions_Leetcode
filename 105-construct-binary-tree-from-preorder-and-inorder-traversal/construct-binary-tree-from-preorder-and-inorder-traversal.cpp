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
    unordered_map<int, int> mp;
    int preIndex;

    TreeNode* buildTree(vector<int>& preorder, vector<int>& inorder) {
        mp.clear();
        for (int i = 0; i < inorder.size(); i++) {
            mp[inorder[i]] = i;
        }
        return buildTree(preorder, 0, inorder.size() - 1);
    }

    TreeNode* buildTree(vector<int>& preorder, int left, int right) {
        if (left > right)
            return NULL;

        int rootValue = preorder[preIndex++];
        TreeNode* root = new TreeNode(rootValue);

        int mid = mp[rootValue];

        root->left = buildTree(preorder, left, mid - 1);
        root->right = buildTree(preorder, mid + 1, right);

        return root;
    }
};