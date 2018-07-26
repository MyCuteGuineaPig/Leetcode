/*
839. Similar String Groups


Two strings X and Y are similar if we can swap two letters (in different positions) of X, so that it equals Y.

For example, "tars" and "rats" are similar (swapping at positions 0 and 2), and "rats" and "arts" are similar, 
but "star" is not similar to "tars", "rats", or "arts".

Together, these form two connected groups by similarity: {"tars", "rats", "arts"} and {"star"}.  
Notice that "tars" and "arts" are in the same group even though they are not similar.  
Formally, each group is such that a word is in the group if and only if it is similar to at least one other word in the group.

We are given a list A of strings.  Every string in A is an anagram of every other string in A.  How many groups are there?

Example 1:

Input: ["tars","rats","arts","star"]
Output: 2
Note:

A.length <= 2000
A[i].length <= 1000
A.length * A[i].length <= 20000
All words in A consist of lowercase letters only.
All words in A have the same length and are anagrams of each other.
The judging time limit has been increased for this question.

*/



class Solution {
public:
    int numSimilarGroups(vector<string>& A) {
        DisjointSet ds(A.size());
        for(int i = 0; i<A.size()-1;i++){
            for(int j = i+1; j<A.size(); j++){
                if(similar(A[i], A[j]))
                    ds.join(i,j);
            }
        }
        return ds.getSize();
    }
    
    bool similar(const string& a, const string &b){
        for(int i = 0, cnt = 0; i<a.size(); i++){
            if(a[i]!=b[i] && ++cnt>2) return false;
        }
        return true;
    }
    
    struct DisjointSet{
        vector<int>parent;
        int size;
        
        DisjointSet(int n){
            parent.resize(n);
            iota(parent.begin(), parent.end(),0);
            size = n;
        }
        
        int getSize(){
            return size;
        }
        
        int find(int i){
            return parent[i] == i ? i: (parent[i] = find(parent[i]));
        }
        
        void join(int i, int j){
            int roota = find(i), rootb = find(j);
            if(roota != rootb){
                parent[roota] = rootb;
                size--;
            }
        }
    };
};


//with Rank heuristic 


class Solution {
public:
    int numSimilarGroups(vector<string>& A) {
        DisjointSet ds(A.size());
        for(int i = 0; i<A.size()-1;i++){
            for(int j = i+1; j<A.size(); j++){
                if(similar(A[i], A[j]))
                    ds.join(i,j);
            }
        }
        return ds.getSize();
    }
    
    bool similar(const string& a, const string &b){
        for(int i = 0, cnt = 0; i<a.size(); i++){
            if(a[i]!=b[i] && ++cnt>2) return false;
        }
        return true;
    }
    
    struct DisjointSet{
        vector<int>parent;
        vector<int>rank;
        int size;
        
        DisjointSet(int n){
            parent.resize(n);
            rank.resize(n);
            iota(parent.begin(), parent.end(),0);
            size = n;
        }
        
        int getSize(){
            return size;
        }
        
        int find(int i){
            return parent[i] == i ? i: (parent[i] = find(parent[i]));
        }
        
        void join(int i, int j){
            int roota = find(i), rootb = find(j);
            if(roota == rootb) return;
            size--;
            if(rank[roota] > rank[rootb])
                parent[rootb] = roota;
            else 
                parent[roota] = rootb;
            if(rank[roota] == rank[rootb]){
                rank[roota]++;
            }
        }
    };
};


class Solution {
public:
  struct Node {
    Node* root;
  };
  
  vector<Node> r;
  
  Node* getR(Node* v) {
    if (!v->root) return v;
    return v = getR(v->root);
  }
  
  inline bool connect(string& a, string& b) {
    int cnt = 0;
    for (int i = 0; i < a.size(); ++i)
      if (a[i] != b[i])
        if (++cnt > 2) return 0;
    return 1;
  }
  
  int numSimilarGroups(vector<string>& A) {
    int n = A.size();
    r.assign(n, {nullptr});
    for (int i = 0; i < n; ++i)
      for (int j = i+1; j < n; ++j)
        if (connect(A[i], A[j])){
          Node* x = getR(&r[i]), *y = getR(&r[j]);
          if (x != y) y->root = x;
        }
    int ans = 0;
    for (auto v : r) if (!v.root) ++ans;
    return ans;
  }
};