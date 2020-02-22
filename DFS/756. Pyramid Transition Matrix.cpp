/*
756. Pyramid Transition Matrix

We are stacking blocks to form a pyramid. Each block has a color which is a one letter string, like `'Z'`.

For every block of color `C` we place not in the bottom row, we are placing it on top of a left block of color `A` and right block of color `B`. We are allowed to place the block there only if `(A, B, C)` is an allowed triple.

We start with a bottom row of bottom, represented as a single string. We also start with a list of allowed triples allowed. Each allowed triple is represented as a string of length 3.

Return true if we can build the pyramid all the way to the top, otherwise false.

Example 1:
Input: bottom = "XYZ", allowed = ["XYD", "YZE", "DEA", "FFF"]
Output: true
Explanation:
We can stack the pyramid like this:
    A
   / \
  D   E
 / \ / \
X   Y   Z

This works because ('X', 'Y', 'D'), ('Y', 'Z', 'E'), and ('D', 'E', 'A') are allowed triples.
Example 2:
Input: bottom = "XXYX", allowed = ["XXX", "XXY", "XYX", "XYY", "YXZ"]
Output: false
Explanation:
We can't stack the pyramid to the top.
Note that there could be allowed triples (A, B, C) and (A, B, D) with C != D.
Note:
bottom will be a string with length in range [2, 8].
allowed will have length in range [0, 200].
Letters in all strings will be chosen from the set {'A', 'B', 'C', 'D', 'E', 'F', 'G'}.


*/


class Solution {
    vector<vector<int>>T; // T用来记录三个的关系，T[0][1] 0是left child, 1 是right child 等于值是parent
    unordered_set<long>seen; // 用来memoization， 避免重复的中间行
    vector<vector<int>>A; //用来记录pyramid 的
public:
    bool pyramidTransition(string bottom, vector<string>& allowed) {
        T.resize(7,vector<int>(7,0));
        for(auto a: allowed){
            T[a[0]-'A'][a[1]-'A'] |= (1<<(a[2]-'A'));
        }
        int N = bottom.size();
        A.resize(N,vector<int>(N,0));
        for(int i = 0; i<bottom.size();i++)
            A[N-1][i] = bottom[i]-'A';
        return solve(0,N-1,0);
    }
    //A[i] - the ith row of the pyramid
    //R - integer representing the current row of the pyramid
    //N - length of current row we are calculating
    //i - index of how far in the current row we are calculating
    //Returns true iff pyramid can be built
    bool solve(long R, int N, int i){
        if(N==1 && i == 1) return true; // If successfully placed entire pyramid
        else if(i == N){
            if(seen.find(R) != seen.end())  return false; // If we've already tried this row, give up
            seen.insert(R);// Add row to cache
            return solve(0,N-1,0);// Calculate next row
        }else{
            int w = T[A[N][i]][A[N][i+1]];
            for(int b =0 ; b<7; b++) {
                if(((w>>b) & 1) == 1 ){
                A[N-1][i] = b;//set parent to be equal to block #b
                //If rest of pyramid can be built, return true
                //R represents current row, now with ith bit set to b+1
                // in base 8.
                 if(solve(R*8+b+1, N, i+1)) return true;
                A[N-1][i] = 0;
                }
                
              }

         }
        return false;
    }
};


//self
class Solution {
public:
    bool pyramidTransition(string bottom, vector<string>& allowed) {
        unordered_map<char, unordered_map<char, unordered_set<char>>>mp;
        for(auto s: allowed){
            mp[s[0]][s[1]].insert(s[2]);
        }
        return build(bottom, "", mp, 0);
    }
    
    bool build(string s, string top, unordered_map<char, unordered_map<char, unordered_set<char>>>&mp, int index){
        if(s.size() == 1)
            return true;
        if(index == s.size()-1)
            return build(top, "", mp, 0); //这层走完走上一层
        if(mp.find(s[index]) == mp.end() || mp[s[index]].find(s[index+1]) == mp[s[index]].end())
            return false;
        for(auto i: mp[s[index]][s[index+1]])
            if(build(s, top + i, mp, index + 1))
                return true;
        return false;
    }
};
