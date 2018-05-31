/*
142. Linked List Cycle II

Given a linked list, return the node where the cycle begins. If there is no cycle, return null.

Note: Do not modify the linked list.

Follow up:
Can you solve it without using extra space?


*/


/*

Alogrithm Description:
Step 1: Determine whether there is a cycle

1.1) Using a slow pointer that move forward 1 step each time

1.2) Using a fast pointer that move forward 2 steps each time

1.3) If the slow pointer and fast pointer both point to the same location after several moving steps, there is a cycle;

1.4) Otherwise, if (fast->next == NULL || fast->next->next == NULL), there has no cycle.

Step 2: If there is a cycle, return the entry location of the cycle

2.1) L1 is defined as the distance between the head point and entry point

2.2) L2 is defined as the distance between the entry point and the meeting point

2.3) C is defined as the length of the cycle

2.4) n is defined as the travel times of the fast pointer around the cycle When the first encounter of the slow pointer and the fast pointer

According to the definition of L1, L2 and C, we can obtain:

the total distance of the slow pointer traveled when encounter is L1 + L2

the total distance of the fast pointer traveled when encounter is L1 + L2 + n * C

Because the total distance the fast pointer traveled is twice as the slow pointer, Thus:

2 * (L1+L2) = L1 + L2 + n * C => L1 + L2 = n * C => L1 = (n - 1) C + (C - L2)*



It can be concluded that the distance between the head location and entry location is equal to the distance between the meeting location and the entry location along the direction of forward movement.

So, when the slow pointer and the fast pointer encounter in the cycle, we can define a pointer "entry" that point to the head, 
this "entry" pointer moves one step each time so as the slow pointer. 
When this "entry" pointer and the slow pointer both point to the same location, 
this location is the node where the cycle begins.

my solution is like this: using two pointers, one of them one step at a time. another pointer each take two steps. Suppose the first meet at step k,the length of the Cycle is r. so..2k-k=nr,k=nr
Now, the distance between the start node of list and the start node of cycle is s. the distance between the start of list and the first meeting node is k(the pointer which wake one step at a time waked k steps).the distance between the start node of cycle and the first meeting node is m, so...s=k-m,
s=nr-m=(n-1)r+(r-m),here we takes n = 1..so, using one pointer start from the start node of list, another pointer start from the first meeting node, all of them wake one step at a time, the first time they meeting each other is the start of the cycle.

*/


class Solution {
public:
    ListNode *detectCycle(ListNode *head) {
        if (head == NULL || head->next == NULL)
            return NULL;

        ListNode *slow  = head;
        ListNode *fast  = head;
        ListNode *entry = head;

        while (fast->next && fast->next->next) {
            slow = slow->next;
            fast = fast->next->next;
            if (slow == fast) {                      // there is a cycle
                while(slow != entry) {               // found the entry location
                    slow  = slow->next;
                    entry = entry->next;
                }
                return entry;
            }
        }
        return NULL;                                 // there has no cycle
    }
};

/*  
    我们可以使用两枚指针oneStep、twoStep，每次分别移动1、2步，若存在圈，则两枚指针在第1、2、3、4...n圈后终会相遇(我们并不知道会在第几圈相遇)
    整个圈：1 -> 2 -> 3 -> 1
    部分圈：1 -> 2 -> 3 -> 4 -> 5 -> 6 -> 7 -> 8 -> 9 -> 10 -> 11 -> 12 -> 13 -> 14 -> 15 -> 5(跟5相连，形成圈)
           |<--------s------->| |<----------------------------r------------------------>|
           |<--------------------k----------------------->|
           |<------------------------------------2k--------------------------------------  
                                 ------------------------>|
           我们假设链表头到圈始点长度为s，圈长度为r，移动两枚指针后，相遇时oneStep走了k步，twoStep则走了2k步：
           1. 我们知道相遇时twoStep比oneStep多走了n圈，(1)(2k - s) - (k - s) = nr  =>  k = nr  =>  k = r (n = 1)
              (注意：我们取n = 1，即twoStep比oneStep多走一圈，因为一旦相遇我们便知道了有圈)

            k = r 于是便有了下面这幅图：
    部分圈：1 -> 2 -> 3 -> 4 -> 5 -> 6 -> 7 -> 8 -> 9 -> 10 -> 11 -> 12 -> 13 -> 14 -> 15 -> 5(跟5相连，形成圈)
           |<--------s------->| |<----------------------------r------------------------>|        
           |<--------------------r----------------------->|
           |<------------------------------------2r--------------------------------------  
                                 ------------------------>|
           2. s(我们知道s就是我们要求的圈始点)怎么求呢？
       
           3. 眼尖的同学可能已经看出来了，没错 s + r = 链表总长度，我们再将oneStep或者twoStep移动s就会再次相遇！
           
           于是便有了下面这幅图：
    部分圈：1 -> 2 -> 3 -> 4 -> 5 -> 6 -> 7 -> 8 -> 9 -> 10 -> 11 -> 12 -> 13 -> 14 -> 15 -> 5(跟5相连，形成圈)
           |<--------s------->| |<----------------------------r------------------------>|        
           |<--------------------r----------------------->| |************* s ************|
           |<------------------------------------2r--------------------------------------  
                                 ------------------------>| |************* s ************|
          
          4. 现在我们让oneStep再次从head开始，oneStep和twoStep每次均移动一步，再次相遇就会在起始点咯！

          5. 大家可以自行思考整个圈的情况是否如此.
*/


class Solution {
public:
    ListNode *detectCycle(ListNode *head) {
        ListNode * ret;
        ListNode *slow = head;
        ListNode *fast = head;
        ListNode *meetNode = NULL;
        while(fast != NULL) {
            fast = fast->next;
            slow = slow->next;
            if(fast == NULL) return NULL;
            fast = fast->next;
            if(slow == fast) {
                meetNode = slow;
                break;
            }
        }
        
        if(meetNode != NULL) {
            ListNode *start = meetNode->next;
            int length=1;
            while(start != meetNode) {
                start = start->next;
                length++;
            }
            start = head;
            int i=length;
            while(i-- > 0) {
                start=start->next;
            }
            ListNode *tmp = head;
            while(tmp != start) {
                tmp=tmp->next;
                start = start->next;
            }
            return tmp;
        }
        
        return NULL;
    }
};