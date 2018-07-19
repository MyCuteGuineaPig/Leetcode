
/*
405. Convert a Number to Hexadecimal


Given an integer, write an algorithm to convert it to hexadecimal. For negative integer, two’s complement method is used.

Note:

All letters in hexadecimal (a-f) must be in lowercase.
The hexadecimal string must not contain extra leading 0s. If the number is zero, it is represented by a single zero character '0'; otherwise, the first character in the hexadecimal string will not be the zero character.
The given number is guaranteed to fit within the range of a 32-bit signed integer.
You must not use any method provided by the library which converts/formats the number to hex directly.
Example 1:

Input:
26

Output:
"1a"
Example 2:

Input:
-1

Output:
"ffffffff"

*/

class Solution {
public:
    string toHex(int num) {
        if (!num) {
            return "0";
        }
        string res;
        while(num && res.length()!=sizeof(int)*2){
            int hex = num & 15;
            if (hex < 10) {
                res.push_back('0' + hex);
            } else {
                res.push_back('a' + hex - 10);
            }
            num >>= 4;
        }
        reverse(res.begin(),res.end());
        return res;
    }
};


class Solution {
public:
    string toHex(int num) {
        if (!num) {
            return "0";
        }
        char arr[16] = {'0','1','2','3','4','5','6','7','8','9','a','b','c','d','e','f'};
        string res;
        while(num && res.length()!=sizeof(int)*2){
            if(num % 16<0){
                res.push_back(arr[16+num % 16]);
            }else{
                res.push_back(arr[num%16]);
            }
            num >>= 4;
        }
        reverse(res.begin(),res.end());
        return res;
    }
};


class Solution {
public:
    string toHex(int num) {
        if (!num) {
            return "0";
        }
        char arr[16] = {'0','1','2','3','4','5','6','7','8','9','a','b','c','d','e','f'};
        string res;
        while(num && res.length()!=sizeof(int)*2){
            res.push_back(arr[num &15]);
            num >>= 4;
        }
        reverse(res.begin(),res.end());
        return res;
    }
};


class Solution {
public:
    string toHex(int num) {
        if(num == 0) return "0";
        string hexrep = "0123456789abcdef";
        string res;
        int count = 0;
        while(num && count++ < 8)
        {
            res = hexrep[num & 0xf] + res;
            num >>= 4;
        }
        return res;
    }
};