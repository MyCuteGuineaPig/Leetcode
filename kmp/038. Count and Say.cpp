/*
38. Count and Say

The count-and-say sequence is the sequence of integers with the first five terms as following:

1.     1
2.     11
3.     21
4.     1211
5.     111221
6.     312211
1 is read off as "one 1" or 11.
11 is read off as "two 1s" or 21.
21 is read off as "one 2, then one 1" or 1211.
Given an integer n, generate the nth term of the count-and-say sequence.

Note: Each term of the sequence of integers will be represented as a string.

Example 1:

Input: 1
Output: "1"
Example 2:

Input: 4
Output: "1211"

*/
class Solution {
public:
    string countAndSay(int n) {
        string res = "1";
        for(int i = 2; i<=n; i++){
            int j = 1, count = 1;
            char cur = res[0];
            string temp;
            while(j<=res.size()){
                if(j==res.size() || res[j] != cur){
                    temp += to_string(count) + cur;
                    count = 1;
                    cur = res[j];
                }
                else 
                    count++;
                j++;
            }
            res = temp;
        }
        return res;
    }
};


// Time:  O(n * 2^n)
// Space: O(2^n)

class Solution {
public:
    string countAndSay(int n) {
        string seq{"1"};
        for (int i = 0; i < n - 1; ++i) {
            seq = getNext(seq);
        }
        return seq;
    }

private:
    string getNext(const string& seq) {
        string next_seq;
        for(auto i = seq.cbegin(); i != seq.cend();) {
            auto j = find_if(i, seq.cend(), bind1st(not_equal_to<char>(), *i));
            next_seq.append(to_string(distance(i, j)));
            next_seq.push_back(*i);
            i = j;
        }
        return next_seq;
    }
};

