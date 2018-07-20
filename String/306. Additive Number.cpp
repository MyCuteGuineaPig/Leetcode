/*
306. Additive Number

Additive number is a string whose digits can form additive sequence.

A valid additive sequence should contain at least three numbers. Except for the first two numbers, 
each subsequent number in the sequence must be the sum of the preceding two.

Given a string containing only digits '0'-'9', write a function to determine if it's an additive number.

Note: Numbers in the additive sequence cannot have leading zeros, so sequence 1, 2, 03 or 1, 02, 3 is invalid.

Example 1:

Input: "112358"
Output: true 
Explanation: The digits can form an additive sequence: 1, 1, 2, 3, 5, 8. 
             1 + 1 = 2, 1 + 2 = 3, 2 + 3 = 5, 3 + 5 = 8
Example 2:

Input: "199100199"
Output: true 
Explanation: The additive sequence is: 1, 99, 100, 199. 
             1 + 99 = 100, 99 + 100 = 199
Follow up:
How would you handle overflow for very large input integers?

*/

class Solution {
public:
    bool isAdditiveNumber(string num) {
        for(int i = 1; i<=num.size()/2;i++){
            for(int j = 1; j<=(num.size() - i)/2;j++){
                if(isValid(num, i, j, 0)) return true;
            }
        }
        return false;
    }

    bool isValid(const string&num, int i, int j, int start){
        if(i>1 && num[start] == '0') return false;
        if(j>1 && num[start+i] == '0') return false;
        string sumup = addTwonumber(num.substr(start, i), num.substr(start+i,j));
        
        int m = start + i + j;
        if(num.substr(m,sumup.size())!=sumup) return false;

        if(m+sumup.size() == num.size()) return true;
        return isValid(num, j, sumup.size() , start + i );
    }

    string addTwonumber(string a, string b){
        //cout<<" two num "<<a<<" b "<<b<<endl;
        string res;
        int i = a.size()-1, j = b.size() - 1, carry = 0;
        while( i>=0 || j>=0 || carry > 0) {
            if(i>=0) carry += a[i] - '0';
            if(j>=0) carry += b[j] - '0';
            res += to_string(carry%10);
            carry /= 10;
            i--; j--;
        }
        reverse(res.begin(),res.end());
        return res;
    }
};


class Solution {
public:
        bool isAdditiveNumber(string num) {
            for(int i=1; i<=num.size()/2; i++){
                for(int j=1; j<=(num.size()-i)/2; j++){
                    if(check(num.substr(0,i), num.substr(i,j), num.substr(i+j))) return true;
                }
            }
            return false;
        }
        bool check(string num1, string num2, string num){
            if(num1.size()>1 && num1[0]=='0' || num2.size()>1 && num2[0]=='0') return false;
            string sum=add(num1, num2);
            if(num==sum) return true;
            if(num.size()<=sum.size() || sum.compare(num.substr(0,sum.size()))!=0) return false;
            else return check(num2, sum, num.substr(sum.size()));
        } 
        string add(string n, string m){
            string res;
            int i=n.size()-1, j=m.size()-1, carry=0;
            while(i>=0 || j>=0){
                int sum=carry+(i>=0 ? (n[i--]-'0') : 0) + (j>=0?  (m[j--]-'0') : 0);
                res.push_back(sum%10+'0');
                carry=sum/10;
            }
            if(carry) res.push_back(carry+'0');
            reverse(res.begin(), res.end());
            return res;
        }
    };