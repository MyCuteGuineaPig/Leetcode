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