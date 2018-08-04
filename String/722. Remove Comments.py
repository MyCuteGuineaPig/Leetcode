"""
722. Remove Comments

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
"""

class Solution:
    def removeComments(self, source):
        """
        :type source: List[str]
        :rtype: List[str]
        """
        res = []
        CommentOpen = False
        pre = ""
        for c in source: 
            i = 0
            while i<len(c):
                if i<len(c) -1 and not CommentOpen and c[i] == '/' and (c[i+1] == '*' or c[i+1] == '/'):
                    CommentOpen = True if c[i+1] == '*' else False
                    i+=2
                    if not CommentOpen: break
                elif i<len(c) -1 and CommentOpen and c[i] == '*' and c[i+1] == '/':
                    CommentOpen = False
                    i+=2
                elif not CommentOpen:
                    print(i,c)
                    pre += c[i]
                    i+=1
                else:
                    i+=1
            if not CommentOpen and pre:
                res.append(pre)
                pre = ""
        return res

/*

Explanation of regex in details, hope it will be helpful for regex beginner like me...

//.*     # matches single line comments
|        # 'or' operator
/\*      # matches '/*',
(.|\n)*? # matches everything(including '\n') inside block comment 
         # question mark will make regex '(.|\n)*' non-greedy or lazy
\*/      # matches '*/'
re.sub('//.*|/\*(.|\n)*?\*/', '', inputString) # replace matched result in the inputString with empty string.
Notes: The difference between (.*) and (.*?) is that the latter one is non-greedy regex.
 For example, given a inputString = '/*comment*/NotComment*/',
'/\*(.*)\*/' will match comment*/NotComment in the brackets.
'/\*(.*?)\*/' will match comment lazily
*/
class Solution:
    def removeComments(self, source):
        return [*filter(None, re.sub('//.*|/\*(.|\n)*?\*/', '', '\n'.join(source)).split('\n'))]