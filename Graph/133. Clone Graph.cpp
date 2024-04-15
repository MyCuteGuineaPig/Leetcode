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
        if (!node) return {};
        unordered_map<int,Node*> visited;
        queue<Node*>q;
        int root_val = node->val;
        visited[root_val] = new Node(node->val);
        q.push(node); //Queue里要存原来的 node, 否则新的node 还没有neighbor
        while(!q.empty()){
            int size = q.size(); 
            for(int i = 0; i < size; ++i){
                Node* top = q.front(); q.pop();
                for(auto& neighbor: top->neighbors){
                    if (visited.count(neighbor->val) == 0){
                        visited[neighbor->val] = new Node(neighbor->val);
                        q.push(neighbor);
                    }
                    visited[top->val]->neighbors.push_back(visited[neighbor->val]);
                }
            }
        }
        return visited[root_val];
    }
};