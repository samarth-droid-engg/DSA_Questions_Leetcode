/*
// Definition for a Node.
class Node {
public:
    int val;
    Node* prev;
    Node* next;
    Node* child;
};
*/

class Solution {
public:
    Node* solve(Node* head) {
        Node* curr = head;
        Node* tail = head;
        while (curr != NULL) {
            tail = curr;
            if (curr->child != NULL) {
                Node* nextNode = curr->next;
                Node* newHead = curr->child;
                Node* newTail = solve(newHead);
                newTail->next = nextNode;
                if (nextNode) {
                    nextNode->prev = newTail;
                }
                newHead->prev = curr;
                curr->next = newHead;
                curr->child = NULL;
                tail = newTail;
                curr = newTail;
            }
            curr = curr->next;
        }
        return tail;
    }
    Node* flatten(Node* head) {
        if (head == NULL) {
            return NULL;
        }
        solve(head);
        return head;
    }
};