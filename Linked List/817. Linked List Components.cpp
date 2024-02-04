/*
817. Linked List Components

We are given head, the head node of a linked list containing unique integer values.

We are also given the list G, a subset of the values in the linked list.

Return the number of connected components in G, where two values are connected if they appear consecutively in the linked list.

Example 1:

Input: 
head: 0->1->2->3
G = [0, 1, 3]
Output: 2
Explanation: 
0 and 1 are connected, so [0, 1] and [3] are the two connected components.
Example 2:

Input: 
head: 0->1->2->3->4
G = [0, 3, 1, 4]
Output: 2
Explanation: 
0 and 1 are connected, 3 and 4 are connected, so [0, 1] and [3, 4] are the two connected components.
Note:

If N is the length of the linked list given by head, 1 <= N <= 10000.
The value of each node in the linked list will be in the range [0, N - 1].
1 <= G.length <= 10000.
G is a subset of all values in the linked list.

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
    int numComponents(ListNode* head, vector<int>& G) {
        unordered_set<int>s(G.begin(),G.end());
        int count = 0;
        bool begin = false;
        while(head){
            if(s.find(head->val) != s.end()){
                begin = true;
            }else if(begin){
                count++;
                begin = false;
            }
            head= head->next;
        }
        if(begin) count++;
        return count;
    }
};


class Solution {
public:
    int numComponents(ListNode* head, vector<int>& nums) {
        unordered_set<int>st(nums.begin(), nums.end());
        int cnt = 0;
        ListNode* prev = nullptr;
        while(head){
            if(st.count(head->val) && (prev == nullptr || st.count(prev->val) == 0))
                ++cnt;
            prev = head;
            head = head->next;
        }
        return cnt;
    }
};


class Solution {
public:
    int numComponents(ListNode* head, vector<int>& G) {
        unordered_set<int> lookup(G.cbegin(), G.cend());
        ListNode dummy(-1);
        dummy.next = head;
        auto curr = &dummy;
        int result = 0;
        while (curr && curr->next) {
            if (!lookup.count(curr->val) && lookup.count(curr->next->val)) {//之前不在，之后在
                ++result;
            }
            curr = curr->next;
        }
        return result;
    }
};



class Solution {
public:
    int numComponents(ListNode* head, vector<int>& G) {
        unordered_set<int>s(G.begin(),G.end());
        int count = 0;
        while(head){
            if(s.find(head->val) != s.end()){
                count++;
                while(head && s.count(head->val)) head = head->next;
            }else{
                head= head->next;
            }
           
        }
        return count;
    }
};