/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode(int x) : val(x), next(NULL) {}
 * };
 */
class Solution {
public:
    bool isCyclePresent(ListNode*& head, ListNode*& meet) {
        ListNode* slow = head;
        ListNode* fast = head;
        while (fast != NULL && fast->next != NULL) {
            slow = slow->next;
            fast = fast->next->next;
            if (slow == fast) {
                meet = slow;
                return true;
            }
        }
        return false;
    }
    ListNode* detectCycle(ListNode* head) {
        ListNode* meet = NULL;
        if (!isCyclePresent(head, meet))
            return NULL;
        ListNode* fast = head;
        while (fast != NULL) {
            if (fast == meet)
                return fast;
            fast = fast->next;
            meet = meet->next;
        }
        return NULL;
    }
};