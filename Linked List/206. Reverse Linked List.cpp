/*
206. Reverse Linked List

Reverse a singly linked list.

Example:

Input: 1->2->3->4->5->NULL
Output: 5->4->3->2->1->NULL
Follow up:

A linked list can be reversed either iteratively or recursively. Could you implement both?


*/

/*
Iterative Solution 1: 
设prev, prev = new ListNode(0), prev永远指向0,, head 指向最开始的位置， （先挂head->next点再prev->next后，再把prev->next放在prev->next->next后面）
每次把head->next 放在prev->next的位置（0后面的位置）, 然后断开head->next和后面的点, 再把之前prev->next（在head->next此点之前弄好的点） append到prev->next->next

Iterative Solution 2: 
设prev, prev = new ListNode(0), prev永远指向0,, head 指向最开始的位置，（先断链，把prev->next放在head->next后面，再挂head->next在prev->next后面）
每次把next = head->next, 断了head->next 和head->next->next的链，把next->next = prev->next（把之前弄好的放在将要提前的点上），把next挂在prev的后面 


Iterative Solution 3: 
prev = null
存好next =  head->next
每次把head直接设为prev的头,  head->next = prev, prev = head;(prev是在head>next此点之前弄好的点）)
再把head 往前进一位, head = next;


*/

class Solution {
public:
    ListNode* reverseList(ListNode* head) {
        ListNode* new_head = new ListNode(0);
        new_head -> next = head;
        ListNode* pre = new_head;
        ListNode* cur = head; 
        while (cur && cur -> next) {
        /*
        cur会一直在1上，一直到最后一位
        (0)-1-2-3-4-5
        prev 在0上, cur在1上
        ListNode* temp = pre -> next;   temp = 1-2-3-4-5  //把当前的cur点存好
        pre -> next = cur -> next;  prev = 0-2-3-4-5, cur = 1-2-3-4-5  //把下一个点提上来
        cur -> next = cur -> next -> next;     cur = 1-3-4-5  temp = 1-3-4-5 prev = 0-2-3-4-5 //消除提上来点的next

        pre -> next -> next = temp;     prev = 0-2-1-3-4-5 放在提上来点的下一位 

step 2:  把cur->next 提上来放在
        prev 在0上, cur在1上
        cur = 1-3-4-5
        ListNode* temp = pre -> next;   temp = 2-1-3-4-5  //把当前的cur点存好
        pre -> next = cur -> next;  prev = 0-3-4-5, cur = 1-3-4-5  //把下一个点提上来
        cur -> next = cur -> next -> next;     cur = 1-4-5， temp = 2-1-4-5  prev = 0-3-4-5 //消除下一个点的next

        pre -> next -> next = temp;     prev = 0-3-2-1-4-5 放在提上来点的下一位

step 3:
        prev 在0上, cur在1上
        cur = 1-4-5
        ListNode* temp = pre -> next;   temp = 3-2-1-4-5  //把当前的cur点存好
        pre -> next = cur -> next;  prev = 0-4-5, cur = 1-4-5  //把下一个点提上来
        cur -> next = cur -> next -> next;     cur = 1-5， temp = 3-2-1-5  prev = 0-4-5 //消除下一个点的next

        pre -> next -> next = temp;     prev = 0-4-3-2-1-5 放在提上来点的下一位

step 4:
        prev 在0上, cur在1上
        cur = 1-5
        ListNode* temp = pre -> next;   temp = 4-3-2-1-5  //把当前的cur点存好
        pre -> next = cur -> next;  prev = 0-5, cur = 1-5  //把下一个点提上来
        cur -> next = cur -> next -> next;     cur = 1-null， temp = 4-3-2-1-null prev = 0-5 //消除下一个点的next

        pre -> next -> next = temp;     prev = 0-5-4-3-2-1 放在提上来点的下一位
        */

            ListNode* temp = pre -> next;
            pre -> next = cur -> next;
            cur -> next = cur -> next -> next; 
            pre -> next -> next = temp;
        }
        return new_head -> next;
    }
};

class Solution {
public:
    ListNode* reverseList(ListNode* head) {
        ListNode dummy(0);
        ListNode* res = &dummy;
        while(head){ //process head
            ListNode* next = head->next;
            head->next = res->next;
            res->next = head;
            head = next;
        }
        return dummy.next;
    }
};

class Solution {
public:
    ListNode* reverseList(ListNode* head) {
        ListNode dummy(0);
        ListNode* res = &dummy;
        res->next = head;
        while(head && head->next){ //process head->next
            ListNode* tmp = head->next;
            head->next = head->next->next; 
            tmp->next = res->next;
            res->next = tmp;
        }
        
        return dummy.next;
    }
};


class Solution {
public:
    ListNode* reverseList(ListNode* head) {
        ListNode* pre = NULL;
        while (head) {
            /*
            prev都是指向head最前面, 每一次先存好head next, prev是之前已经倒过顺序的部分, 然后把prev 挂在head->next 上, prev = head head再前进一位
            1-2-3-4-5
            ListNode* next = head -> next;  next 2-3-4-5
            head -> next = pre;  head 1-null
            pre = head;  pre = 1-null
            head = next  head = 2-3-4-5

            head  2-3-4-5
            ListNode* next = head -> next;  next 3-4-5
            head -> next = pre;  head 2-1-null
            pre = head;  pre = 2-1-null
            head = next  head = 3-4-5

            */
            ListNode* next = head -> next;
            head -> next = pre;
            pre = head;
            head = next;
        } 
        return pre;
    }
};

class Solution {
public:
    ListNode* reverseList(ListNode* head) {
        ListNode *pre = NULL;
        while (head != NULL) {
            ListNode *temp = head;
            head = head->next;
            temp->next = pre;
            pre = temp;
        }
        return pre;
    }
};
/*

The basic idea of this recursive solution is to reverse all the following nodes after head. Then we need to set head to be the final node in the reversed list. 
We simply set its next node in the original list (head -> next) to point to it and sets its next to be NULL.
*/

/*
4-5  
node = 5, 
head->next->next = head;   4-5-4-5-4-5
head->next = null   5-4-null
return node 

3->4<-5
node = 4<-5;
head->next->next = head   node:  3<-4<-5, head 3->4-3-4
head->next = null   4-3 

2 -> 3 
      <- 4 <- 5
node = 5 -> 4 -> 3
head->next->next = head;   
                    2 -> 3 -> 2 -> 3  
                         <- 4 <- 5
head->next = null   3 -> 2 
                    <- 4 <- 5

return 5

*/

class Solution {
public:   
    ListNode* reverseList(ListNode* head) {
        if (!head || !(head -> next)) return head;
        ListNode* node = reverseList(head -> next);
        head -> next -> next = head;
        head -> next = NULL;
        return node; 
    }
}; 




