/*
43. Multiply Strings

Given two non-negative integers num1 and num2 represented as strings, 
return the product of num1 and num2, also represented as a string.

Example 1:

Input: num1 = "2", num2 = "3"
Output: "6"
Example 2:

Input: num1 = "123", num2 = "456"
Output: "56088"
Note:

The length of both num1 and num2 is < 110.
Both num1 and num2 contain only digits 0-9.
Both num1 and num2 do not contain any leading zero, except the number 0 itself.
You must not use any built-in BigInteger library or convert the inputs to integer directly.


*/

//back_inserter, 相当于按照原来从头到尾顺序push back
class Solution {
public:
    string multiply(string num1, string num2) {
        vector<int>vec(num1.size()+num2.size());
        for(int i = num1.size()-1; i>=0; i--){ //从最后一位开始算，因为最后一位是个位数，如果从第0位(最大位数)开始算，可能有一位算上carry的超过10，比如“"123", "456"
            for(int j = num2.size()-1; j>=0; j--){
                int a = num1[i] - '0';
                int b = num2[j] - '0';
                vec[i+j+1] += a*b;
                vec[i+j] += vec[i+j+1]/10;
                vec[i+j+1] %= 10;
            }
        }
        string res; 
        auto int_to_char = [](const int& i){return i+'0';};
        transform(find_if(vec.begin(), prev(vec.end()),[](const int& i){return i!=0; }),
            vec.end(), back_inserter(res), int_to_char);
        return res;
    }
};

class Solution {
public:
    string multiply(string num1, string num2) {
        if(num1 == "0" || num2 == "0")  return "0";
        string res(num1.size()+num2.size(), '0');
        for(int i = num1.size()-1; i>=0; i--){
            int carry = 0;
            for(int j = num2.size()-1; j>=0; j--){
                int temp = (res[i+j+1] - '0') + (num1[i] - '0')*(num2[j]-'0') + carry;
                res[i+j+1] = temp % 10 + '0';
                carry = temp / 10;
            }
            res[i] += carry;
        }
        size_t begin = res.find_first_not_of('0');
        return res.substr(begin);
    }
};

// Time:  O(m * n)
// Space: O(m + n)

class Solution {
public:
    string multiply(string num1, string num2) {
        const auto char_to_int = [](const char c) { return c - '0'; };
        const auto int_to_char = [](const int i) { return i + '0'; };

        vector<int> n1;
        transform(num1.rbegin(), num1.rend(), back_inserter(n1), char_to_int); //把顺序颠倒
        vector<int> n2;
        transform(num2.rbegin(), num2.rend(), back_inserter(n2), char_to_int);

        vector<int> tmp(n1.size() + n2.size());
        for(int i = 0; i < n1.size(); ++i) {
            for(int j = 0; j < n2.size(); ++j) {
                tmp[i + j] += n1[i] * n2[j];
                tmp[i + j + 1] += tmp[i + j] / 10;
                tmp[i + j] %= 10;
            }
        }
            
        string res;
        transform(find_if(tmp.rbegin(), prev(tmp.rend()),//把顺序恢复
                         [](const int i) { return i != 0; }),
                  tmp.rend(), back_inserter(res), int_to_char);
        return res;
    }
};




// Time:  O(m * n)
// Space: O(m + n)
// Define a new BigInt class solution. 
class Solution2 {
public:
    string multiply(string num1, string num2) {
        return BigInt(num1) * BigInt(num2);
    }

    class BigInt {
    public:
        BigInt(const string& s) {
            transform(s.rbegin(), s.rend(), back_inserter(n_), 
                      [](const char c) { return c - '0'; });
        }
    
        operator string() {
            string s;
            transform(find_if(n_.rbegin(), prev(n_.rend()),
                             [](const int i) { return i != 0; }),
                      n_.rend(), back_inserter(s), 
                      [](const int i) { return i + '0'; });
            return s;
        }
    
        BigInt operator*(const BigInt &rhs) const {
            BigInt res(n_.size() + rhs.size(), 0);
            for(auto i = 0; i < n_.size(); ++i) {
                for(auto j = 0; j < rhs.size(); ++j) {
                    res[i + j] += n_[i] * rhs[j];
                    res[i + j + 1] += res[i + j] / 10;
                    res[i + j] %= 10;
                }
            }
            return res;
        }
    
    private:
        vector<int> n_;
    
        BigInt(int num, int val): n_(num, val) {
        }
    
        // Getter.
        int operator[] (int i) const {
            return n_[i];
        }
    
        // Setter.
        int & operator[] (int i) {
            return n_[i];
        }
    
        size_t size() const {
            return n_.size();
        }
    };
};