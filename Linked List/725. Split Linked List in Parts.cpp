/*
725. Split Linked List in Parts

Given a (singly) linked list with head node root, 
write a function to split the linked list into k consecutive linked list "parts".

The length of each part should be as equal as possible: no two parts should have a size differing by more than 1. 
This may lead to some parts being null.

The parts should be in order of occurrence in the input list, 
and parts occurring earlier should always have a size greater than or equal parts occurring later.

Return a List of ListNode's representing the linked list parts that are formed.

Examples 1->2->3->4, k = 5 // 5 equal parts [ [1], [2], [3], [4], null ]
Example 1:
Input: 
root = [1, 2, 3], k = 5
Output: [[1],[2],[3],[],[]]
Explanation:
The input and each element of the output are ListNodes, not arrays.
For example, the input root has root.val = 1, root.next.val = 2, \root.next.next.val = 3, and root.next.next.next = null.
The first element output[0] has output[0].val = 1, output[0].next = null.
The last element output[4] is null, but it's string representation as a ListNode is [].

Example 2:
Input: 
root = [1, 2, 3, 4, 5, 6, 7, 8, 9, 10], k = 3
Output: [[1, 2, 3, 4], [5, 6, 7], [8, 9, 10]]
Explanation:
The input has been split into consecutive parts with size difference at most 1, 
and earlier parts are a larger size than the later parts.
Note:

The length of root will be in the range [0, 1000].
Each value of a node in the input will be an integer in the range [0, 999].
k will be an integer in the range [1, 50].


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
    vector<ListNode*> splitListToParts(ListNode* root, int k) {
        int len = getLength(root);
        vector<ListNode *>res(k);
        int each = len/k, rem = len%k;
        for(int i = 0; i<k && root; i++){
            int j = 0;
            ListNode*head = root;
            ListNode *prev;
            while(j++<each){
                prev = root;
                root = root->next;
                
            }
            if(rem>0){
                rem--;
                prev = root;
                root = root->next;
            }
            ListNode *next = root;  //root是下一个的起点
            prev->next = NULL;   //prev是这次的结尾
           
            res[i] = head;
            root = next;
        }
        return res;
    }

    int getLength(ListNode *root){
        int i = 0;
        while(root){
            root = root->next;
            i++;
        }
        return i;
    }
};




class Solution {
public:
    vector<ListNode*> splitListToParts(ListNode* root, int k) {
        int len = getLength(root);
        vector<ListNode *>res(k);
        int each = len/k, rem = len%k;
        for(int i = 0; i<k && root; i++){
            int j = 0;
            ListNode dummy(0);
            dummy.next = root;
            ListNode* cur = &dummy;
            while(j++<each){
                cur = cur->next;
            }
            if(rem-->0){
                cur = cur->next;
            }
            ListNode *next = cur->next; 
            cur->next = NULL;    //cur是放进i个vector 的结尾 node
            res[i] = dummy.next;
            root = next;
        }
        return res;
    }

    int getLength(ListNode *root){
        int i = 0;
        while(root){
            root = root->next;
            i++;
        }
        return i;
    }
};

class Solution {
public:
    vector<ListNode*> splitListToParts(ListNode* root, int k) {
        auto n = 0;
        auto curr = root;
        while (curr) {
            curr = curr->next;
            n += 1;
        }
        auto width = n / k;
        auto remainder = n % k;

        vector<ListNode *> result;
        curr = root;
        for (int i = 0; i < k; ++i) {
            auto head = curr;
            for (int j = 0; curr &&
                 j < width - 1 + static_cast<int>(i < remainder); ++j) {  //加上remaining，curr只前进到此次push进vector的最后一位
                curr = curr->next;
            }
            if (curr) {
                auto tail = curr;
                curr = curr->next;
                tail->next = nullptr;
            }
            result.emplace_back(head);
        }
        return result;
    }
};



class Solution {
public:
    vector<ListNode*> splitListToParts(ListNode* root, int k) {
        vector<ListNode*> parts(k, nullptr);
        int len = 0;
        for (ListNode* node = root; node; node = node->next)
            len++;
        int n = len / k, r = len % k; // n : minimum guaranteed part size; r : extra nodes spread to the first r parts;
        ListNode* node = root, *prev = nullptr;
        for (int i = 0; node && i < k; i++, r--) {
            parts[i] = node;
            for (int j = 0; j < n + (r > 0); j++) {
                prev = node;
                node = node->next;
            }
            prev->next = nullptr;
        }
        return parts;
    }
};