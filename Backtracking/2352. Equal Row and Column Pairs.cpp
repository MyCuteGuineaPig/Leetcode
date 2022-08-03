class Solution {
public:
    int equalPairs(vector<vector<int>>& grid) {
        Trie cur;
        for(int i = 0; i<grid.size(); ++i){
            cur.build(grid[i]);
        }
        int res = 0;
        for(int i = 0; i<grid.size(); ++i){
            res += cur.count(grid, i);
        }
        return res;
    }
    
class Trie{
private: 
    unordered_map<int, Trie*>mp;
    int cnt = 0;

public:
    void build(const vector<int>&row){
        Trie* t = this;
        for(int i = 0; i<row.size(); ++i){
            if (t->mp.count(row[i]) == 0) {
                t->mp[row[i]] = new Trie();
            }
            t = t->mp[row[i]];
        }
         ++(t->cnt);
    }
    
    int count(const vector<vector<int>>&grid, int index) {
        Trie* t = this;
        for(int i = 0; i<grid.size(); ++i) {
            if (t->mp.count(grid[i][index]) == 0) 
                return 0;
            t = t->mp[grid[i][index]];
        }
        return t->cnt;
    }
    
};
};


class Solution {
public:
    int equalPairs(vector<vector<int>>& grid) {
        int res = 0, n = grid.size();
        map<vector<int>, int> m;
        for (int j = 0; j < n; ++j) {
            vector<int> col;
            for (int i = 0; i < n; ++i)
                col.push_back(grid[i][j]);
            auto it = m.find(col);
            if (it == end(m))
                m.emplace(move(col), 1);
            else
                ++it->second;
        }
        for (const auto &row : grid)
            res += m[row];
        return res;
    }
};


class Solution {
    
    struct Trie {
        unordered_map<int, Trie*> m;
        int cnt = 0;
        int insert(vector<vector<int>>& g, int i, int j, bool row) {
            auto node = this;
            for (; max(i, j) < g.size(); i += row, j += !row) {
                auto it = node->m.find(g[i][j]);
                if (it == end(node->m)) {
                    if (row)
                        return 0; // no match.
                    it = node->m.insert({g[i][j], new Trie()}).first;
                }
                node = it->second;
            }
            return node->cnt += !row;
        }
    };
public:
    int equalPairs(vector<vector<int>>& g) {
        Trie t;
        int res = 0;
        for (int i = 0; i < g.size(); ++i)
            t.insert(g, i, 0, false);
        for (int j = 0; j < g.size(); ++j)
            res += t.insert(g, 0, j, true);
        return res;
    }

};