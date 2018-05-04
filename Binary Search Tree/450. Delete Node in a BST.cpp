/*
450. Delete Node in a BST
Given a root node reference of a BST and a key, delete the node with the given key in the BST.
 Return the root node reference (possibly updated) of the BST.

Basically, the deletion can be divided into two stages:

Search for a node to remove.
If the node is found, delete the node.
Note: Time complexity should be O(height of tree).

Example:

root = [5,3,6,2,4,null,7]
key = 3

    5
   / \
  3   6
 / \   \
2   4   7

Given key to delete is 3. So we find the node with value 3 and delete it.

One valid answer is [5,4,6,2,null,null,7], shown in the following BST.

    5
   / \
  4   6
 /     \
2       7

Another valid answer is [5,2,6,null,4,null,7].

    5
   / \
  2   6
   \   \
    4   7


*/


/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */

/*
Steps:

Recursively find the node that has the same value as the key, while setting the left/right nodes equal to the returned subtree
Once the node is found, have to handle the below 4 cases
node doesn't have left or right - return null
node only has left subtree- return the left subtree
node only has right subtree- return the right subtree
node has both left and right - find the minimum value in the right subtree, 
set that value to the currently found node, then recursively delete the minimum value in the right subtree

*/

class Solution {
public:
    TreeNode* deleteNode(TreeNode* root, int key) {
        if(!root) return root;
        if(key<root->val){
            root->left = deleteNode(root->left, key);
        }
        else if(key>root->val){
            root->right = deleteNode(root->right, key);
        }
        
        else{
            if(!root->right) return root->left;
            else if(!root->left) return root->right;
            else{
                TreeNode *cur = root->right;
                while(cur->left){  //直到左面没有值了
                    cur = cur->left;
                }
                root->val = cur->val;
                root->right = deleteNode(root->right,root->val);
            }
        }  
        return root;
    }

    
};



class Solution {
public:
    TreeNode* deleteNode(TreeNode* root, int key) {
        if (!root)
            return NULL;
        if (root->val == key)
        {
            if (!root->right)
            {
                TreeNode *left = root->left;
                delete root;
                return left;
            }
            else 
            {
                TreeNode *right = root->right;
                while (right->left)
                    right = right->left;
                std::swap(right->val, root->val); 
            }
        }
        root->left = deleteNode(root->left, key);
        root->right = deleteNode(root->right, key);
        return root;
    }
};



class Solution {
public:
    TreeNode* deleteNode(TreeNode* root, int key) {
        if (root == nullptr) {
            // key is not found, do nothing!!
            return nullptr;
        }

        if (key < root->val) {
            root->left = deleteNode(root->left, key);
        } else if (key > root->val) {
            root->right = deleteNode(root->right, key);
        } else {
            // get the right TreeNode
            if (root->left == nullptr && root->right == nullptr) {
                delete root;
                root = nullptr;
            } else if (root->left == nullptr) {
                root = root->right;
            } else if (root->right == nullptr) {
                root = root->left;
            } else {
                // put left subtree to the left most of the right subtree
                TreeNode* temp = root->right;
                while (temp->left != nullptr) {
                    temp = temp->left;
                }
                temp->left = root->left; //把root left 的接到temp的left

                // let right subtree be the new root                
                temp = root;  //让temp = root 之后root = root->right 这样删除temp，就不会影响root的值
                root = root->right; //删除原有root的左面
                delete temp;
                temp = nullptr;
            }
        }
        return root;
    }
};


/*
  比如tree 
                20
               /   \ 
             10    30
                  /   \ 
                22     40
                /      /  \ 
               21     35   50
                      /      \
                    33       60
            删除30 得到新的tree
                 20
               /   \ 
             10    40
                  /   \ 
                35     50
                /        \ 
               20         60
              /
             33
             /
            22
            /
           21

             

                       


*
/


class Solution {
public:
    TreeNode* deleteNode(TreeNode* root, int key) {
        if(!root)
            return root;
        if(root->val > key)
            root->left = deleteNode(root->left, key);
        else if(root->val < key)
            root->right = deleteNode(root->right, key);
        else{
            if(!root->left && !root->right) {
                delete root;
                root=nullptr;
            }
            else if(!root->left) root = root->right;
            else if(!root->right) root = root->left;
            else{
                TreeNode *temp = root->right;
                while(temp->left)
                    temp = temp->left;

                temp->left = root->left;   
                //temp = root;
                root = root->right;
                //delete temp;
                //temp = nullptr;
            }
        }
        return root;
    }
};
