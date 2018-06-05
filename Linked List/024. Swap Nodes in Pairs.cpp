/*
24. Swap Nodes in Pairs
Given a linked list, swap every two adjacent nodes and return its head.

Example:

Given 1->2->3->4, you should return the list as 2->1->4->3.
Note:

Your algorithm should use only constant extra space.
You may not modify the values in the list's nodes, only nodes itself may be changed.

*/


//把第二个提取出来，断第二，第三链
class Solution {
public:
    ListNode* swapPairs(ListNode* head) {
        if(!head || !head->next) return head;
        ListNode dummy(0);
        dummy.next = head;
        ListNode * cur = &dummy;
        while(cur->next && cur->next->next){
            ListNode *nextnext = cur->next->next;//提出往后第二个
            cur->next->next = cur->next->next->next;//断往后第二个链
            nextnext->next = cur->next; //换下一个和下两个的顺序
            cur->next = nextnext;
            cur = cur->next->next ; //往后蹦两个
        }
        return dummy.next;
    }
};

//把第一个提取出来，断第一，第二链
class Solution {
public:
    ListNode* swapPairs(ListNode* head) {
        if(!head || !head->next) return head;
        ListNode dummy(0);
        dummy.next = head;
        ListNode * cur = &dummy;
        while(cur->next && cur->next->next){
            ListNode *next = cur->next;//提出下一个
            cur->next = cur->next->next;//把第二个往前提上来，并断第一个后面的链
            next->next = cur->next->next; //把原来的第三个放在第一个后面
            cur->next->next = next; //把原来第一个放在第三个
            cur = cur->next->next ; //往后蹦两个
        }
        return dummy.next;
    }
};

class Solution {
public:
    ListNode* swapPairs(ListNode* head) {
        ListNode dummy{0};
        dummy.next = head;
        auto curr = &dummy;
        while (curr->next && curr->next->next) {
            auto next_one = curr->next;
            auto next_two = next_one->next;
            auto next_three = next_two->next;
            curr->next = next_two; //
            next_two->next = next_one; //
            next_one->next = next_three; //上面三个 顺序可以顺便换，因为三个都是相连的，换一个next后面，所有都换，
            curr = next_one;
        }
        return dummy.next; 
    }
};

class Solution {
public:
    ListNode* swapPairs(ListNode* head) {
        ListNode dummy{0};
        dummy.next = head;
        auto curr = &dummy;
        while (curr->next && curr->next->next) {
            auto next_one = curr->next;
            auto next_two = next_one->next;
            auto next_three = next_two->next;
            next_two->next = next_one;
            next_one->next = next_three;
            curr->next = next_two;
            curr = next_one;
        }
        return dummy.next; 
    }
};


class Solution {
public:
    ListNode* swapPairs(ListNode* head) {
        ListNode **pp = &head;
        ListNode *a = nullptr;
        ListNode *b = nullptr;
        while((a = *pp) && (b = a->next))
        {
            a->next = b->next; //把第一个后面挂上第三个
            b->next = a; //第二个后面挂第一个
            *pp = b; //把当前改了 
            pp = &(a->next);
        }
        return head;
    }
};


class Solution {
public:
    ListNode* swapPairs(ListNode* head) {
        if(head == NULL)
            return NULL;
        if(head->next == NULL)
            return head;
        
        ListNode* next = head->next;
        head->next = swapPairs(next->next);
        next->next = head;
        
        return next;
    }
};