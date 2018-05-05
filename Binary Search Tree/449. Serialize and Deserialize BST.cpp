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


/*
Sharing my solution which doesn't have to parse string for comma at all!

The encoding schema is preorder of BST, and to decode this we can use the same preorder traversal to do it in one pass with recursion in O(n) time.

To minimize the memory, I used binary format instead of ascii format for each integer, just burn those int into 4 chars will save you a lot!!!

Really if using ASCII numbers you are paying a lot of penalty memory for integers over 4 digit long and parsing comma is just as painful.

*/

class Codec {
public:

    // Encodes a tree to a single string.
    string serialize(TreeNode* root) {
        string order;
        inorderDFS(root, order);
        return order;
    }
    
    inline void inorderDFS(TreeNode* root, string& order) {
        if (!root) return;
        char buf[4];
        memcpy(buf, &(root->val), sizeof(int)); //burn the int into 4 chars
        for (int i=0; i<4; i++) order.push_back(buf[i]);
        inorderDFS(root->left, order);
        inorderDFS(root->right, order);
    }

    // Decodes your encoded data to tree.
    TreeNode* deserialize(string data) {
        int pos = 0;
        return reconstruct(data, pos, INT_MIN, INT_MAX);
    }
    
    inline TreeNode* reconstruct(const string& buffer, int& pos, int minValue, int maxValue) {
        if (pos >= buffer.size()) return NULL; //using pos to check whether buffer ends is better than using char* directly.
        
        int value;
        memcpy(&value, &buffer[pos], sizeof(int));
        if (value < minValue || value > maxValue) return NULL;
        
        TreeNode* node = new TreeNode(value);
        pos += sizeof(int);
        node->left = reconstruct(buffer, pos, minValue, value);
        node->right = reconstruct(buffer, pos, value, maxValue);
        return node;
    }
};


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
            char buf[4];
            memcpy(buf,&(root->val),sizeof(int));
            for(int i = 0;i<4; i++)  *outstring += buf[i];
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
        if(*pos==data.size()) 
            return nullptr;
        int val;
        memcpy(&val, &data[*pos], sizeof(int));
        if(val>minval && val<maxval){
            TreeNode * node = new TreeNode(val);
            *pos += sizeof(int);
            node->left = deserializehelper(minval, val, data, pos);
            node->right = deserializehelper(val, maxval, data,pos);
            return node;
        }
        return nullptr;
    }
};