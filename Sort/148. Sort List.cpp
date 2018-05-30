/*

148. Sort List

Sort a linked list in O(n log n) time using constant space complexity.

Example 1:

Input: 4->2->1->3
Output: 1->2->3->4
Example 2:

Input: -1->5->3->4->0
Output: -1->0->3->4->5

*/



// complexity O(nlogn), space O(logn)

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
    ListNode* sortList(ListNode* head) {
        if(!head || !head->next) return head;
        ListNode *fast = head, *slow = head;
        while(fast->next && fast->next->next){
		/*
		条件需要fast->next and fast->next->next
		假如条件是 fast and fast->next: 
		比如现在head是[1,2], fast可以指导2的后面一个元素, slow 指的是2
		而且会循环下去，一直是head[1,2]，
		所以fast->next and fast->next->next, slow就会指向1
		
		条件也可以用fast and fast->next
		但是在初始化fast时候 fast = head->next
		
		*/
            slow = slow->next;
            fast = fast->next->next;
        }
        fast = slow;
        slow = slow->next;
        fast->next = nullptr;
        return mergeList(sortList(head),sortList(slow));
    }
    
    ListNode*mergeList(ListNode* l1, ListNode* l2){
        ListNode dummy(0);
        ListNode* cur = &dummy;
        while(l1 && l2){
            if(l1->val<=l2->val){
                cur->next = l1;
                l1 = l1->next;
            }else{
                cur->next = l2;
                l2 = l2->next;
            }
            cur = cur->next;
        }
        cur->next = l1 ? l1 : l2;
        return dummy.next;
    }
};


// complexity O(nlogn), space O(n)

class Solution {
public:
    static bool cmp(ListNode* a, ListNode* b) {
            return a->val < b->val;
    }
    ListNode* sortList(ListNode* head) {
        if (head == nullptr || head->next == nullptr) return head;
        vector<ListNode*> nodes;
        ListNode* p = head;
        while (p != nullptr) { 
            nodes.emplace_back(p);
            p = p->next;
        }
   
        sort(nodes.begin(), nodes.end(), cmp);

        p = nodes[0];
        for (int i = 1; i != nodes.size(); ++i) {
            
            p->next = nodes[i];
            p = p->next;
        }
        p->next = nullptr;
        return nodes[0];
        
    }
};





/**
 * Merge sort use bottom-up policy, 
 * so Space Complexity is O(1)
 * Time Complexity is O(NlgN)
 * stable sort
*/
class Solution {
public:
	ListNode *sortList(ListNode *head) {
		if(!head || !(head->next)) return head;
		
		//get the linked list's length
		ListNode* cur = head;
		int length = 0;
		while(cur){
			length++;
			cur = cur->next;
		}
		
		ListNode dummy(0);
		dummy.next = head;
		ListNode *left, *right, *tail;
		for(int step = 1; step < length; step <<= 1){
			cur = dummy.next;
			tail = &dummy;
			while(cur){
				left = cur;
				right = split(left, step);
				cur = split(right,step);
				tail = merge(left, right, tail);
			}
		}
		return dummy.next;
	}
private:
	/**
	 * Divide the linked list into two lists,
     * while the first list contains first n ndoes
	 * return the second list's head
	 */
	ListNode* split(ListNode *head, int n){
		//if(!head) return NULL;
		for(int i = 1; head && i < n; i++) head = head->next;
		
		if(!head) return NULL;
		ListNode *second = head->next;
		head->next = NULL;
		return second;
	}
	/**
	  * merge the two sorted linked list l1 and l2,
	  * then append the merged sorted linked list to the node head
	  * return the tail of the merged sorted linked list
	 */
	ListNode* merge(ListNode* l1, ListNode* l2, ListNode* head){
		ListNode *cur = head;
		while(l1 && l2){
			if(l1->val > l2->val){
				cur->next = l2;
				cur = l2;
				l2 = l2->next;
			}
			else{
				cur->next = l1;
				cur = l1;
				l1 = l1->next;
			}
		}
		cur->next = (l1 ? l1 : l2);
		while(cur->next) cur = cur->next;
		return cur;
	}
};
