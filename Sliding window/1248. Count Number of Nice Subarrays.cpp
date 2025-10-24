class Solution {
public:
    int numberOfSubarrays(vector<int>& nums, int k) {
        auto f = [&](this auto && f, int k){
            int res = 0; 
            int odd = 0;
            int l = 0;
            int n  = nums.size();
            for(int i = 0; i < n ; ++i) {
                odd += nums[i] & 1;
                while(odd > k) {
                    odd -= nums[l++] & 1;
                }
                //cout <<" i "<<i<<" l "<<l <<endl;
                res += i - l + 1;
            }
            return res;
        };
        return f(k) - f(k-1);
    }
};



class Solution {
public:
    int numberOfSubarrays(vector<int>& nums, int k) {
        int res = 0; 
        int odd = 0;
        unordered_map<int,int >mp;
        mp[0] = 1;
        int n  = nums.size();
        for(int i = 0; i < n ; ++i) {
            odd += nums[i] & 1;
            res += mp[odd-k];
            mp[odd] += 1;
        }
        return res;
    }
};


/*

q based approach, q.front() 是第一个可以组成k个odd number的index

*/
class Solution {
public:
    int numberOfSubarrays(vector<int>& nums, int k) {
        int res = 0; 
        queue<int> q; //store all the odd number index 
        int lastPopped = -1;
        int n  = nums.size();
        for(int i = 0; i < n ; ++i) {
            if (nums[i] & 1) 
                q.push(i);
            if (q.size() > k) {
                lastPopped = q.front();
                q.pop();
            }
            if (q.size() == k) {
           /*
           important logic
           */  res += q.front() - lastPopped;//是q.front()
            }
        }
        return res;
    }
};

/*

While iterating through all possible endpoints of the windows, 
keep track of the count of odd values using an integer qsize. If qsize reaches k, 
adjust the start pointer to skip over even values at the beginning of the subarray 
until an odd value is encountered.
 */

class Solution {
public:
    int numberOfSubarrays(vector<int>& nums, int k) {
        int res = 0; 
        int l  = 0;
        int odd = 0;
        int initial_gap = 0;
        int n  = nums.size();
        for(int i = 0; i < n ; ++i) {
            odd += nums[i] & 1;
            if (odd == k) {
                initial_gap = 0; //表示在当前 有几个符合的
                while(odd == k) {
                    ++initial_gap;
                    odd -= nums[l++] & 1;
                }
            }
            res += initial_gap;
        }
        return res;
    }
};