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

/*
最后一步可以是 

1. (p2 = prev)把next = p1->next 拿出来存着，然后把p1->next设为  p2->next, p2->next和p2->next->next 锻炼
 再把之前存的next放在p1->next->next后面，p1前进两位

 2. (p2 = prev->next) 先把下一个p2放在prev->next, 把P1->next 放在p2->next, p1->next = p2, p
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
        ListNode *p1 = head, *p2 = prev->next;
        while(p1!=prev){ 
            prev->next = p2->next; //先换pre
            p2->next = p1->next; //p2 后面接p1-Next
            p1->next = p2;  //p1 后面接p2
            p1 = p1->next->next; //p1 往后走一位
            p2 = prev->next; //p2 往后走一位
        }
    }
};




class Solution {
public:
    void reorderList(ListNode* head){
        if (!head || !head->next) return;

        // find the middle node: O(n)
        ListNode *p1 = head, *p2 = head->next;
        while (p2 && p2->next) {
            p1 = p1->next;
            p2 = p2->next->next;
        }

        // cut from the middle and reverse the second half: O(n)
        ListNode *head2 = p1->next;
        p1->next = NULL;
    
        p2 = head2->next;
        head2->next = NULL;
        /*
        p1 = 3
        p2 = 5->6
        head2 = 4
        */
        while (p2) {
            /*
            p2 = 5-6

            p1 = p2->next;   p1 = 6
            p2->next = head2; p2 = 5-4
            head2 = p2;     head2 = 5-4
            p2 = p1;        p2 = 6

            p2 = 6
            p1 = p2->next;   p1 = null
            p2->next = head2; p2 = 6-5-4
            head2 = p2;     head2 = 6-5-4
            p2 = p1;        p2 = null

            
            */
            p1 = p2->next;
            p2->next = head2; //head2在p2这个点之前存好的点（倒叙的）
            head2 = p2;//head2 是包括现在的点，倒叙的
            p2 = p1;
        }

        // merge two lists: O(n)
        for (p1 = head, p2 = head2; p1; ) {
            /*
                p1 1 p2 6
                p1 6 p2 2
                p1 2 p2 5
                p1 5 p2 3
                p1 3 p2 4
                p1 4 p2 null
            */
            auto t = p1->next;
            p1 = p1->next = p2;
            p2 = t;
        }
    }
};