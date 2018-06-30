/*
771. Jewels and Stones

You're given strings J representing the types of stones that are jewels, and S representing the stones you have.  
Each character in S is a type of stone you have.  You want to know how many of the stones you have are also jewels.

The letters in J are guaranteed distinct, and all characters in J and S are letters. Letters are case sensitive, 
so "a" is considered a different type of stone from "A".

Example 1:

Input: J = "aA", S = "aAAbbbb"
Output: 3
Example 2:

Input: J = "z", S = "ZZ"
Output: 0
Note:

S and J will consist of letters and have length at most 50.
The characters in J are distinct.

*/


class Solution {
public:
    int numJewelsInStones(string J, string S) {
        unordered_set<char>set;
        for(auto s: J)
            set.insert(s);
        int res = 0;
        for(auto s: S)
            if(set.count(s)) res++;
        return res;
    }
};


class Solution {
public:
    int numJewelsInStones(string J, string S) {
        unordered_set<char> lookup;
        for (const auto& j : J) {
            lookup.emplace(j);
        }
        int result = 0;
        for (const auto& s : S) {
            result += lookup.count(s);
        }
        return result;
    }
};

class Solution {
public:
    int numJewelsInStones(string J, string S) {
        int count[128]={0};
        int res = 0;
        for (int i = 0; i < J.size(); i++)
        {
            count[J[i]]++;
        }
        for (int i = 0; i < S.size(); i++)
        {
            if ((count[S[i]]) > 0)
            {
                res++;
            }
        }
        return res;
    }
};



class Solution {
public:
    int numJewelsInStones(string J, string S) {
        int count = 0;
        string::const_iterator s_it = S.begin();
        string::const_iterator s_end = S.end();
        while (s_it != s_end) {
        	std::size_t pos = J.find(*s_it);
            if (pos != string::npos) count++;
            s_it++;
        }
        return count;
    }
};