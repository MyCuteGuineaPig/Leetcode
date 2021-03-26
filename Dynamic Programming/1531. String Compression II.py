"""

Start from the beginning of the s, meet two situations:

1. The next character is the same as the last one, e.g. "aaa" with the next one still "a"
    - The former characters would be "a3", so you need to combine them and make it "a4"
    - The total length of this part would be changed if you get count from 1->2 ("a" -> "a2"), 9->10 ("a9" -> "a10") or 99 -> 100 ("a99"->"a100")

2. The next character is not the same, e.g. "aaa" with the next one "b"
    You can either choose to :
        - accept "b" -> your length would increase 1 and the count resets to 1
        - deny "b" -> your length would remain the same, the last character still "a", while the chances would decrease 1
Since we want the minimum length for the answer, so use min while taking situation 2.

"""


class Solution:
    def getLengthOfOptimalCompression(self, s: str, k: int) -> int:
		# this decorator automatically use memo with key = (start, last, last_count, left)
        @lru_cache(None)
        def counter(start, last, last_count, left): #count the cost of compressing from the start
            if left < 0:
                return float('inf') # this is impossible
            if start >= len(s):
                return 0
            if s[start] == last:
				# we have a stretch of the last_count of the same chars, what is the cost of adding one more? 
                incr = 1 if last_count == 1 or last_count == 9 or last_count == 99 else 0
				# no need to delete here, if we have a stretch of chars like 'aaaaa' - we delete it from the beginning in the else delete section
                return incr + counter(start+1, last, last_count+1, left) # we keep this char for compression
            else:
				# keep this char for compression - it will increase the result length by 1 plus the cost of compressing the rest of the string 
				keep_counter = 1 + counter(start+1, s[start], 1, left)
				# delete this char
				del_counter =  counter(start + 1, last, last_count, left - 1)
                return min(keep_counter, del_counter)
            
        return counter(0, "", 0, k)