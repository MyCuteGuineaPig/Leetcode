/*
445. Add Two Numbers II

You are given two non-empty linked lists representing two non-negative integers. The most significant digit comes first and each of their nodes contain a single digit. Add the two numbers and return it as a linked list.

You may assume the two numbers do not contain any leading zero, except the number 0 itself.

Follow up:
What if you cannot modify the input lists? In other words, reversing the lists is not allowed.

Example:

Input: (7 -> 2 -> 4 -> 3) + (5 -> 6 -> 4)
Output: 7 -> 8 -> 0 -> 7

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
    ListNode* addTwoNumbers(ListNode* l1, ListNode* l2) {
        stack<int>s1, s2;
        while(l1){
            s1.push(l1->val);
            l1 = l1->next;
        }
        while(l2){
            s2.push(l2->val);
            l2 = l2->next;
        }
        ListNode dummy(0);
        ListNode *next;
        int carry = 0;
        while(s1.size()||s2.size()||carry){
            next = dummy.next;
            if(s1.size()){
                carry += s1.top();s1.pop();
            }
            if(s2.size()){
                carry += s2.top();s2.pop();
            }
            //cout<<" carry "<<carry<<endl;
            dummy.next = new ListNode(carry%10);
            carry /= 10;
            dummy.next->next = next;
        }
        
        return dummy.next;
    }
};



class Solution {
public:
    int len(ListNode* l) {
        int count = 0;
        while (l != NULL) {
            count++;
            l = l->next;
        }
        
        return count;
    }
    
    int addTwoNumbers(int diff, ListNode* result, ListNode* longer, ListNode* shorter) {
        if (longer == NULL) {
            return 0;
        }
        
        int carry = 0;
        if (diff > 0) {
            result->next = new ListNode(longer->val);
            carry = addTwoNumbers(diff - 1, result->next, longer->next, shorter);
        } else {
            result->next = new ListNode(longer->val + shorter->val);
            carry = addTwoNumbers(diff, result->next, longer->next, shorter->next);
        }
        
        int sum = result->next->val + carry;
        result->next->val = sum % 10;
        return sum / 10;
    }
    
    ListNode* addTwoNumbers(ListNode* l1, ListNode* l2) {
        int len1 = len(l1), len2 = len(l2);
        ListNode* longer = len1 > len2 ? l1 : l2;
        ListNode* shorter = longer == l1 ? l2 : l1;
        
        ListNode* preHead = new ListNode(0);
        int carry = addTwoNumbers(abs(len1 - len2), preHead, longer, shorter);
        if (carry != 0) {
            preHead->val += carry;
            return preHead;
        } else {
            return preHead->next;
        }
    }
};


class Solution {
public:
    ListNode* reverse(ListNode* l){
        ListNode* res = nullptr;
        while(l){
            ListNode* next = l->next;
            l->next = res;
            res = l;
            l = next;
        }
        return res;
    }


    ListNode* addTwoNumbers(ListNode* l1, ListNode* l2) {
        ListNode* r1 = reverse(l1);
        ListNode* r2 = reverse(l2);

        ListNode* res = nullptr;
        int cnt = 0;
        while (r1 || r2 || cnt ){
            cnt += r1? r1->val: 0;
            cnt += r2? r2 ->val:0;
            ListNode* new_head = new ListNode(cnt % 10);
            new_head->next = res;
            res = new_head; 

            cnt = cnt / 10;
            r1 = r1 ?  r1->next: nullptr;
            r2 = r2 ? r2->next: nullptr;
        }

        return res;
    }
};


class Solution {
public:
    ListNode *reverse(ListNode *head) {
        ListNode *prev = NULL;
        ListNode *curr = head;
        while(curr) {
            ListNode *next = curr->next;
            curr->next = prev;
            prev = curr;
            curr = next;
        }
        return prev;
    }
    int advance(ListNode* &l) {
        if (l) {
            int ret = l->val;
            l = l->next;
            return ret;
        } 
        return 0;
    }
    ListNode* addTwoNumbers(ListNode* l1, ListNode* l2) {
        ListNode *r1 = reverse(l1);
        ListNode *r2 = reverse(l2);
        int carry = 0;
        ListNode *prev = NULL;
        while(r1 || r2 || (carry > 0)) {
            int sum = advance(r1) + advance(r2) + carry;
            if (sum >= 10) {
                sum -= 10;
                carry = 1;
            } else {
                carry = 0;
            }
            ListNode *nd = new ListNode(sum);
            nd->next = prev;
            prev = nd;
        }
        return prev;
    }
};