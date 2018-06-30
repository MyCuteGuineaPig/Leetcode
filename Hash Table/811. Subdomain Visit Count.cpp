/*
811. Subdomain Visit Count


A website domain like "discuss.leetcode.com" consists of various subdomains. At the top level, we have "com", 
at the next level, we have "leetcode.com", and at the lowest level, "discuss.leetcode.com". 
When we visit a domain like "discuss.leetcode.com", we will also visit the parent domains "leetcode.com" and "com" implicitly.

Now, call a "count-paired domain" to be a count (representing the number of visits this domain received), 
followed by a space, followed by the address. An example of a count-paired domain might be "9001 discuss.leetcode.com".

We are given a list cpdomains of count-paired domains. We would like a list of count-paired domains, 
(in the same format as the input, and in any order), that explicitly counts the number of visits to each subdomain.

Example 1:
Input: 
["9001 discuss.leetcode.com"]
Output: 
["9001 discuss.leetcode.com", "9001 leetcode.com", "9001 com"]
Explanation: 
We only have one website domain: "discuss.leetcode.com". As discussed above, 
the subdomain "leetcode.com" and "com" will also be visited. So they will all be visited 9001 times.

Example 2:
Input: 
["900 google.mail.com", "50 yahoo.com", "1 intel.mail.com", "5 wiki.org"]
Output: 
["901 mail.com","50 yahoo.com","900 google.mail.com","5 wiki.org","5 org","1 intel.mail.com","951 com"]
Explanation: 
We will visit "google.mail.com" 900 times, "yahoo.com" 50 times, "intel.mail.com" once and "wiki.org" 5 times. 
For the subdomains, we will visit "mail.com" 900 + 1 = 901 times, "com" 900 + 50 + 1 = 951 times, and "org" 5 times.

Notes:

The length of cpdomains will not exceed 100. 
The length of each domain name will not exceed 100.
Each address will have either 1 or 2 "." characters.
The input count in any count-paired domain will not exceed 10000.
The answer output can be returned in any order.


*/


class Solution {
public:
    vector<string> subdomainVisits(vector<string>& cpdomains) {
        unordered_map<string, int>count;
        string temp;
        for(auto s: cpdomains){
            size_t pos = s.find(' ');
            int times = stoi(s.substr(0,pos));
            while(pos!=string::npos){
                count[s.substr(pos+1)] += times;
                pos = s.find('.', pos+1);
            }
        }
        vector<string>res;
        for(auto it: count){
            res.push_back(to_string(it.second)+" "+it.first);
        }
        return res;
    }
};


class Solution {
public:
    vector<string> subdomainVisits(vector<string>& cpdomains) 
    {    
        unordered_map<string, int> m; 

        for (const auto& word : cpdomains) 
        {
            int i    = word.find (" "); 
            int n    = stoi (word.substr (0, i)); 
            string s = word.substr (i+1, word.size ()-i-1);

            for (int i = s.size ()-1; i >= 0; i--) {
                if (s[i] == '.') m[s.substr (i+1, s.size ()-i-1)] += n; 
                else if (i == 0) m[s.substr (i,   s.size ()-i)  ] += n;
            }
        }

        vector<string> v;
        for (const auto& e : m) v.push_back (to_string (e.second) + " " + e.first);
        return v;
    }
};


class Solution {
public:
    vector<string> subdomainVisits(vector<string>& cpdomains) {
        unordered_map<string, int> c;
        for (auto cd : cpdomains) {
            int i = cd.find(" ");
            int n = stoi(cd.substr (0, i));
            string s = cd.substr (i + 1, cd.size () - i - 1);
            for (int i = 0; i < s.size(); ++i) if (s[i] == '.') c[s.substr(i + 1, s.size () - i)] += n;
            c[s] += n;
        }
        vector<string> res;
        for (auto k : c) res.push_back (to_string(k.second) + " " + k.first);
        return res;
    }
};