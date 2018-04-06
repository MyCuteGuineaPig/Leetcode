/*
679. 24 Game

You have 4 cards each containing a number from 1 to 9. You need to judge whether they could operated through *, /, +, -, (, ) to 
get the value of 24.

Example 1:
Input: [4, 1, 8, 7]
Output: True
Explanation: (8-4) * (7-1) = 24
Example 2:
Input: [1, 2, 1, 2]
Output: False
Note:
The division operator / represents real division, not integer division. For example, 4 / (1 - 2/3) = 12.
Every operation done is between two numbers. In particular, we cannot use - as a unary operator. For example, with [1, 1, 1, 1] 
as input, the expression -1 - 1 - 1 - 1 is not allowed.
You cannot concatenate numbers together. For example, if the input is [1, 2, 1, 2], we cannot write this as 12 + 12.



*/



class Solution {
public:
    bool judgePoint24(vector<int>& nums) {
        vector<double>num;
        for(int i = 0; i<nums.size();i++) num.push_back(nums[i]);
        return backtrack(num);
    }
    
    bool backtrack(vector<double>nums){
        if(nums.size() == 0) return false;
        if(nums.size() == 1) {
            if(nums[0]<25 && nums[0]>21)
                cout<<nums[0]<<endl;
            return abs(nums[0]-24.0)<0.00001;
        }
        for(int i = 0; i<nums.size();i++)
            for(int j = 0; j<nums.size();j++)
                if(i!=j ){
                    vector<double>arr;
                    for(int k = 0; k<nums.size();k++) if (k!=i && k!=j) arr.push_back(nums[k]);
                    for(int k = 0; k<4;k++){
                        if(k<2 && j>i|| k==3 && nums[j]==0) continue;
                        if(k == 0) arr.push_back(nums[i]+nums[j]);
                        if(k == 1) arr.push_back(nums[i]*nums[j]);
                        if(k == 2) arr.push_back(nums[i]-nums[j]);
                        if(k == 3 ) arr.push_back(nums[i]/nums[j]);
                        if(backtrack(arr)) return true;
                        arr.pop_back();
                    }
                }
        return false;
    }
    
};


class Solution {
public:
    bool judgePoint24(vector<int>& nums) {
        sort(nums.begin(), nums.end());
        do {
            if (valid(nums)) return true;
        } while(next_permutation(nums.begin(), nums.end()));
        return false;
    }
private:
    bool valid(vector<int>& nums) {
        double a = nums[0], b = nums[1], c = nums[2], d = nums[3];
        if (valid(a+b, c, d) || valid(a-b, c, d) || valid(a*b, c, d) || valid(a/b, c, d)) return true;
        if (valid(a, b+c, d) || valid(a, b-c, d) || valid(a, b*c, d) || valid(a, b/c, d)) return true;
        if (valid(a, b, c+d) || valid(a, b, c-d) || valid(a, b, c*d) || valid(a, b, c/d)) return true;
        return false;
    }
    bool valid(double a, double b, double c) {
        if (valid(a+b, c) || valid(a-b, c) || valid(a*b, c) || b&&valid(a/b, c)) return true;
        if (valid(a, b+c) || valid(a, b-c) || valid(a, b*c) || c&&valid(a, b/c)) return true;
        return false;
    }
    bool valid(double a, double b) {
        if (abs(a+b-24.0) < 0.0001 || abs(a-b-24.0) < 0.0001 || abs(a*b-24.0) < 0.0001 || b&&abs(a/b-24.0) < 0.0001) 
            return true;
        return false;
    }
};
