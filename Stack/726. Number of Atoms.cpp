/*
726. Number of Atoms

Given a chemical formula (given as a string), return the count of each atom.

An atomic element always starts with an uppercase character, then zero or more lowercase letters, 
representing the name.

1 or more digits representing the count of that element may follow if the count is greater than 1.
 If the count is 1, no digits will follow. For example, H2O and H2O2 are possible, but H1O2 is impossible.

Two formulas concatenated together produce another formula. For example, H2O2He3Mg4 is also a formula.

A formula placed in parentheses, and a count (optionally added) is also a formula. 
For example, (H2O2) and (H2O2)3 are formulas.

Given a formula, output the count of all elements as a string in the following form: 
the first name (in sorted order), followed by its count (if that count is more than 1), 
followed by the second name (in sorted order), followed by its count (if that count is more than 1), and so on.

Example 1:
Input: 
formula = "H2O"
Output: "H2O"
Explanation: 
The count of elements are {'H': 2, 'O': 1}.
Example 2:
Input: 
formula = "Mg(OH)2"
Output: "H2MgO2"
Explanation: 
The count of elements are {'H': 2, 'Mg': 1, 'O': 2}.
Example 3:
Input: 
formula = "K4(ON(SO3)2)2"
Output: "K4N2O14S4"
Explanation: 
The count of elements are {'K': 4, 'N': 2, 'O': 14, 'S': 4}.
Note:

All atom names consist of lowercase letters, except for the first character which is uppercase.
The length of formula will be in the range [1, 1000].
formula will only consist of letters, digits, and round parentheses, 
and is a valid formula as defined in the problem.


*/


//write by own
class Solution {
public:
    string countOfAtoms(string formula) {
        map<string, int>mp;
        stack<unordered_map<string,int>>stk;
        stk.push(unordered_map<string,int>());
        for(int i = 0; i<formula.size();){
            if(formula[i] == '('){
                stk.push(unordered_map<string,int>());
                i++;
            }
            else if(formula[i] == ')'){
                int start_c = ++i;
                while(i<formula.size() && isdigit(formula[i])) i++;
                int count = i==start_c ? 1 : stoi(formula.substr(start_c, i-start_c));
                unordered_map<string,int>cur_mp = stk.top();
                stk.pop();
                for(auto p: cur_mp){
                    stk.top()[p.first] += p.second*count;
                }
            }else{
                int start = i;
                while(i+1<formula.size() && islower(formula[i+1])) i++;
                string cur = formula.substr(start,i+1-start);
                int start_c = ++i;
                while(i<formula.size() && isdigit(formula[i])) i++;
                int count = i==start_c ? 1 : stoi(formula.substr(start_c, i-start_c+1));
                stk.top()[cur] += count;
            }
        }
        for(auto p: stk.top()){
            mp[p.first] = p.second;
        }
        
        
        string res = "";
        for(auto p: mp){
            res += p.first + (p.second == 1 ? "": to_string(p.second));
        }
        
        return res;
    }
};

class Solution {
public:
    string countOfAtoms(string formula) {
        stack<map<string, int>>stk;
        map<string,int>cur;
        for(int i = 0; i<formula.size();){
            if(formula[i] == '('){
                stk.push(move(cur));
                cur = map<string,int>();
                i++;
            }else if(formula[i] == ')'){
                int k = i++,x = 0;
                while(i<formula.size() && isdigit(formula[i])) x = x*10 + formula[i++] - '0';
                x = max(x, 1);
                for(auto it: cur) stk.top()[it.first] += it.second*x;
                cur = move(stk.top());
                stk.pop();
            }else{
                int j = i++;
                while(i<formula.size() && islower(formula[i])) i++;
                int k = i,x = 0;
                while(i<formula.size() && isdigit(formula[i])) x = x*10 + formula[i++] - '0';
                x = max(x, 1);
                cur[formula.substr(j,k-j)] += x;
            }
        }
        string res;
        for(auto it: cur)
            if(it.second == 1) res += it.first;
            else res += it.first + to_string(it.second);
        return res;
    }
};



class Solution {
public:
    string countOfAtoms(string formula) {
        string output;
        const int n = formula.size();
        int i = 0;
        map<string, int> counts = parseFormula(formula, i);
        for (pair<string, int> p : counts) {
            output += p.first;
            if (p.second > 1) output += to_string(p.second);
        }
        return output;
    }

private:
    map<string, int> parseFormula(string& s, int& i) {
        map<string, int> counts;
        const int n = s.size();
        while (i < n && s[i] != ')') {
            map<string, int> cnts = parseUnit(s, i);
            merge(counts, cnts, 1);
        }
        return counts;
    }

    map<string, int> parseUnit(string& s, int& i) {
        map<string, int> counts;
        const int n = s.size();
        if (s[i] == '(') {
            map<string, int> cnts = parseFormula(s, ++i); // ++i for '('
            int digits = parseDigits(s, ++i); // ++i for ')'
            merge(counts, cnts, digits);
        }
        else {
            int i0 = i++; // first letter
            while (i < n && islower(s[i])) { i++; }
            string atom = s.substr(i0, i - i0);
            int digits = parseDigits(s, i);
            counts[atom] += digits;
        }
        return counts;
    }

    int parseDigits(string& s, int& i) {
        int i1 = i;
        while (i < s.size() && isdigit(s[i])) { i++; }
        int digits = i == i1 ? 1 : stoi(s.substr(i1, i - i1));
        return digits;
    }

    void merge(map<string, int>& counts, map<string, int>& cnts, int times) {
        for (pair<string, int> p : cnts) counts[p.first] += p.second * times;
    }
};



/*
C++ regular expression 慢很多，

regex_token_iterator<string::iterator> it(formula.begin(), formula.end(), e, submatches), submatched, 代表match几个选项
一个括号代表一个选项([A-Z][a-z]*)(\\d*) 代表数字必须跟在字母后边, |(\\()  | 代表或者
*/

class Solution {
public:
    string countOfAtoms(string formula) {
        stack<map<string, int>> stk;
        stk.emplace();
        int submatches[] = { 1, 2, 3, 4, 5 };
        const auto e = regex("([A-Z][a-z]*)(\\d*)|(\\()|(\\))(\\d*)");
        for (regex_token_iterator<string::iterator> it(formula.begin(), formula.end(), e, submatches), end;
             it != end;) {
            const auto& name = (it++)->str();
            const auto& m1 = (it++)->str();
            const auto& left_open = (it++)->str();
            const auto& right_open = (it++)->str();
            const auto& m2 = (it++)->str();
            cout<<" name "<<*name<<" m1 "<<m1<<" left open " <<*left_open<<" right_open " <<*right_open<<" m2 "<<*m2<<endl;
            if (!name.empty()) {
                stk.top()[name] += stoi(!m1.empty() ? m1 : "1");
            }
            if (!left_open.empty()) {
                stk.emplace();
            }
            if (!right_open.empty()) {
                const auto top = move(stk.top()); stk.pop();
                for (const auto& kvp: top) {
                    stk.top()[kvp.first] += kvp.second * stoi(!m2.empty() ? m2 : "1");
                }
            }
        }
        string result;
        for (const auto& kvp : stk.top()) {
            result += kvp.first;
            if (kvp.second > 1) {
                result += to_string(kvp.second);
            }
        }
        return result;
    }
};
