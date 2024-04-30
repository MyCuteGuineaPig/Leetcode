class Solution {
public:

    int medianOfUniquenessArray(vector<int>& nums) {
        int n = nums.size();
        long long total_subarrays = (n+1)*(long long)n/2;
        function<long long(int)> count = [&](int k){
            long long res = 0;
            unordered_map<int,int>mp;
            for(int i = 0, j = 0; j < n; ++j){
                ++mp[nums[j]];
                while(mp.size () > k){
                    if(--mp[nums[i]] == 0 ){
                        mp.erase(nums[i]);
                    }
                    ++i;
                }
                res += j - i + 1;
            }
            return res;
        };
        int left = 1, right = unordered_set<int>(nums.begin(), nums.end()).size();
        while (left < right){
            int mid = (left + right)/2;
            //cout<<" left "<<left<<" right "<<right<<" mid "<<mid<<" mid count "<<count(mid) <<endl;
            if(count(mid) * 2 >= total_subarrays){
                right = mid;
            } else {
                left = mid + 1;
            }
        }
        return left;
    }
};