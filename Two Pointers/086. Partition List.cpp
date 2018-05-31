/*
86. Partition List

Given a linked list and a value x, partition it such that all nodes less than x come before nodes
 greater than or equal to x.

You should preserve the original relative order of the nodes in each of the two partitions.

Example:

Input: head = 1->4->3->2->5->2, x = 3
Output: 1->2->2->4->3->5
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
    ListNode* partition(ListNode* head, int x) {
        ListNode **slow = &head;
        ListNode **fast = &head;
        while(*fast && (*fast)->val < x) { //0->4->3->2->5->1,x=3 跳过所有一开始小于的 x的,最后fast在4上，slow在4上
            fast = &((*fast)->next);
            slow = &((*slow)->next);
        }
        while(*fast){
            while(*fast && (*fast)->val>=x){
                fast = &((*fast)->next);
                /*
                跳过大于等于的0->4->3->2->5->1，fast之后等于3后面的2,
                先把当前slow存成 4-3-2-5-2 存成slownext
                再把2挂在0后面, 0-2-5-1
                把2后面的抹去,  0-4-3-5-1, slow = 0-2
                再把slow-next 设为之前slow slow = 0-2-4-3-5-1
                slow = slow-next, slow又到4的位置，前进一位slow原因是，
                要是不前进，最后一位1会在2的前面，变成0-1-2,
                但是如果前进了，会保持顺序0-2-1
                */
            }
            if(*fast){
                ListNode *slownext = (*slow);
                *slow = *fast;
                *fast = (*fast)->next;
                (*slow)->next = slownext; 
                slow = &((*slow)->next);
            }
        }
        return head;
    }
};



class Solution {
public:
    ListNode* partition(ListNode* head, int x){
    	ListNode node1(0), node2(0);
    	ListNode *smaller = &node1, *bigger = &node2;
    	while(head){
    		if(head->val < x){
    			smaller = smaller->next = head;
    		}else{
    			bigger = bigger->next = head;
    		}
    		head = head->next;
    	}
    	bigger->next = NULL;
    	smaller->next = node2.next;
    	return node1.next;
    }
};


class Solution {
public:
    ListNode* partition(ListNode* head, int x) {
        ListNode left(0), right(0);
        ListNode *l = &left, *r = &right;

        while(head){
            ListNode* & ref = head->val < x ? l : r;
            ref->next = head;
            ref = ref->next;
            
            head = head->next;
        }
        l->next = right.next;
        r->next = NULL;
        return left.next;
    }
};


class Solution {
public:
    ListNode* partition(ListNode* head, int x) {
        
        if (head == NULL)
            return head;
        ListNode dum(-1);
        dum.next = head;
        
        ListNode *pre = &dum; //向前loop的位置
        ListNode *head2 = &dum;//记录所有小于点的位置
        
        while(pre->next != NULL){
            if(pre->next->val < x){
                ListNode *current = pre->next;//小于x的点
                if (pre != head2) {
                    pre->next = current->next;//跳过这个小于的点
                    current->next = head2->next; //把之前小于点后面（后面是大于等于x的）放在这个小于点后面
                    head2->next = current;//把这个小于点挂在所有小于的后面
                }
                else {
                    pre = pre->next;
                }
                head2 = current; //找到小于点，前进一位小于点
            }
            else
                pre = pre->next;
        }
        
        return dum.next;
    }
};