/*
796. Rotate String

We are given two strings, A and B.

A shift on A consists of taking string A and moving the leftmost character to the rightmost position. 
For example, if A = 'abcde', then it will be 'bcdea' after one shift on A. Return True if and only if A can become B after some number of shifts on A.

Example 1:
Input: A = 'abcde', B = 'cdeab'
Output: true

Example 2:
Input: A = 'abcde', B = 'abced'
Output: false
Note:

A and B will have length at most 100.

*/
class Solution {
public:
    bool rotateString(string s, string goal) {
        if (s.size() != goal.size())
            return false;
        string text = s  + s;
        vector<int>lps = computeLps(goal);
        int j = 0;
        for(int i = 0; i<text.size(); ++i){
            while(j > 0 && text[i]!=goal[j]){
                j = lps[j-1];
            }
            if (text[i] == goal[j]){
                ++j;
            }
            if(j == goal.size()){
                return true;
            }
        }
        return false;
    }

    vector<int> computeLps(const string& text){
        vector<int>lps(text.size());
        int j = 0;
        for(int i = 1; i<text.size(); ++i){
            while(j > 0 && text[i]!=text[j])
                j = lps[j-1];
            if (text[i] == text[j])
                ++j;
            lps[i] = j;
        }
        return lps;
    }
};


class Solution {
public:
    bool rotateString(string A, string B) {
        if(A.size()!=B.size()) return false;
        if(A == B) return true;
        vector<int>prefix(B.size());
        for(int i = 1, j = 0; i<B.size(); i++){
            while(j>0 && B[i] != B[i]) j = prefix[j-1];
            if( B[i] == B[j]) ++j;
            prefix[i] = j; 
        }

        for(int i = 0, j = 0; i<2*A.size(); i+=1){
            while(j>0 && A[i%A.size()]!=B[j]) j = prefix[j-1];
            if(A[i%A.size()] == B[j]) ++j;
            if(j == B.size()) return true;
        }
        return false;
    }
};


class Solution {
public:
    bool rotateString(string A, string B) {
        if(A.size()!=B.size()) return false;
        if(A == B) return true;
        vector<int>prefix(B.size());
        for(int i = 1, j = 0; i<B.size(); i++){
            while(j>0 && B[i] != B[i]) j = prefix[j-1];
            if( B[i] == B[j]) ++j;
            prefix[i] = j; 
        }

        for(int i = 0, j = 0; i<A.size(); i+= j - prefix[j-1], j = prefix[j-1]){
            while(j<B.size() && A[(i+j)%A.size()] == B[j]) j++;
            if(j == B.size()) return true;
            if(j == 0) j = 1;
        }
        return false;
    }
};



//complexity O(n^2)
class Solution {
public:
    bool rotateString(string A, string B) {
        return A.size() == B.size() && (A+A).find(B) != string::npos;
    }
};



// Time:  O(n)
// Space: O(1)

// Rabin-Karp Algorithm (rolling hash)
class Solution {
public:
    bool rotateString(string A, string B) {
        if (A.length() != B.length()) {
            return false;
        }
        static const uint64_t M = 1000000007;
        static const uint64_t p = 113; 
        static const uint64_t p_inv = pow(p, M - 2, M);
    
        uint64_t b_hash = 0, power = 1;
        for (int i = 0; i < B.length(); ++i) {
            b_hash += power * B[i];
            b_hash %= M;
            power = (power * p) % M;
        }

        uint64_t a_hash = 0; power = 1;
        for (int i = 0; i < B.length(); ++i) {
            a_hash += power * A[i % A.length()];
            a_hash %= M;
            power = (power * p) % M;
        }
        if (a_hash == b_hash && check(0, A, B)) {
            return true;
        }
        
        power = (power * p_inv) % M;
        for (int i = B.length(); i < 2 * A.length(); ++i) {
            a_hash -= A[(i - B.length()) % A.length()];
            a_hash *= p_inv;
            a_hash += power * A[i % A.length()];
            a_hash %= M;
            if (a_hash == b_hash && check(i - B.length() + 1, A, B)) {
                return true;
            }
        }
        return false;
    }

private:
    bool check(int index, const string& A, const string& B) {
        for (int i = 0; i < B.length(); ++i) {
            if (A[(i + index) % A.length()] != B[i]) {
                return false;
            }
        }
        return true;
    }

    uint64_t pow(uint64_t a,uint64_t b, uint64_t m) {
        a %= m;
        uint64_t result = 1;
        while (b) {
            if (b & 1) {
                result = (result * a) % m;
            }
            a = (a * a) % m;
            b >>= 1;
        }
        return result;
    }
};
