
/*

rand() % x gives a value in the range of [0, x - 1]. 
rand() % (x + 1) gives a value in the range of [0, x] 

(we will get zero if rand() generates something dividable by x+1).

It is not exactly what we want.
However (rand() % x)+ 1 shifts the value in the range of [0, x - 1] by 1. 
And the final value will be in [1, x] range.
*/

class Solution {
public:

    vector<int>v;
    Solution(vector<int>& w) {
        v = w;
        for(int i =1; i< w.size(); ++i){
            v[i] += v[i-1];
        }
    }
    
    int pickIndex() {
        int num = rand() % (v.back());
        auto ind = upper_bound(v.begin(), v.end(), num) - v.begin();
        return ind;
    }
};
