/*
824. Goat Latin

We would like to convert the sentence to "Goat Latin" (a made-up language similar to Pig Latin.)

The rules of Goat Latin are as follows:

If a word begins with a vowel (a, e, i, o, or u), append "ma" to the end of the word.
For example, the word 'apple' becomes 'applema'.
 
If a word begins with a consonant (i.e. not a vowel), remove the first letter and append it to the end, then add "ma".
For example, the word "goat" becomes "oatgma".
 
Add one letter 'a' to the end of each word per its word index in the sentence, starting with 1.
For example, the first word gets "a" added to the end, the second word gets "aa" added to the end and so on.
Return the final sentence representing the conversion from S to Goat Latin. 

 

Example 1:

Input: "I speak Goat Latin"
Output: "Imaa peaksmaaa oatGmaaaa atinLmaaaaa"
Example 2:

Input: "The quick brown fox jumped over the lazy dog"
Output: "heTmaa uickqmaaa rownbmaaaa oxfmaaaaa umpedjmaaaaaa overmaaaaaaa hetmaaaaaaaa azylmaaaaaaaaa ogdmaaaaaaaaaa"
 

Notes:

S contains only uppercase, lowercase and spaces. Exactly one space between each word.
1 <= S.length <= 150.

*/



class Solution {
public:
    string toGoatLatin(string S) {
        unordered_set<char>vowel = {'a','e','i','o','u', 'A','E','I','O','U'};
        string res = "", temp = "";
        int i = 2;
        istringstream iss(S);
        while(iss>>temp){
            if(vowel.find(temp[0]) == vowel.end()) temp = temp.substr(1) + temp[0];
            res = res+ (temp + "m" +(string(i++,'a'))+" ");
        }
        return res.substr(0, res.length()-1);
    }
};


class Solution {
public:
    string toGoatLatin(string S) {
        stringstream iss(S), oss;
        string vowels("aeiouAEIOU"), word, a;
        while (iss >> word) {
            a.push_back('a');
            if (vowels.find_first_of(word[0]) != string::npos) // begin with a vowel
                oss << ' ' << word << "ma" << a;
            else // begin with a consonant
                oss << ' ' << word.substr(1) << word[0] << "ma" << a;
        }
        return oss.str().substr(1);
    }
};