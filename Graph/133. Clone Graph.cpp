/*
// Definition for a Node.
class Node {
public:
    int val;
    vector<Node*> neighbors;
    Node() {
        val = 0;
        neighbors = vector<Node*>();
    }
    Node(int _val) {
        val = _val;
        neighbors = vector<Node*>();
    }
    Node(int _val, vector<Node*> _neighbors) {
        val = _val;
        neighbors = _neighbors;
    }
};
*/


class Solution {
public:
    Node* cloneGraph(Node* node) {
        if (!node) return nullptr;
        unordered_map<int, Node*> mp;
        auto f = [&](this auto && f, Node* cur){
            if (mp.count(cur->val))
                return mp[cur->val];
            Node* res = new Node(cur->val);
            mp[cur->val] = res;
            for(auto& nei: cur->neighbors){
                res->neighbors.push_back(f(nei));
            }
            return res;
        };
       
        return f(node);
    }
};

class Solution {
public:
    Node* helper(Node* node, unordered_map<int, Node*>&visited){
        //不能用unordered_map<int, Node**> visited. 比如 1->2, 2->3, 3->4, 1->4, 
        //到1->4 时候 visited 会发现visited 没有4, 但是之前3->4 已经visited 过了

        if (!node) return {};
        if (visited.count(node->val)){
            //cout<<" in visited "<<" node->val"<<"return "<<endl;
            return visited[node->val];
        }
        Node* cur = new Node(node->val);
        visited[node->val] = cur;
        for(auto& neighbor: node->neighbors){
            //cout<<" val "<<node->val<<" neighbor "<<neighbor->val<<endl;
            cur->neighbors.push_back(helper(neighbor, visited));
            
        }
        return cur;
    }

    Node* cloneGraph(Node* node) {
        unordered_map<int, Node*>visited;
        return helper(node, visited);
    }
};


//BFS

class Solution {
public:
    Node* cloneGraph(Node* node) {
        if (!node) return nullptr;
        unordered_map<int, Node*> visited;
        visited[node->val] = new Node(node->val); //存的copy
        queue<Node*> q; q.push(node); //存的original node
        while (!q.empty()) {
            int size = q.size();
            for(int i = 0; i < size; ++i) {
                auto top = q.front(); q.pop();
                for(auto& nei: top->neighbors) {
                    if (visited.count(nei->val) == 0){
                        visited[nei->val] = new Node(nei->val); 
                        q.push(nei);
                    } 
                    visited[top->val]->neighbors.push_back(visited[nei->val]);
                }
            }
        }
       
        return visited[node->val];
    }
};