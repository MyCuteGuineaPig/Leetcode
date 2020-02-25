class Solution {
public:
    vector<string> generateParenthesis(int n) {
        vector<string> ans;
        string str;
        gen(0, 0, n, str, ans);
        return ans;
    }
    
    void gen(int open, int close, int n, string& str, vector<string>& ans) {
        if (open + close == 2 * n) {
            ans.push_back(str);
        } else {
            if (open != n) {
                str.push_back('(');
                gen(open + 1, close, n, str, ans);
                str.pop_back();
            }
            if (close < open) {
                str.push_back(')');
                gen(open, close + 1, n, str, ans);
                str.pop_back();
            }
        }
    }
};


class Solution {
public:
    vector<string> generateParenthesis(int n) {
        vector<string>res;
        helper(res, "", 0, 0, n);
        return res;
    }

    void helper(vector<string>&res,  string cur, int left, int right, const int& n){
        if(left >= n && right >= n){
            if(left == n && right == n)
            {
                res.push_back(cur);
            }
            return;
        }
        if(left < n)
            helper (res, cur + '(', left + 1, right, n); 
        if(left >right)
            helper(res, cur + ')', left, right + 1, n);
    }
};


class Solution {
public:
    vector<string> generateParenthesis(int n) {
        vector<string> res;
        addingpar(res, "", n, 0);
        return res;
    }
    void addingpar(vector<string> &v, string str, int n, int m){
        if(n==0 && m==0) {
            v.push_back(str);
            return;
        }
        if(m > 0){ addingpar(v, str+")", n, m-1); }
        if(n > 0){ addingpar(v, str+"(", n-1, m+1); }
    }
};

class Solution {
public:
    vector<string> generateParenthesis(int n) {
        vector<string> ret;
        helper(ret, "", n, n);
        return ret;
    }
    void helper(vector<string> & res, string str, int left, int right){
        if(left == 0 && right == 0){
            res.push_back(str);
            return;
        }
        if(left > 0) helper(res, str + "(", left - 1, right);
        if(right > left) helper(res, str + ")", left, right - 1);
    }
};
