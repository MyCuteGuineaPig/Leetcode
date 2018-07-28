/*
12. Integer to Roman

Roman numerals are represented by seven different symbols: I, V, X, L, C, D and M.

Symbol       Value
I             1
V             5
X             10
L             50
C             100
D             500
M             1000
For example, two is written as II in Roman numeral, just two one's added together. 
Twelve is written as, XII, which is simply X + II. The number twenty seven is written as XXVII, which is XX + V + II.

Roman numerals are usually written largest to smallest from left to right. However, the numeral for four is not IIII. 
Instead, the number four is written as IV. Because the one is before the five we subtract it making four. 

The same principle applies to the number nine, which is written as IX. There are six instances where subtraction is used:

I can be placed before V (5) and X (10) to make 4 and 9. 
X can be placed before L (50) and C (100) to make 40 and 90. 
C can be placed before D (500) and M (1000) to make 400 and 900.
Given an integer, convert it to a roman numeral. Input is guaranteed to be within the range from 1 to 3999.

Example 1:

Input: 3
Output: "III"
Example 2:

Input: 4
Output: "IV"
Example 3:

Input: 9
Output: "IX"
Example 4:

Input: 58
Output: "LVIII"
Explanation: C = 100, L = 50, XXX = 30 and III = 3.
Example 5:

Input: 1994
Output: "MCMXCIV"
Explanation: M = 1000, CM = 900, XC = 90 and IV = 4.



*/


class Solution {
public:
    string intToRoman(int num) {
        vector<int> divider{1000, 900, 500, 400, 100, 90,  50,  40, 10,  9,  5,   4,   1 };
        vector<string>roman{"M", "CM", "D", "CD","C", "XC","L","XL","X","IX", "V","IV","I"};
        string res;
        for(int i = 0; num; i++){
            int times = num/divider[i];
            while(times-->0){
                res.append(roman[i]);
                num -= divider[i];
            }
        }
        return res;
    }
};


class Solution {
    //Adding dummies at the start for easy indexing
    //1000 - 3000
    vector<string> M = {"", "M", "MM", "MMM"};
    //100 - 900
    vector<string> C = {"", "C", "CC", "CCC", "CD", "D", "DC", "DCC", "DCCC", "CM"};
    //10 - 90
    vector<string> X = {"", "X", "XX", "XXX", "XL", "L", "LX", "LXX", "LXXX", "XC"};
    //1 - 9
    vector<string> I = {"", "I", "II", "III", "IV", "V", "VI", "VII", "VIII", "IX"};
public:
    string intToRoman(int num) {
        return M[num/1000] + C[(num%1000)/100] + X[(num%100)/10] + I[num%10];
        // return M[num/1000] + C[(num/100)%10] + X[(num/10)%10] + I[num%10];
    }
};


class Solution {
public:
    string intToRoman(int num) {
        string lookup = "IVXLCDM";
        string res;
        for(int i = 0; num; i+=2, num/=10){
            int div = num%10;
            if(div<=3)
                res = string(div, lookup[i])+res;
            else if(div == 4)
                res = lookup.substr(i,1)+lookup.substr(i+1,1)+res;
            else if(div == 5)
                res = lookup.substr(i+1, 1)+res;
            else if(div <=8 )
                res =  lookup.substr(i+1,1)+string(div-5, lookup[i])+res;
            else 
                res = lookup.substr(i,1)+lookup.substr(i+2,1)+res;
        }
        return res;
    }
};