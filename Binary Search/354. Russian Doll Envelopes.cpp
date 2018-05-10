/*
354. Russian Doll Envelopes
You have a number of envelopes with widths and heights given as a pair of integers (w, h). 
One envelope can fit into another if and only if both the width and height of one envelope is greater than the width and height of the other envelope.

What is the maximum number of envelopes can you Russian doll? (put one inside other)

Example:
Given envelopes = [[5,4],[6,4],[6,7],[2,3]], the maximum number of envelopes you can Russian doll is 3 ([2,3] => [5,4] => [6,7]).

*/

class Solution {
public:
    int maxEnvelopes(vector<pair<int, int>>& envelopes) {
        if(envelopes.empty()) return 0;
        vector<int>dp(envelopes.size(),1);
        sort(envelopes.begin(),envelopes.end(),[](const pair<int,int>a, const pair<int,int>b){
            if(a.first == b.first) return a.second > b.second; else return a.first > b.first;
        }); //把大的element放前main
        for(int i = 1; i<envelopes.size();i++)
            for(int j = 0; j<i;j++)
                if(envelopes[i].first<envelopes[j].first && envelopes[i].second<envelopes[j].second)
                    dp[i] = max(dp[i], dp[j]+1);
        return *max_element(dp.begin(),dp.end());
    }
};

/*
Sort the array. Ascend on width and descend on height if width are same.
Find the longest increasing subsequence based on height.
Since the width is increasing, we only need to consider height.
[3, 4] cannot contains [3, 3], so we need to put [3, 4] before [3, 3] when sorting otherwise it will be counted as an increasing number if the order is [3, 3], [3, 4]

*/




class Solution {
public:
    int maxEnvelopes(vector<pair<int, int>>& envelopes) {
        if(envelopes.empty()) return 0;
        vector<int>dp;
        sort(envelopes.begin(),envelopes.end(),[](const pair<int,int>a, const pair<int,int>b){
            if(a.first == b.first) return a.second > b.second; else return a.first < b.first;
        }); /*按照width由小到达排序，按照height又大到小排序， 同样width，把height由大到小排序，可以避免同样width，不一样height，不可以组
         的element放前main, 比如[[2,3],[3,1],[3,5]] sort时候要把[3,5] 放在[3,1]前面，因为这样才能保证[2,3]，[3,5] 可以组，
        比如[[2,3],[3,1],[3,3]] 要是把[3,1] 放在[3,3] 前面，按照height [3，1],[3,3] 就可以组了
        */
        
        //for(auto i: envelopes)
        //    cout<<i.first<<" "<<i.second<<endl;
        for(auto e: envelopes){
            auto it = lower_bound(dp.begin(),dp.end(),e.second);
            if(it == dp.end()) dp.push_back(e.second);
            else *it = e.second;
        }
        return dp.size();
    }
};



class Solution {
public:
    int maxEnvelopes(vector<pair<int, int>>& envelopes) {
        if(envelopes.empty()) return 0;
        vector<int>dp;
        sort(envelopes.begin(),envelopes.end(),[](const pair<int,int>a, const pair<int,int>b){
            if(a.first == b.first) return a.second > b.second; else return a.first < b.first;
        }); /*按照width由小到达排序，按照height又大到小排序， 同样width，把height由大到小排序，可以避免同样width，不一样height，不可以组
         的element放前main, 比如[[2,3],[3,1],[3,5]] sort时候要把[3,5] 放在[3,1]前面，因为这样才能保证[2,3]，[3,5] 可以组，
        比如[[2,3],[3,1],[3,3]] 要是把[3,1] 放在[3,3] 前面，按照height [3，1],[3,3] 就可以组了

        dp\[i] 存组成递增subarray长度为i+1时，末尾最小数
        */
        
        //for(auto i: envelopes)
        //    cout<<i.first<<" "<<i.second<<endl;
        for(auto e: envelopes){
            int i = 0, j = dp.size();
            while(i<j){
                int mid = i + (j-i)/2;
                if(dp[mid]<e.second)
                    i = mid+1;
                else j = mid;
            }
            if(i==dp.size()) dp.push_back(e.second);
            else dp[i] = e.second;
        }
        return dp.size();
    }
};