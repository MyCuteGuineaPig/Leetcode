/*

787. Cheapest Flights Within K Stops


There are n cities connected by m flights. Each fight starts from city u and arrives at v with a price w.

Now given all the cities and fights, together with starting city src and the destination dst, your task is to find the cheapest price from src to dst with up to k stops. If there is no such route, output -1.

Example 1:
Input: 
n = 3, edges = [[0,1,100],[1,2,100],[0,2,500]]
src = 0, dst = 2, k = 1
Output: 200
Explanation: 
The graph looks like this:


The cheapest price from city 0 to city 2 with at most 1 stop costs 200, as marked red in the picture.
Example 2:
Input: 
n = 3, edges = [[0,1,100],[1,2,100],[0,2,500]]
src = 0, dst = 2, k = 0
Output: 500
Explanation: 
The graph looks like this:


The cheapest price from city 0 to city 2 with at most 0 stop costs 500, as marked blue in the picture.
Note:

The number of nodes n will be in range [1, 100], with nodes labeled from 0 to n - 1.
The size of flights will be in range [0, n * (n - 1) / 2].
The format of each flight will be (src, dst, price).
The price of each flight will be in the range [1, 10000].
k is in the range of [0, n - 1].
There will not be any duplicated flights or self cycles.
*/


/*
graph store from i to j and time
BFS
everytime check the nearest point
每次像外延伸，用priority queue，每次先弄距离source cost最小的店, 
pq. [0] step to this point, [1] distance from source, [2] point

*/
//这是错的


class Solution {
public:
    int findCheapestPrice(int n, vector<vector<int>>& flights, int src, int dst, int K) {
        int m = flights.size();
        vector<vector<pair<int,int>>>graph(n,vector<pair<int,int>>());
        for(int i = 0; i<m; i++)
            graph[flights[i][0]].push_back({flights[i][1],flights[i][2]});

        unordered_map<int,int>dist;
        for(int i = 0;i<n;i++)
            dist[i] = INT_MAX;
        dist[src] = 0;

        auto compare = [](vector<int>a, vector<int>b){ if (a[0]!=b[0]) return a[0]>b[0]; else return a[1] > b[1];};
        priority_queue<vector<int>,vector<vector<int>>,decltype(compare)>pq(compare);
        pq.push({0,0,src});
        int stop = 0, res = INT_MAX;
        while(pq.size() && stop<=K){
            int cursize = pq.size();
            stop++;
            for(int i = 0; i<cursize; i++){
                int curdist = pq.top()[1];
                int curpoint = pq.top()[2];
                pq.pop();
                for(auto path: graph[curpoint]){
                    if(dist[path.first]>curdist+path.second){
                        if(dist[path.first]==INT_MAX){
                            // 比如 A->B 500, B->C 300,   A-F 100 F-D:100 D-F 100       
                        /*  
                            第一次push 进B 500, F 100, 第二次push 进 C 300, D 100, 
                            因为B 被push 过，所以最后C就是300+500 = 800，但其实C = 600
                            test set : 
                            5 
                            [[0,1,500],[1,2,200],[0,3,100],[3,4,100],[4,1,100]]
                            0 (src)
                            2 (sink)
                            6
                            this code: 700, correct answer 500
                        */
                            pq.push({stop,curdist+path.second,path.first});
                        }
                            
                        dist[path.first]=curdist+path.second;
                        if(path.first == dst) {
                            res = min(res,dist[path.first]);
                        };
                    }
                }
            }
        }
        return res == INT_MAX ? -1: res;
    }
};



class Solution {
public:
    int findCheapestPrice(int n, vector<vector<int>>& flights, int src, int dst, int K) {
        int m = flights.size();
        vector<vector<pair<int,int>>>graph(n,vector<pair<int,int>>());
        for(int i = 0; i<m; i++)
            graph[flights[i][0]].push_back({flights[i][1],flights[i][2]});

        auto compare = [](vector<int>a, vector<int>b){ return a[0] > b[0];};
        priority_queue<vector<int>,vector<vector<int>>,decltype(compare)>pq(compare);
        pq.push({0,src,0});
        int stop = 0, res = INT_MAX;
        while(pq.size()){
            int price = pq.top()[0];
            int city = pq.top()[1];
            int stop = pq.top()[2];
            if(city == dst) 
                return price;
            pq.pop();
            if(stop<=K){
                for(auto adj: graph[city]){
                     pq.push({price+adj.second,adj.first,stop+1});
                }
            }
        }
        return -1;
    }
};