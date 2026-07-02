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
    ListNode* partition(ListNode* head, int x) {
        if (head == NULL || head->next == NULL) {
            return head;
        }
        ListNode* small = NULL;
        ListNode* greater = NULL;
        ListNode* greaterHead = NULL;
        ListNode* smallHead = NULL;
        ListNode* temp = head;
        while (temp != NULL) {
            if (temp->val < x) {
                if (smallHead == NULL) {
                    smallHead = temp;
                    small = smallHead;
                    temp = temp->next;
                    small->next = NULL;
                } else {
                    small->next = temp;
                    temp = temp->next;
                    small = small->next;
                    small->next = NULL;
                }
            } else {
                if (greaterHead == NULL) {
                    greaterHead = temp;
                    greater = greaterHead;
                    temp = temp->next;
                    greater->next = NULL;
                } else {
                    greater->next = temp;
                    temp = temp->next;
                    greater = greater->next;
                    greater->next = NULL;
                }
            }
        }
        if (greaterHead == NULL) {
            return smallHead;
        } else if (smallHead == NULL) {
            return greaterHead;
        } else {
            small->next = greaterHead;
            return smallHead;
        }
    }
};