class Solution {
public:
    int maxSizeSlices(vector<int>& slices) {
        int n = (int)slices.size() / 3;
        auto l1 = vector<int>(slices.begin(), slices.end()-1);
        auto l2 = vector<int>(slices.begin()+1, slices.end());
        return max(linear(l1, n), linear(l2, n));
    }
    
private:
    int linear(vector<int>& slices, int n) {
        vector<vector<int>> eat((int)slices.size()+2, vector<int>(n+1, INT_MIN));

        int res = INT_MIN;
        for (int i=0; i<eat.size(); ++i) eat[i][0] = 0;
        for (int i=2; i<eat.size(); ++i) {
            for (int j=1; j<n+1; ++j)
                eat[i][j] = max(eat[i-1][j], eat[i-2][j-1] + slices[i-2]);
            res = max(eat[i][n], res);
        }
        return res;
    }
};

/*
[4,1,2,5,8,3,1,9,7]
stdout

4, 1, 2, 5, 8, 3, 1, 9,
-----------------------
4, 4, 4, 5, 8, 8, 8, 9, 
0, 0, 6, 9, 12, 12, 12, 17, 
0, 0, 0, 0, 14, 14, 14, 21, 

1, 2, 5, 8, 3, 1, 9, 7
---------------------
1, 2, 5, 8, 8, 8, 9, 9, 
0, 0, 6, 10, 10, 10, 17, 17, 
0, 0, 0, 0, 9, 11, 19, 19, 

 

*/

class Solution {
public:
    int maxSizeSlices(vector<int>& slices) {
        vector<int>s1 (slices.begin(), slices.end()-1);
        vector<int>s2 (slices.begin()+1, slices.end());
        int n = slices.size()/3;
        return max(maxSlice(s1, n), maxSlice(s2, n));
    }
    
    int maxSlice(const vector<int>& slices,int n){
        vector<vector<int>>dp(n, vector<int>(slices.size()));
        int res = 0;
        for(int i = 0; i < n; ++i){ //pieces of pizza to pick 
            for(int j = 0; j<slices.size(); ++j){
                if(i == 0)
                    dp[0][j] = max( j >0 ? dp[0][j-1] : 0, slices[j]) ; //只pick 一个pizza
                else if(j >= 2*i) //i = 1, pick 两个pizza, 开始只能拿0, 2
                                //  i = 2, pick 三个pizza, 开始只能pick 0,2,4
                    dp[i][j]  = max(dp[i][j-1], dp[i-1][j-2] + slices[j]);   
                
                res = max(res, dp[i][j]);
            }
        }
        return res;
    }
};



class Solution {
public:
    int maxSizeSlices(vector<int>& slices) {
        unordered_map<int, unordered_map<int, unordered_map<int, int>>>mp;
        return dp(0,slices.size()-1, slices.size()/3, slices, mp, 1);
    }
    
    int dp(int i , int j, int k, const vector<int>&slices, unordered_map<int, unordered_map<int, unordered_map<int, int>>>&mp, int lastOne = 0){
        if(k == 1)
            return *max_element(slices.begin()+i, slices.begin()+j+1);
        if(j-i + 1 < 2*k - 1)
            return numeric_limits<int>::min();
        if(mp.count(i) && mp[i].count(j) && mp[i][j].count(k))
            return mp[i][j][k];
        return mp[i][j][k] = max(slices[j] + dp(i + lastOne, j-2, k-1, slices, mp), dp(i, j-1, k, slices,mp));;
    }
};