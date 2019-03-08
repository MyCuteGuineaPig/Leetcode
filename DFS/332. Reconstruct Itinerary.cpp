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
