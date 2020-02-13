/*
331. Verify Preorder Serialization of a Binary Tree

One way to serialize a binary tree is to use pre-order traversal. When we encounter a non-null node, we record the node's value.
 If it is a null node, we record using a sentinel value such as #.

     _9_
    /   \
   3     2
  / \   / \
 4   1  #  6
/ \ / \   / \
# # # #   # #
For example, the above binary tree can be serialized to the string "9,3,4,#,#,1,#,#,2,#,6,#,#", where # represents a null node.

Given a string of comma separated values, verify whether it is a correct preorder traversal serialization of a binary tree. 
Find an algorithm without reconstructing the tree.

Each comma separated value in the string must be either an integer or a character '#' representing null pointer.

You may assume that the input format is always valid, for example it could never contain two consecutive commas such as "1,,3".

Example 1:

Input: "9,3,4,#,#,1,#,#,2,#,6,#,#"
Output: true
Example 2:

Input: "1,#"
Output: false
Example 3:

Input: "9,#,#,1"
Output: false

Input: "9,3,4,#,#,1,#,#,#,2,#,6,#,#"
Output: false

*/

class Solution {
public:
    bool isValidSerialization(string preorder) {
        stack<int>stk;  //every node need to be pop out twice, so when encounter new node push 2 inside 
        string cur;
        stk.push(1);
        stringstream ss(preorder);
        while(getline(ss,cur,',')){
            if(stk.empty()) return false; //现在node 必须有挂的位置
            if(cur == "#"){
                if(stk.top() == 2) stk.top()--;
                else{
                    while(!stk.empty() && stk.top() == 1) stk.pop();
                    if(!stk.empty()) stk.top()--;
                }
            }
            else{
                stk.push(2);
            }
        }
        return stk.empty();
    }
};

//or 
class Solution {
public:
    bool isValidSerialization(string preorder) {
        stack<int>stk;
        stringstream ss(preorder);
        string cur;
        bool begin = true;
        while(getline(ss, cur, ',')){
            if(stk.empty()) {
                if(begin) begin = false; //只有刚开始的点没有地方挂
                else return false;
            }
            if(cur == "#"){
                while(!stk.empty() && stk.top() == 1) stk.pop();
                if(!stk.empty()) --stk.top();
            }else stk.push(2);
        }
        return stk.empty();
    }
};

/*
"9,3,4,#,#,1,#,#,2,#,6,#,#"
Your stdout
9, -1
3, -2
4, -3
#, -4
#, -3
1, -2
#, -3
#, -2
2, -1
#, -2
6, -1
#, -2
#, -1

*/

//indegree(到parent的) = outdegree（到child的） 每个node 都有一个indegree, 只有不是NULL的node,才有outdegreee
class Solution {
public:
    bool isValidSerialization(string preorder) {
        int degree = -1;  // root has no indegree, for compensate init with -1
        /*
        为什么是 -1？
        算上null，总共n个node，两两相连，就有n-1个线，保证最后是0的话，初始为-1，
        */
        string cur;
        stringstream ss(preorder);
        while(getline(ss,cur,',')){
            degree++;  // all nodes have 1 indegree (root compensated)
            if(degree > 0) return false; // total degree should never exceeds 0
            if(cur != "#"){// only non-leaf node has 2 outdegree
                degree -= 2;   
            }
        }
        return degree == 0;
    }
};


class Solution {
public:
    bool isValidSerialization(string preorder) {
        int degree = 0;
        stringstream ss(preorder);
        string cur;
        while(getline(ss, cur, ',')){
            if (degree >= 1) return false;
            ++degree;
            if(cur == "#") continue;
            else degree-=2;
        }
        return degree==1; //表示出root点的 是1个degree
    }
};
