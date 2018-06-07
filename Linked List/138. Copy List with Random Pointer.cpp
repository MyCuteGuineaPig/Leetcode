/*
138. Copy List with Random Pointer
A linked list is given such that each node contains an additional random pointer which could point to any node in the list or null.

Return a deep copy of the list.

*/


/**
 * Definition for singly-linked list with a random pointer.
 * struct RandomListNode {
 *     int label;
 *     RandomListNode *next, *random;
 *     RandomListNode(int x) : label(x), next(NULL), random(NULL) {}
 * };
 */
class Solution {
public:
    RandomListNode *copyRandomList(RandomListNode *head) {
        RandomListNode* cur = head;
        while(cur){ ///Iterate the original list and duplicate each node. The duplicate of each node follows its original.
            RandomListNode* node =  new RandomListNode(cur->label);
            node->next = cur->next;
            cur->next = node;
            cur = cur->next->next;
        }
        cur = head; 
        while(cur){ //Iterate the new list and assign the random pointer for each duplicated node.
            if(cur->random)
                cur->next->random = cur->random->next;
            cur = cur->next->next;
        }
        RandomListNode dummy(0);
        RandomListNode *res = &dummy;
        cur = head;
        while(cur){
            res->next = cur->next;
            cur->next = cur->next->next; //要加上这个否则original chain是被修改过的
            res = res->next;
            cur = cur->next;
        }
        return dummy.next;
    }
};



class Solution {
public:
    RandomListNode *copyRandomList(RandomListNode *head) {
        if(!head) return NULL;
        RandomListNode *newHead, *l1, *l2;
        l1 = head;
        while(l1) {
            l2 = new RandomListNode(l1->label);
            l2->next = l1->next;
            l1->next = l2;
            l1 = l1->next->next;
        }
        
        l1 = head;
        while(l1) {
            if(l1->random)
                l1->next->random = l1->random->next;
            l1 = l1->next->next;
        }
        
        l1 = head;
        newHead = l1->next;
        while(l1) {
            l2 = l1->next;
            l1->next = l1->next->next; // Must restore the original list
            if(l2->next) l2->next = l2->next->next;
            l1 = l1->next;
        }
        
        return newHead;
    }
};