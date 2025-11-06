class Solution {
public:
    int maxConsecutiveAnswers(string answerKey, int k) {
        int f = 0;
        int t = 0;
        int l = 0;
        int res = 1;
        int n  = answerKey.size();
        for(int i = 0; i < n; ++i){
            t += answerKey[i] == 'T';
            f += answerKey[i] == 'F';
            while (t > k && f > k) {
                t -= answerKey[l] == 'T';
                f -= answerKey[l++] == 'F';
            }
            //cout<<"i "<<i<<" l "<<l<<" t "<<endl;
            res = max(res, i - l + 1);
        }
        return res;
    }
};

class Solution {
public:
    int maxConsecutiveAnswers(string answerKey, int k) {
        int f = 0;
        int t = 0;
        int l = 0;
        int res = 1;
        int n  = answerKey.size();
        for(int i = 0; i < n; ++i){
            t += answerKey[i] == 'T';
            f += answerKey[i] == 'F';
            if (t > k && f > k) {
                t -= answerKey[l] == 'T';
                f -= answerKey[l++] == 'F';
            }
        }
        return n - l;
    }
};


class Solution {
public:
    int maxConsecutiveAnswers(string answerKey, int k) {
        int res = 0, maxf = 0; //maxf means the max frequency of the same character in the sliding window.
        unordered_map<int, int> count;
        for (int i = 0; i < answerKey.length(); ++i) {
            maxf = max(maxf, ++count[answerKey[i]]);
            if (res  < k + maxf)
                res++;
            else
                count[answerKey[i - res]]--;
        }
        return res;
    }
};