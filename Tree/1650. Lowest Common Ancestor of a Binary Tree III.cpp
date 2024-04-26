/*

 the same as finding the convergence point of 2 linked lists
*/

class Solution {
public:
    Node* lowestCommonAncestor(Node* p, Node * q) {
        Node* p1 = p;
        Node* q1 = q;
        while (p1 != q1){
            p1 = p1->parent ? p1->parent: q;
            q1 = q1->parent ? q1->parent: p;
        }
        return p1;
    }
};


/*
// Definition for a Node.
class Node {
public:
    int val;
    Node* left;
    Node* right;
    Node* parent;
};
*/


class Solution {
public:
    Node* lowestCommonAncestor(Node* p, Node * q) {
        std::stack<Node*> p_ancestors;
        std::stack<Node*> q_ancestors;
        
        Node* n = p;
        while (n->parent){
            p_ancestors.push(n);
            n = n->parent;
        }
        p_ancestors.push(n);
        
        n = q;
        while (n->parent){
            q_ancestors.push(n);
            n = n->parent;
        }
        q_ancestors.push(n);
        
        Node* lca = nullptr;
        while (!p_ancestors.empty() && !q_ancestors.empty() && p_ancestors.top() == q_ancestors.top()) {
            lca = p_ancestors.top();
            p_ancestors.pop();
            q_ancestors.pop();
        }
        return lca;
        
    }
};