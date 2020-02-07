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



//from StefanPochmann
class Codec {
public:

    string serialize(TreeNode* root) {
        ostringstream out;
        serialize(root, out);
        return out.str();
    }

    TreeNode* deserialize(string data) {
        istringstream in(data);
        return deserialize(in);
    }

private:

    void serialize(TreeNode* root, ostringstream& out) {
        if (root) {
            out << root->val << ' ';
            serialize(root->left, out);
            serialize(root->right, out);
        } else {
            out << "# ";
        }
    }

    TreeNode* deserialize(istringstream& in) {
        string val;
        in >> val;
        if (val == "#")
            return nullptr;
        TreeNode* root = new TreeNode(stoi(val));
        root->left = deserialize(in);
        root->right = deserialize(in);
        return root;
    }
};


//BFS
class Codec {
public:
    
    // Encodes a tree to a single string.
    string serialize(TreeNode* root) {
        ostringstream out;
        queue<TreeNode*>q;
        q.push(root);
        while(!q.empty()){
            TreeNode* top = q.front();
            q.pop();
            if(!top) out << "# ";
            else{
                out<<top->val<<" ";
                q.push(top->left);
                q.push(top->right);
            }
        }
        return out.str();
    }

    // Decodes your encoded data to tree.
    TreeNode* deserialize(string data) {
        TreeNode* root = nullptr;
        queue<TreeNode**>q;
        q.push(&root);
        istringstream in(data);
        while(!q.empty()){
            TreeNode** top = q.front();
            // TreeNode* top = *(q.front());  *(q.front()) 取值, 然后复制给新的pointer
            string val;
            in >> val;
            cout<<" val "<<val<<endl;
            if(val == "#")
                *top = nullptr;
            else{
                *top = new TreeNode(stoi(val));
                q.push(&((*top)->left));
                q.push(&((*top)->right));
            }
            q.pop();
        }
        return root;
    }
    
};
