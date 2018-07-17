/*
68. Text Justification

Given an array of words and a width maxWidth, format the text such that each line has exactly maxWidth characters 
and is fully (left and right) justified.

You should pack your words in a greedy approach; that is, pack as many words as you can in each line. Pad extra spaces ' ' 
when necessary so that each line has exactly maxWidth characters.

Extra spaces between words should be distributed as evenly as possible. If the number of spaces on a line do not divide evenly between words,
the empty slots on the left will be assigned more spaces than the slots on the right.

For the last line of text, it should be left justified and no extra space is inserted between words.

Note:

A word is defined as a character sequence consisting of non-space characters only.
Each word's length is guaranteed to be greater than 0 and not exceed maxWidth.
The input array words contains at least one word.
Example 1:

Input:
words = ["This", "is", "an", "example", "of", "text", "justification."]
maxWidth = 16
Output:
[
   "This    is    an",
   "example  of text",
   "justification.  "
]
Example 2:

Input:
words = ["What","must","be","acknowledgment","shall","be"]
maxWidth = 16
Output:
[
  "What   must   be",
  "acknowledgment  ",
  "shall be        "
]
Explanation: Note that the last line is "shall be    " instead of "shall     be",
             because the last line must be left-justified instead of fully-justified.
             Note that the second line is also left-justified becase it contains only one word.
Example 3:

Input:
words = ["Science","is","what","we","understand","well","enough","to","explain",
         "to","a","computer.","Art","is","everything","else","we","do"]
maxWidth = 20
Output:
[
  "Science  is  what we",
  "understand      well",
  "enough to explain to",
  "a  computer.  Art is",
  "everything  else  we",
  "do                  "
]


*/

class Solution {
public:
    vector<string> fullJustify(vector<string>& words, int maxWidth) {
        vector<string>res;
        for(int i = 0, j = 0; i<words.size(); i = j){
            int width = 0;
            for(; j<words.size() && width+words[j].size()+j - i<=maxWidth; j++)
                width += words[j].size();
            int space = 1, extra = 0;
            if(j-i> 1 && j!= words.size()){
                space = (maxWidth - width) / (j-i-1);
                extra = (maxWidth - width) % (j - i - 1);
            }
            string cur = words[i++];
            for(;i<j; i++){
                cur += string(space, ' ');
                if(extra-->0)
                    cur += " ";
                cur += words[i];
            }
            cur += string(maxWidth - cur.size(), ' ');
            res.push_back(cur);
        }
        return res;
    }
};



class Solution {
public:
    vector<string> fullJustify(vector<string>& words, int maxWidth) {
        vector<string>res;
        for(int i = 0; i<words.size();){
            int width = 0, k = 0, j = 0;
            for(; i+k<words.size() && width+words[i+k].size()+ k <=maxWidth; k++)
                width += words[i+k].size();

            string cur = words[i+j++];
            for(;j<k ; j++){
                if(i+k == words.size()) cur+= " ";
                else cur += string((maxWidth - width)/(k-1) + (j<= ( maxWidth - width) % (k-1)), ' ');
                cur += words[i+j];
            }
            i += k;
            cur += string(maxWidth - cur.size(), ' ');
            
            res.push_back(cur);
        }
        return res;
    }
};