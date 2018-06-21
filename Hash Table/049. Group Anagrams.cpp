/*
49. Group Anagrams


Given an array of strings, group anagrams together.

Example:

Input: ["eat", "tea", "tan", "ate", "nat", "bat"],
Output:
[
  ["ate","eat","tea"],
  ["nat","tan"],
  ["bat"]
]
Note:

All inputs will be in lowercase.
The order of your output does not matter.


*/


class Solution {
public:
    vector<vector<string>> groupAnagrams(vector<string>& strs) {
        unordered_map<string,vector<string>>map;
        for(auto i: strs){
            string key = i;
            sort(key.begin(),key.end());
            map[key].push_back(i);
        }
        vector<vector<string>>res;
        for(auto it: map){
            res.push_back(it.second);
        }
        return res;
    }
};