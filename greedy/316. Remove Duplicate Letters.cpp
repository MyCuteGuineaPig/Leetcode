/*

316. Remove Duplicate Letters
Given a string which contains only lowercase letters, 
remove duplicate letters so that every letter appear once and only once. 
You must make sure your result is the smallest in lexicographical order among all possible results.

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
        
        for(int i = 0; i<s.size();i++) //也可以用priority queue pop index https://leetcode.com/problems/remove-duplicate-letters/discuss/76766/Easy-to-understand-iterative-Java-solution
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
    
    int findMinLastPos(){ //
        int minLastPos = INT_MAX;
        for(auto itr: lastappear){
            minLastPos = min(minLastPos, itr.second);
        }
        return minLastPos;
    }
};



/*
思路: 建立一个ascending stack, 让stack 的元素越来越大，而且需要保证stack中元素只出现一次
其次还有保证如果当 stack top 比char 大，如果后没有stack top了，就不能删除stack。top,因为保证每个元素至少出现一次

需要数据结构：
1. stack 记录当前顺序
2. unordered_map, 记录char后面的个数，当从stack中pop时候，map[top]--
3. unordered_set, 记录当前stack中元素

step： 
1. 看能不能删除stack.top(); stack top比char大的话，
    a. 看stack 中前面是不是已经有char(unordered_set)，如果有不能加入，因为顺序已经定了
       比如： stack = ['a','b','c']， char 是'a',不能说因为stack.top() = c > a, 就pop c，因为a已经在stack中了
    b. 看stack.top() 如果pop了，后面需要还有stack.top()的char，因为保证stack中元素只出现一次

    c. 如果都满足a, b, 先减去map中top的个数减去，因为pop它，后面就少一个了，set再删除top

2. 插入stack时候同样需要看set 中有没有这个char，如果有不能插入


*/

class Solution {
public:
    string removeDuplicateLetters(string s) {
        unordered_map<char, int>map;
        for(auto i: s)
            map[i]++;
        stack<char>stk;
        unordered_set<char>set;
        for(auto i: s){
            while(!stk.empty() && set.count(i) == 0 && map[stk.top()] >1 && stk.top() >= i){
                map[stk.top()]--;
                set.erase(stk.top());
                stk.pop();
            }
            if(set.count(i) == 0){
                set.insert(i);
                stk.push(i);
            }else{
                map[i]--;
            }
        }
        string res;
        while(!stk.empty()){
            res += stk.top(); stk.pop();
        }
        reverse(res.begin(),res.end());
        return res;
    }
};


class Solution {
public:
    string removeDuplicateLetters(string s) {
        unordered_map<char, int> remaining;
        for (const auto& c : s) {
            ++remaining[c];
        }

        unordered_set<char> in_stack;
        string stk;
        for (const auto& c : s) {
            if (!in_stack.count(c)) {
                while (!stk.empty() && stk.back() > c && remaining[stk.back()]) {
                    in_stack.erase(stk.back());
                    stk.pop_back();
                }
                stk.push_back(c);
                in_stack.emplace(c);
            }
            --remaining[c];
        }
        return stk; 
    }
};