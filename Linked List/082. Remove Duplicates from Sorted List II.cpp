/*
82. Remove Duplicates from Sorted List II

Given a sorted linked list, delete all nodes that have duplicate numbers, leaving only distinct numbers from the original list.

Example 1:

Input: 1->2->3->3->4->4->5
Output: 1->2->5
Example 2:

Input: 1->1->1->2->3
Output: 2->3

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
        ListNode dummy(0);
        dummy.next = head;
        ListNode* cur = &dummy;
        while(cur){
            //cout<<"cur "<<cur->val<<endl;
            if(cur->next && cur->next->next && cur->next->val == cur->next->next->val){
                while(cur->next->next && cur->next->val == cur->next->next->val){
                    //比如1，0-1-1-1-4 只要 下一个和下下一个相等,就把下下一个删了，就是先删第二个1，再删第三个1
                    cur->next->next = cur->next->next->next; 
                }
                cur->next = cur->next->next;  //直到loop 到没有下下个 或者下下个不等于下个，把下个也删了
                /// 之前从0-1-1-1-4  变成0-1-4 就把1也删了
            }else cur = cur->next;
        }
        return dummy.next;
    }
};


class Solution {
public:
    ListNode* deleteDuplicates(ListNode* head) {
        ListNode dummy{0};
        auto prev = &dummy;
        while (head) {
            if (head->next && head->next->val == head->val) {
                auto val = head->val;
                while (head && head->val == val) {
                    head = head->next;
                }
                prev->next = head;
            } else {
                prev->next = head;
                prev = head; //prev向前进一位
                head = head->next;//head也向前进一位
            }
        }
        return dummy.next;
    }
};


//recursion
class Solution {
public:
    ListNode* deleteDuplicates(ListNode* head) {
        if(!head || !head->next){
            return head;
        }
        bool repeat = false;
        while(head->next && head->val == head->next->val){
            head = head->next;
            repeat = true;
        }
        if(repeat){
            if(head){
                return deleteDuplicates(head->next);
            }
            return nullptr;
        } else{
            head->next = deleteDuplicates(head->next);
            return head;
        }
    }
};