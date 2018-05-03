/*
449. Serialize and Deserialize BST

Serialization is the process of converting a data structure or object into a sequence of bits 
so that it can be stored in a file or memory buffer, 
or transmitted across a network connection link to be reconstructed later in the same or another computer environment.

Design an algorithm to serialize and deserialize a binary search tree. 
There is no restriction on how your serialization/deserialization algorithm should work. 
You just need to ensure that a binary search tree can be serialized to a string and
 this string can be deserialized to the original tree structure.

The encoded string should be as compact as possible.

Note: Do not use class member/global/static variables to store states. Your serialize and deserialize algorithms should be stateless.


*/








// Time:  O(n)
// Space: O(h)


// Your Codec object will be instantiated and called as such:
// Codec codec;
// codec.deserialize(codec.serialize(root));




// Time:  O(n)
// Space: O(h)
class Codec {
public:

    // Encodes a tree to a single string.
    string serialize(TreeNode* root) {
        string outstring;
        serializehelper(root, &outstring);
        return outstring;
    }
    
    void serializehelper(TreeNode* root, string *outstring) {
        if(root){
            *outstring += to_string(root->val)+" ";
            serializehelper(root->left, outstring);
            serializehelper(root->right, outstring);
        }
    }

    // Decodes your encoded data to tree.
    TreeNode* deserialize(string data) {
        int pos = 0;
        return deserializehelper(numeric_limits<int>::min(), numeric_limits<int>::max(),data,&pos);
    }
    
    TreeNode* deserializehelper(int minval, int maxval, const string & data, int * pos) { 
        //必须需要pointer 或者reference
    /* 
    比如 结果是 
         5
        3 6
       2   7
    data = 5 3 6 2 7， 当左树loop 完，到右面，val=5，但是要保证pos指向index 6, 不能是指向3的
     */
        if(*pos==data.size()) 
            return nullptr;
        int j = data.find(' ', *pos);
        int val = stoi(data.substr(*pos, j - *pos));
        if(val>minval && val<maxval){
            TreeNode * node = new TreeNode(val);
            *pos = j+1;
            node->left = deserializehelper(minval, val, data, pos);
            node->right = deserializehelper(val, maxval, data,pos);
            return node;
        }
        return nullptr;
    }
};