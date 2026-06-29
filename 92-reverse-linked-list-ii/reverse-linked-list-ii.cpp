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
    ListNode* reverse(ListNode* head) {
        ListNode* prev = NULL;
        ListNode* curr = head;

        while (curr != NULL) {
            ListNode* forward = curr->next;
            curr->next = prev;
            prev = curr;
            curr = forward;
        }

        return prev;
    }

    ListNode* reverseBetween(ListNode* head, int left, int right) {

        if (head == NULL || left == right)
            return head;

        ListNode* leftPrev = NULL;
        ListNode* leftNode = NULL;
        ListNode* rightNode = NULL;
        ListNode* rightNext = NULL;

        ListNode* temp = head;
        int pos = 1;

        while (temp != NULL) {

            if (pos == left - 1)
                leftPrev = temp;

            if (pos == left)
                leftNode = temp;

            if (pos == right) {
                rightNode = temp;
                rightNext = temp->next;
                break;
            }

            temp = temp->next;
            pos++;
        }

        // Detach the sublist
        if (leftPrev != NULL)
            leftPrev->next = NULL;

        rightNode->next = NULL;

        // Reverse detached list
        ListNode* newHead = reverse(leftNode);

        // Attach back
        if (leftPrev != NULL)
            leftPrev->next = newHead;
        else
            head = newHead;

        // leftNode becomes the tail after reversal
        leftNode->next = rightNext;

        return head;
    }
};