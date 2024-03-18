class Solution {
public:
    ListNode* removeZeroSumSublists(ListNode* head) {
        ListNode* res = new ListNode();
        res->next = head;
        ListNode* cur = res->next;
        unordered_map<int, ListNode*>mp; 
        mp[0] = res;
        int tot = 0, prev = 0;
        while(cur){
            tot += cur->val;
            cout<<" cur->val "<<cur->val<<" tot "<<tot<<endl;
            if(mp.count(tot)){
                //cout<<" has "<<" prev "<< mp[tot]->val <<endl;
                ListNode* tmp = mp[tot]->next;
                int tmp_tot = tot;
                
                while(tmp != cur){
                    tmp_tot += tmp->val;
                    mp.erase(tmp_tot);
                    tmp = tmp->next;
                }
                mp[tot]->next = cur->next;
                
                ListNode* r2 = res->next;
            } else {
                cout<<" [not counter] "<<endl;
                mp[tot] = cur;
            }
            //prev = tot;
            cur = cur->next;
        }
        return res->next;
    }
};