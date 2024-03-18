class Solution {
public:
    vector<string> reorderLogFiles(vector<string>& logs) {
        vector<string>letters;
        vector<string>digits;
        for(int i = 0; i<logs.size(); ++i){
            string key1 = logs[i].substr(0, logs[i].find(' '));
            string c1 = logs[i].substr(logs[i].find(' ')+1); 
            if(isalpha(c1[0]))
                letters.push_back(logs[i]);
            else 
                digits.push_back(logs[i]);
        }


        sort(letters.begin(), letters.end(), [](const string& a, const string& b){
            string key1 = a.substr(0, a.find(' '));
            string key2 = b.substr(0, b.find(' '));
            string c1 = a.substr(a.find(' ')+1); 
            string c2 = b.substr(b.find(' ')+1); 

            if (c1 != c2)
                return c1 < c2;
            return key1 < key2;
        });
        letters.reserve(letters.size() + distance(digits.begin(), digits.end()));
        letters.insert(letters.end(), digits.begin(), digits.end());
        return letters;
    }
};

class Solution {
public:
    vector<string> reorderLogFiles(vector<string>& logs) {
        vector<string> res, digitLogs;
        vector<vector<string>> data;
        for (string log : logs) {
            auto pos = log.find(" ");
            if (log[pos + 1] >= '0' && log[pos + 1] <= '9') {
                digitLogs.push_back(log);
                continue;
            }
            data.push_back({log.substr(0, pos), log.substr(pos + 1)});
        }
        sort(data.begin(), data.end(), [](vector<string>& a, vector<string>& b) {
            return a[1] < b[1] || (a[1] == b[1] && a[0] < b[0]);
        });
        for (auto &a : data) {
            res.push_back(a[0] + " " + a[1]);
        }
        for (string log : digitLogs) res.push_back(log);
        return res;
    }
};


class Solution {
public:
    vector<string> reorderLogFiles(vector<string>& logs) {

        auto it = stable_partition(logs.begin(), logs.end(), [](const string& str)-> bool{
            return isalpha(str.back());
        });

        sort(logs.begin(),it,[](const string& a, const string& b) -> bool{
            string_view a_v(a.c_str(),a.size());
            string_view b_v(b.c_str(),b.size());
            auto substr1=a_v.substr(a_v.find(' '),a_v.size());
            auto substr2=b_v.substr(b_v.find(' '),b_v.size());
            return (substr1 == substr2) ? a<b : substr1 < substr2;
        });
        return logs;
    }
};


class Solution {
public:
    static bool compare(string &a, string &b){
        string s1=string( a.begin()+ a.find(' '), a.end());
        string s2=string(b.begin()+ b.find(' '), b.end());
        return (s1==s2) ? a<b : s1<s2;
    }
    vector<string> reorderLogFiles(vector<string>& logs) {
        int count=0;
        int dig_insert=logs.size()-1;

        for(int i=logs.size()-1;i>=0;i--){
            int pos=logs[i].find(' ');
            if(isdigit(logs[i][pos+1])){
                swap(logs[dig_insert], logs[i]);
                dig_insert--;
            }
            else 
            count++;
        }
        sort(logs.begin(), logs.begin()+count, compare);
        return logs;
    }
};