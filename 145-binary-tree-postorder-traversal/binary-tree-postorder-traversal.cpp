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
    // Iterative approach
    vector<int> postorderTraversal(TreeNode* root) {
        if (root == NULL)
            return {};
        stack<TreeNode*> s1;
        stack<TreeNode*> s2;
        vector<int> postOrder;
        TreeNode* node = root;
        s1.push(node);
        while (true) {
            node = s1.top();
            s1.pop();
            s2.push(node);
            if (node->left != NULL) {
                s1.push(node->left);
            }
            if (node->right != NULL) {
                s1.push(node->right);
            }
            if (s1.empty())
                break;
        }
        while (!s2.empty()) {
            postOrder.push_back(s2.top()->val);
            s2.pop();
        }
        return postOrder;
    }
};