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
    ListNode* deleteDuplicates(ListNode* head) {
        ListNode* temp = head;
        ListNode* prev = NULL;
        int data = INT_MIN;
        while (temp != NULL) {
            if (temp->val == data) {
                prev->next = temp->next;
                temp = prev->next;
            } else {
                data = temp->val;
                prev = temp;
                temp = temp->next;
            }
        }
        return head;
    }
};