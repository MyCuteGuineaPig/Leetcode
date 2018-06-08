/*
328. Odd Even Linked List


Given a singly linked list, group all odd nodes together followed by the even nodes. 
Please note here we are talking about the node number and not the value in the nodes.

You should try to do it in place. The program should run in O(1) space complexity and O(nodes) time complexity.

Example 1:

Input: 1->2->3->4->5->NULL
Output: 1->3->5->2->4->NULL
Example 2:

Input: 2->1->3->5->6->4->7->NULL
Output: 2->3->6->7->1->5->4->NULL
Note:

The relative order inside both the even and odd groups should remain as it was in the input.
The first node is considered odd, the second node even and so on ...


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
    ListNode* oddEvenList(ListNode* head) {
        if(!head || !head->next) return head;
        ListNode* odd = head;
        ListNode* even = head->next, *evenhead = head->next;
        while(even && even->next){ //如果有的话，even->next 指的一定是奇数位的数
            odd =  odd->next = odd->next->next; 
            /*
            必须odd 在前面，even不能在前面(否则下个odd会被even遮盖, 因为odd在even前，even改变odd一定改变)，
            even->next 表示奇数位存在，表示，仍有奇数为没有断开的  3-4-5， 比如3,5为奇数位，4-5代表偶数位 
            要把奇数位的偶数位断开，就是断开3-4, Odd->next->next 就断开了
            
            否则会有nullptr报错
            比如even->next = even->next->next 在 odd->next = odd->next->next前面
            [1,2,3,4,5,6]
            1. odd = 1, even = 2
               even 先来 2-4, 3已经没了
               这时odd->next = odd->next->nex 直接从1到4了，直接跳过三了


            正常顺序 【1，2，3，4，5，6】
            a.  odd = 1-3-4-5-6(头在1), even = 2-4-5-6(头在2)
            
            b. odd = 1-3-5-6(头在3), even = 2-4-6(头在4)

            结束 odd 头在5， even头在6


            正常顺序 【1，2，3，4，5】
            a.  odd = 1-3-4-5(头在1), even = 2-4-5(头在2)
            
            b. odd = 1-3-5(头在3), even = 2-4(头在4)

            结束 odd 头在5， even头在

            */
            even = even->next = even->next->next;
        }
        odd->next = evenhead;
        return head;
    }
};



class Solution {
public:
    ListNode* oddEvenList(ListNode* head) {
        if (head) {
            for (auto odd_tail = head, curr = head->next;
                 curr && curr->next;  //cur是偶数位，cur->next是奇数位
                 curr = curr->next)
            {
                ListNode *even_head = odd_tail->next;  
                //cout<<" evn "<<even_head->val<<" cur "<<curr->val<<endl;
                odd_tail->next = curr->next; //assign 奇数位
                odd_tail = odd_tail->next;    //old tail往下走一位
                curr->next = curr->next->next; //跳过奇数位
                odd_tail->next = even_head;
            }
        }
        return head; 
    }
};




class Solution {
public:
    ListNode* oddEvenList(ListNode* head) {
        if(!head || !head->next) return head;
        ListNode *odd = head, *cur = head->next;
        while(cur && cur->next){
            auto evenhead = odd->next;
            odd->next = cur->next;
            cur->next = cur->next->next; //断奇数链
            odd->next->next = evenhead;
            
            cur = cur->next;//cur 前进
            odd = odd->next; //old 尾部前进
        }
        return head;
    }
};



class Solution {
public:
    ListNode* oddEvenList(ListNode* head) {
        if(!head || !head->next) {
            return head;
        }
        ListNode dummy(0);
        auto odd_tail = head, even_tail = head->next;
        while(even_tail && even_tail->next) {
            auto tmp = even_tail->next;
            even_tail->next = tmp->next;
            tmp->next = odd_tail->next;
            odd_tail->next = tmp;
            odd_tail = odd_tail->next;
            even_tail = even_tail->next;
        }
        return head;
    }
};