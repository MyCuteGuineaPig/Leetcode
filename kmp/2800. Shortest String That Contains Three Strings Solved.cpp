/*
solve_use_kmp(solve_use_kmp(a, b), c), 
 和 
solve_use_kmp(a, solve_use_kmp(b, c)),
结果是一样的，

因为 t = solve_use_kmp(b, c) 是得到以b开始 含有c最小的， t是以b开始的 
v = solve_use_kmp(a, b) 结果是以a开始 且还有b的， v中含有b，且以b结尾

a + b 的最小的组合是 a的suffix是b的prefix，所以求 b + "#" + a 的lps

*/

class Solution {
public:
    string minimumString(string a, string b, string c) {
        std::function<string(const string& a, const string& b)> solve_use_kmp;//需要提前declare,要不然不能run recursion

        solve_use_kmp = [](const string& a, const string& b) -> string{
            string text = b + "#" + a;
            vector<int>lps(text.size(), 0);
            int j = 0;
            for(int i = 1; i<text.size(); ++i){
                while(j>0 && text[i]!=text[j]){
                    j = lps[j-1];
                }
                if(text[i] == text[j]) ++j;
                lps[i] = j;
            } 
            for(int i =  b.size()+1; i<text.size(); ++i){
                if(lps[i] == b.size()) 
                    return a; //check if a contains b
            }
            return a + b.substr(lps.back());
        };
        vector<string> res = {
            solve_use_kmp(solve_use_kmp(a, b), c),
            solve_use_kmp(solve_use_kmp(a, c), b),
            solve_use_kmp(solve_use_kmp(b, a), c),
            solve_use_kmp(solve_use_kmp(b, c), a),
            solve_use_kmp(solve_use_kmp(c, a), b),
            solve_use_kmp(solve_use_kmp(c, b), a),
        };
            
        return *min_element(res.begin(), res.end(), [](const string& a, const string& b){
            return a.size() != b.size() ? a.size() < b.size(): a < b;
        });
    }
};