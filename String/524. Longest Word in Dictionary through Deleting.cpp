/*
524. Longest Word in Dictionary through Deleting

Given a string and a string dictionary, find the longest string in the dictionary that can be formed by deleting some characters of the given string. 
If there are more than one possible results, return the longest word with the smallest lexicographical order. 
If there is no possible result, return the empty string.

Example 1:
Input:
s = "abpcplea", d = ["ale","apple","monkey","plea"]

Output: 
"apple"
Example 2:
Input:
s = "abpcplea", d = ["a","b","c"]

Output: 
"a"
Note:
All the strings in the input will only contain lower-case letters.
The size of the dictionary won't exceed 1,000.
The length of all the strings in the input won't exceed 1,000.
 


*/


class Solution {
public:
    string findLongestWord(string s, vector<string>& d) {
        sort(d.begin(), d.end(), [](const string& a, const string & b){ return a.size() == b.size() ? a < b : a.size() > b.size();  });     

        for(int i = 0; i<d.size(); i++){
            if(isValid(s, d[i])) return d[i];
        }
        return "";
    }
    
    bool isValid(const string & s, const string& dict){
        int j = 0;
        for(int i = 0; i<s.size();i++){
            if(s[i] == dict[j])
                j++;
        }
        return j == dict.size();
    }
};



class Solution {
public:
    string findLongestWord(string s, vector<string>& d) {
        string res = "";
        for(int i = 0; i<d.size(); i++){
            if(isValid(s, d[i])) {
                if(res.size() < d[i].size() || res.size() == d[i].size() && d[i] < res) {
                    res  = d[i];
                }
            }
        }
        return res;
    }
    
    bool isValid(const string & s, const string& dict){
        int j = 0;
        for(int i = 0; i<s.size();i++){
            if(s[i] == dict[j])
                j++;
        }
        return j == dict.size();
    }
};