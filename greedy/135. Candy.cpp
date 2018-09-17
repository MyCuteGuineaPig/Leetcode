/*
135. Candy
https://leetcode.com/problems/candy/description/

There are N children standing in a line. Each child is assigned a rating value.

You are giving candies to these children subjected to the following requirements:

Each child must have at least one candy.
Children with a higher rating get more candies than their neighbors.
What is the minimum candies you must give?



*/


/*
如果现在rating 比两边都邻居大， 拿的糖需要比两面邻居都要多, candy[i] = max(candy[i-1], candy[i+1])+1,
如果只比左面大，candy[i] = candy[i-1] + 1
如果只比右面大，candy[i] = candy[i+1] + 1

step1: 看左面邻居
先从左到右loop 一遍，如果现在比左面的大，糖就比左面+1， 小于的或者等于的不管，给他们先assign 糖为1

step2: 看右面邻居
从右往左loop，如果比右面大，对比右面糖+1， 和现在比(现在是算了左面的)谁大，keep大的

比如 [1,2,3,1], 在3的位置 左面糖是2，右面糖是1，keep 大的为1
比如 [1,5,6,4,3,2,1], 在6的位置，右侧糖更多

不能担心极值在两边， 比如[10,9,8,6]
从左面loop, candy = [1,1,1,1]
但是从右面loop完，candy 会修正的 = [4,3,2,1]

也不用担心小的值在中间
比如[9,8,7,1,4,5], 中间1最小，
从左面loop, candy = [1,1,1,1, 2, 3] 把小的值(1)右面改了
从右面loop完，candy = [4,3,2,1，2，3] 把小的值(1)左面改了


*/

class Solution {
public:
    int candy(vector<int>& ratings) {
        if(ratings.size()<=1) return ratings.size();
        int n = ratings.size();
        vector<int>candy(n, 1);

        for(int i = 1; i<n; i++)
            if(ratings[i] > ratings[i-1])
                candy[i] = candy[i-1]+1;
        
        for(int i = n-2; i>=0; i--)
            if(ratings[i] > ratings[i+1])
                candy[i] = max(candy[i], candy[i+1]+1);
        
        return accumulate(candy.begin(), candy.end(), 0);
    }
};



class Solution {
public:
    int candy(vector<int>& ratings) {
        int n = ratings.size();
        vector<int> left(n), right(n);
        left[0] = right[n - 1] = 1;
        for (int i = 1; i < n; ++i) {
            if (ratings[i] > ratings[i - 1]) left[i] = left[i - 1] + 1;
            else left[i] = 1;
            if (ratings[n - i] < ratings[n - i - 1]) right[n - i - 1] = right[n - i] + 1;
            else right[n - i - 1] = 1;
        }
        int c = 0;
        for (int i = 0; i < n; ++i) c += max(left[i], right[i]);
        return c;
    }
};



class Solution {
public:
    int candy(vector<int>& ratings) {
        typedef pair<int, int> pin;
        priority_queue<pin, vector<pin>, greater<pin>> pq; //由小到大一个一个pop,然后变邻居的糖
        for(int i = 0; i < ratings.size(); i++)
            pq.push({ratings[i], i});
        vector<int> candies(ratings.size(), 1);
        while(pq.size()){
            pin next = pq.top();
            pq.pop();
            int val = next.first, idx = next.second;
            if(idx - 1 >= 0 && ratings[idx-1] > ratings[idx] && candies[idx-1] <= candies[idx])
                candies[idx-1] = candies[idx] + 1;
            if(idx + 1 < ratings.size() && ratings[idx+1] > ratings[idx] && candies[idx+1] <= candies[idx])
                candies[idx+1] = candies[idx] + 1;
        }
        int su = 0;
        for(auto c:candies)
            su += c;
        return su;
    }
};

class Solution {
public:
    int candy(vector<int>& ratings) {
        typedef pair<int, int> pin;
        priority_queue<pin, vector<pin>, greater<pin>> pq; //由小到大一个一个pop,然后变邻居的糖
        for(int i = 0; i < ratings.size(); i++)
            pq.push({ratings[i], i});
        vector<int> candies(ratings.size(), 1);
        while(pq.size()){
            pin next = pq.top();
            pq.pop();
            int val = next.first, idx = next.second;
            if(idx - 1 >= 0 && ratings[idx-1] < ratings[idx] && candies[idx-1] >= candies[idx])
                candies[idx] = candies[idx-1] + 1;
            if(idx + 1 < ratings.size() && ratings[idx+1] < ratings[idx] && candies[idx+1] >= candies[idx])
                candies[idx] = candies[idx+1] + 1;
        }
        int su = 0;
        for(auto c:candies)
            su += c;
        return su;
    }
};

/*

Complexity O(n)
Space: O(1)

http://www.allenlipeng47.com/blog/index.php/2016/07/21/candy/

当现在数减小时候 countdown ++， 
当现在数比前一个数大于等于，先把之前减小的部分算上，把连续countdown 的最后一个高度(连续最右侧的)假设为1，连续下降的起点也是最左侧高度为(countdown)
那么这些countdown的高度是 (1+countdown)*countdown/2

如果下降最左侧 等于或者高于 上一个高度，需要增高上一个高度，增高到 countdown + 1, 因为之前算过了pre, 
那么pre 到 countdown + 1增加的是 countdown - pre + 1



*/

class Solution {
public:
    int candy(vector<int>& ratings) {
        if(ratings.size()<=1) return ratings.size();
        int total = 1, pre = 1, countdown = 0;
        for(int i = 1; i<ratings.size(); i++){
            if(ratings[i] >= ratings[i-1]){
                if(countdown > 0){
                    total += (1+countdown)*countdown/2;
                    if(countdown>=pre){
                        total += countdown - pre + 1;
                    }
                    pre = 1;
                    countdown = 0;
                }
                pre = ratings[i] == ratings[i-1] ? 1 : pre+1;
                total += pre;
                
            }else{
                countdown++;
            }
        }
        if(countdown > 0){
            total += (1+countdown)*countdown/2;
            if(countdown>=pre)
                total += countdown - pre + 1;
        }
        return total;
    }
};
