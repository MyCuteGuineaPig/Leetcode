/*
8. String to Integer (atoi)

Implement atoi which converts a string to an integer.

The function first discards as many whitespace characters as necessary until the first non-whitespace character is found. 
Then, starting from this character, takes an optional initial plus or minus sign followed by as many numerical digits as possible, 
and interprets them as a numerical value.

The string can contain additional characters after those that form the integral number, 
which are ignored and have no effect on the behavior of this function.

If the first sequence of non-whitespace characters in str is not a valid integral number, 
or if no such sequence exists because either str is empty or it contains only whitespace characters, no conversion is performed.

If no valid conversion could be performed, a zero value is returned.

Note:

Only the space character ' ' is considered as whitespace character.
Assume we are dealing with an environment which could only store integers within the 32-bit signed integer range: 
[−231,  231 − 1]. If the numerical value is out of the range of representable values, INT_MAX (231 − 1) or INT_MIN (−231) is returned.
Example 1:

Input: "42"
Output: 42
Example 2:

Input: "   -42"
Output: -42
Explanation: The first non-whitespace character is '-', which is the minus sign.
             Then take as many numerical digits as possible, which gets 42.
Example 3:

Input: "4193 with words"
Output: 4193
Explanation: Conversion stops at digit '3' as the next character is not a numerical digit.
Example 4:

Input: "words and 987"
Output: 0
Explanation: The first non-whitespace character is 'w', which is not a numerical 
             digit or a +/- sign. Therefore no valid conversion could be performed.
Example 5:

Input: "-91283472332"
Output: -2147483648
Explanation: The number "-91283472332" is out of the range of a 32-bit signed integer.
             Thefore INT_MIN (−231) is returned.

*/

class Solution {
public:
    int myAtoi(string str) {
        int i = 0;
        while(i<str.size() && str[i]==' ') i++;
        if(i>=str.size() || str[i]!='-' && str[i]!='+' && !isdigit(str[i])) return 0;
        int sign = 1;
        if(!isdigit(str[i]))
            sign = str[i++] == '-' ? -1 : 1;
        long cur = 0;
        while(i<str.size() && cur<numeric_limits<int>::max() && isdigit(str[i]))
            cur = cur*10 + str[i++]-'0' ;
        if (cur > numeric_limits<int>::max())
            return sign == 1 ? numeric_limits<int>::max() : numeric_limits<int>::min();
        else 
            return cur*sign;
    }
};


static int hello=[](){
    std::ios::sync_with_stdio(false);
    cin.tie(NULL);
    return 0;
}();
class Solution {
public:
    int myAtoi(string str) {
        int temp = 0;
        stringstream stream(str);
        stream>>temp;
        return temp;
    }
};



class Solution {
public:
	inline bool isdigit(char c)
	{
		return c >= '0'&c <= '9';
	}

	int myAtoi(string str) {
		if (str.size() == 0)return 0;
		int i = 0, res = 0;
		bool minus = false;
		while (str[i] == ' ')i++;
		if (str[i] == '-'){
			minus = true;
			++i;
		}
		else if (str[i] == '+')++i;
		else if (!isdigit(str[i]))return 0;

		while (isdigit(str[i])){
            int tmp=res*10+str[i] - '0';
			if (tmp/10!=res)return minus ? INT_MIN : INT_MAX;
            res=tmp;
			++i;
		}
		return minus ? -res : res;
	}
};

class Solution {
public:
    int myAtoi(string str) {
        long result = 0;
        int indicator = 1;
        for(int i = 0; i<str.size();)
        {
            i = str.find_first_not_of(' ');
            if(str[i] == '-' || str[i] == '+')
                indicator = (str[i++] == '-')? -1 : 1;
            while('0'<= str[i] && str[i] <= '9') 
            {
                result = result*10 + (str[i++]-'0');
                if(result*indicator >= INT_MAX) return INT_MAX;
                if(result*indicator <= INT_MIN) return INT_MIN;                
            }
            return result*indicator;
        }
    }
};