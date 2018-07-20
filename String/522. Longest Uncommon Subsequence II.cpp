/*
522. Longest Uncommon Subsequence II

Given a list of strings, you need to find the longest uncommon subsequence among them. 
The longest uncommon subsequence is defined as the longest subsequence of one of these strings and this subsequence should not be any subsequence of the other strings.

A subsequence is a sequence that can be derived from one sequence by deleting some characters without changing the order of the remaining elements.
Trivially, any string is a subsequence of itself and an empty string is a subsequence of any string.

The input will be a list of strings, and the output needs to be the length of the longest uncommon subsequence. 
If the longest uncommon subsequence doesn't exist, return -1.

Example 1:
Input: "aba", "cdc", "eae"
Output: 3
Note:

All the given strings' lengths will not exceed 10.
The length of the given list will be in the range of [2, 50].

*/


class Solution {
public:
    int findLUSlength(vector<string>& strs) {
        sort(strs.begin(),strs.end(), [](const string& a, const string& b) { return a.size() > b.size();});
        for(int i = 0; i<strs.size(); i++){
            bool find = true;
            for(int j = 0; j<strs.size(); j++){
                if(i!=j && isSubstring(strs[i], strs[j])){
                    find = false;
                    break;
                }
            }
            if(find)
                return strs[i].size();
        }
        return -1;
    }
    
    bool isSubstring(const string & a, const string & b){
        int i = 0;
        for(int j = 0; j<b.size() && i<a.size(); j++){
            if(a[i] ==b[j]){
                i++;
            }
        }
        return i == a.size();
    }
};


class Solution {
public:
    template<class ForwardIterator1, class ForwardIterator2>
    static
    bool subsequence(ForwardIterator1 first1, 
                     ForwardIterator1 last1,  // first sequence contain subsequence of the second
                     ForwardIterator2 first2, 
                     ForwardIterator2 last2) {
        while (first1 != last1 && first2 != last2) {
            if (*first1 == *first2) {
                first1++;
                first2++;
            } else {
                first1++;
            }
        }
        return first2 == last2;
    }


    int findLUSlength(vector<string>& strs) {
        // sort string by len from long to short
        auto comp = [](const string& a, const string& b) { return a.size() > b.size(); }; 
        sort(strs.begin(), strs.end(), comp);
        auto start = begin(strs);
        while (start != end(strs)) {
            auto ans = start->size();
            // find range of string of same length
            auto range = equal_range(start, end(strs), *start, comp); 
            // examine each string  in this range
            for (auto it = range.first; it != range.second; ++it) {   
                // search from begining to end of this range
                if (count_if(strs.begin(), range.second, 
                    [it](const string&a) { return subsequence(a.begin(), a.end(), it->begin(), it->end()); }) == 1)//只用对比现在长度大的
                    // find a string that is not subsequence of any string of equal or longer length, 
                    // ==1 means find just itself
                    return ans;  
            }
            // try a shorter string if no solution found yet
            start = range.second; 
        }
        return -1;
    }
};