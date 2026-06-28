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
    ListNode* addTwoNumbers(ListNode* l1, ListNode* l2) {
        ListNode* temp1 = l1;
        ListNode* temp2 = l2;
        ListNode* tail = NULL; // last node jo process hua
        int carry = 0;
        while (temp1 != NULL && temp2 != NULL) {
            int sum = temp1->val + temp2->val + carry;
            temp1->val = sum % 10;
            carry = sum / 10;
            tail = temp1;
            temp1 = temp1->next;
            temp2 = temp2->next;
        }
        while (temp1 != NULL) {
            int sum = temp1->val + carry;
            temp1->val = sum % 10;
            carry = sum / 10;
            tail = temp1;
            temp1 = temp1->next;
        }
        while (temp2 != NULL) {
            int sum = temp2->val + carry;
            temp2->val = sum % 10;
            carry = sum / 10;
            tail->next = temp2; // l2 ke baki nodes ko l1 se attach karo
            tail = temp2;
            temp2 = temp2->next;
        }
        if (carry == 1) {
            tail->next = new ListNode(1);
        }
        return l1;
    }
};