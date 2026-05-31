class Solution {
public:
    string getHappyString(int n, int k) {

        string cur = "";
        vector<string> holder; 
        auto generate = [&](this auto&& generate, int len) -> void {
            if(len == n) {
                holder.push_back(cur);
                return;
            }
            for(auto c = 'a'; c <= 'c'; ++c) {
                if (cur.length() && cur[cur.size()-1] == c) 
                    continue;
                cur.push_back(c);
                generate(len+1);
                cur.pop_back();
            }
        };

        generate(0);
        if(holder.size() < k) return "";
        return holder[k-1]; 
    }
};



class Solution {
public:
    string getHappyString(int n, int k) {

        string cur = "";
        int index = 0;
        string res = "";
        auto generate = [&](this auto&& generate, int len) -> void {
            if(len == n) {
                if(++index == k) {
                    res = cur;
                }
                return;
            }
            for(auto c = 'a'; c <= 'c'; ++c) {
                if (cur.length() && cur[cur.size()-1] == c) 
                    continue;
                cur.push_back(c);
                generate(len+1);
                cur.pop_back();
            }
        };

        generate(0);
        
        return res; 
    }
};


class Solution {
public:
    string getHappyString(int n, int k) {
        stack<string> stk; stk.push("");
        int index = 0;
        while(!stk.empty()) {
            string cur = stk.top(); stk.pop();
            if(cur.size() == n) {
                if(++index == k) 
                    return cur;
                continue;
            }

            for(auto c = 'c'; c >= 'a'; --c) {
                if(!cur.empty() && cur.back() == c) 
                    continue;
                stk.push(cur + c);
            }
        }
        return "";
    }
};
