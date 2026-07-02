/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode() : val(0), next(nullptr) {}
 *     ListNode(int x) : val(x), next(nullptr) {}
 *     ListNode(int x, ListNode *next) : val(x), next(next) {}
 * };
 */
class Solution {
public:
    vector<ListNode*> splitListToParts(ListNode* head, int k) {
        // No. of nodes
        int count = 0;
        ListNode* temp = head;
        while (temp != NULL) {
            count++;
            temp = temp->next;
        }
        // Now find sizes of prts
        int idealPartSize = count / k;
        int extraNodes = count % k; // Divide it part by part

        vector<ListNode*> ans(k, nullptr);
        temp = head;
        for (int i = 0; i < k && temp != NULL; i++) {
            ans[i] = temp;
            int actualPartSize = idealPartSize + (extraNodes-- > 0 ? 1 : 0);
            ListNode* vec = ans[i];
            for (int j = 1; j < actualPartSize; j++) {
                vec->next = temp->next;
                temp = temp->next;
                vec = vec->next;
            }
            if (temp != NULL)
                temp = temp->next;
            vec->next = NULL;
        }
        return ans;
    }
};