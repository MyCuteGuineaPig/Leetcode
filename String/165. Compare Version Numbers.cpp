/*
165. Compare Version Numbers

Compare two version numbers version1 and version2.
If version1 > version2 return 1; if version1 < version2 return -1;otherwise return 0.

You may assume that the version strings are non-empty and contain only digits and the . character.
The . character does not represent a decimal point and is used to separate number sequences.
For instance, 2.5 is not "two and a half" or "half way to version three", 
it is the fifth second-level revision of the second first-level revision.

Example 1:

Input: version1 = "0.1", version2 = "1.1"
Output: -1
Example 2:

Input: version1 = "1.0.1", version2 = "1"
Output: 1
Example 3:

Input: version1 = "7.5.2.4", version2 = "7.5.3"
Output: -1

*/

class Solution {
public:
    int compareVersion(string version1, string version2) {
        int i = 0, j = 0, n1 = version1.size(), n2 = version2.size();
        while(i< n1 || j<n2){
            int c1 = 0, c2 = 0;
            while(i<n1 && version1[i]!='.')
                c1 = c1*10 + version1[i++] - '0';
            while(j<n2 && version2[j]!='.')
                c2 = c2*10 + version2[j++] - '0';
            if(c1 != c2)
                return c1 > c2 ? 1 : -1;
            i++; j++;
        }
        
        return 0;
    }
};



class Solution {
public:
    int compareVersion(string version1, string version2) {
        const int n1 = version1.length(), n2 = version2.length();
        for (int i = 0, j = 0; i < n1 || j < n2; ++i, ++j) {
            int v1 = 0, v2 = 0;
            while (i < n1 && version1[i] != '.') {
                v1 = v1 * 10 + version1[i++] - '0';
            }
            while (j < n2 && version2[j] != '.') {
                v2 = v2 * 10 + version2[j++] - '0';
            }
            if (v1 != v2) {
                return v1 > v2 ? 1 : -1;
            }
        }
        return 0;
    }
};


class Solution {
public:
    int compareVersion(string version1, string version2) {
        for(auto& w : version1) if (w == '.') w=' ';
        for(auto& w : version2) if (w == '.') w=' ';
        istringstream s1(version1), s2(version2);
        while(1) {
            int n1,n2;
            if (not(s1 >> n1) ) n1 = 0;
            if (not(s2 >> n2) ) n2 = 0;
            if (not s1 and not s2) return 0;
            if (n1<n2) return -1;
            if (n1>n2) return 1;
        }
    }
};


/*
long int strtol (const char* str, char** endptr, int base);

strtol
The function first discards as many whitespace characters as necessary until the first non-whitespace character is found.
 Then, starting from this character, takes as many characters as possible that are valid following a syntax 
 that depends on the base parameter, and interprets them as a numerical value. 
 Finally, a pointer to the first character following the integer representation in str is stored in the object pointed by endptr.
先跳过whie space的尽可能多的转化，一个pointer指向 当前valid的整数的下一位被存在endptr中。
在此题中 '.'被存到endptr中

*/
class Solution {
public:
    int compareVersion(string version1, string version2) {
        int result = 0;
        char *vStr1 = (char*) version1.c_str();
        char *vStr2 = (char*) version2.c_str();

        while (result == 0 && (*vStr1 != '\0' || *vStr2 != '\0')) {
            long v1 = *vStr1 == '\0' ? 0 : strtol(vStr1, &vStr1, 10);
            long v2 = *vStr2 == '\0' ? 0 : strtol(vStr2, &vStr2, 10);
            if (v1 > v2) result = 1;
            else if (v2 > v1) result = -1;
            else {
                if (*vStr1 != '\0') vStr1++;
                if (*vStr2 != '\0') vStr2++;
            }
        }        

        return result;
    }
};

class Solution {
public:
    int compareVersion(string version1, string version2) {
        vector<int> v1 = split(version1);
        vector<int> v2 = split(version2);
        int n = v1.size()<v2.size()? v1.size():v2.size();
        for(int i=0;i<n;i++){
            if(v1[i]<v2[i])
                return -1;
            if(v1[i]>v2[i])
                return 1;
        }
        for(int i=n;i<v1.size();i++){
            if(v1[i]>0)
                return 1;
        }
        for(int i=n;i<v2.size();i++){
            if(v2[i]>0)
                return -1;
        }
        return 0;
    }
    vector<int> split(string s){
        vector<int> res;
        for(int i=0;i<s.size();){
            int j=i;
            while(s[j]!='.' && j<s.size())
                j++;
            string temp=s.substr(i, j-i);
            res.push_back(stoi(temp));
            i=j+1;
        }
        return res;
    }
};