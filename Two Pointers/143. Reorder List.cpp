/*
143. Reorder List

Given a singly linked list L: L0→L1→…→Ln-1→Ln,
reorder it to: L0→Ln→L1→Ln-1→L2→Ln-2→…

You may not modify the values in the list's nodes, only nodes itself may be changed.

Example 1:

Given 1->2->3->4, reorder it to 1->4->2->3.
Example 2:

Given 1->2->3->4->5, reorder it to 1->5->2->4->3.

*/


/*
Three Steps:
1. Find the middle of the list
2. Reverse the half after middle  1->2->3->4->5->6 to 1->2->3->6->5->4
3. Start reorder one by one  1->2->3->6->5->4 to 1->6->2->5->3->4
*/

class Solution {
public:
    void reorderList(ListNode* head){
        if(!head ||!head->next) return ;
        ListNode *fast = head;
        ListNode *prev = head;
        while(fast->next && fast->next->next){
            fast = fast->next->next;
            prev = prev->next;
        }
        ListNode *cur = prev->next;
        while(cur->next){
            ListNode *temp = prev->next;
            prev->next = cur->next;
            cur->next = cur->next->next;
            prev->next->next = temp;
        }
        ListNode *p1 = head, *p2 = prev;
        while(p1!=prev){ 
            /*
            不用!p2原因是比如1-2-3-4-5-6  head = 1-2-3-6-5-4  p2=3-6-5-4
            第一个循环  1-6-2-3-5-4   p2 = 3-5-4
            第二个循环  1-6-5-2-3-4   p2 = 3-4
            第三个循环 p2 = 3-4,  p1 = 3-4 (p1,p2指向一个object)
            p1next = 4,  p2->next = 4
            p1->next = p2->next, p1 = 3-4, p2 = 3,4
            p2->next = p2->next->next;  p2 = 3-null, p1 = 3-null
            p1->next->next = p1next; p1 = 3-4-4, p2 = 3-4-4
            p1 = p1next   p1 = 4-4
            */
            ListNode *p1next = p1->next;
            p1->next = p2->next; //因为p2在p1 后面，p2中没有p1， 所以先不用断p2的链
            p2->next = p2->next->next;
            p1->next->next = p1next;
            p1 = p1next;
        }
    }
};