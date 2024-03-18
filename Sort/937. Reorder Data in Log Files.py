class Solution:
    def reorderLogFiles(self, logs: List[str]) -> List[str]:
        digits = []
        letters = []
		# divide logs into two parts, one is digit logs, the other is letter logs
        for log in logs:
            if log.split()[1].isdigit():
                digits.append(log)
            else:
                letters.append(log)
                
        letters.sort(key = lambda x: (x.split()[1:], x.split()[0]))
        result = letters + digits                                        #put digit logs after letter logs
        return result