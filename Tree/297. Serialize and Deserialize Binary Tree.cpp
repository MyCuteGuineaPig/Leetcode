/*
297. Serialize and Deserialize Binary Tree
Serialization is the process of converting a data structure or object into a sequence of bits 
so that it can be stored in a file or memory buffer, 
or transmitted across a network connection link to be reconstructed later in the same or another computer environment.

Design an algorithm to serialize and deserialize a binary tree. 
There is no restriction on how your serialization/deserialization algorithm should work. 
You just need to ensure that a binary tree can be serialized to a string 
and this string can be deserialized to the original tree structure.

Example: 

You may serialize the following tree:

    1
   / \
  2   3
     / \
    4   5

as "[1,2,3,null,null,4,5]"
Clarification: The above format is the same as how LeetCode serializes a binary tree. 
You do not necessarily need to follow this format, so please be creative and come up with different approaches yourself.

Note: Do not use class member/global/static variables to store states. 
Your serialize and deserialize algorithms should be stateless.


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
class Codec {
public:

    // Encodes a tree to a single string.
    string serialize(TreeNode* root) {
        string out;
        serializehelper(root, out);
        return out;
    }

    // Decodes your encoded data to tree.
    TreeNode* deserialize(string data) {
        istringstream in(data);
        return deserializehelper(in);
    }
    
private:
    void serializehelper(TreeNode* root, string& out){
        if(!root){
            out+="# ";
        }else{
            out+=to_string(root->val)+" ";
            serializehelper(root->left, out);
            serializehelper(root->right, out);
        }
    }
    
    TreeNode* deserializehelper(istringstream& in){
        string val;
        in>>val;
        if(val == "#") return nullptr;
        else{
            TreeNode *cur = new TreeNode(stoi(val));
            cur->left = deserializehelper( in);
            cur->right = deserializehelper(in);
            return cur;
        }
       
    }
};

// Your Codec object will be instantiated and called as such:
// Codec codec;
// codec.deserialize(codec.serialize(root));



class Codec {
public:
    // Encodes a tree to a single string.
    string serialize(TreeNode* root) {
        if (root == nullptr) return "#";
        return to_string(root->val)+","+serialize(root->left)+","+serialize(root->right);
    }

    // Decodes your encoded data to tree.
    TreeNode* deserialize(string data) {
        return mydeserialize(data);
    }
    TreeNode* mydeserialize(string& data) {
        if (data[0]=='#') {
            if(data.size() > 1) data = data.substr(2);
            return nullptr;
        } else {
            TreeNode* node = new TreeNode(helper(data));
            node->left = mydeserialize(data);
            node->right = mydeserialize(data);
            return node;
        }
    }
private:
    int helper(string& data) {
        int pos = data.find(',');
        int val = stoi(data.substr(0,pos));
        data = data.substr(pos+1);
        return val;
    }
};


class Codec {
public:
    void se(TreeNode* node, stringstream &ss) {
        if (node) {
            ss << 'n';
            ss << node->val;
            se(node->left, ss);
            se(node->right, ss);
        } else {
            ss << '@';
        }
    }
    
    void de(TreeNode* &node, stringstream &ss) {
        char ch;
        ss >> ch;
        int num;
        if (ch == 'n') {
            ss >> num;
            node = new TreeNode(num);
            de(node->left, ss);
            de(node->right, ss);
        } else {
            node = nullptr;
        }
    }

    // Encodes a tree to a single string.
    string serialize(TreeNode* root) {
        stringstream ss;
        se(root, ss);
        return ss.str();
    }

    // Decodes your encoded data to tree.
    TreeNode* deserialize(string data) {
        stringstream ss(data);
        TreeNode *root;
        de(root, ss);
        return root;
    }
};



//BFS
class Codec {
public:

    // Encodes a tree to a single string.
    string serialize(TreeNode* root) {
        queue<TreeNode*> q;
        q.push(root);
        string str;
        while (!q.empty()) {
            if (q.front() == nullptr) {
                str = str + "#,";
            } else {
                q.push(q.front()->left);
                q.push(q.front()->right);
                str = str + to_string(q.front()->val) + ",";
            }
            q.pop();
        }
        return str;
    }

    // Decodes your encoded data to tree.
    TreeNode* deserialize(string data) {
        TreeNode* root = nullptr;
        queue<TreeNode**> q;
        q.push(&root);
        string::iterator first = data.begin();
        while (first != data.end()) {
            TreeNode** pp = q.front();
            if (*first == '#') {
                // *pp = nullptr;
                advance(first, 2);
            } else {
                string::iterator last = find(first, data.end(), ',');
                int val = stoi(string(first, last));
                *pp = new TreeNode(val);
                q.push(&((*pp)->left));
                q.push(&((*pp)->right));
                first = next(last);
            }
            q.pop();
        }
        return root;
    }
};
