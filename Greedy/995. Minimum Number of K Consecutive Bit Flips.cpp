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


//O(n) space
class Solution {
public:
    int minKBitFlips(vector<int>& A, int K) {
        int n = A.size(), flipped = 0, res = 0;
        vector<int>isFlipped(n);
        for (int i = 0; i < A.size(); ++i) {
            if (i >= K)
                flipped ^= isFlipped[i - K];
            if (flipped == A[i]) { //if not flipped, A[i]=0 是flip起点; if flip,  A[i]=1 是另一个flip起点
                if (i + K > A.size())
                    return -1;
                isFlipped[i] = 1;
                flipped ^= 1;
                res++;
            }
        }
        return res;
    }
};


//O(1) space
class Solution {
public:
    int minKBitFlips(vector<int>& A, int K) {
        int cur = 0, res = 0, n = A.size();
        for (int i = 0; i < n; ++i) {
            if (i >= K && A[i - K] > 1) {
                cur--;
                A[i - K] -= 2;
            }
            if (cur % 2 == A[i]) {
                if (i + K > n) return -1;
                A[i] += 2;
                cur++;
                res++;
            }
        }
        return res;
    }
};