class Solution {
public:
    ListNode* deleteDuplicatesUnsorted(ListNode* head) {
        unordered_map<int,int>cnt;
        ListNode* cur = head;
        while(cur){
            ++cnt[cur->val];
            cur = cur->next;
        }
        ListNode* tmp = new ListNode(0);
        tmp->next = head;
        cur = tmp;
        while(cur && cur->next){
            while(cur->next && cnt[cur->next->val] > 1)
                cur->next = cur->next->next;
            cur = cur->next;
        }
        return tmp->next;
    }
};

class Solution {
public:
    ListNode* deleteDuplicatesUnsorted(ListNode* head) {
        ListNode tmp(0, head);
        unordered_map<int, int> m;
        for (auto p = head; p != nullptr; p = p->next)
            ++m[p->val];
        for (auto p = &tmp, c = &tmp; p != nullptr; p = p->next) {
            c->next = p->next;
            if (p->next && m[p->next->val] == 1)
                c = c->next;
        }
        return tmp.next;
    }
};