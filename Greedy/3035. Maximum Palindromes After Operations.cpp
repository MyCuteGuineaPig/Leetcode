class Solution {
public:
    int maxPalindromesAfterOperations(vector<string>& words) {
        priority_queue<int, vector<int>,greater<int>>pq;
        unordered_map<char, int>mp;
        for(const auto &s: words){
            pq.push(s.size());
            for(const auto &c: s)
                ++mp[c];
        }
        
        int pair = 0;
        for(auto & c: mp)
            pair += c.second / 2; 
        int cnt = 0; 
        while(pq.size()){
            int size = pq.top(); pq.pop();
            //cout<<" size "<<size<<" pair "<<pair <<endl;
            if( (pair -= size /2) <0 ){
                return cnt;
            }
            cnt += 1;
        }
        return words.size();
    }
};


class Solution {
public:
    int maxPalindromesAfterOperations(vector<string>& words) {
        vector<int> A;
        for (const string& w : words)
            A.push_back(w.length());
        sort(A.begin(), A.end());

        unordered_map<char, int> count;
        for (auto& w : words)
            for (char c : w)
                count[c]++;
        int pairs = 0, n = A.size();
        for (auto& p : count)
            pairs += p.second / 2;

        for (int i = 0; i < n; ++i)
            if ((pairs -= A[i] / 2) < 0)
                return i;
        return n;
    }
};