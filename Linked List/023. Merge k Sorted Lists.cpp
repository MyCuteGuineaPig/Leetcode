/*
23. Merge k Sorted Lists

Merge k sorted linked lists and return it as one sorted list. Analyze and describe its complexity.

Example:

Input:
[
  1->4->5,
  1->3->4,
  2->6
]
Output: 1->1->2->3->4->4->5->6
*/



/*

During 1st iteration, we merge two lists(every list is N) into one, this will make K down to K / 2.

During 2nd iteration, we merge two lists(every list is 2N) into one, this will make K / 2 down to k /4.

During 3rd iteration, we merge two lists(every list is 4N) into one, this will make K / 4 down to k /8.

And so forth...

I think when we merge two lists, the complexity is O(list1.length) + O(list2.length).

So the total complexity is:

(2N) * (K / 2) + 
(4N) * (K / 4) + 
(8N) * (K / 8) + 
.............. + 
(2^logK*N) * (K / (2 ^logK)) 

= logK*KN
*/



// Time:  O(knlogk) n是linkedlist 长度, k是list的个数
// Space: O(1)

/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode(int x) : val(x), next(NULL) {}
 * };
 */
 
// Merge two by two solution.
class Solution {
public:
    ListNode* mergeKLists(vector<ListNode*>& lists) {
        if(lists.empty()) return NULL;
        /*

        int r = lists.size()-1;
        while(r>=1){
            lists[0] = mergeList(lists[0],lists[r--]);
             //这个费时间的原因是每次都在让list[0] 长度增大，最后一个r，list[0]由 n-2n
            // 倒数第二个n 由2n 变成3n, 到最后merge list[0]会很大，loop很费时间
            
            lists.pop_back();
        }
        return lists[0];
        */

        int left = 0, right = lists.size() - 1;
        while (right > 0) {
            if (left >= right) {
                left = 0;
            } else {
                lists[left] = mergeList(lists[left], lists[right]);
                ++left;
                --right;
            }
        }
        return lists[0];
        
    }
    
    ListNode* mergeList(ListNode *l1, ListNode *l2){
        ListNode dummy(0);
        ListNode *cur = &dummy;
        while(l1 && l2){
            if(l1->val<=l2->val){
                cur->next = l1; //切记不能用new ListNode(l1->val) 否则会内存溢出
                l1 = l1->next;
            }else{
                cur->next = l2;
                l2 = l2->next;
            }
            cur = cur->next;
        }
        cur->next = l1 ? l1: l2;
        return dummy.next;
    }
};



// Time:  O(n * logk)
// Space: O(logk)
// Divide and Conquer solution.
class Solution {
public:
    ListNode* mergeKLists(vector<ListNode*>& lists) {
        return divideConquer(lists, 0, lists.size()-1);
    }
    
    ListNode *divideConquer(vector<ListNode*>& lists, int begin, int end){
        if(begin>end) return NULL;
        if(begin==end) return lists[begin];
        int mid = (begin+end)>>1;
        return mergeTwoLists(divideConquer(lists,begin,mid), divideConquer(lists, mid+1, end)); 
    }
    ListNode *mergeTwoLists(ListNode *l1, ListNode *l2) {
        ListNode dummy{0};
        auto curr = &dummy;

        while (l1 && l2) {
            if (l1->val <= l2->val) {
                curr->next = l1;
                l1 = l1->next;
            } else {
                curr->next = l2;
                l2 = l2->next;
            }
            curr = curr->next;
        }
        curr->next = l1 ? l1 : l2;

        return dummy.next;
    }
};




// Time:  O(n * logk)
// Space: O(k)
// Heap solution.
class Solution {
public:
    ListNode* mergeKLists(vector<ListNode*>& lists) {
        if(lists.size()==0) return NULL;
        if(lists.size()==1) return lists[0];
        auto comp = [](ListNode * l1, ListNode *l2){
            return l1->val>l2->val;
        };
        priority_queue<ListNode *, vector<ListNode*>, decltype(comp)>pq(comp);
        ListNode dummy(0);
        ListNode *cur = &dummy;
        for(auto i: lists){
            if(i) pq.push(i); 
        }
        while(pq.size()){
            auto node = pq.top();
            pq.pop();
            cur->next = node;
            cur = cur->next;
            node = node->next;
            if(node)
                pq.push(node);
        }
        return dummy.next;
    }
};

//make_heap + pop_heap: we can access all the elements (from my answer for that solution)
    
class Solution {
public:
    static bool heapComp(ListNode* a, ListNode* b) {
            return a->val > b->val;
    }
    ListNode* mergeKLists(vector<ListNode*>& lists) { //make_heap
        ListNode head(0);
        ListNode *curNode = &head;
        vector<ListNode*> v;   
        for(int i =0; i<lists.size(); i++){
            if(lists[i]) v.push_back(lists[i]);
        }
        make_heap(v.begin(), v.end(), heapComp); //vector -> heap data strcture

        while(v.size()>0){
            curNode->next=v.front();
            pop_heap(v.begin(), v.end(), heapComp); 
            v.pop_back(); 
            curNode = curNode->next;
            if(curNode->next) {
                v.push_back(curNode->next); 
                push_heap(v.begin(), v.end(), heapComp);
            }
        }
        return head.next;
    }
};