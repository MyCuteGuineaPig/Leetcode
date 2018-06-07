/*

203. Remove Linked List Elements
Remove all elements from a linked list of integers that have value val.

Example:

Input:  1->2->6->3->4->5->6, val = 6
Output: 1->2->3->4->5
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
    ListNode* removeElements(ListNode* head, int val) {
        ListNode dummy(0);
        dummy.next = head;
        ListNode* cur = &dummy;
        while(cur->next){
            if(cur->next->val == val)
                cur->next = cur->next->next;
            else cur = cur->next;
        }
        
        return dummy.next;
    }
};

//Free memory 
class Solution {
public:
    ListNode* removeElements(ListNode* head, int val) {
        ListNode dummy(0);
        dummy.next = head;
        ListNode* cur = &dummy;
        while(cur->next){
            if(cur->next->val == val){
                ListNode *next = cur->next;
                cur->next = cur->next->next;
                delete next;
            }
            else cur = cur->next;
        }
        
        return dummy.next;
    }
};


class Solution {
public:
    ListNode* removeElements(ListNode* head, int val) {
        ListNode** cur = &head;
        while(*cur){
            if((*cur)->val == val)
                *cur = (*cur)->next;
            else cur = &((*cur)->next);
        }
        
        return head;
    }
};


class Solution {
public:
    ListNode* removeElements(ListNode* head, int val) {
        ListNode dummy{0};
        dummy.next = head;
        auto *prev = &dummy, *cur = dummy.next;
        
        while (cur) {
            if (cur->val == val) {
                prev->next = cur->next;
                delete cur;
            } else {
                prev = cur;
            }
            cur = cur->next;
        }
        return dummy.next;
    }
};