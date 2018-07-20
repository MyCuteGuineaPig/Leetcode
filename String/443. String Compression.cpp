/*
443. String Compression

Given an array of characters, compress it in-place.

The length after compression must always be smaller than or equal to the original array.

Every element of the array should be a character (not int) of length 1.

After you are done modifying the input array in-place, return the new length of the array.


Follow up:
Could you solve it using only O(1) extra space?


Example 1:
Input:
["a","a","b","b","c","c","c"]

Output:
Return 6, and the first 6 characters of the input array should be: ["a","2","b","2","c","3"]

Explanation:
"aa" is replaced by "a2". "bb" is replaced by "b2". "ccc" is replaced by "c3".
Example 2:
Input:
["a"]

Output:
Return 1, and the first 1 characters of the input array should be: ["a"]

Explanation:
Nothing is replaced.
Example 3:
Input:
["a","b","b","b","b","b","b","b","b","b","b","b","b"]

Output:
Return 4, and the first 4 characters of the input array should be: ["a","b","1","2"].

Explanation:
Since the character "a" does not repeat, it is not compressed. "bbbbbbbbbbbb" is replaced by "b12".
Notice each digit has it's own entry in the array.
Note:
All characters have an ASCII value in [35, 126].
1 <= len(chars) <= 1000.

*/


class Solution {
public:
    int compress(vector<char>& chars) {
        if(chars.empty()) return 0;
        int start = 0, j = 1;
        for(int i = 1; i<=chars.size() ; i++){
            if(i == chars.size() || chars[i]!=chars[start]){
                int count = i - start; //记录多少个
                if(count > 1){
                    int cnt = 0;
                    while(count){
                        chars[j++] = count % 10 + '0';
                        count /= 10;
                        cnt ++;
                    }
                    reverse(chars.begin()+j-cnt, chars.begin()+j); //因为先push 个位，然后十位... 所以最后顺序要反过来
                }
                if(i< chars.size()) chars[j++] = chars[i];
                start = i;
            }
        }   
        return j;
    }
};



class Solution {
public:
    int compress(vector<char>& chars) {
        if(chars.empty()) return 0;
        int j = 0;
        for(int i = 0; i<chars.size(); ){
            int start = i;
            while(i<chars.size() && chars[start] == chars[i]) i++;
            int count = i - start;
            chars[j++] = chars[start];
            if(count > 1){
                int cnt = 0;
                while(count){
                    chars[j++] = count % 10 + '0';
                    count /= 10;
                    cnt ++;
                }
                reverse(chars.begin()+j-cnt, chars.begin()+j); //因为先push 个位，然后十位... 所以最后顺序要反过来
            }
        }   
        return j;
    }
};




class Solution {
public:
    int compress(vector<char>& chars) {
        int write = 0, anchor = 0;
        for (int read = 0; read < chars.size(); ++read) {
            if (read + 1 == chars.size() || chars[read + 1] != chars[read]) {
                chars[write++] = chars[read];
                if (read - anchor > 0) {
                    auto n = read - anchor + 1, cnt = 0;
                    while (n > 0) {
                        chars[write++] = n % 10 + '0';
                        n /= 10;
                        ++cnt;
                    }
                    reverse(chars.begin() + write - cnt, chars.begin() + write);
                }
                anchor = read + 1;
            }
        }
        return write;
    }
};