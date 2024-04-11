class Solution {
public:
	int maximumElementAfterDecrementingAndRearranging(vector<int>& arr) {
        int n = arr.size();
		// for a size n array, the max number could be n
		// so all number > n is treated as n
        vector<int> cnt(n + 1);
        for (int a : arr)
            ++cnt[min(a, n)];
        
        int top = 1;
        for (int val = 1; val <= n; ++val){
				// the top value can be increased cnt[val] times, but can't larger than the val
				top = min(top + cnt[val], val);
                //top 是上一个满足的解, 
                //比如[1,2,3,3,6,6,8,10]  到3 时候 top = min (3+2, 3) = 3
                //到6的时候, top = min(3+3, 6) =  5, 让array 变成[1,2,3,3,4,5] 可以满足
                //cout<<" val "<<val<<" top "<<top<<endl;
        }
        
        return top;
    }
};