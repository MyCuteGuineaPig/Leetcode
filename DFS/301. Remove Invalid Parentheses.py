def removeInvalidParentheses(self, s):
    level = {s}
    while True:
        valid = []
        for s in level:
            try:
                eval('0,' + filter('()'.count, s).replace(')', '),'))
                valid.append(s)
            except:
                pass
        if valid:
            return valid
        level = {s[:i] + s[i+1:] for s in level for i in range(len(s))}

#Solution 2
def removeInvalidParentheses(self, s):
    def isvalid(s):
        ctr = 0
        for c in s:
            if c == '(':
                ctr += 1
            elif c == ')':
                ctr -= 1
                if ctr < 0:
                    return False
        return ctr == 0
    level = {s}
    while True:
        valid = filter(isvalid, level)
        if valid:
            return valid
        level = {s[:i] + s[i+1:] for s in level for i in range(len(s))}
        
        
  #Solution 3
  def removeInvalidParentheses(self, s):
    def isvalid(s):
        try:
            eval('0,' + filter('()'.count, s).replace(')', '),'))
            return True
        except:
            pass
    level = {s}
    while True:
        valid = filter(isvalid, level)
        if valid:
            return valid
        level = {s[:i] + s[i+1:] for s in level for i in range(len(s))}
        
        
   #Solution 4
   def removeInvalidParentheses(self, s):
    def isvalid(s):
        s = filter('()'.count, s)
        while '()' in s:
            s = s.replace('()', '')
        return not s
    level = {s}
    while True:
        valid = filter(isvalid, level)
        if valid:
            return valid
        level = {s[:i] + s[i+1:] for s in level for i in range(len(s))}
