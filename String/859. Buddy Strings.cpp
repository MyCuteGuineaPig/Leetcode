/*
859. Buddy Strings


Example 1:

Input: A = "ab", B = "ba"
Output: true
Example 2:

Input: A = "ab", B = "ab"
Output: false
Example 3:

Input: A = "aa", B = "aa"
Output: true
Example 4:

Input: A = "aaaaaaabc", B = "aaaaaaacb"
Output: true
Example 5:

Input: A = "", B = "aa"
Output: false
 

Note:

0 <= A.length <= 20000
0 <= B.length <= 20000
A and B consist only of lowercase letters.


*/
class Solution {
public:
    bool buddyStrings(string A, string B) {
        if(A.size() != B.size()) return false;
        bool isrepeat = false;
        unordered_set<char>set;
        vector<int>pos;
        for(int i = 0; i<A.size(); i++){
            if(A[i] != B[i]){
                if(pos.size()>2) return false; //三个位置不一样，false
                pos.push_back(i);
            }
            else{
                if(set.find(A[i])!=set.end()) isrepeat = true;
                else set.insert(A[i]);
            }
        }
        if(!pos.empty() && (pos.size() == 1 || A[pos[0]] != B[pos[1]] ||A[pos[1]] != B[pos[0]] )) { //只有一个位置不一样不行, 两个位置都要看，比如”"ab" "ca"
            return false;
        }
        else if(pos.size() == 2) 
            return true;
        return isrepeat;
    }
};


class Solution {
public:
    bool buddyStrings(string A, string B) {
        if (A.length() != B.length()) {
            return false;
        }
        vector<int> diff;
        for (int i = 0; i < A.length(); ++i) {
            if (A[i] != B[i]) {
                diff.emplace_back(i);
                if (diff.size() > 2) {
                    return false;
                }
            }
        }
        return (diff.empty() && unordered_set<char>(A.begin(), A.end()).size() < A.size()) ||
               (diff.size() == 2 && A[diff[0]] == B[diff[1]] && A[diff[1]] == B[diff[0]]);
    }
};

class Solution {
public:
    bool buddyStrings(string A, string B) {
        if (A.length() != B.length()) return false;
        if (A == B && set<char>(A.begin(), A.end()).size() < A.size()) return true;
        vector<int> dif;
        for (int i = 0; i < A.length(); ++i) if (A[i] != B[i]) dif.push_back(i);
        return dif.size() == 2 && A[dif[0]] == B[dif[1]] && A[dif[1]] == B[dif[0]];
    }
};


class Solution {
public:
    bool buddyStrings(string A, string B) {
        if (A.size() < 2 || A.size()!=B.size()) return false;
        unordered_map<char,int> m;
        bool dup=false; for (auto& c: A) if (++m[c]>1) dup=true;
        if (A==B) return dup;
        int i=0,N=(int)A.size(),j=N-1;
        while (i<N-1 && A[i]==B[i]) ++i;
        while (j>0   && A[j]==B[j]) --j;
        swap(A[i],A[j]);
        return A==B;
    }
};