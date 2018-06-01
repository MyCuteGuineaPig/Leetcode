/*
92. Reverse Linked List II

Reverse a linked list from position m to n. Do it in one-pass.

Note: 1 ≤ m ≤ n ≤ length of list.

Example:

Input: 1->2->3->4->5->NULL, m = 2, n = 4
Output: 1->4->3->2->5->NULL


*/


/*

再prev->next接到head->next前要断链（head->next = head->next->next）

Iterative solution1: 
建立一个dummy Node, prev指向dummy，head loop 到第m个node(prev指向第m-1个node)
接下来每步存好next = prev->next(在此前已经摆好的顺序), 把每个head->next, 提到prev->next的位置,  
并且断掉head->next 和head->next->next连接，把prev->next->next = next


Iterative solution2: 
建立一个dummy Node, **prev指向dummy，loop head,prev同时指向 第m个node
再建立一个middle node,每次存next = head->next;  head->next = middle(在此前已经摆好的顺序)
middle = head, head =next(下一个node) 
最后在prev第m个node 后面接上所有n后面的node（head，这样middle最后一位后面也接上了n后面的node,因为middle是由head生成的, dummy&middle共享head),
 再修改prev为middle

*/

class Solution {
public:
    ListNode* reverseBetween(ListNode* head, int m, int n) {
        int i = 1;
        ListNode *dummy = new ListNode(0);
        dummy->next = head;
        ListNode *prev = dummy;
        while(i<m){
            i++;
            head = head->next;
            prev = prev->next;
        }
        /*
        1-2-3-4-5  m = 2 n =4, 结果应该为 1-4-3-2-5

        i = 2时， head 指向2, prev指向1
    i = 2: 把2挂前面  
        temp = 2-3-4-5
        prev = 1-3-2-4-5；
        head = 2-4-5

    i = 3  
        temp = 2-4-5
        prev = 1-4-3-2-5；
        head = 2-5
        */
        while(i<n){
            i++;
            ListNode *temp = prev->next;
            prev->next = head->next;
            head->next = head->next->next;
            prev->next->next = temp;
        }
        return dummy->next;
    }
};






class Solution {
public:
    ListNode* reverseBetween(ListNode* head, int m, int n) {
        int i = 1;
        ListNode *dummy = head;
        ListNode **prev = &dummy;
        while(i<m){
            i++;
            head = head->next;
            prev = &((*prev)->next);
        }
        ListNode *middle = NULL;
        /*
        1-2-3-4-5, m = 2, n = 4
        head prev都在2点上，接下来middle 会返回4-3-2
        把2后面挂上head(在n之后的node), middle = 4-3-2-1
        再把当前node 修改为middle
        */
        while(i<=n){  
            i++;
            ListNode *next = head->next;
            head->next = middle;
            middle = head;
            head = next;
        }
        (*prev)->next = head;
        *prev = middle;
        return dummy;
    }
};




class Solution {
public:
    ListNode* reverseBetween(ListNode* head, int m, int n) {
        
        if(m==n)
            return head;
        
        n = n-m;
        ListNode* dummy = new ListNode(-1);
        dummy->next = head;
        
        ListNode* pre = dummy;
        while(--m)pre=pre->next;
        
        ListNode* pStart = pre->next;
        while(n--){
            ListNode *p = pStart->next;
            pStart->next = pStart->next->next;//断了链
            p->next = pre->next; //提前的node上加上prev 后面的 
            pre->next = p;  //把提前的node 放在prev 后面
        }
        return dummy->next;
    }
};