class Solution {
public:
    int totalFruit(vector<int>& tree) {
        unordered_map<int,int>mp;
        int cnt = 0, res = 0, start = 0;
        for(int i = 0; i<tree.size(); ++i){
            if(mp[tree[i]]++ == 0) ++cnt;
            while(cnt > 2){ //if not satify, move to next valid start point
                if(--mp[tree[start++]] == 0) --cnt;
            }
            if(cnt <= 2)
                res = max(res, i - start + 1);
        }
        return res;
    }
};

// keep the maxmize the windows size, 比如 之前最大windows size 是3， 现在windows size = 5 (start 会停住)
class Solution {
public:
    int totalFruit(vector<int>& tree) {
        unordered_map<int,int>mp;
        int cnt = 0, res = 0, start = 0;
        for(int i = 0; i<tree.size(); ++i){
            if(mp[tree[i]]++ == 0) ++cnt;
            if(cnt > 2){
                if(--mp[tree[start++]] == 0) --cnt;
            }
           
        }
        return tree.size() - start;
    }
};

/*
Loop all fruit c in tree,
Note that a and b are the last two different types of fruit that we met,
c is the current fruit type,
so it's something like "....aaabbbc..."

Case 1 c == b:
fruit c already in the basket,
and it's same as the last type of fruit
cur += 1
count_b += 1

Case 2 c == a:
fruit c already in the basket,
but it's not same as the last type of fruit
cur += 1
count_b = 1
a = b, b = c

Case 3 c != b && c!= a:
fruit c not in the basket,
cur = count_b + 1
count_b = 1
a = b, b = c

Of course, in each turn we need to update res = max(res, cur)

*/


class Solution {
public:
    int totalFruit(vector<int>& tree) {
        int res = 0, cur = 0, count_b = 0, a = 0, b = 0;
        for (int c :  tree) {
            cur = c == a || c == b ? cur + 1 : count_b + 1;
            count_b = c == b ? count_b + 1 : 1;
            if (b != c) a = b, b = c;
            res = max(res, cur);
        }
        return res;
    }
};