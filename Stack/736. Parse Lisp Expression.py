"""
736. Parse Lisp Expression


Input: (add 1 2)
Output: 3

Input: (mult 3 (add 2 3))
Output: 15

Input: (let x 2 (mult x 5))
Output: 10

Input: (let x 2 (mult x (let x 3 y 4 (add x y))))
Output: 14
Explanation: In the expression (add x y), when checking for the value of the variable x,
we check from the innermost scope to the outermost in the context of the variable we are trying to evaluate.
Since x = 3 is found first, the value of x is 3.

Input: (let x 3 x 2 x)
Output: 2
Explanation: Assignment in let statements is processed sequentially.

Input: (let x 1 y 2 x (add x y) (add x y))
Output: 5
Explanation: The first (add x y) evaluates as 3, and is assigned to x.
The second (add x y) evaluates as 3+2 = 5.

Input: (let x 2 (add (let x 3 (let x 4 x)) x))
Output: 6
Explanation: Even though (let x 4 x) has a deeper scope, it is outside the context
of the final x in the add-expression.  That final x will equal 2.

Input: (let a1 3 b2 (add a1 1) b2) 
Output 4
Explanation: Variable names can contain digits after the first character.


"""


import collections, copy
class Solution(object):
    def evaluate(self, expression):
        """
        :type expression: str
        :rtype: int
        """
        def calculate(cur, dict):
            #print(cur)
            if cur[0] == 'add' or cur[0] == 'mult':
                return str(int(lookup(cur[1], dict)) + int(lookup(cur[2], dict))) if cur[0] == 'add' else str(int(lookup(cur[1], dict))*int(lookup(cur[2], dict))) 
            i, n = 1, len(cur)
            while i + 1 < n:
                dict[cur[i]] = str(lookup(cur[i+1], dict))
                i+=2
            return lookup(cur[-1], dict)
            
        
        def lookup(key, dict):  #需要返回string, 比如 (let a1 3 b2 (add a1 1) b2)  "(let a1 3 b2" b2还没有声明
            return dict.get(key,key)
        
        strstk, dictstk = [], []
        cur, dict, res = [], collections.defaultdict(str), 0
        for ele in expression.split():
            print("ele",ele)
            if ele[0] == '(':
                if cur and cur[0] == 'let': calculate(cur, dict)
                strstk.append(cur)
                dictstk.append(copy.deepcopy(dict))
                cur = [ele[1:]]
            elif ele[-1] == ')':
                ind = ele.find(')')
                cur.append(ele[:ind])
                while ele[-1] == ')': #(let x 1 y 2 x (add x y) (add x y)) 可能一个ele多个')'， 比如'y))'
                    ele = ele[:-1]
                    res =  calculate(cur, dict)
                    cur, dict = strstk.pop() + [res],  dictstk.pop()
            else: 
                cur.append(ele)
        return int(res)
        

class Solution(object):
    def evaluate(self, expression):
        st, d, tokens = [], {}, ['']

        def getval(x):
            return d.get(x, x)

        def evaluate(tokens):
            if tokens[0] in ('add', 'mult'):
                tmp = map(int, map(getval, tokens[1:]))
                return str(tmp[0] + tmp[1] if tokens[0] == 'add' else tmp[0] * tmp[1])
            else: #let
                for i in range(1, len(tokens)-1, 2):
                    if tokens[i+1]:
                        d[tokens[i]] = getval(tokens[i+1])
                return getval(tokens[-1])

        for c in expression:
            if c == '(':
                if tokens[0] == 'let':
                    evaluate(tokens)
                st.append((tokens, dict(d)))
                tokens =  ['']
            elif c == ' ':
                tokens.append('')
            elif c == ')':
                val = evaluate(tokens)
                tokens, d = st.pop()
                tokens[-1] += val
            else:
                tokens[-1] += c
        return int(tokens[0])