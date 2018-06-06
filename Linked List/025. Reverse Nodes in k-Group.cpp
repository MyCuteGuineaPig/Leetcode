/*
25. Reverse Nodes in k-Group

Given a linked list, reverse the nodes of a linked list k at a time and return its modified list.

k is a positive integer and is less than or equal to the length of the linked list. 
If the number of nodes is not a multiple of k then left-out nodes in the end should remain as it is.

Example:

Given this linked list: 1->2->3->4->5

For k = 2, you should return: 2->1->4->3->5

For k = 3, you should return: 3->2->1->4->5

Note:

Only constant extra memory is allowed.
You may not alter the values in the list's nodes, only nodes itself may be changed.

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
    ListNode* reverseKGroup(ListNode* head, int k) {
        ListNode dummy(0);
        dummy.next = head;
        ListNode *cur = &dummy;
        while(head){
            ListNode *next = head;
            for(int i = 1; i<k && next;i++){
                  //这是为了看是不是有足够多的next 够swap 比如[1,2,3,4,5], k=3,只能swap前3个  3-2-1-4-5, 不能swap4-5
                next = next->next;
            }
            if(!next) break;
            for(int i = 1; i<k; i++){
                ListNode *temp = head->next; //提出下一个调上来的
                head->next = head->next->next; //断下一个和下下一个链
                temp->next = cur->next;//把现在后面的接在swap之后的下一个
                cur->next = temp;
            }
            head = head->next; 

            cur = head;
            /*
                cur也要想前进k位，比如0-1-2-3-4-5-6, 变成0-3-2-1-4-5-6
                之后要把cur从0变成1
            */
            head = head->next;
            /*
            比如1-2-3-4-5-6, k=3
            dummy 在0的位置，head是1-2-3-4-5-6, 1-3-4-5-6, 1-4-5-6, 所以k个之后要把head向前进一位，
            */
        }
        return dummy.next;
    }
};



class Solution {
public:
   ListNode* reverseKGroup(ListNode* head, int k) {
      if( k > 1 ) for(auto pp=&head; *pp;) pp = reverse(pp, k);
      return head;
   }
private:
   ListNode** reverse(ListNode** pphead, int k) {
      auto ppnew = &((*pphead)->next);
      for(int kr=1; kr<k; kr++) {
         if( ! *ppnew ) return reverse(pphead, kr);
         auto pnext = (*ppnew)->next;
         (*ppnew)->next = *pphead;
         *pphead = *ppnew;
         *ppnew = pnext;
      }
      return ppnew;
   }
};



class Solution {
public:
    ListNode* reverseKGroup(ListNode* head, int k) {
        ListNode dummy{0};
        dummy.next = head;
        auto curr = head, curr_dummy = &dummy;
        int len = 0;

        while (curr) {
            auto next_curr = curr->next;
            len = (len + 1) % k;

            if (len == 0) {
                auto next_dummy = curr_dummy->next;
                reverseList(&curr_dummy, curr->next);
                curr_dummy = next_dummy;//比如0-1-2-3-4-5-6, 变成0-3-2-1-4-5-6, 把dummy head从0变成1
            }
            curr = next_curr;
        }
        return dummy.next;
    }

    void reverseList(ListNode **pre, const ListNode *end) {
        ListNode *cur = (*pre)->next;//是现在的数
         while (cur->next != end) {
            ListNode *temp = cur->next; //存储下个
            cur->next = cur->next->next;//断链
            temp->next = (*pre)->next;//把之前的接到现在的后面
            (*pre)->next = temp; //把下下个弄上来的
        }
    }

    /*
    or   接上pre->next 之前的都是先断链
    void reverseList(ListNode*& pre, ListNode *end){
        ListNode* cur = pre->next;
        while(cur->next!=end){
            ListNode *begnext = pre->next;
            pre->next = cur->next;
            cur->next = cur->next->next;
            pre->next->next = begnext;
        }
    }
    
    */
};



class Solution {
public:
    ListNode* reverseKGroup(ListNode* head, int k) {
        if (head == nullptr || head->next == nullptr || k < 2)
			return head;
		ListNode *next_group = head;
		for (int i = 0; i < k; i++) {
			if (next_group)
				next_group = next_group->next;
			else
				return head;
		}
		//next_group is the head of next group
		//new_next_group is the new head of next group after reversion
		ListNode *new_next_group = reverseKGroup(next_group, k);
		ListNode *prev = nullptr, *cur = head;
		while (cur != next_group) {
			ListNode *next = cur->next;
			cur->next = prev ? prev : new_next_group;
			prev = cur;
			cur = next;
		}
		return prev; 
    }
};



class Solution {
public:
    ListNode* reverseKGroup(ListNode* head, int k) {
        if(!inrange(head,k))    return head;
        ListNode* node=head;
        while(true){
            if(inrange(node,k)){
                for(int i=0;i<k;i++){
                    if(i<k/2)   swaptwo(node,k-2*i-1);
                    node=node->next;
                }
            }
            else    break;
        }
        return head;
        
    }
    bool inrange(ListNode* node,int k){
        int flag=0;
        ListNode* test=node;
        while(test){
            test=test->next;
            flag++;
            if(flag==k) break;
        }
        return flag==k?1:0;
    }
    void swaptwo(ListNode* node,int index){
        ListNode* temp =node;
        for(int i=0;i<index;i++){
            temp=temp->next;
        }
        int t=node->val;
        node->val=temp->val;
        temp->val=t;
    }