/*
848. Shifting Letters


We have a string S of lowercase letters, and an integer array shifts.

Call the shift of a letter, the next letter in the alphabet, (wrapping around so that 'z' becomes 'a'). 

For example, shift('a') = 'b', shift('t') = 'u', and shift('z') = 'a'.

Now for each shifts[i] = x, we want to shift the first i+1 letters of S, x times.

Return the final string after all such shifts to S are applied.

Example 1:

Input: S = "abc", shifts = [3,5,9]
Output: "rpl"
Explanation: 
We start with "abc".
After shifting the first 1 letters of S by 3, we have "dbc".
After shifting the first 2 letters of S by 5, we have "igc".
After shifting the first 3 letters of S by 9, we have "rpl", the answer.
Note:

1 <= S.length = shifts.length <= 20000
0 <= shifts[i] <= 10 ^ 9

*/

class Solution {
public:
    string shiftingLetters(string S, vector<int>& shifts) {
        string lookup = "abcdefghijklmnopqrstuvwxyz";
        int sum = 0;
        transform(shifts.rbegin(), shifts.rend(), shifts.rbegin(), [&](int & i){ sum= (sum +i)%26; return i+sum-i;});
        for(int i = 0; i<S.size(); i++){
            int sf = (S[i] - 'a' + shifts[i])%26;
            S[i] = lookup[sf >= 0 ? sf : 26 +sf];
        }
        return S;
    }
};


class Solution {
public:
    string shiftingLetters(string S, vector<int>& shifts) {
        int sum = 0;
        for(int i = shifts.size() - 1; i >= 0; --i){
            shifts[i] %= 26;
            int t = shifts[i];
            shifts[i] += sum;
            sum += t;
        }
        for(int i = 0; i < S.size(); ++i){
            int t = S[i] - 'a';
            t = (t + shifts[i]) % 26;
            S[i] = char('a' + t);
        }
        return S;
    }
};


class Solution {
public:
    string shiftingLetters(string S, vector<int>& shifts) {
        for (int i = S.size() - 1, p = 0; i >= 0; i--)
            S[i] = (S[i] - 'a' + (p += shifts[i] % 26)) % 26 + 'a';
        return S;
    }
};

class Solution {
public:
    string shiftingLetters(string S, vector<int>& shifts) {
        string result;
        auto times = accumulate(shifts.cbegin(), shifts.cend(), 0L) % 26;
        for (int i = 0; i < S.length(); ++i) {
            result.push_back('a' + (S[i] - 'a' + times) % 26);
            times = ((times - shifts[i]) % 26 + 26) % 26;
        }
        return result;
    }
};
