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
    ListNode* detectCycle(ListNode* head) {
        // Approach:Use of set, better from map saving some space
        unordered_set<ListNode*> visited;
        ListNode* temp = head;
        while (temp != nullptr) {
            if (visited.count(temp)) {
                return temp;
            }
            visited.insert(temp);
            temp = temp->next;
        }
        return nullptr;
    }
};