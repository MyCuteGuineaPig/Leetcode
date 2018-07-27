"""
468. Validate IP Address

Example 1:
Input: "172.16.254.1"

Output: "IPv4"

Explanation: This is a valid IPv4 address, return "IPv4".
Example 2:
Input: "2001:0db8:85a3:0:0:8A2E:0370:7334"

Output: "IPv6"

Explanation: This is a valid IPv6 address, return "IPv6".
Example 3:
Input: "256.256.256.256"

Output: "Neither"

Explanation: This is neither a IPv4 address nor a IPv6 address.

"""

class Solution:
    def validIPAddress(self, IP):
        """
        :type IP: str
        :rtype: str
        """
        hex_ = '0123456789abcdefABCDEF'
        def isIPv4():
            li = IP.split(".")
            if len(li)!=4: return False
            for i in li:
                cur = 0
                if len(i) == 0: return False
                for v in i:
                    if not v.isdigit() or len(i)>1 and cur == 0 and v == '0':
                        return False
                    cur = cur*10 + ord(v)-ord('0')
                if cur >= 256: return False
            return True
            
        def isIPv6():
            li = IP.split(":")
            if len(li)!=8: return False
            for i in li:
                if len(i) > 4 or len(i) == 0: return False
                for v in i:
                    if v not in hex_:
                        return False
            return True     
        
        if "." in IP and isIPv4():
            return "IPv4"
        if ":" in IP and isIPv6():
            return "IPv6"
        return "Neither"


class Solution:
    def validIPAddress(self, IP):
        """
        :type IP: str
        :rtype: str
        """
        def isIPv4(s):
            try: return str(int(s)) == s and 0 <= int(s) <= 255
            except: return False
            
        def isIPv6(s):
            if len(s) > 4: return False
            try: return int(s, 16) >= 0 and s[0] != '-'
            except: return False

        if IP.count(".") == 3 and all(isIPv4(i) for i in IP.split(".")): 
            return "IPv4"
        if IP.count(":") == 7 and all(isIPv6(i) for i in IP.split(":")): 
            return "IPv6"
        return "Neither"

import string

class Solution(object):
    def validIPAddress(self, IP):
        """
        :type IP: str
        :rtype: str
        """
        blocks = IP.split('.')
        if len(blocks) == 4:
            for i in range(len(blocks)):
                if not blocks[i].isdigit() or not 0 <= int(blocks[i]) < 256 or \
                   (blocks[i][0] == '0' and len(blocks[i]) > 1):
                    return "Neither"
            return "IPv4"

        blocks = IP.split(':')
        if len(blocks) == 8:
            for i in range(len(blocks)):
                if not (1 <= len(blocks[i]) <= 4) or \
                   not all(c in string.hexdigits for c in blocks[i]):
                    return "Neither"
            return "IPv6"
        return "Neither"