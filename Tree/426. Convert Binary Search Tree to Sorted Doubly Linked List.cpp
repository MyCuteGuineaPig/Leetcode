/*
// Definition for a Node.
class Node {
public:
    int val;
    Node* left;
    Node* right;

    Node() {}

    Node(int _val) {
        val = _val;
        left = NULL;
        right = NULL;
    }

    Node(int _val, Node* _left, Node* _right) {
        val = _val;
        left = _left;
        right = _right;
    }
};
*/

class Solution {
public:
    

    Node* treeToDoublyList(Node* root) {
        if (!root) return root;
        Node* prev = nullptr;
        Node* left_most = nullptr;
        function <void(Node*)> dfs = [&](Node* cur){
            if (!cur) return;
            dfs(cur->left);
            if (prev) {
                prev->right = cur;
                cur->left = prev;
            } else {
                left_most = cur;
            }
            prev = cur;
            dfs(cur->right);
        };
        dfs(root);
        prev->right = left_most;
        left_most->left = prev;
        return left_most;

    }
};