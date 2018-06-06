/*
61. Rotate List


Given a linked list, rotate the list to the right by k places, where k is non-negative.

Example 1:

Input: 1->2->3->4->5->NULL, k = 2
Output: 4->5->1->2->3->NULL
Explanation:
rotate 1 steps to the right: 5->1->2->3->4->NULL
rotate 2 steps to the right: 4->5->1->2->3->NULL
Example 2:

Input: 0->1->2->NULL, k = 4
Output: 2->0->1->NULL
Explanation:
rotate 1 steps to the right: 2->0->1->NULL
rotate 2 steps to the right: 1->2->0->NULL
rotate 3 steps to the right: 0->1->2->NULL
rotate 4 steps to the right: 2->0->1->NULL
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
    ListNode* rotateRight(ListNode* head, int k) {
        if(!head || !head->next || k == 0) return head;
        ListNode *cur = head;
        int len = 1;
        while(cur->next){
            cur = cur->next;
            len++;
        }
        if(k%len== 0) return head; 
        ListNode* end = cur;
        int pos = (len-k%len)-1; //前进减1位
        cur = head;
        while(pos-->0){
            cur = cur->next;
        }
        ListNode *next = cur->next;//rotate开始的位置, cur是rotate的前一位
        cur->next = NULL;
        end->next = head;
        return next;
    }
};




class Solution {
public:
    ListNode* rotateRight(ListNode* head, int k) {
        if (head == nullptr || head->next == nullptr) {
            return head;
        }

        int n = 1;
        auto curr = head;
        for (; curr->next; curr = curr->next) {
            ++n;
        }
        curr->next = head; //头尾相连

        auto tail = curr;
        k = n - k % n;
        curr = head;
        for (int i = 0; i < k; curr = curr->next, ++i) {
            tail = curr;//这里的k从0到k前进k个原因是，从第一个算，前进k个，正是rotate之后的起点，tail是起点前一位
        }

        tail->next = nullptr;
        return curr; 
    }
};