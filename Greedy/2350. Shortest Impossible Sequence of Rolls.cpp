/*
For a sequence of size 1, all k dice must appear in rolls.
For a sequence of size 2, all k dice must appear after all k dice appear in rolls.
... and so on.

Let us consider an example :

Input: rolls = [4,2,1,2,3,3,2,4,1], k = 4
Output: 3

(Digit 1) (Digit 2)
|--------| |------|
4 2 1 2 3 3 2 4 1

*/


class Solution {
public:
    int shortestSequence(vector<int>& rolls, int k) {
        unordered_set<int>st;
        int res = 1;
        for(auto r: rolls){
            st.insert(r);
            if ( st.size() == k) {
                ++res;
                st.clear();
            }
        }
        return res;
    }
};


class Solution {
public:
    int shortestSequence(vector<int>& rolls, int k) {
        int seq = 0, cnt = 0, dice[100001] = {};
        for (auto r : rolls)
            if (dice[r] == seq) {
                dice[r] = seq + 1;
                if (++cnt % k == 0)
                    ++seq;
            }
        return seq + 1;
    }
};