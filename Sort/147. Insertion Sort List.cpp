/*
147. Insertion Sort List

Sort a linked list using insertion sort.


A graphical example of insertion sort. The partial sorted list (black) initially contains only the first element in the list.
With each iteration one element (red) is removed from the input data and inserted in-place into the sorted list
 

Algorithm of Insertion Sort:

Insertion sort iterates, consuming one input element each repetition, and growing a sorted output list.
At each iteration, insertion sort removes one element from the input data, finds the location it belongs within the sorted list, 
and inserts it there.
It repeats until no input elements remain.

Example 1:

Input: 4->2->1->3
Output: 1->2->3->4
Example 2:

Input: -1->5->3->4->0
Output: -1->0->3->4->5
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
    ListNode* insertionSortList(ListNode* head) {
        ListNode *newhead = new ListNode(0);
        newhead -> next = head;
        ListNode * prev = newhead;
        while(head){
            if(head->next && head->next->val < head->val){
                while(prev->next && prev->next->val<head->next->val)
                    prev = prev->next;
                ListNode *temp = prev->next;/*
                    prev,head,temp连在一起,只是头位置不一样
                    现在是[3,4,2,1,5] 比如顺序是, head在4的位置
                     ListNode *temp = prev->next; temp = [3,4,2,1,5], prev = 0-3-4-2-1-5
                     prev->next = head->next;   prev = 0-2-1-5, new-head = 0-2-1-5, temp = 3-4-2-1-5, prev变,temp不变的原因是
                     temp 等于prev->next的位置，现在prev->next 指向了新的位置,所以老的位置元素不变
                     
                     head->next = head->next->next; head = 4, 1, 5, prev = 0-2-1-5. new-head = 0-2-1-5, temp = 3-4-1-5
                     
                     prev->next->next = temp,   prev = 0-2-3-4-1-5
                     
                     (如果有head-> next = head-> next->head, 因为head和prev共享的, prev = )
                     prev->next->next = temp;   [0,2,3,4,2,3,4,2......] 因为prev->next指的是2，prev->next->nexxt 值得3, 
                     
                     temp 和prev 想连的，如果不设head->next = head->next->next的话，4后面是2,而同时又把2后面设置3，所以构成循环2,3,4
                     同时 因为prev->next->next = temp, prev是0，prev->next 是2, prev->next->next 是2后面的，2和3,4相连,4后面接上2
                      
                     prev

                    
                    prev = 0, 4,2,1,3 prevnext = 2, 1, 3 = temp
                    head = 4, 
                    head ->next = head->next->next, prev->next = temp = 1,3
                */
                prev->next = head->next;
                head->next = head->next->next;
                prev->next->next = temp;
                prev = newhead;
            }
            else{
                head = head->next;
            }
        }
        return newhead->next;  
    }
};



class Solution {
    public:
        ListNode *insertionSortList(ListNode *head) {
        ListNode dummy{numeric_limits<int>::min()};

        auto curr = head;
        ListNode *position = nullptr;

        while (curr) {
            position = findInsertPosition(&dummy, curr->val);
            ListNode *tmp = curr->next;
            curr->next = position->next;
            position->next = curr;
            curr = tmp;
        }

        return dummy.next;
    }

    ListNode* findInsertPosition(ListNode *head, int x) {
        ListNode *prev = nullptr;
        for (auto curr = head; curr && curr->val <= x;
             prev = curr, curr = curr->next);
        return prev;
    }
};


class Solution {
    public:
        ListNode *insertionSortList(ListNode *head) {
            ListNode *dummy = new ListNode(numeric_limits<int>::min());
            ListNode *pos;
            while(head){
                pos = dummy;
                while(pos->next && pos->next->val<head->val){
                    pos = pos->next;
                }
                ListNode *next = head->next;
                head->next = pos->next;
                pos->next = head;
                head = next;
            }
            return dummy->next;
        }
};


class Solution {
public:
    ListNode* insertionSortList(ListNode* head) {
        ListNode *h = new ListNode(0);
        ListNode *cur = head;
        ListNode *prev = h;
        ListNode *next = NULL;
        while (cur)
        {
            next = cur->next;
            if (!prev->next || prev->next->val > cur->val) prev = h;
            while (prev->next && prev->next->val < cur->val)
            {
                prev = prev->next;
            }
            cur->next = prev->next;
            prev->next = cur;
            cur = next;
        }
        return h->next;
    }
};