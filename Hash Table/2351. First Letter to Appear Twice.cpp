class Solution {
public:
    char repeatedCharacter(string s) {
        unordered_set<char>st;
        for (auto i: s){
            if (st.count(i)) return i;
            st.insert(i);
        }
        return ' ';
    }
};

class Solution {
public:
    char repeatedCharacter(string s) {
        vector<int> v(26);
        for(char c:s){
            v[c-'a']++;
            if(v[c-'a']>1)return c;
        }
        return 'a';
    }
};


class Solution {
public:
    char repeatedCharacter(string s) {
        vector<bool> v(26);
        for(char c:s){
            if(v[c-'a'])return c;
			v[c-'a']=true;
        }
        return 'a';
    }
};


class Solution {
public:
    char repeatedCharacter(string s) {
        int cnt[26]{};
        for(char ch:s) if(++cnt[ch-'a']==2) return ch;
        return 0;
    }
};