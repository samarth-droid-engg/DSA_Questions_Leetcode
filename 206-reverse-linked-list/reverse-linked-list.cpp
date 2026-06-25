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
    ListNode* solve(ListNode* curr, ListNode* prev) {
        if (curr == NULL) {
            return prev;
        }
        ListNode* temp = curr->next;
        curr->next = prev;
        prev = curr;
        curr = temp;
        return solve(curr, prev);
    }
    ListNode* reverseList(ListNode* head) {
        ListNode* prev = NULL;
        ListNode* curr = head;
        return solve(curr, prev);
    }
};