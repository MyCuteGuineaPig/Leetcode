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
        unordered_map<string, priority_queue<string>> m; 
        vector<string>res={"JFK"};
        for(auto t: tickets){
            m[t.first].push(t.second);
        }
        dfs("JFK", res, m);
        return res;
    }

    void dfs( string cur,vector<string>& res, unordered_map<string,priority_queue<string>>&m){
        string goplace = m[cur].top();
        m[cur].pop();
        res.push_back(goplace);
        dfs(goplace,res, m);
    }
};