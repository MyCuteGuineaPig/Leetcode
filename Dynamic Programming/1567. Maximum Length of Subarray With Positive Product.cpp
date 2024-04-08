/*

elements      :   9    5    8    2    -6    4    -3    0    2    -5    15    10    -7    9    -2
positive_len  :   1    2    3    4     0    1     7    0    1     0     1     2     5    6     5
negative_len  :   0    0    0    0     5    6     2    0    0     2     3     4     3    4     7

*/

//dp_pos[i] record the longest positive sequence length till i 
//dp_neg[i] record the longest negative sequence length till i

class Solution {
public:
    int getMaxLen(vector<int>& nums) {
        int n = nums.size();
        vector<int>dp_pos(n+1);
        vector<int>dp_neg(n+1);
        for(int i = 0; i < nums.size(); ++i){
            if(nums[i] == 0){
                dp_pos[i+1] = 0;
                dp_neg[i+1] = 0;
            } else if (nums[i] > 0){
                dp_pos[i+1] = dp_pos[i]+1;
                dp_neg[i+1] = dp_neg[i] == 0 ? 0 : dp_neg[i]+1;
            } else {
                dp_pos[i+1] = dp_neg[i] == 0 ? 0 : dp_neg[i]+1;
                //前面没有negative, dp_pos[i+1] = 0 比如  1, 2, -1  到-1 dp_pos[i+1] = 0
                dp_neg[i+1] = dp_pos[i] + 1;
            }
            //cout<<i<<" dp_pos[i+1] "<< dp_pos[i+1] << " dp_neg[i+1] "<< dp_neg[i+1]<<endl;
        }
        return *max_element(dp_pos.begin(), dp_pos.end());
    }
};


class Solution {
    public int getMaxLen(int[] nums) {
        int positive = 0, negative = 0;    // length of positive and negative results
        int ans = 0;
        for(int x : nums) {
            if(x == 0)  {
                positive = 0;
                negative = 0;
            }
            else if(x > 0) {
                positive++;
                negative = negative == 0 ? 0  : negative+1;
            }
            else {
                int temp = positive;
                positive = negative == 0 ? 0  : negative+1;
                negative = temp+1;
            }
            ans = Math.max(ans, positive);
        }
        return ans;
    }
}