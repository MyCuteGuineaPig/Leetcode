/*
299. Bulls and Cows


ou are playing the following Bulls and Cows game with your friend: You write down a number and 
ask your friend to guess what the number is. Each time your friend makes a guess, 
you provide a hint that indicates how many digits in said guess match your secret number exactly in both digit and position (called "bulls") 
and how many digits match the secret number but locate in the wrong position (called "cows"). 
Your friend will use successive guesses and hints to eventually derive the secret number.

Write a function to return a hint according to the secret number and friend's guess, 
use A to indicate the bulls and B to indicate the cows. 

Please note that both secret number and friend's guess may contain duplicate digits.

Example 1:

Input: secret = "1807", guess = "7810"

Output: "1A3B"

Explanation: 1 bull and 3 cows. The bull is 8, the cows are 0, 1 and 7.
Example 2:

Input: secret = "1123", guess = "0111"

Output: "1A1B"

Explanation: The 1st 1 in friend's guess is a bull, the 2nd or 3rd 1 is a cow.
Note: You may assume that the secret number and your friend's guess only contain digits, and their lengths are always equal.


*/


/*
One pass solution
只有当scret[i] != guess [i]时候，再加入map,
如果之前m[secret[i] - '0'] 小于0， 意味着之在guess中已经出现
如果之前m[guess[i] - '0'] 大于0， 意味着之在scret中已经出现

把scret[i] 数加上1， 
把guess[i] 减去1，
*/
class Solution {
public:
    string getHint(string secret, string guess) {
        int bulls = 0, cows = 0;
        vector<int> m(10, 0);
        for(int i = 0; i < secret.size(); i++){
            if(secret[i] == guess[i]) cows++;
            else {
                if( m[secret[i] - '0'] < 0) bulls++;
                if( m[guess[i] - '0'] > 0) bulls++;
                m[secret[i] - '0']++;
                m[guess[i] - '0']--;
            }
            
        }
        return to_string(cows) + "A" + to_string(bulls) + "B";
    }
};

/*
Two pass solution
分成两个for loop原因是，因为bull比cow重要,比如
"1087"
"7880"
合成一个可能会算成
1A3B
正确应为 1A2B
*/
class Solution {
public:
    string getHint(string secret, string guess) {
        unordered_map<char,int>m;
        for(auto i: secret) m[i]++;
        int bull = 0, cow = 0;
        for(int i = 0; i<guess.size();i++){
            if(guess[i] == secret[i]) {
               bull++;
               if(--m[guess[i]]==0) m.erase(guess[i]); 
            }
        }
        for(int i = 0; i<guess.size();i++){ //
            if(guess[i] != secret[i] && m[guess[i]]>0) {
               cow++;
               if(--m[guess[i]]==0) m.erase(guess[i]); 
            }
        }
        return to_string(bull)+"A"+to_string(cow)+"B";
    }
};



class Solution {
public:
    string getHint(string secret, string guess) {
        unordered_map<char, int> lookup;
        int A = 0, B = 0;
        for (const auto& s : secret) {
            ++lookup[s];
        }
        for (const auto& g : guess) {
            if (lookup[g]) {
                --lookup[g];
                ++B;
            }
        }
        const int n = min(secret.length(), guess.length());
        for (int i = 0; i < n; ++i) {
            if (secret[i] == guess[i]) {
                ++A, --B;
            }
        }
        return to_string(A).append("A").append(to_string(B)).append("B");
    }
};



