
"""
591. Tag Validator
Input: "<DIV>This is the first line <![CDATA[<div>]]></DIV>"

Output: True

Explanation: 

The code is wrapped in a closed tag : <DIV> and </DIV>. 

The TAG_NAME is valid, the TAG_CONTENT consists of some characters and cdata. 

Although CDATA_CONTENT has unmatched start tag with invalid TAG_NAME, it should be considered as plain text, not parsed as tag.

So TAG_CONTENT is valid, and then the code is valid. Thus return (int)true.


Input: "<DIV>>>  ![cdata[]] <![CDATA[<div>]>]]>]]>>]</DIV>"

Output: True

Explanation:

We first separate the code into : start_tag|tag_content|end_tag.

start_tag -> "<DIV>"

end_tag -> "</DIV>"

tag_content could also be separated into : text1|cdata|text2.

text1 -> ">>  ![cdata[]] "

cdata -> "<![CDATA[<div>]>]]>", where the CDATA_CONTENT is "<div>]>"

text2 -> "]]>>]"


The reason why start_tag is NOT "<DIV>>>" is because of the rule 6.
The reason why cdata is NOT "<![CDATA[<div>]>]]>]]>" is because of the rule 7.
Invalid Code Examples:
Input: "<A>  <B> </A>   </B>"
Output: False
Explanation: Unbalanced. If "<A>" is closed, then "<B>" must be unmatched, and vice versa.

Input: "<DIV>  div tag is not closed  <DIV>"
Output: False

Input: "<DIV>  unmatched <  </DIV>"
Output: False

Input: "<DIV> closed tags with invalid tag name  <b>123</b> </DIV>"
Output: False

Input: "<DIV> unmatched tags with invalid tag name  </1234567890> and <CDATA[[]]>  </DIV>"
Output: False

Input: "<DIV>  unmatched start tag <B>  and unmatched end tag </C>  </DIV>"
Output: False
Note:

"""

class Solution:
    def isValid(self, code):
        """
        :type code: str
        :rtype: bool
        """
        self.index = 0
        return self.validtag(code) and self.index == len(code)
    
    def validtag(self,code):
        tagname = self.parseTagName(code)
        if not tagname: 
            print("return false ")
            return False
        self.index += len(tagname)
        self.validContent(code)
        if self.index == -1 or code[self.index: self.index+len(tagname)+2]!='</'+tagname:
            self.index = -1
            return False
        self.index += len(tagname)+2
        return True

    def validContent(self,code):
        while self.index!=-1 and self.index < len(code):
            self.index = code.find("<",self.index)
            if self.index==-1 or not self.isvalidCdata(code) and not self.validtag(code):
               break
    
    
    def parseTagName(self,code):
        if code[self.index]!= "<" or code.find('>', self.index) == -1: return ""
        end = code.find('>',self.index)
        if not 1<end - self.index < 11: return ""
        for c in code[self.index+1: end]:
            if not c.isupper():
                return ""
        return code[self.index+1: end+1]#include ">" in tag
    
    def isvalidCdata(self, code):
        if not code.startswith("<![CDATA[",self.index):
            return False
        self.index += len("<![CDATA[")
        if code.find(']]>', self.index) == -1:
            return False
        self.index = code.find(']]>', self.index)+3
        return True


