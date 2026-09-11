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
    int postIndex;

    TreeNode* buildTree(vector<int>& inorder, vector<int>& postorder,
                        int inStart, int inEnd) {
        if (inStart > inEnd) {
            return NULL;
        }
        int rootValue = postorder[postIndex--];
        TreeNode* root = new TreeNode(rootValue);

        int mid = mp[rootValue];

        root->right = buildTree(inorder, postorder, mid + 1, inEnd);
        root->left = buildTree(inorder, postorder, inStart, mid - 1);

        return root;
    }

    TreeNode* buildTree(vector<int>& inorder, vector<int>& postorder) {
        postIndex = postorder.size() - 1;
        for (int i = 0; i < inorder.size(); i++) {
            mp[inorder[i]] = i;
        }
        return buildTree(inorder, postorder, 0, inorder.size() - 1);
    }
};