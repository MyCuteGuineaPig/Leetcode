class Solution {
public:
    int longestSubarray(vector<int>& nums) {
        int l = 0; 
        int cnt = 0;
        int res = 0;
        for(int i = 0; i < nums.size(); ++i){
            cnt += nums[i] == 0;
            while(cnt > 1) {
                cnt -= (nums[l++] == 0);
            }
            res = max(res, i - l ); //没有i-l+1 因为除去0
        }
        return res;
    }
};


class Solution {
public:
    int longestSubarray(vector<int>& nums) {
        int l = 0; 
        int cnt = 0;
        int res = 0;
        int n = nums.size();
        for(int i = 0; i < nums.size(); ++i){
            cnt += nums[i] == 0;
            if (cnt > 1) {
                cnt -= nums[l++] == 0;
            }            
        }
        return n - l -1;
    }
};


//Q based approach 
class Solution {
public:
    int longestSubarray(vector<int>& nums) {
        queue<int>q;
        int res = 0;
        int n = nums.size();
        int lastpop = 0; //0之后的一位
        for(int i = 0; i < nums.size(); ++i){
            if (nums[i] == 0) {
                q.push(i);
            }
            if (q.size() >= 2) {
                lastpop = q.front() + 1; 
                q.pop();
            }
            else if (q.size() <= 1){
                res = max(res, i - lastpop);
            }
            
        }
        return res;
    }
};