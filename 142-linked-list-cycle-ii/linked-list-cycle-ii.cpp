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
    ListNode *detectCycle(ListNode *head) {
        //Approach:Use of maps
        unordered_map<ListNode*, bool> visited;
        ListNode* temp = head;
        while(temp!=nullptr){
            if(visited[temp]){
                ListNode* newNode = temp;
                temp = temp->next;
                newNode->next=NULL;
                return newNode;
            }
            else{
                visited[temp] = true;
                temp = temp->next;
            }
        }
        return nullptr;
    }
};