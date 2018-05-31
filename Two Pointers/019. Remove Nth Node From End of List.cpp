/*
19. Remove Nth Node From End of List

Given a linked list, remove the n-th node from the end of list and return its head.

Example:

Given linked list: 1->2->3->4->5, and n = 2.

After removing the second node from the end, the linked list becomes 1->2->3->5.
Note:

Given n will always be valid.

Follow up:

Could you do this in one pass?
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
    ListNode* removeNthFromEnd(ListNode* head, int n) {
        ListNode *dummy = new ListNode(0); 
        //用dummy的原因是防止 input 是[1] 1
        dummy->next = head;
        helper(dummy,n);
        return dummy->next;
    }
    
   int helper(ListNode *&cur, int & n){
        if(!cur) return 0;
        if(helper(cur->next, n) == 1)
            return 1;
        if(n==0) { 
            cur->next = cur->next->next;
            return 1;
        }
        n--;
        return 0;
    }
};


/*
One pass solution
最后前进N-1位，N是linked list length
先前进n，再前进只能是N-1-n, 正好到倒数第n位的前一位
*/

class Solution {
public:
    ListNode* removeNthFromEnd(ListNode* head, int n) {
        ListNode *fast = head;
        ListNode *slow = head;
        for(int i = 0; i<n; i++){ //1-2-3-4-5, fast前进到3的位置，还有两个前进两个
            fast = fast->next;
        }
        if(!fast) return slow->next;
        while(fast->next){ //slow 前两个1-2-3
            fast = fast->next;
            slow = slow->next;
        }
        slow->next = slow->next->next;
        return head;
    }
};

ListNode* removeNthFromEnd(ListNode* head, int n) {
    ListNode* ans;
    ListNode* slow = head;   //t1
    ListNode* fast = head;    //t2
    
    for(int i=0;i<n;++i)
    {
        fast = fast->next;
    }
    
    if(fast == NULL) 
    {
        ans = head->next;
        delete head;
        return ans;
    }
    
    while(fast->next != NULL)
    {
        fast = fast->next;
        slow = slow->next;
    }
    delete slow->next;
    slow->next = slow->next->next;
    
    return head;
}


class Solution {
public:
    ListNode* removeNthFromEnd(ListNode* head, int n) {
        // t2 用于 计数 t1 才是关键
        ListNode** t1 = &head, *t2 = head;
        for(int i = 1; i < n; ++i)
        {            
            t2 = t2->next;//1-2-3-4-5, fast前进到2的位置，还有两个前进三个
        }
        
        while(t2->next != NULL)//前进3个到4的位置
        {
            t1 = &((*t1)->next);
            t2 = t2->next;
        }
        *t1 = (*t1)->next;

        return head;
        
    }
};