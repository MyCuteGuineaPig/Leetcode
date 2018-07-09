"""
811. Subdomain Visit Count

Example 1:
Input: 
["9001 discuss.leetcode.com"]
Output: 
["9001 discuss.leetcode.com", "9001 leetcode.com", "9001 com"]
Explanation: 
We only have one website domain: "discuss.leetcode.com". As discussed above, the subdomain "leetcode.com" and "com" will also be visited. So they will all be visited 9001 times.

Example 2:
Input: 
["900 google.mail.com", "50 yahoo.com", "1 intel.mail.com", "5 wiki.org"]
Output: 
["901 mail.com","50 yahoo.com","900 google.mail.com","5 wiki.org","5 org","1 intel.mail.com","951 com"]
Explanation: 
We will visit "google.mail.com" 900 times, "yahoo.com" 50 times, "intel.mail.com" once and "wiki.org" 5 times. For the subdomains, we will visit "mail.com" 900 + 1 = 901 times, "com" 900 + 50 + 1 = 951 times, and "org" 5 times.

"""
class Solution:
    def subdomainVisits(self, cpdomains):
        """
        :type cpdomains: List[str]
        :rtype: List[str]
        """
        dic = collections.defaultdict(int)
        for domain in cpdomains:
            count = int(domain[:domain.find(" ")])
            ip = domain[domain.find(" "): ]
            while '.' in ip:
                dic[ip[1:]] += count
                ip = ip[ip.find('.',1):]
        res = []
        for k ,v in dic.items():
            res.append(str(v)+" "+k)  # or use : list(map(lambda kv: str(kv[1])+" "+kv[0],  dic.items()))
        return res


class Solution:
    def subdomainVisits(self, cpdomains):
        """
        :type cpdomains: List[str]
        :rtype: List[str]
        """
        result = defaultdict(int)
        for domain in cpdomains:
            count, domain = domain.split()
            count = int(count)
            frags = domain.split('.')
            curr = []
            for i in reversed(range(len(frags))):
                curr.append(frags[i])
                result[".".join(reversed(curr))] += count

        return ["{} {}".format(count, domain) for domain, count in result.item()]