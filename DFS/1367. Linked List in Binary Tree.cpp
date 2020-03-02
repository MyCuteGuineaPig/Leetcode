//KMP Solution 
//Speed O(n+l)
//Memory O(h+l)
class Solution {
public:
    bool isSubPath(ListNode* head, TreeNode* root) {
        if(!head)
            return true;
        const auto & [pattern, prefix] = getPrefix(head);
        return dfs(pattern, prefix, root, 0);
    }

    bool dfs(const vector<int>&pattern, const vector<int>& prefix, TreeNode* node, int i){
        if(i == prefix.size())
            return true; 
        if(!node)
            return false;
        if ( i > 0 && node->val != pattern[i])
            i = prefix[i-1];
        if ( pattern[i] == node->val)
            ++i;
        return dfs(pattern, prefix, node->left, i) || dfs(pattern, prefix, node->right, i);
    }


    pair<vector<int>, vector<int>>getPrefix(ListNode* node){
        vector<int>pattern = {node->val};
        vector<int>prefix = {0};
        node = node->next;
        int i = 0;
        while(node){
            while(i >0  && node->val != pattern[i] )
                i =  prefix[i-1];
            if(node->val == pattern[i])
                ++i;
            prefix.push_back(i);
            pattern.push_back(node->val);
            node = node->next;
        }
        return {pattern, prefix};
    }
};


// kmp solution
class Solution {
public:
    bool isSubPath(ListNode* head, TreeNode* root) {
        if (!head) {
            return true;
        }
        const auto& [pattern, prefix] = getPrefix(head);
        return dfs(pattern, prefix, root, -1);
    }

private:
    bool dfs(const vector<int>& pattern,
             const vector<int>& prefix,
             TreeNode *root, int j) {
        if (!root) {
            return false;
        }
        while (j + 1 && pattern[j + 1] != root->val) {
            j = prefix[j];
        }
        if (pattern[j + 1] == root->val) {
            ++j;
        }
        if (j + 1 == pattern.size()) {
            return true;
        }
        return dfs(pattern, prefix, root->left, j) ||
               dfs(pattern, prefix, root->right, j);
    }
    
    pair<vector<int>, vector<int>> getPrefix(ListNode *head) {
        vector<int> pattern = {head->val};
        vector<int> prefix = {-1};
        int j = -1;
        auto node = head->next;
        while (node) {
            while (j + 1 && pattern[j + 1] != node->val) {
                j = prefix[j];
            }
            if (pattern[j + 1] == node->val) {
                ++j;
            }
            pattern.emplace_back(node->val);
            prefix.emplace_back(j);
            node = node->next;
        }
        return {pattern, prefix};
    }
};

// Time:  O(n * min(h, l))
// Space: O(h)
// dfs solution
class Solution2 {
public:
    bool isSubPath(ListNode* head, TreeNode* root) {
        if (!head) {
            return true;
        }
        if (!root) {
            return false;
        }
        return dfs(head, root) ||
               isSubPath(head, root->left) ||
               isSubPath(head, root->right);
    }

private:
    bool dfs(ListNode *head, TreeNode *root) {
        if (!head) {
            return true;
        }
        if (!root) {
            return false;
        }
        return root->val == head->val &&
               (dfs(head->next, root->left) ||
                dfs(head->next, root->right));
    }
};
