/**
 * 2020 
 如果现在这位开头是0, 必须作为flip的起点, ++cnt, 如果cnt是偶数，cur = A[i]不变，
                                            如果cnt是奇数, cur = A[i]^1
 */

class Solution {
public:
    int minKBitFlips(vector<int>& A, int K) {
        queue<int>q; 
        int need = 0, cnt = 0;
        for(int i = 0; i< A.size(); ++i){
            int cur = cnt & 1 ? 1 ^ A[i] : A[i];
            if(cur == 0){
                ++cnt; ++need;
                q.push(i+K-1);
            }
            if(q.size() && q.front() == i){
                q.pop();
                --cnt;
            }
        }
        return q.empty() ? need: -1;
    }
};