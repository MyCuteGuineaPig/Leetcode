/*
135. Candy
https://leetcode.com/problems/candy/description/

There are N children standing in a line. Each child is assigned a rating value.

You are giving candies to these children subjected to the following requirements:

Each child must have at least one candy.
Children with a higher rating get more candies than their neighbors.
What is the minimum candies you must give?



*/

class Solution {
public:
    int candy(vector<int>& ratings) {
        if(ratings.size()<=1) return ratings.size();

        vector<int>num(ratings.size(),1);
        for(int i = 1; i<ratings.size();i++){
            if(ratings[i]>ratings[i-1])
                num[i] = num[i-1]+1;
        }
        for(int i = ratings.size()-1; i>0;i--){
            if(ratings[i]<ratings[i-1])
                num[i-1] = max(num[i-1],num[i]+1);
        }
        return accumulate(num.begin(),num.end(),0);
    }
};