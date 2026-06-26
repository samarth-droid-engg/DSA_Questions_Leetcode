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
    ListNode* reverseKGroup(ListNode* head, int k) {
        int count = 0;
        ListNode* temp = head;
        while (temp != NULL && count < k) {
            temp = temp->next;
            count++;
        }
        if (count == k) {
            // Now reverse the list:
            ListNode* prev = NULL;
            ListNode* curr = head;
            ListNode* forward = NULL;
            // K nodes ka reverse
            int i = 0;
            while (i < k) {
                forward = curr->next;
                curr->next = prev;
                prev = curr;
                curr = forward;
                i++;
            }
            ListNode* recursionHead = reverseKGroup(forward, k);
            head->next = recursionHead;
            return prev;
        } else {
            return head;
        }
    }
};