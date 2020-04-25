class Solution {
public:
    string reformat(string s) {
        string str, digit;
        for(auto i: s){
            if(isalpha(i))
                str.push_back(i);
            else if(isdigit(i))
                digit.push_back(i);
        }
        if( abs(static_cast<int>(str.size() - digit.size())) > 1 )
            return "";
        if(str.size() < digit.size())
        {
            swap(str, digit);
        }
        string res;
        for(int i = 0; i< str.size(); ++i){
            res += str[i];
            if(i < digit.size())
                res += digit[i];
        }
        return res;
    }
};

class Solution {
public:
    string reformat(string s) {
        string a="",d="";
        // split string into alpha string and digit strings
        for(auto x:s)
            isalpha(x)?a.push_back(x):d.push_back(x);
  
        // if difference is more than 1, return "" since not possible to reformat
        if(abs(int(a.size()-d.size()))>1)
            return "";
        // merge the strings accordingly, starting with longer string
        bool alpha=a.size()>d.size();
        int i=0,j=0,k=0;
            while(i<s.size()){
                if(alpha){
                    s[i++]=a[j++];
                }
                else{
                    s[i++]=d[k++];
                }
                alpha=!alpha;
            }
        return s;
    }
};


class Solution {
public:
    string reformat(string s) {
        int lCount = 0, dCount = 0;
        for (char i : s) {
            if ('a' <= i && i <= 'z')
                lCount++;
            else
                dCount++;
        }
        
        if (abs(lCount - dCount) > 1)
            return "";
        
        int lPos = 0, dPos = 1;
        if (lCount < dCount) {
            swap(lPos, dPos);
        }
        for (lPos; lPos < s.size(); lPos += 2) {
            while (dPos + 1 < s.size() && !('a' <= s[dPos] && s[dPos] <= 'z')) {
                dPos += 2; //如果是数字就跳
            }
            if (!('a' <= s[lPos] && s[lPos] <= 'z')) { //如果lPos 是数字，跟dPos 是字母的换
                swap(s[lPos], s[dPos]);
            }   
        }
        return s;
    }
};


class Solution {
public:
    string reformat(string s) {
        int c1(0), c2(0);
        unordered_map<char, int> cnts;
        
        for (const char& c: s) {
            isalpha(c) ? c1++ : c2++;
            cnts[c]++;
        }
        
        if (abs(c1 - c2) > 1) return "";
        
        string ans;
        for (int i = 0; i < s.length(); ++i) {
		    // if c1 >= c2, "letter-number-letter..."
			// otherwise, "number-letter-number..."
            string t = (i % 2) ^ (c1 >= c2) ? "az" : "09";
            for (char c = t[0]; c <= t[1]; ++c) {
                if (cnts[c]) {
                    cnts[c]--;
                    ans += c;
                    break;
                }
            }
        }
        
        return ans;
    }
};



class Solution {
public:
    string reformat(string s) {
        int c1(0), c2(0), i(0), j(0);
        
        for (const char& c: s)
            isalpha(c) ? c1++ : c2++;
        
        if (abs(c1 - c2) > 1) return "";
        
        string ans;
        
        while (ans.length() < s.length())
            if ((ans.length() % 2) ^ (c1 > c2)) {
                while (isdigit(s[i])) i++;
                ans += s[i++];
            } else {
                while (isalpha(s[j])) j++;
                ans += s[j++];
            }
        
        return ans;
    }
};