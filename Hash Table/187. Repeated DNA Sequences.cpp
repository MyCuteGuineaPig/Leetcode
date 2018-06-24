/*
187. Repeated DNA Sequences

All DNA is composed of a series of nucleotides abbreviated as A, C, G, and T, for example: "ACGAATTCCG". When studying DNA, it is sometimes useful to identify repeated sequences within the DNA.

Write a function to find all the 10-letter-long sequences (substrings) that occur more than once in a DNA molecule.

Example:

Input: s = "AAAAACCCCCAAAAACCCCCCAAAAAGGGTTT"

Output: ["AAAAACCCCC", "CCCCCAAAAA"]
*/




/*
不是hash，因为如果是hash结果一样，不能表示完全吻合，
又不能存储substring，因为会超过memory limit

因为只有ACGT四个字母，所以可以用bit operation代表string：
’A' = 0, 'C' = 1, 'G' = 2, 'T' = 3



The key point is that it is not doing hash, it is doing the exact coding of a 10-letter sequence into a 4-bytes number,
which is simply not possible for any generic string, but is possible for strings in this problem because they can have only 4 differfent characters.

In more detail:

If two objects have same hash it means that they may or may not be equal (though two equal objects are required to have same hash). 
So hashing is not enough here (like calling just "AACCCCCGGG".hashCode() and storing it in the map), 
because there can be another (different) string with same hash and the program will output wrong result.

We also cannot store the 10-letter substrings themselves because they consume too much memory and the program will exceed memory limit.

So, instead of hashing or storing strings themselves the solution converts 10 letter string into 4-bytes integer 
(which is much smaller than string in terms of consumed memory). 
This would not be possible if the string could contain all 26 letters of English alphabet for example. 
But it is possible for our case, because there can be only 'A', 'C', 'G' and 'T' letters.

So we have only 4 possible letters, and we can use as little bits as possible to store each character of our 10-letter string. 
We really need only 2 bits (bits, not bytes) for this. Specifically the solution uses the following coding:

0 = 00 (bits in binary number system) = 'A'

1 = 01 (bits in binary number system) = 'C'

2 = 10 (bits in binary number system) = 'G'

3 = 11 (bits in binary number system) = 'T'

Note that since there 10 letters and each letter requires only 2 bits, we will need only 10 * 2= 20 bits to code the string (which is less then size of integer in java (as well as in all othere popular languages), which is 4 bytes = 32 bits).

For example, this is how "AACCTCCGGT" string will be coded:

A A C C T C C G G T

00 00 01 01 11 01 01 10 10 11 = 00000101110101101011 (binary) = 23915 (decimal)
*/


class Solution {
public:
    vector<string> findRepeatedDnaSequences(string s) {
        if(s.size()<10) return {};
        unordered_set<int>set;
        unordered_set<int>res_count;
        unordered_map<char,int>map = {{'A',0}, {'C',1}, {'G',2}, {'T',3}};
        vector<string>res;
        for(int i = 0; i<=s.size()-10;i++){
            int num = 0;
            for(int j = 0; j<10; j++){
                num <<= 2;
                num |= map[s[i+j]];
            }
            if(set.count(num) && !res_count.count(num)) {
                res.push_back(s.substr(i,10));
                res_count.insert(num);
            }
            else set.insert(num);
        }
        return res;
    }
};


//理论上，比上面的快10倍， 因为省去了重新计算的时间
class Solution {
public:
    vector<string> findRepeatedDnaSequences(string s) {
        if(s.size()<10) return {};
        unordered_set<int>set;
        unordered_set<int>res_count;
        unordered_map<char,int>map = {{'A',0}, {'C',1}, {'G',2}, {'T',3}};
        vector<string>res;
        int num = 0;
        int constant = pow(2,18)-1; //保留前18位bit //& 0xfffff
        for(int i = 0; i<s.size();i++){
            num <<= 2;
            num |= map[s[i]];
            if(i>=9){
                if(set.count(num) && !res_count.count(num)) {
                    res.push_back(s.substr(i-9,10));
                    res_count.insert(num);
                }
                else set.insert(num);
                num &= constant;
            }
        }
        return res;
    }
};


/*

bin(ord('A') & 7)  = 001 
Out[4]: '0b1'

bin(ord('C') & 7) = 011
Out[5]: '0b11'

bin(ord('G') & 7) = 111
Out[6]: '0b111'

bin(ord('T') & 7) = 100
Out[7]: '0b100'

7的bit 是 111，决定后三位， 每一个数用三个bit位表示
因为A is 0101, C is 0103, G is 0107, T is 0124


There are only four possible character A, C, G, and T, but I want to use 3 bits per letter instead of 2.

Why? It's easier to code.

A is 0x41, C is 0x43, G is 0x47, T is 0x54. Still don't see it? Let me write it in octal.

A is 0101, C is 0103, G is 0107, T is 0124. The last digit in octal are different for all four letters. That's all we need!

We can simply use s[i] & 7 to get the last digit which are just the last 3 bits, 
it's much easier than lookup table or switch or a bunch of if and else, right?

We don't really need to generate the substring from the int. While counting the number of occurrences, 
we can push the substring into result as soon as the count becomes 2, so there won't be any duplicates in the result.
*/
class Solution {
public:
    vector<string> findRepeatedDnaSequences(string s) {
        unordered_map<int, int> m;
        vector<string> r;
        int t = 0, i = 0, ss = s.size();
        while (i < 9)
            t = t << 3 | s[i++] & 7;
        while (i < ss)
            if (m[t = t << 3 & 0x3FFFFFFF | s[i++] & 7]++ == 1)
                r.push_back(s.substr(i - 10, 10));
        return r;
    }
};


class Solution {
public:
    vector<string> findRepeatedDnaSequences(string s) {
        unordered_map<int, bool> m;
        vector<string> r;
        for (int t = 0, i = 0; i < s.size(); i++) {
            t = t << 3 & 0x3FFFFFFF | s[i] & 7;
            if (m.find(t) != m.end()) {
                if (m[t]) {
                    r.push_back(s.substr(i - 9, 10));
                    m[t] = false;
                }
            } else {
                m[t] = true;
            }
        }
        return r;
    }
};