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
    vector<vector<int>> zigzagLevelOrder(TreeNode* root) {
        if (root == NULL) {
            return {};
        }
        vector<vector<int>> ans;
        bool flag = 1;
        queue<TreeNode*> q;
        q.push(root);

        while (!q.empty()) {
            vector<int> temp;
            int sz = q.size();
            // if (flag) {
            for (int i = 0; i < sz; i++) {
                TreeNode* curr = q.front();
                temp.push_back(curr->val);
                q.pop();
                if (curr->left != NULL) {
                    q.push(curr->left);
                }
                if (curr->right != NULL) {
                    q.push(curr->right);
                }
            }
            // }
            if (!flag)
                reverse(temp.begin(), temp.end());
            flag = !flag;
            ans.push_back(temp);
        }
        return ans;
    }
};