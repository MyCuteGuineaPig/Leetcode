class Solution {
public:
    bool canChange(string start, string target) {
        int i = 0, j = 0, n = start.size();
        for(;i < n || j < n; ++i, ++j){
            while (i < n && start[i] == '_') ++i;
            while (j < n && target[j] == '_') ++j;
            if (i == n || j == n  || start[i]!=target[j] || (start[i] == 'L' && i < j) || (start[i] == 'R' && i > j))
                break;
        }
        return i == n && j == n;
    }
};

class Solution {
public:
    bool canChange(string start, string target) {
        vector<pair<char,int>>st;
        for(int i = 0; i<start.size(); ++i)
            if (start[i] != '_')
                st.push_back({start[i], i});
        vector<pair<char,int>>tt;
        for(int i = 0; i<target.size(); ++i)
            if (target[i] != '_')
                tt.push_back({target[i], i});
        
        if (st.size() != tt.size()) return false;
        
        for(int i = 0; i<st.size(); ++i) {
            if (st[i].first != tt[i].first) return false;
            if (st[i].first == 'L' && st[i].second < tt[i].second) return false;
            else if (st[i].first == 'R' && st[i].second > tt[i].second) return false;
        }
        return true;
    }
};