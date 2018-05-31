/*
141. Linked List Cycle

Given a linked list, determine if it has a cycle in it.

Follow up:
Can you solve it without using extra space?
*/

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
    bool hasCycle(ListNode *head) {
        ListNode *faster = head;
        while(faster && faster->next){
            faster = faster->next->next;
            head = head->next;
            if(faster ==head) return true;
        }
        return false;
    }
};


class Solution {
public:
    bool hasCycle(ListNode *head) 
{
    ListNode *fast;
    fast = head;
    while (head)
    {
        head = head->next;
        if (fast->next && fast->next->next)
            fast = fast->next->next;
        else
            return false;
            
        if (fast == head)
            return true;
    }
    
    return false;
}
};