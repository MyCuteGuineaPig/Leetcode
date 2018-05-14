/*
109. Convert Sorted List to Binary Search Tree

Given a singly linked list where elements are sorted in ascending order, convert it to a height balanced BST.

For this problem, a height-balanced binary tree is defined as a binary tree in which the depth of the two subtrees of every node never differ by more than 1.

Example:

Given the sorted linked list: [-10,-3,0,5,9],

One possible answer is: [0,-3,9,-10,null,5], which represents the following height balanced BST:

      0
     / \
   -3   9
   /   /
 -10  5


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
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */
class Solution {
public:
    TreeNode* sortedListToBST(ListNode* head) {
        return helper(head, nullptr);
    }
    
    TreeNode *helper(ListNode* head, ListNode* tail){//tail 是永远不能达到的
        if(head == tail) return nullptr; 
        if(head->next == tail) return new TreeNode(head->val); //去掉这个条件也可以
        ListNode *fast = head, *slow = head;
        while(fast != tail && fast->next!=tail){
            slow = slow->next;
            fast = fast->next->next;
        }
        TreeNode *root = new TreeNode(slow->val);
        root->left = helper(head,slow); 
        root->right = helper(slow->next, tail);
        return root;
    }
};


class Solution {
public:
    TreeNode* sortedListToBST(ListNode* head) {
        return helper(head, nullptr);
    }
    
    TreeNode *helper(ListNode* head, ListNode* tail){
        if(head == tail) return nullptr;
        ListNode *fast = head, *slow = head;
        while(fast != tail && fast->next!=tail){
            slow = slow->next;
            fast = fast->next->next;
        }
        TreeNode *root = new TreeNode(slow->val);
        root->left = helper(head,slow);
        root->right = helper(slow->next, tail);
        return root;
    }
};


class Solution {
public:
    TreeNode* sortedListToBST(ListNode* head) {
        auto curr = head;
        int n = 0;
        while (curr) {
            curr = curr->next;
            ++n;
        }
        return BuildBSTFromSortedDoublyListHelper(&head, 0, n);
    }

    TreeNode * BuildBSTFromSortedDoublyListHelper(ListNode **head, int s, int e) {
        if (s == e) {
            return nullptr;
        }

        int m = s + ((e - s) / 2);
        auto left = BuildBSTFromSortedDoublyListHelper(head, s, m);
        auto curr = new TreeNode((*head)->val);

        *head = (*head)->next;
        curr->left = left;
        curr->right = BuildBSTFromSortedDoublyListHelper(head, m + 1, e);
        return curr;
    }
};

/*
Given the sorted linked list: [-10,-3,0,5,9],
上面解会返回    
      0
     / \
   -3   9
   /   /
 -10  5
 一开始是left[0,2], left[0,1],left[0,0]返回nullptr，
 【0，1】创建-10，再right【1,1] 返回nullptr，
 [0,2] left 返回时-10， 再建立node-3， -10在-3left tree, 再right[2,2] 返回nullptr
 形成
           -3   
            /   
          -10 

 下面解会返回
       0
     / \
   -10   5
    \     \
    -3    9
 一开始是left[0,1], left[0,-1],返回nullptr，
 【0，1】创建-10，再right【1,1] 再建立node-3， -3是-10的right tree, -3的再right[2,1] 返回nullptr
 形成
    -10   
    \     
    -3    
*/


class Solution {
public:
    TreeNode* sortedListToBST(ListNode* head) {
        auto curr = head;
        int n = 0;
        while (curr) {
            curr = curr->next;
            ++n;
        }
        return BuildBSTFromSortedDoublyListHelper(&head, 0, n-1);
    }

    TreeNode * BuildBSTFromSortedDoublyListHelper(ListNode **head, int s, int e) {
        if (s > e) {
            return nullptr;
        }

        int m = s + ((e - s) / 2);
        auto left = BuildBSTFromSortedDoublyListHelper(head, s, m-1);
        auto curr = new TreeNode((*head)->val);

        *head = (*head)->next;
        curr->left = left;
        curr->right = BuildBSTFromSortedDoublyListHelper(head, m + 1, e);
        return curr;
    }
};