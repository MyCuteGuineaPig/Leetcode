"""
726. Number of Atoms

Example 1:
Input: 
formula = "H2O"
Output: "H2O"
Explanation: 
The count of elements are {'H': 2, 'O': 1}.
Example 2:
Input: 
formula = "Mg(OH)2"
Output: "H2MgO2"
Explanation: 
The count of elements are {'H': 2, 'Mg': 1, 'O': 2}.
Example 3:
Input: 
formula = "K4(ON(SO3)2)2"
Output: "K4N2O14S4"
Explanation: 
The count of elements are {'K': 4, 'N': 2, 'O': 14, 'S': 4}.

"""
import collections
class Solution:
    def countOfAtoms(self, formula):
        """
        :type formula: str
        :rtype: str
        """
        cur, stack = collections.defaultdict(int), []
        i, n  = 0, len(formula)
        while i < n:
            if formula[i] == '(':
                stack.append(cur)
                cur =  collections.defaultdict(int)
                i+=1
            elif formula[i] == ')':
                i+=1
                start = i
                while i < n and formula[i].isdigit():
                    i+=1
                num = 1 if i == start else int(formula[start:i])
                for k,v in cur.items():
                    stack[-1][k] += v*num
                cur = stack.pop()
            else:
                start = i; i+=1
                while i<n and formula[i].islower():
                    i+=1
                words = formula[start:i]
                start = i
                while i<n and formula[i].isdigit():
                    i+=1
                num = 1 if i == start else int(formula[start:i])
                cur[words] += num
        res = ""
        for i, v in sorted(cur.items()):
            if v > 1: res += i + str(v)
            else: res += i
        return res



 class Solution(object):
    def countOfAtoms(self, formula):
        """
        :type formula: str
        :rtype: str
        """
        parse = re.findall(r"([A-Z][a-z]*)(\d*)|(\()|(\))(\d*)", formula)
        stk = [collections.Counter()]
        for name, m1, left_open, right_open, m2 in parse:
            if name:
              stk[-1][name] += int(m1 or 1)
            if left_open:
              stk.append(collections.Counter())
            if right_open:
                top = stk.pop()
                for k, v in top.iteritems():
                  stk[-1][k] += v * int(m2 or 1)

        return "".join(name + (str(stk[-1][name]) if stk[-1][name] > 1 else '') \
                       for name in sorted(stk[-1]))       
                
