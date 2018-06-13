/*
71. Simplify Path

Given an absolute path for a file (Unix-style), simplify it.

For example,
path = "/home/", => "/home"
path = "/a/./b/../../c/", => "/c"

Corner Cases:

Did you consider the case where path = "/../"?
In this case, you should return "/".
Another corner case is the path might contain multiple slashes '/' together, such as "/home//foo/".
In this case, you should ignore redundant slashes and return "/home/foo".



*/


/*

"/b/c/" - directory 'b ' - > directory 'c '
"." - current directory
"./" - current directory
"../" - one directory up
e.g
"/" : root directory
"b/c/../" : it will go from c to b
"c/b/./" : it is still in directory b

*/

class Solution {
public:
    string simplifyPath(string path) {
        stack<string>stk;
        stringstream ss(path);
        string res, tmp;
        while(getline(ss, tmp, '/' )){
            cout<<tmp<<"  ";
            if(tmp == "" || tmp == ".") continue;
            else if(tmp == ".." && !stk.empty()) stk.pop();
            else if(tmp!="..") stk.push(tmp);
        }
        while(!stk.empty()) {
            res = "/"+stk.top()+res; stk.pop(); //cost time
        }
        return res.empty() ? "/" : res;
    }
};



class Solution {
public:
    string simplifyPath(string path) {
        string res, tmp;
        vector<string> stk;
        stringstream ss(path);
        while(getline(ss,tmp,'/')) {
            if (tmp == "" or tmp == ".") continue;
            if (tmp == ".." and !stk.empty()) stk.pop_back();
            else if (tmp != "..") stk.push_back(tmp);
        }
        for(auto str : stk) res += "/"+str;
        return res.empty() ? "/" : res;
    }
};


class Solution {
public:
    string simplifyPath(string path) {
        vector<string> names;
        vector<string> tokens(move(split(path, '/')));
        for (const auto& token : tokens) {
            if (token == ".." && !names.empty()) {
                names.pop_back();
            } else if (token != ".." && token != "." && !token.empty()) {
                names.emplace_back(token);
            }
        }
        return string("/").append(join(names, '/'));
    }

private:
    // Split string by delimitor.
    vector<string> split(const string& s, const char delim) {
        vector<string> tokens;
        stringstream ss(s);
        string token;
        while (getline(ss, token, delim)) {
            tokens.emplace_back(token);
        }
        return tokens;
    }

    // Join strings with delimitor.
    string join(const vector<string>& names, const char delim) {
        ostringstream ss;
        if (!names.empty()) {
            const string delim_str(1, delim);
            copy(names.cbegin(), prev(names.cend()),
                 ostream_iterator<string>(ss, delim_str.c_str()));
            ss << names.back();
        }
        return ss.str();
    }
};