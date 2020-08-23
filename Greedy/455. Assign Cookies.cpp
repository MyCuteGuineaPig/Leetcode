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
        priority_queue<int, vector<int>, greater<int>> gq(g.begin(), g.end());//minHeap, 先pop小的
        priority_queue<int, vector<int>, greater<int>> sq(s.begin(), s.end());//minHeap, 先pop小的
        int res = 0 ;
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