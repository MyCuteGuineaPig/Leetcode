/*
83. Remove Duplicates from Sorted List


Given a sorted linked list, delete all duplicates such that each element appear only once.

Example 1:

Input: 1->1->2
Output: 1->2
Example 2:

Input: 1->1->2->3->3
Output: 1->2->3
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
    ListNode* deleteDuplicates(ListNode* head) {
        ListNode *cur = head;
        while(cur && cur->next){
            if(cur->val == cur->next->val){
                cur->next = cur->next->next;
            }else{
                cur = cur->next;
            }
        }
        return head;
    }
};


class Solution {
public:
    ListNode* deleteDuplicates(ListNode* head) {
        ListNode *cur = head;
        while(cur){
            while(cur->next && cur->next->val == cur->val) cur->next = cur->next->next;
            cur = cur->next;
        }
        return head;
    }
};

/*
Cannot use Recursion, 
I highly doubt if we should use recursion in solving linked list problems. 
We use it for tree because its stack space is O(logn), where n is the number of nodes. 
But it's O(n) space required for linked list, which is very likely to be stack overflow. 

*/