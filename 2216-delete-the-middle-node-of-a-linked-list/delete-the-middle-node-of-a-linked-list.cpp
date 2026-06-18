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
    int getLength(ListNode* head) {
        ListNode* temp = head;
        int count = 0;
        while (temp != NULL) {
            count++;
            temp = temp->next;
        }
        return count;
    }
    ListNode* deleteMiddle(ListNode* head) {
        if (head == NULL || head->next == NULL) {
            return NULL;
        }
        int len = getLength(head);
        ListNode* prev = head;
        for (int i = 0; i < len / 2 - 1 && prev != NULL; i++) {
            prev = prev->next;
        }
        ListNode* curr = prev->next;
        ListNode* forward = curr->next;
        prev->next = curr->next;
        curr->next = NULL;
        return head;
    }
};