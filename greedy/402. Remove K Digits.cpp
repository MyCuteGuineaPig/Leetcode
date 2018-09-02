/*
402. Remove K Digits
https://leetcode.com/problems/remove-k-digits/description/



*/


/*
The first algorithm is straight-forward. Let's think about the simplest case: 
how to remove 1 digit from the number so that the new number is the smallest possible？
 Well, one can simply scan from left to right, and remove the first "peak" digit; 
 the peak digit is larger than its right neighbor. One can repeat this procedure k times,
  and obtain the first algorithm:


*/

/*
Solution 1: ascending stack, pop时候，如果有富余的值，就pop，没得有话，push——back
*/
class Solution {
public:
    string removeKdigits(string num, int k) {
        string out;
        for(auto c: num){
            while(k>0 && !out.empty() && out.back() > c){
                out.pop_back();
                k--;
            }
            if(out.empty() && c == '0') continue; //如果stack为空，不能往里面push 0
            out.push_back(c);
        }
        while(k && !out.empty()) out.pop_back(), k--;
        if(out.empty()) return "0";
        return out;
    }
};


class Solution {
public:
    string removeKdigits(string num, int k) {
        string ret;
        int keep = num.size()-k; 
        for (auto c : num) {
            while (k && !ret.empty() && ret.back() > c) { //compare if 之前push的跟现在对比是大是小
            //如果大了， 而且k>0(有删除的空间)，就删除之前的
                ret.pop_back();
                --k;
            }
            ret.push_back(c);
        }
        ret.resize(keep);
        while (!ret.empty() && ret[0] == '0') ret.erase(ret.begin());
        return ret.empty()? "0": ret;
    }
};



string removeKdigits(string num, int k) {
        while (k > 0) {
            int n = num.size();
            int i = 0;
            while (i+1<n && num[i]<=num[i+1])  i++;
            num.erase(i, 1);
            k--;
        }
        // trim leading zeros
        int s = 0;
        while (s<(int)num.size()-1 && num[s]=='0')  s++;
        num.erase(0, s);
        
        return num=="" ? "0" : num;
    }




class Solution {
public:
    
    unordered_map<int,int>m;
    string removeKdigits(string num, int k) {
        int n = num.size();
        if(k==0) return num;
        if(n==k) return "0";
        
        int i = 0, start = 0, step = 0;
        string result = "";
        k = n-k;
        while(i<n && k>0){
            while(m.size()< 10 && i<=n-k){
                if(m.count(num[i]-'0') ==0 )
                    m[num[i]-'0'] = i;
                i++;
             }
            int minIndex = findMin(); char minChar = num[minIndex];
            if(minChar!= '0' || result.length()>0 || k==1){
                result += minChar;
            }
            for(int j = start; j<=minIndex;j++){
                if(m.count(num[j]-'0')>0 && m[num[j]-'0'] == j){
                    m.erase(num[j]-'0');
                }
            }
            k--;
            start = minIndex+1;
            i = minIndex+1;
        }
        return result;
    }
    
    int findMin(){
        int minNum = 11, minIndex = -1;
        for(auto itr:m)
            if (minNum> itr.first)
                minNum = itr.first, minIndex = itr.second;
        return minIndex;
    }
};