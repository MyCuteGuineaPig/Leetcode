/*
455. Assign Cookies
https://leetcode.com/problems/assign-cookies/description/

Assume you are an awesome parent and want to give your children some cookies. 
But, you should give each child at most one cookie. Each child i has a greed factor gi, 
which is the minimum size of a cookie that the child will be content with; and each cookie j has a size sj. 
If sj >= gi, we can assign the cookie j to the child i, and the child i will be content. 
Your goal is to maximize the number of your content children and output the maximum number.

Note:
You may assume the greed factor is always positive. 
You cannot assign more than one cookie to one child.

Example 1:
Input: [1,2,3], [1,1]

Output: 1

Explanation: You have 3 children and 2 cookies. The greed factors of 3 children are 1, 2, 3. 
And even though you have 2 cookies, since their size is both 1, you could only make the child whose greed factor is 1 content.
You need to output 1.
Example 2:
Input: [1,2], [1,2,3]

Output: 2

Explanation: You have 2 children and 3 cookies. The greed factors of 2 children are 1, 2. 
You have 3 cookies and their sizes are big enough to gratify all of the children, 
You need to output 2.


*/

class Solution {
public:
    int findContentChildren(vector<int>& g, vector<int>& s) {
        sort(g.begin(),g.end(),[](int a, int b){return a<b;});
        sort(s.begin(),s.end());
        int i = 0, j=0, count = 0;
        while(i<g.size() && j<s.size()){
            if(g[i]>s[j]) j++;
            else if (g[i++]<=s[j++]) count++;
        }
        return count;
    }
};

class Solution {
public:
    int findContentChildren(vector<int>& g, vector<int>& s) {
        sort(g.begin(), g.end()); sort(s.begin(), s.end());
        int i = 0;
        for(int j = 0; i<g.size() && j<s.size();){
            if(s[j]<g[i]) j++;
            else if(s[j]>=g[i]) i++, j++;
        }
        return i;
    }
};


class Solution {
public:
    int findContentChildren(vector<int>& g, vector<int>& s) {
        priority_queue<int, vector<int>, greater<int>> gq(g.begin(), g.end());
        priority_queue<int, vector<int>, greater<int>> sq(s.begin(), s.end());
        int res;
        while(!sq.empty() && !gq.empty())
        {
            if (sq.top()>=gq.top())
            {
                sq.pop();
                gq.pop();
                res++;
            }
            else
            {
                sq.pop();
            }
        }

        return res;
    }
};