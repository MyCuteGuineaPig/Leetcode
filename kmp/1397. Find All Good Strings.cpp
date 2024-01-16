class Solution {
public:
    int findGoodStrings(int n, string s1, string s2, string evil) {
        vector<int> kmp = KMP(evil);
        vector<vector<vector<vector<long>>>>mp(n+1, vector<vector<vector<long>>>(n+1, vector<vector<long>>(2, vector<long>(2,-1))));
        return DFS(n, s1, s2, evil, true, true, 0, 0, kmp, mp);
    }
    
    long DFS(const int & n, const  string& s1, const string& s2, const string& evil,  bool useBoundS1, bool useBoundS2, int ind, int ind_evil, const vector<int>& kmp, vector<vector<vector<vector<long>>>>&mp){
        if( ind_evil == evil.size())
            return 0;
        if( ind  == n)
            return 1;
        if(mp[ind][ind_evil][useBoundS1][useBoundS2] != -1)
            return mp[ind][ind_evil][useBoundS1][useBoundS2]; 
        long tot = 0; 
        int begin = useBoundS1 ? s1[ind]- 'a' : 0;
        int end = useBoundS2 ? s2[ind] - 'a' : 'z' - 'a';
        for(int i = begin ; i< end+1 ; ++i){
            bool nextUseBoundS1 = useBoundS1 && i == begin;
            bool nextUseBoundS2 = useBoundS2 && i == end;
            int j = ind_evil;
            while ( j && evil[j] - 'a' != i )
                j = kmp[j -1];
            if ( i + 'a' == evil[j] )
                ++j;
            /*
            比如现在记录的是 a b a b a 
                   evil 是 a b a b e
                                   | 
                                   v  jump to 
                               a b a b 
            */
            mp[ind+1][j][nextUseBoundS1][nextUseBoundS2] = DFS(n, s1, s2, evil,nextUseBoundS1 , nextUseBoundS2, ind+1, j, kmp, mp) % (1000000000 + 7);
            tot =  (tot + mp[ind+1][j][nextUseBoundS1][nextUseBoundS2]) % (1000000000 + 7);
        }
        return tot;
    }
    
    vector<int>KMP(const string& str){
        vector<int>res(str.size());
        for(int i = 1, j = 0; i<str.size(); ++i){
            while( j && str[j] != str[i])
                j = res[j-1];
            if(str[j] == str[i]) ++j;
            res[i] = j;
        }
        return res;
    }
};


class Solution {
public:
    int findGoodStrings(int n, string s1, string s2, string evil) {
        vector<vector<vector<vector<int>>>> memo = vector(n+1, vector(evil.size()+1, vector(2, vector(2, -1)))); 
        return dfs(0, 0, true, true,
			n, s1, s2, evil, computeLPS(evil), memo);
    }
    int dfs(int i, int matchEvilLen, bool useBoundS1, bool useBoundS2,
			int n, string& s1, string& s2, string& evil, const vector<int>& lps, vector<vector<vector<vector<int>>>>& memo) {
        if (matchEvilLen == evil.size()) return 0; // contain `evil` as a substring -> not good string
        if (i == n) return 1; // it's a good string
        if (memo[i][matchEvilLen][useBoundS1][useBoundS2] != -1) return memo[i][matchEvilLen][useBoundS1][useBoundS2];
        char from = useBoundS1 ? s1[i] : 'a';
        char to = useBoundS2 ? s2[i] : 'z';
        int res = 0;
        for (char c = from; c <= to; c++) {
            int j = matchEvilLen; // j means nextMatchEvilLen
            while (j > 0 && evil[j] != c) j = lps[j - 1];
            if (c == evil[j]) j++;
            res += dfs(i + 1, j, useBoundS1 && (c == from), useBoundS2 && (c == to),
                    n, s1, s2, evil, lps, memo);
            res %= 1000000007;
        }
        return memo[i][matchEvilLen][useBoundS1][useBoundS2] = res;
    }
    vector<int> computeLPS(const string& str) { // Longest Prefix also Suffix
        int n = str.size();
        vector<int> lps = vector<int>(n);
        for (int i = 1, j = 0; i < n; i++) {
            while (j > 0 && str[i] != str[j]) j = lps[j - 1];
            if (str[i] == str[j]) lps[i] = ++j;
        }
        return lps;
    }
};

class Solution {
public:
    int findGoodStrings(int n, string s1, string s2, string evil) {
        vector<int>lps (evil.size());
        kmp(evil, lps);
        vector<vector<vector<vector<long>>>>mp(n+1, vector<vector<vector<long>>>(n+1, vector<vector<long>>(2, vector<long>(2,-1))));
        //s1 index, s2 index, use_s1_boundary, use_s2_boundary;
        return helper(n, s1, s2, evil, 0, 0, true, true, lps, mp);
    }

    long helper(int n, const string &s1, const string& s2, const string& evil, int ind, int ind_evil, 
        bool use_s1_boundary, bool use_s2_boundary, 
        const vector<int>&lps, 
        vector<vector<vector<vector<long>>>>& mp)
    {
        if(ind_evil == evil.size()){
            return 0;
        }
        if (ind == n) {
            return 1;
        }
        if (mp[ind][ind_evil][use_s1_boundary][use_s2_boundary]!=-1){
            return mp[ind][ind_evil][use_s1_boundary][use_s2_boundary];
        }
        long res = 0;
        char begin = use_s1_boundary? s1[ind]: 'a';
        char end = use_s2_boundary? s2[ind]: 'z';
        for(auto c = begin; c <= end; ++c){
            bool next_use_s1_boundary = use_s1_boundary && c == s1[ind];
            bool next_use_s2_boundary = use_s2_boundary && c == s2[ind];
            int j = ind_evil;
            while(j > 0 && evil[j]!= c){
                j = lps[j-1];
            }
            if(evil[j] == c)
                ++j;
            long next = helper(n, s1, s2, evil, ind+1, j,next_use_s1_boundary,next_use_s2_boundary , lps, mp);
            res = (res + next) % ((long)(1e9 + 7));
        }
        return mp[ind][ind_evil][use_s1_boundary][use_s2_boundary] = res;
    }

    void kmp(const string& evil, vector<int>&lps){
        int j = 0; 
        for(int i = 1; i<evil.size(); ++i){
            while( j > 0 && evil[i]!=evil[j])
                j = lps[j-1];
            if (evil[i] == evil[j]) ++j;
            lps[i] = j;
        }
    }
};