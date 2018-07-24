/*

722. Remove Comments

*/









class Solution {
public:
    vector<string> removeComments(vector<string>& source) {
        string cur;
        vector<string>res; 
        bool commentOpen = false;
        for(auto word: source){
            int j = 0;
            for(int i = 0; i<word.size(); i++){
                if(!commentOpen && i+1<word.size() && word[i] == '/' && (word[i+1] == '/' || word[i+1] == '*')){
                    commentOpen = word[i+1] == '/' ? false : true;
                    i = word[i+1] == '/' ? word.size() : i+1;
                }
                else if(commentOpen && i+1<word.size() && word[i] == '*' && word[i+1] == '/' ){
                    commentOpen = false;
                    i++;
                }
                else if(!commentOpen) cur += word[i];
            }
            if(!commentOpen && !cur.empty()){
                res.push_back(cur);
                cur = "";
            }
        }
        return res;
    }
};


class Solution {
public:
    vector<string> removeComments(vector<string>& source) {
        bool in_block = false;
        vector<string> result;
        string newline;
        for (const auto& line : source) {
            for (int i = 0; i < line.length(); ++i) {
                if (!in_block && i + 1 < line.length() && line.substr(i, 2) == "/*") {
                    in_block = true;
                    ++i;
                } else if (in_block && i + 1 < line.length() && line.substr(i, 2) == "*/") {
                    in_block = false;
                    ++i;
                } else if (!in_block && i + 1 < line.length() && line.substr(i, 2) == "//") {
                    break;
                } else if (!in_block) {
                    newline.push_back(line[i]);
                }
            }
            if (!in_block && !newline.empty()) {
                result.emplace_back(move(newline));
            }
        }
        return result;
    }
};


/*
Explanation of regex in details, hope it will be helpful for regex beginner like me...

//.*     # matches single line comments
|        # 'or' operator
/\*      # matches '/*',
(.|\n)*? # matches everything(including '\n') inside block comment 
         # question mark will make regex '(.|\n)*' non-greedy or lazy
\*/      # matches '*/'
re.sub('//.*|/\*(.|\n)*?\*/', '', inputString) # replace matched result in the inputString with empty string.
Notes: The difference between (.*) and (.*?) is that the latter one is non-greedy regex. For example, given a inputString = '/*comment*/NotComment*/',
'/\*(.*)\*/' will match comment*/NotComment in the brackets.
'/\*(.*?)\*/' will match comment lazily

*/

class Solution {
public:
    vector<string> removeComments(vector<string>& source) {
        stringstream ss;
        const char* delim="\n";
        copy(source.begin(),source.end(),ostream_iterator<string>(ss,delim));
        string s=ss.str();
        //cout<<s;
        regex e("//.*|/\\*(.|\n)*?\\*/");
        string ns=regex_replace(s,e,"");
        //cout<<ns;
        //split the string into vector using tokened string
        ss.str(ns);
        vector<string> ans;
        while(ss.good())
        {
            string token;
            getline(ss,token,'\n');
            if(!token.empty())
            ans.push_back(token);
        }
        //copy(ans.begin(),ans.end(),ostream_iterator<string>(cout,"\n"));
        return ans;
    }
};

/*
Given a C++ program, remove comments from it. The program source is an array where source[i] is the i-th line of the source code. 
This represents the result of splitting the original source code string by the newline character \n.

In C++, there are two types of comments, line comments, and block comments.

The string // denotes a line comment, which represents that it and rest of the characters to the right of it in the same line should be ignored.

The string /* denotes a block comment, which represents that all characters until the next (non-overlapping) occurrence of */ should be ignored. 
(Here, occurrences happen in reading order: line by line from left to right.) 
To be clear, the string /*/ does not yet end the block comment, as the ending would be overlapping the beginning.

The first effective comment takes precedence over others: if the string // occurs in a block comment, it is ignored. 
Similarly, if the string /* occurs in a line or block comment, it is also ignored.

If a certain line of code is empty after removing comments, you must not output that line: each string in the answer list will be non-empty.

There will be no control characters, single quote, or double quote characters. 
For example, source = "string s = "/* Not a comment. */";" will not be a test case. 
(Also, nothing else such as defines or macros will interfere with the comments.)

It is guaranteed that every open block comment will eventually be closed, so /* outside of a line or block comment always starts a new comment.

Finally, implicit newline characters can be deleted by block comments. Please see the examples below for details.

After removing the comments from the source code, return the source code in the same format.

Example 1:
Input: 
source = ["/*Test program */", "int main()", "{ ", "  // variable declaration ", "int a, b, c;", "/* This is a test", "   multiline  ", "   comment for ", "   testing */", "a = b + c;", "}"]

The line by line code is visualized as below:
/*Test program */
int main()
{ 
  // variable declaration 
int a, b, c;
/* This is a test
   multiline  
   comment for 
   testing */
a = b + c;
}

Output: ["int main()","{ ","  ","int a, b, c;","a = b + c;","}"]

The line by line code is visualized as below:
int main()
{ 
  
int a, b, c;
a = b + c;
}

Explanation: 
The string /* denotes a block comment, including line 1 and lines 6-9. The string // denotes line 4 as comments.

Example 2:
Input: 
source = ["a/*comment", "line", "more_comment*/b"]
Output: ["ab"]
Explanation: The original source string is "a/*comment\nline\nmore_comment*/b", where we have bolded the newline characters.  After deletion, the implicit newline characters are deleted, leaving the string "ab", which when delimited by newline characters becomes ["ab"].
Note:

The length of source is in the range [1, 100].
The length of source[i] is in the range [0, 80].
Every open block comment is eventually closed.
There are no single-quote, double-quote, or control characters in the source code.

*/