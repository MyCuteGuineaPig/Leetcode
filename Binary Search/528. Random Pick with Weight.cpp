
/*

rand() % x gives a value in the range of [0, x - 1]. 
rand() % (x + 1) gives a value in the range of [0, x] 

(we will get zero if rand() generates something dividable by x+1).

It is not exactly what we want.
However (rand() % x)+ 1 shifts the value in the range of [0, x - 1] by 1. 
And the final value will be in [1, x] range.
*/


/*

why upper_bound not lower_bound

As far as I understand it is because after mod (%)
 operation you will get a value in the range of [0, x -1]. 

But you actually need a value in the range of [1, x]. So one way is to keep it in mind and 
 just search for the value greater than the generated one. And upper_bound does the trick here.
The other option is to increase the generated value and then use lower_bound:

int index = rand() % x + 1;
auto it = lower_bound(s.begin(), s.end(), index);


for example [1,2,3]

generate 1 for 1 
generate 2, 3 for 2 
generate 4,5,6 for 3
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
