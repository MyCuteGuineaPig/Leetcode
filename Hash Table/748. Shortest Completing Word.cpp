/*
748. Shortest Completing Word

Find the minimum length word from a given dictionary words, which has all the letters from the string licensePlate. 
Such a word is said to complete the given string licensePlate

Here, for letters we ignore case. For example, "P" on the licensePlate still matches "p" on the word.

It is guaranteed an answer exists. If there are multiple answers, return the one that occurs first in the array.

The license plate might have the same letter occurring multiple times. For example, given a licensePlate of "PP", 
the word "pair" does not complete the licensePlate, but the word "supper" does.

Example 1:
Input: licensePlate = "1s3 PSt", words = ["step", "steps", "stripe", "stepple"]
Output: "steps"
Explanation: The smallest length word that contains the letters "S", "P", "S", and "T".
Note that the answer is not "step", because the letter "s" must occur in the word twice.
Also note that we ignored case for the purposes of comparing whether a letter exists in the word.
Example 2:
Input: licensePlate = "1s3 456", words = ["looks", "pest", "stew", "show"]
Output: "pest"
Explanation: There are 3 smallest length words that contains the letters "s".
We return the one that occurred first.
Note:
licensePlate will be a string with length in range [1, 7].
licensePlate will contain digits, spaces, or letters (uppercase or lowercase).
words will have a length in the range [10, 1000].
Every words[i] will consist of lowercase letters, and have length in range [1, 15].


*/

class Solution {
public:
    string shortestCompletingWord(string licensePlate, vector<string>& words) {
        vector<int>map(26);
        for(auto s: licensePlate)
            if(isalpha(s))
                map[tolower(s)-'a']++;
        string res;
        for(auto word: words){
            vector<int>count(26);
            bool find = true;
            if(!res.empty() && word.size()>=res.size()) continue;
            for(auto s: word)
                if(isalpha(s))
                    count[tolower(s)-'a']++;
            for(int i = 0; i<26; i++){
                if(count[i]<map[i]) {
                    find = false;
                    break;
                }
            }
            if(find) res = word;
        }
        return res;
    }
};




class Solution {
public:
    string shortestCompletingWord(string licensePlate, vector<string>& words) {
        string result;
        const auto& counter = counts(licensePlate);
        for (const auto& word : words) {
            if ((result.empty() || word.length() < result.length()) &&
               contains(counter, word)) {
                result = word;
            }
        }
        return result;
    }
    
private:
    bool contains(const vector<int>& counter1, const string& w2) const {
        const auto& counter2 = counts(w2);
        for (int i = 0; i < counter2.size(); ++i) {
            if (counter1[i] > counter2[i]) {
                return false;
            }
        }
        return true;
    }
    
    vector<int> counts(const string& s) const {
        vector<int> count(26);
        for (const auto& c : s) {
            if (isalpha(c)) {
                ++count[tolower(c) - 'a'];
            }
        }
        return count;
    }
};


class Solution {
public:
    void countChars(const string& str, vector<int>* counts) {
        for (char ch : str) {
            if (ch >= 'a' && ch <= 'z') (*counts)[ch-'a']++;
            if (ch >= 'A' && ch <= 'Z') (*counts)[ch-'A']++;
        }
    }
    string shortestCompletingWord(string licensePlate, vector<string>& words) {
        vector<int> counts(26, 0);
        countChars(licensePlate, &counts);
        
        int min = -1;
        string result;
        for (const string& word : words) {
            vector<int> cur(26, 0);
            countChars(word, &cur);
            bool match = true;
            for (int i = 0; i < 26; i++) {
                if (counts[i] > cur[i]) {
                    match = false;
                }
            }
            if (match && (min == -1 || word.size() < min)) {
                min = word.size();
                result = word;
            }
        }
        return result;
    }
};