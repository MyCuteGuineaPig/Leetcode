/*
241. Different Ways to Add Parentheses

Given a string of numbers and operators, return all possible results from computing all the different possible ways to group numbers and operators. 
The valid operators are +, - and *.

Example 1:

Input: "2-1-1"
Output: [0, 2]
Explanation: 
((2-1)-1) = 0 
(2-(1-1)) = 2
Example 2:

Input: "2*3-4*5"
Output: [-34, -14, -10, -10, 10]
Explanation: 
(2*(3-(4*5))) = -34 
((2*3)-(4*5)) = -14 
((2*(3-4))*5) = -10 
(2*((3-4)*5)) = -10 
(((2*3)-4)*5) = 10


*/

//self, beat 100% speed, 100% memory
class Solution {
public:
    void helper(unordered_map<int,unordered_map<int, vector<int>>>&mp, const vector<int>&nums, const vector<char>& signs, int start, int end){
        for(int i = start; i<end; ++i){
            vector<int>left;
            if(mp.find(start) == mp.end() || mp[start].find(i) == mp[start].end())
                helper(mp, nums, signs,start, i);
            left = mp[start][i]; 
            vector<int>right;
            if(mp.find(i+1) == mp.end() || mp[i+1].find(end) == mp[i+1].end())
                helper(mp, nums, signs, i+1, end);
            right = mp[i+1][end];   
            //cout<<"start "<<start<<" end "<<end<<" i "<<i<<" left "<<left.size()<<" right "<<right.size() <<endl;
            for(auto l: left)
                for(auto r: right)
                    mp[start][end].push_back(cal(l, r, signs[i]));
        }
    }
    
    void parse(const string& s, vector<int>&nums, vector<char>& signs, unordered_map<int,unordered_map<int, vector<int>>>&mp ){
        int n = 0, cnt = 0;
        for(auto i:  s){
            if(isdigit(i)){
                n = n*10 + i-'0';   
            }
            else {
                nums.push_back(n);
                mp[cnt][cnt++].push_back(n);
                n = 0;
                signs.push_back(i);
            }
        }
        mp[cnt][cnt].push_back(n);
        nums.push_back(n);
    }
    
    int cal(int a, int b, char sign){
        if(sign == '+') return a+b;
        else if(sign == '-') return a-b;
        return a*b;
    }
    
    vector<int> diffWaysToCompute(string input) {
        unordered_map<int,unordered_map<int, vector<int>>>mp; //key is start, end is second key
        vector<int>nums;   vector<char>signs;
        parse(input, nums, signs, mp);
        helper(mp, nums, signs, 0, nums.size()-1);
        return mp[0][nums.size()-1];
    }
};






class Solution {
public:
    unordered_map<int, unordered_map<int,vector<int>>>dp;
    vector<int> diffWaysToCompute(string input) {
        return helper(input,0,input.size()-1);
    }
    
    vector<int>helper(const string &input,int i, int end){
        if(dp.count(i) && dp[i].count(end)) return dp[i][end];
        vector<int>res;
        int beg = i; 
        while(i<=end){
            if(ispunct(input[i])){
                vector<int>before = helper(input, beg, i-1);
                vector<int>after = helper(input,i+1,end);
                for(auto v1: before)
                    for(auto v2: after)
                        res.push_back(calcul(input[i],v1,v2));
            }
            i++;
        }
        return dp[beg][end] = res.size()? res : vector<int>({convertToNum(input,beg)});
    }
    
    int calcul(char sign, int v1, int v2){
        if(sign == '+') return v1+v2;
        else if(sign == '-')  return v1-v2;
        else if(sign == '/' && v2!=0)  return v1/v2;
        else return v1*v2;
    }
    
    int convertToNum(const string &input, int i){
        int start = i;
        while(i<=input.size() && isdigit(input[i])) 
            i++;
        return stoi(input.substr(start,i-start));
    }
};



class Solution {
public:
    vector<int> diffWaysToCompute(string input) {
        vector<int>res;
        for(int i = 0; i<input.size();i++){
            if(isdigit(input[i])) continue;
            vector<int>before = diffWaysToCompute(input.substr(0,i));
            vector<int>after = diffWaysToCompute(input.substr(i+1));
            for(auto b:before)
                for(auto a:after)
                    if(input[i] == '+') res.push_back(a+b);
                    else if(input[i] == '-')  res.push_back(b-a);
                    else if(input[i] == '/' && b!=0)  res.push_back(b/a);
                    else res.push_back(a*b);
        }
        return res.size() ? res : vector<int>{stoi(input)};
    }
};
