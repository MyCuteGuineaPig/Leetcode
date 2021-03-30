
class Solution {
public:
    Node* connect(Node* root) {
        helper(root);
        return root;
    }
    
    void helper(Node* root){
        if(!root)
            return;
        Node* cur = root, *prev = nullptr;
        Node* nextLeftMostChild = nullptr;
        while(cur){
            if(cur->left){
                if(!nextLeftMostChild)// !nextLeftMostChild 也是 !prev,  
                    nextLeftMostChild = cur->left;
                else prev->next =cur->left;
                prev = cur->left;
            }
            if(cur->right){
                if(!nextLeftMostChild) 
                     nextLeftMostChild = cur->right;
                else prev->next =cur->right;
                prev = cur->right;
            }
            cur = cur->next;
        }
        helper(nextLeftMostChild);
        return;
    }
};


class Solution {
public:
    Node* connect(Node* root) {
        Node* cur = root;
        while(cur){
            Node   *prev = nullptr;
            Node* nextLeftMostChild = nullptr;
            while(cur){
                if(cur->left){
                    if(!nextLeftMostChild)
                        nextLeftMostChild = cur->left;
                    else prev->next =cur->left;
                    prev = cur->left;
                }
                if(cur->right){
                    if(!nextLeftMostChild) //
                         nextLeftMostChild = cur->right;
                    else prev->next =cur->right;
                    prev = cur->right;
                }
                cur = cur->next;
            }
            cur = nextLeftMostChild;
        }
        return root;
    }
};