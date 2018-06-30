/*
473. Matchsticks to Square

Remember the story of Little Match Girl? By now, you know exactly what matchsticks the little match girl has, 
please find out a way you can make one square by using up all those matchsticks. You should not break any stick, 
but you can link them up, and each matchstick must be used exactly one time.

Your input will be several matchsticks the girl has, represented with their stick length. Your output will either be true or false, 
to represent whether you could make one square using all the matchsticks the little match girl has.

Example 1:
Input: [1,1,2,2,2]
Output: true

Explanation: You can form a square with length 2, one side of the square came two sticks with length 1.
Example 2:
Input: [3,3,3,3,4]
Output: false

Explanation: You cannot find a way to form a square with all the matchsticks.
Note:
The length sum of the given matchsticks is in the range of 0 to 10^9.
The length of the given matchstick array will not exceed 15.

*/

class Solution {
public:
    bool makesquare(vector<int>& nums) {
        if(nums.empty()) return false;
        int sum = accumulate(nums.begin(), nums.end(),0);
        if(sum % 4)  return false;
        sort(nums.begin(),nums.end(),[](int a, int b){return a>b;});
        const int target = sum / 4;
        vector<int>used(4);
        return helper(used, nums, target, 0);
    }
    
    bool helper(vector<int>& used, const vector<int>& nums, const int& target, int ind){
        if(ind == nums.size()) {
            return used[0] == used[1] && used[1] == used[2] && used[2] == used[3];
        }
        for(int i = 0; i<4; i++){
            if(used[i] + nums[ind] <= target){
                int j = i-1;
                while(j>=0){
                    if (used[j] == used[i]) break;
                    j--;
                }
                if(j == -1){
                    used[i] += nums[ind];
                    if(helper(used, nums, target, ind+1))
                        return true;
                    used[i] -= nums[ind];
                }
            }
        }
        return false;
    }
};



class Solution {
private:
    void dfs(const vector<int> &nums, vector<int> &sides, const int &n, int cur, const int &target, bool &res) {
        if (cur == n) {
            res = 1;
            return;
        }
        for (int i = 0; i < 4; i++) {
            if (i > 0 && sides[i] == sides[i-1]) continue;
            
            if (sides[i] + nums[cur] <= target) {
                sides[i] += nums[cur];
                dfs(nums, sides, n, cur+1, target, res);
                if (res) return;
                sides[i] -= nums[cur];
            }
        }
    }
    
public:
    bool makesquare(vector<int>& nums) {
        const int n = nums.size();
        if (n < 4) return false;
        int sum = 0;
        for (auto &i : nums) {
            sum += i;
        }
        if (sum % 4 != 0) {
            return false;
        }
        int target = sum/4;
        
        
        for (auto &i : nums) {
            if (i > target) {
                return false;
            }
        }
        
        sort(nums.begin(), nums.end(), greater<int>());
        
        bool res = false;
        vector<int> sides(4, 0);
        dfs(nums, sides, n, 0, target, res);
        return res;
        
        
    }
};


/*
Use bit operation

试全部组合，
比如5个数, 当前组合subset是00101，这个数代表用了第一个数和第三个数，
当subset的和 == 边长时, append to usedsets, 如果used sets中有与当前subset & 为0的（代表两个valid set没有交点，且两个set的和都等于边长）
取两个数的 或，append 到validsets中， 比如当前数 01010， 之前有used set是 101000,这样就append解111100到valid中（这个是两个边长都是valid 边长的使用的）

当所有的数的  与当前subset组合去异或^ （xor），如果也在validsets里面（当前subset的补集），return true
比如： 111111 代表用了所有的数，现在subset是110000， 之前有001111，代表所有的数都用了，可以构成解了

*/


class Solution {
public:
    bool makesquare(vector<int>& nums) {
        if(nums.empty()) return false;
        int sum = accumulate(nums.begin(), nums.end(),0);
        if(sum % 4)  return false;
        int each = sum / 4, n = nums.size();
        int all = (1<<n) - 1;
        unordered_set<int>usedsets, validsets;
        for(int subset = 1; subset<=all; subset++){
            int sum = 0;
            for(int j = 0; j<n; j++){
                if(subset & (1<<j))
                    sum += nums[j];
            }
            if(sum == each){
                for(auto used: usedsets){
                    if((used & subset) == 0){
                        int cur = used | subset;
                        if(validsets.find(all ^ cur)!=validsets.end()) return true;
                        validsets.insert(cur);
                    }
                }
                usedsets.insert(subset);
            }
        }
        return false;     
    }
};