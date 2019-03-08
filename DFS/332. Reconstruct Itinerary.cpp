 /*
332. Reconstruct Itinerary

 Given a list of airline tickets represented by pairs of departure and arrival airports [from, to], reconstruct the itinerary in order. 
 All of the tickets belong to a man who departs from JFK. Thus, the itinerary must begin with JFK.

Note:
If there are multiple valid itineraries, you should return the itinerary that has the smallest lexical order when read as a single string. 
For example, the itinerary ["JFK", "LGA"] has a smaller lexical order than ["JFK", "LGB"].
All airports are represented by three capital letters (IATA code).
You may assume all tickets form at least one valid itinerary.
Example 1:
tickets = [["MUC", "LHR"], ["JFK", "MUC"], ["SFO", "SJC"], ["LHR", "SFO"]]
Return ["JFK", "MUC", "LHR", "SFO", "SJC"].
Example 2:
tickets = [["JFK","SFO"],["JFK","ATL"],["SFO","ATL"],["ATL","JFK"],["ATL","SFO"]]
Return ["JFK","ATL","JFK","SFO","ATL","SFO"].
Another possible reconstruction is ["JFK","SFO","ATL","JFK","ATL","SFO"]. But it is larger in lexical order.

Credits:
Special thanks to @dietpepsi for adding this problem and creating all test cases.


 
 */

/*
First keep going forward until you get stuck. That's a good main path already. 
Remaining tickets form cycles which are found on the way back and get merged into that main path.
By writing down the path backwards when retreating from recursion, merging the cycles into the main path is easy - 
the end part of the path has already been written, the start part of the path hasn't been written yet, 
so just write down the cycle now and then keep backwards-writing the path.

IMAGE:  https://leetcode.com/problems/reconstruct-itinerary/discuss/78768/Short-Ruby-Python-Java-C%2B%2B

From JFK we first visit JFK -> A -> C -> D -> A. There we're stuck, so we write down A as the end of the route and retreat back to D. 
There we see the unused ticket to B and follow it: D -> B -> C -> JFK -> D.
Then we're stuck again, retreat and write down the airports while doing so: Write down D before the already written A, 
then JFK before the D, etc. When we're back from our cycle at D, the written route is D -> B -> C -> JFK -> D -> A. 
Then we retreat further along the original path, prepending C, A and finally JFK to the route, 
ending up with the route JFK -> A -> C -> D -> B -> C -> JFK -> D -> A.

*/
class Solution {
public:
    vector<string> findItinerary(vector<pair<string, string>> tickets) {
        unordered_map<string, map<string, int>> m; 
        vector<string>res={"JFK"};
        for(auto t: tickets){
            m[t.first][t.second]++;
        }
        dfs("JFK", res, tickets.size(), m);
        return res;
    }

    bool dfs( string cur,vector<string>& res, int tickets, unordered_map<string, map<string, int>>&m){
        if(tickets == 0)
            return true;
        for(auto &go: m[cur]){
            if(go.second>0){
                go.second--;
                res.push_back(go.first);
                if(dfs(go.first,res, tickets-1, m)) return true;
                go.second++;
                res.pop_back();
            }
        }
        return false;
    }
};



class Solution {
public:
    vector<string> findItinerary(vector<pair<string, string>> tickets) { 
        unordered_map<string, multiset<string>>m;
        vector<string>route;
        for(auto t: tickets){
            m[t.first].insert(t.second);
        }
        dfs("JFK", route, m);
        return vector<string>(route.rbegin(), route.rend());
    }

    void dfs(string cur,vector<string>& route, unordered_map<string,multiset<string>>&m){
        while(!m[cur].empty()){
            string next = *m[cur].begin();
            m[cur].erase(m[cur].begin());
            dfs(next, route, m);
        }
        route.push_back(cur);
    }
};

//iterative solution using stk
class Solution {
public:
    vector<string> findItinerary(vector<pair<string, string>> tickets) { 
        unordered_map<string, multiset<string>>m;
        vector<string>route;
        for(auto t: tickets){
            m[t.first].insert(t.second);
        }
        stack<string>stk;
        stk.push("JFK");
        while(!stk.empty()){
            string cur = stk.top(); 
            while(!m[cur].empty()){
                string next = *m[cur].begin();
                stk.push(next);
                m[cur].erase(m[cur].begin());
                cur = next;
            }
            route.push_back(cur);
            stk.pop();
        }
        return vector<string>(route.rbegin(), route.rend());
    }
};

class Solution {
        unordered_map<string, priority_queue<string, vector<string>, greater<string>>> graph;
        vector<string> result;
        void dfs(string vtex)
        {
            auto & edges = graph[vtex];
            while (!edges.empty())
            {
                string to_vtex = edges.top();
                edges.pop();
                dfs(to_vtex);
            }
            result.push_back(vtex);
        }
    public:
        vector<string> findItinerary(vector<pair<string, string>> tickets) {
            for (auto e : tickets)
                graph[e.first].push(e.second);
            dfs("JFK");
            reverse(result.begin(), result.end());
            return result;
        }
    };
