
/*
234. Palindrome Linked List

Given a singly linked list, determine if it is a palindrome.

Example 1:

Input: 1->2
Output: false
Example 2:

Input: 1->2->2->1
Output: true
Follow up:
Could you do it in O(n) time and O(1) space?


*/

/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode(int x) : val(x), next(NULL) {}
 * };
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
    bool isPalindrome(ListNode* head) {
        if(!head || !head->next) return true;
        ListNode* slow = NULL, *fast = head;
        while(fast && fast->next){
            fast = fast->next->next;
            auto next = head->next;
            head->next = slow;
            slow = head;
            head = next;
        }
        ListNode *temp = slow;
        ListNode *head2 = fast? head->next : head;
        while(slow){
            if(slow->val!=head2->val) return false;
            head2 = head2->next;
            slow = slow->next;
        }
        return true;
    }
};






class Solution {
public:
    bool isPalindrome(ListNode* head) {
        // Reverse the first half list.
        ListNode *reverse = nullptr, *fast = head;
        while (fast && fast->next) {
            fast = fast->next->next;
            const auto head_next = head->next;
            head->next = reverse;
            reverse = head;
            head = head_next;
        }

        // If the number of the nodes is odd,
        // set the head of the tail list to the next of the median node.
        ListNode *tail = fast ? head->next : head;

        // Compare the reversed first half list with the second half list.
        // And restore the reversed first half list.
        bool is_palindrome = true;
        while (reverse) {
            is_palindrome = is_palindrome && reverse->val == tail->val;
            const auto reverse_next = reverse->next;
            reverse->next = head;
            head = reverse;
            reverse = reverse_next;
            tail = tail->next;
        }
            
        return is_palindrome;   
    }
};




class Solution {
public:
    bool isPalindrome(ListNode* head) {
        int num=0;
        ListNode* temp=head;
        for(;temp!=NULL;temp=temp->next)
            num++;
        int z=num/2;  //求长度
        temp=head;
        ListNode* pre=NULL,*tempt;
        for(int i=0;i<z;i++){
            tempt=temp->next;
            temp->next=pre;
            pre=temp;
            temp=tempt;
        }
        if(num%2==1)
            temp=temp->next;
        for(;temp!=NULL&&pre!=NULL;temp=temp->next,pre=pre->next)
            if(temp->val!=pre->val) return false;
        return true;
    }
};