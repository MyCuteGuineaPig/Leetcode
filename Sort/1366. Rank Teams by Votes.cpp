class Solution {
public:
    string rankTeams(vector<string>& votes) {
        vector<vector<int>> count(26, vector<int>(27));
        for (char& c: votes[0])
            count[c - 'A'][26] = c;

        for (string& vote: votes)
            for (int i = 0; i < vote.length(); ++i)
                --count[vote[i] - 'A'][i];
        sort(count.begin(), count.end());
        string res;
        for (int i = 0; i < votes[0].length(); ++i)
            res += count[i][26];
        return res;
    }
};


class Solution {
public:
    string rankTeams(vector<string>& votes) {
        string ans(votes[0]);
        const int n(votes[0].length());
        vector<vector<int>> ranks(26, vector<int>(n));
        
        for (const string& vote: votes)
            for (int i = 0; i < n; ++i)
                ranks[vote[i] - 'A'][i]++;
        /*
        function<bool(const char&, const char&)> compare = [&](const char& x, const char& y) {
            for (int i = 0; i < n; ++i) {
                if (ranks[x - 'A'][i] == ranks[y - 'A'][i]) continue;
                return ranks[x - 'A'][i] > ranks[y - 'A'][i];
            }
            return x < y;
        };
        
        sort(ans.begin(), ans.end(), compare);
		*/
		// @grokus, @plustone: vectors are comparable, faster if your compiler can optimize the comparisons
		sort(ans.begin(), ans.end(), [&](const char& x, const char& y) { return ranks[x - 'A'] > ranks[y - 'A'] || ranks[x - 'A'] == ranks[y - 'A'] && x < y; });
        return ans;
    }
};