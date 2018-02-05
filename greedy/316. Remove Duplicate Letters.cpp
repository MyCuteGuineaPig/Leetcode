/*

316. Remove Duplicate Letters
Given a string which contains only lowercase letters, remove duplicate letters so that every letter appear once and only once. You must make sure your result is the smallest in lexicographical order among all possible results.

Example:
Given "bcabc"
Return "abc"

Given "cbacdcbc"
Return "acdb"

*/


/*

The basic idea is to find out the smallest result letter by letter (one letter at a time). Here is the thinking process for input "cbacdcbc":

find out the last appeared position for each letter;
c - 7
b - 6
a - 2
d - 4
find out the smallest index from the map in step 1 (a - 2);
the first letter in the final result must be the smallest letter from index 0 to index 2;
repeat step 2 to 3 to find out remaining letters.
the smallest letter from index 0 to index 2: a
the smallest letter from index 3 to index 4: c
the smallest letter from index 4 to index 4: d
the smallest letter from index 5 to index 6: b
so the result is "acdb"

Notes:

after one letter is determined in step 3, it need to be removed from the "last appeared position map", and the same letter should be ignored in the following steps
in step 3, the beginning index of the search range should be the index of previous determined letter plus one

*/




class Solution {
public:
    unordered_map<char,int>lastappear;
    
    string removeDuplicateLetters(string s) {
        if(s.size()<=1) return s;
        vector<int>num(26,0);
        string result="";
        
        for(int i = 0; i<s.size();i++)
            lastappear[s[i]]=i;
        
        int start = 0, end = 0;
        while((end = findMinLastPos()) != INT_MAX){
            char minChar = 'z'+1;
            
            for(int i = start; i<= end; i++){
                if(lastappear.count(s[i])>0 && s[i]<minChar){
                    minChar = s[i];
                    start = i+1;
                }
            }
            result+=minChar;
            lastappear.erase(minChar);
        }
        
        return result;
    }
    
    int findMinLastPos(){
        int minLastPos = INT_MAX;
        for(auto itr: lastappear){
            minLastPos = min(minLastPos, itr.second);
        }
        return minLastPos;
    }
};