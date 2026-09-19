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
    int findBottomLeftValue(TreeNode* root) {
        int num = 0, minD = INT_MAX;
        if (root == NULL) {
            return 0;
        }
        queue<pair<TreeNode*, int>> q;
        q.push({root, 0});
        while (!q.empty()) {
            int n = q.size();
            for (int i = 0; i < n; i++) {
                auto it = q.front();
                q.pop();
                TreeNode* node = it.first;
                int dist = it.second;
                if (dist < minD) {
                    minD = dist;
                    num = node->val;
                }
                if (node->left) {
                    q.push({node->left, dist - 1});
                }
                if (node->right) {
                    q.push({node->right, dist - 1});
                }
            }
        }
        return num;
    }
};
