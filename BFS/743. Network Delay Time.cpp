/*
743. Network Delay Time

Time	            Space	        Difficulty
O(|E| + |V|log|V|)	O(|E| + |V|)	Medium	

There are N network nodes, labelled 1 to N.

Given times, a list of travel times as directed edges times[i] = (u, v, w),
 where u is the source node, v is the target node, and w is the time it takes for a signal to travel from source to target.

Now, we send a signal from a certain node K. How long will it take for all nodes to receive the signal? If it is impossible, return -1.

Note:
N will be in the range [1, 100].
K will be in the range [1, N].
The length of times will be in the range [1, 6000].
All edges times[i] = (u, v, w) will have 1 <= u, v <= N and 1 <= w <= 100.


*/
class Solution {
public:
    int networkDelayTime(vector<vector<int>>& times, int N, int K) {
        vector<vector<pair<int,int>>>graph(N+1,vector<pair<int,int>>());
        for(auto t: times)
            graph[t[0]].push_back({t[1],t[2]}); //initialize path, key is source, pair<sink, distance>

        unordered_map<int,int>dist;
        for(int i = 1; i<=N; i++)
            dist[i] = INT_MAX; //initialize distance from source
        dist[K] = 0;

        auto compareFunc = [](pair<int,int>a, pair<int,int>b){return a.first>b.first;};
        priority_queue<pair<int,int>, vector<pair<int,int>>,decltype(compareFunc)>pq(compareFunc);
        pq.push({0,K});

        while(pq.size()){
            int start = pq.top().first; //distance of current pont from sink
            int point = pq.top().second; //current point index;
            pq.pop();
            for(auto p: graph[point]){ // p.first is neighbour that can be reached from point. p.second is the distance from point to neighbour
               if(dist[p.first] > start + p.second)
                {
                    dist[p.first] = start + p.second;
                    pq.push({dist[p.first],p.first});
                }
            }
        } 
        int maxdist = 0;
        for(auto i: dist)
            maxdist = max(i.second, maxdist);
        return maxdist == INT_MAX ? -1 : maxdist;
    }
};


class Solution {
public:
    int networkDelayTime(vector<vector<int>>& times, int N, int K) {
        vector<vector<pair<int,int>>>graph(N+1,vector<pair<int,int>>());
        for(auto t: times)
            graph[t[0]].push_back({t[1],t[2]}); //initialize path, key is source, pair<sink, distance>

        unordered_map<int,int>dist;
        for(int i = 1; i<=N; i++)
            dist[i] = INT_MAX; //initialize distance from source
        dist[K] = 0;


        priority_queue<pair<int,int>>pq;
        pq.push({0,K});

        while(pq.size()){
            int start = pq.top().first; //distance of current pont from sink
            int point = pq.top().second; //current point index;
            pq.pop();
            //cout<<start<<" p "<<point<<endl;
            for(auto p: graph[point]){ // p.first is neighbour that can be reached from point. p.second is the distance from point to neighbour
                //cout<<"negitbour "<<p.first<<" dist[] "<<endl;
                //cout<<dist[p.first]<<" second "<<p.second<<" start "<<start<<endl;
                if(dist[p.first] > start + p.second)
                {
                    
                    dist[p.first] = start + p.second;
                    pq.push({dist[p.first],p.first});
                    //cout<<"push dist "<<dist[p.first]<<" first "<<p.first<<endl;
                }
            }
        } 
        int maxdist = 0;
        for(auto i: dist)
            maxdist = max(i.second, maxdist);
        return maxdist == INT_MAX ? -1 : maxdist;
    }
};


class Solution {
public:
    int networkDelayTime(vector<vector<int>>& times, int N, int K) {
        vector<vector<pair<int,int>>>graph(N+1,vector<pair<int,int>>());
        for(auto t: times)
            graph[t[0]].push_back({t[1],t[2]}); //initialize path, key is source, pair<sink, distance>

        unordered_map<int,int>dist;
        for(int i = 1; i<=N; i++)
            dist[i] = INT_MAX;
        dist.erase(K);
        for(auto p: graph[K])
            dist[p.first] = p.second;

        int maxdist = 0;
        int point,start;
        while(dist.size()){
            point = -1, start = INT_MAX;
            for(auto i: dist){
                if(i.second<start){
                    start = i.second;
                    point = i.first;
                }
            }
            if(point == -1) return -1;
            dist.erase(point);
            maxdist = max(maxdist,start);
            for(auto p: graph[point])
                if(dist.find(p.first)!=dist.end() && dist[p.first] > start + p.second)
                     dist[p.first] = start+p.second;
        }
        return maxdist;
    }
};