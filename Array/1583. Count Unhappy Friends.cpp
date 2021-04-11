/*
Following statement of question can be explained better.
However, this pairing may cause some of the friends to be unhappy. 
A friend x is unhappy if x is paired with y and there exists a friend 
u who is paired with v but:

x prefers u over y, and
u prefers x over v.

Take Example as :

n = 4, preferences = [[1, 3, 2], [2, 3, 0], [1, 3, 0], [0, 2, 1]], pairs = [[1, 3], [0, 2]]


Take pair [0,2]
x-y == 0-2

0 prefers 1 and 3 over 2 (YES WE NEED TO CONSIDER 1 AND 3 BOTH :) )
Now check for 1 as well as 3
Now if any of 1 or 3 preferes 0 over 2 then we have a unhappy friend.
since 3 prefers 0 over two we have a unhappy friend
though we see 1 prefers 2 over zero
PS: most of us thought just to check for 1st preference of 0 and there is where this'
questions explanation was misunderstood.'


If you still have any doubt please raise them in comment section I will do my best to make the question clear.


*/


class Solution {
public:
    int unhappyFriends(int n, vector<vector<int>>& preferences, vector<vector<int>>& pairs) {
        vector<int>distance(n);
        for(auto pair: pairs){
            int x = pair[0], y = pair[1];
            for(int i = 0; i<n; ++i){
                if(preferences[x][i] == y){
                    distance[x] = i;
                    break;
                }
            }
            for(int i = 0; i<n; ++i){
                if(preferences[y][i] == x){
                    distance[y] = i;
                    break;
                }
            }
        }
        
        int unhappy = 0;
        for(int i = 0; i<n; ++i){
            for(int j = 0; j<distance[i]; ++j){
                int u = preferences[i][j];
                for(int k = 0; k<distance[u]; ++k){
                    if(preferences[u][k] == i){
                        j= n;
                        ++unhappy;
                        break;
                    }
                }
            }
        }
        return unhappy;
        
    }
};



class Solution {
public:
int unhappyFriends(int n, vector<vector<int>>& pref, vector<vector<int>>& pairs) {
    vector<unordered_map<int, int>> m(n);
    vector<int> dist(n);
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < pref[i].size(); ++j)
            m[i][pref[i][j]] = j;
    }
    for (auto &p : pairs) {
        dist[p[0]] = m[p[0]][p[1]];
        dist[p[1]] = m[p[1]][p[0]];
    }
    int res = 0;
    for (int i = 0; i < n; ++i) {
        for (int d = 0; d < dist[i]; ++d) {
            int j = pref[i][d];
            for (int d1 = 0; d1 < dist[j]; ++d1) {
                if (i == pref[j][d1]) {
                    ++res;
                    d = d1 = n;
                }
            }
        }
    }
    return res;
}
};