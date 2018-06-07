/*
160. Intersection of Two Linked Lists


Write a program to find the node at which the intersection of two singly linked lists begins.


For example, the following two linked lists:

A:          a1 → a2
                   ↘
                     c1 → c2 → c3
                   ↗            
B:     b1 → b2 → b3
begin to intersect at node c1.


Notes:

If the two linked lists have no intersection at all, return null.
The linked lists must retain their original structure after the function returns.
You may assume there are no cycles anywhere in the entire linked structure.
Your code should preferably run in O(n) time and use only O(1) memory.


*/


/*

Approach #3 (Two Pointers) [Accepted]
Maintain two pointers pA and pB initialized at the head of A and B, respectively. 
Then let them both traverse through the lists, one node at a time.

When pA reaches the end of a list, then redirect it to the head of B (yes, B, that's right.); 
similarly when pB reaches the end of a list, redirect it the head of A.

If at any point pA meets pB, then pA/pB is the intersection node.

To see why the above trick would work, consider the following two lists: A = {1,3,5,7,9,11} and B = {2,4,9,11}, 
which are intersected at node '9'. Since B.length (=4) < A.length (=6), 
pB would reach the end of the merged list first, because pB traverses exactly 2 nodes less than pA does. 
By redirecting pB to head A, and pA to head B, we now ask pB to travel exactly 2 more nodes than pA would. 
So in the second iteration, they are guaranteed to reach the intersection node at the same time.
If two lists have intersection, then their last nodes must be the same one. So when pA/pB reaches the end of a list, 
record the last element of A/B respectively. If the two last elements are not the same one, 
then the two lists have no intersections.
*/


/*
利用的是 lA + lB_1 =  lA_1 + lB (lenA + B交点前的长度 = lenB + A交点前的长度)， pA，pB 每次都前进一步，pA到end,pA设为Bhead, pB到end,pB设为Aend
这种尾对头只换一次，第二次pA 或者pB到end 返回NULL(就是没有交点)

A = {1,3,5,7,9,11} and B = {2,4,9,11},
比如 A长度是6， B长度是4， 
pB 前进为 2, 4, 9, 11, 1 ,3 ,5 ,7, 9
pA 前进为 1, 3, 5, 7,  9, 11, 2, 4, 9

把A长度设为 lenA, intersection前长度为lA_1, intersection后长度为lA_2（包括intersection）
把B长度设为 lenB, intersection前长度为lB_1, intersection后长度为lB_2（包括intersection）
lA_2 = lB_2

lA + lB_1 = lA_1 + lA_2 + lb_1 = lA_1 + lB_2 + LB_1 
          =  lA_1 + lB


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
    ListNode *getIntersectionNode(ListNode *headA, ListNode *headB) {
        ListNode *curA = headA, *curB = headB;
        bool nextA = true, nextB = true;
        while(curA && curB){
            if(curA == curB) 
                return curA;
            
            if (curA->next){
                curA = curA->next;
            }else if(nextA){
                nextA = false;
                curA = headB;
            }else break;
            
            if(curB->next) 
                curB = curB->next;
            else if(nextB){
                nextB = false;
                curB = headA;
            }else break;
        }
        return NULL;
    }
};


class Solution {
public:
    //solution 1
    //两个链表上的指针同时遍历，当一个指针到达链表的尾部（NULL），那么让该指针指向另一个链表的头指针
    //这两个指针必然会相遇（有两种情况，一种是在交叉处相遇，另一种是到达各自链表的尾部（NULL））
    ListNode *getIntersectionNode(ListNode *headA, ListNode *headB) {
        if(headA==NULL||headB==NULL){
            return NULL;
        }
        ListNode* A_curr=headA;
        ListNode* B_curr=headB;
        while(A_curr!=B_curr){
            A_curr=A_curr?A_curr->next:headB;//当前指针不为NULL,则让他指向next指针；若当前指针为NULL,则让他指向另外一个链表的头指针
            B_curr=B_curr?B_curr->next:headA;
        }
        return A_curr;
    }
};



class Solution {
public:
    ListNode *getIntersectionNode(ListNode *headA, ListNode *headB) {
        if (!headA || !headB)
            return nullptr;

        auto cA = headA;
        int lA = 0;
        while (cA) { cA = cA->next; ++lA; }
        
        auto cB = headB;
        int lB = 0;
        while (cB) { cB = cB->next; ++lB; }
        
        cA = headA;  //找长度大的，然后磨平开始的长度差
        cB = headB;
        int shift = abs(lA - lB);
        if (lA > lB)
            while (shift-- > 0) cA = cA->next;
        else
            while (shift-- > 0) cB = cB->next;
        
        while (cA != cB) {
            cA = cA->next;
            cB = cB->next;
        }
        
        return cA;
    }
};



class Solution {
public:
    ListNode *getIntersectionNode(ListNode *headA, ListNode *headB) 
    {
        ListNode *p1 = headA;
        ListNode *p2 = headB;

        if (p1 == NULL || p2 == NULL) return NULL;

        while (p1 != NULL && p2 != NULL && p1 != p2) {
            p1 = p1->next;
            p2 = p2->next;

            //
            // Any time they collide or reach end together without colliding 
            // then return any one of the pointers.
            //
            if (p1 == p2) return p1;

            //
            // If one of them reaches the end earlier then reuse it 
            // by moving it to the beginning of other list.
            // Once both of them go through reassigning, 
            // they will be equidistant from the collision point.
            //
            if (p1 == NULL) p1 = headB;
            if (p2 == NULL) p2 = headA;
        }

        return p1;
    }
};





//Just store addition information in 'next' pointers.
//It's work because memory alignment

ListNode *getIntersectionNode(ListNode *headA, ListNode *headB) {
    for (ListNode *cur = headA; cur;) {
        unsigned long *ptr = (unsigned long *)&cur->next;
        cur = cur->next;
        *ptr |= 1;
    }

    ListNode *result = nullptr;
    for (ListNode *cur = headB; cur; cur = cur->next) {
        unsigned long ptr = (unsigned long)cur->next;
        if (ptr & 1) {
            result = cur;
            break;
        }
    }
    
    for (ListNode *cur = headA; cur; cur = cur->next) {
        unsigned long *ptr = (unsigned long *)&cur->next;
        *ptr &= (~0ULL << 1);
    }

    return result;
}