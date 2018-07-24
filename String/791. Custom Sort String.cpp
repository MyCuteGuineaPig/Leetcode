/*
791. Custom Sort String

S and T are strings composed of lowercase letters. In S, no letter occurs more than once.

S was sorted in some custom order previously. We want to permute the characters of T so that they match the order that S was sorted. 
More specifically, if x occurs before y in S, then x should occur before y in the returned string.

Return any permutation of T (as a string) that satisfies this property.

Example :
Input: 
S = "cba"
T = "abcd"
Output: "cbad"
Explanation: 
"a", "b", "c" appear in S, so the order of "a", "b", "c" should be "c", "b", and "a". 
Since "d" does not appear in S, it can be at any position in T. "dcba", "cdba", "cbda" are also valid outputs.
 

Note:

S has length at most 26, and no character is repeated in S.
T has length at most 200.
S and T consist of lowercase letters only.

*/

/*
Custom Sort Runtime: 0 ms
*/
class Solution {
public:
    string customSortString(string S, string T) {
        vector<int>order(26,100);
        for(int i = 0; i<S.size(); i++)
            order[S[i] - 'a'] = i;

        auto cmp = [&](auto a, auto b){
            if(order[a-'a']!=order[b-'a']) return order[a-'a']<order[b-'a']; 
            else return a < b;
        };      
        sort(T.begin(), T.end(), cmp);
        return T;
    }
};


/*
Bucket Sort  Runtime: 0 ms
*/

class Solution {
public:
    string customSortString(string S, string T) {
        vector<int>container(26,27);
        for(int i = 0; i<S.size(); i++)
            container[S[i] - 'a'] = i;
        map<int, set<int>>order; //key is the order, value is set of value
        for(int i = 0; i<26; i++){
            order[container[i]].insert(i);  
        }

        vector<int>bucket(26);
        for(auto i: T) bucket[i-'a']++;

        string res;
        for(auto it: order){
            for(auto c: it.second){
                for(int i = 0; i<bucket[c]; i++)
                    res += c+'a';
            }
        }

        return res;
    }
};


/*
Priority Queue  Runtime: 0 ms
*/


class Solution {
public:
    string customSortString(string S, string T) {
        vector<int>order(26,27);
        for(int i = 0; i<S.size(); i++)
            order[S[i] - 'a'] = i;
       
             
        auto cmp = [&](const char& a, const char &b){
            return order[a-'a'] != order[b-'a'] ? order[a-'a'] > order[b-'a'] : a >b;
        };
        priority_queue<char, vector<char>, decltype(cmp)>pq(cmp);
        for(auto i: T) pq.push(i);

        string res; 
        while(!pq.empty()){
            res += pq.top();
            pq.pop();
        }
        return res;
    }
};



class Solution {
public:
    string customSortString(string S, string T) {
        unordered_set<char> s(S.cbegin(), S.cend());
        unordered_map<char, int> counter;
        for (const auto& c : T) {
            ++counter[c];
        }
        string result;
        for (const auto& c : S) {
            result += string(counter[c], c);
        }
        for (const auto& kvp : counter) {
            if (!s.count(kvp.first)) {
                result += string(kvp.second, kvp.first);
            }
        } 
        return result;
    }
};


/*
can use stl
*/
class Solution {
  public:
    string customSortString(string S, string T) {
        unordered_map<char, int> dir;
        int i = 0;
        transform(S.begin(), S.end(), inserter(dir, dir.end()),
                  [&](char &a) { return make_pair(a, ++i); });
        sort(T.begin(), T.end(),
             [&](char a, char b) { return dir[a] < dir[b]; });
        return T;
    }
};