"""
721. Accounts Merge

Example 1:
Input: 
accounts = [["John", "johnsmith@mail.com", "john00@mail.com"], ["John", "johnnybravo@mail.com"], ["John", "johnsmith@mail.com", "john_newyork@mail.com"], ["Mary", "mary@mail.com"]]
Output: [["John", 'john00@mail.com', 'john_newyork@mail.com', 'johnsmith@mail.com'],  ["John", "johnnybravo@mail.com"], ["Mary", "mary@mail.com"]]
Explanation: 
The first and third John's are the same person as they have the common email "johnsmith@mail.com".
The second John and Mary are different people as none of their email addresses are used by other accounts.
We could return these lists in any order, for example the answer [['Mary', 'mary@mail.com'], ['John', 'johnnybravo@mail.com'], 
['John', 'john00@mail.com', 'john_newyork@mail.com', 'johnsmit

"""

class Solution:
    def accountsMerge(self, accounts):
        """
        :type accounts: List[List[str]]
        :rtype: List[List[str]]
        """
        def findparent(cur):
            return cur if parent[cur] == cur else findparent(parent[cur])
        
        parent = collections.defaultdict()
        name = collections.defaultdict(int)
        lookup = collections.defaultdict(set)
        res= []
        for i, v in enumerate(accounts):
            for acct in v[1:]:
                if acct not in name:
                    name[acct] = v[0]
                    parent[acct] = acct
        for i, v in enumerate(accounts):
            curp = findparent(v[1])
            parent[v[1]] = curp  
            for acct in v[2:]:
                parent[findparent(acct)] = curp
        for i, v in enumerate(accounts):
            for acct in v[1:]:
                lookup[findparent(acct)].add(acct)
        
        for k,v in lookup.items():
            v = list(v)
            v.sort()
            res.append([name[v[0]]]+v)
        return res


##DFS
class Solution:
    def accountsMerge(self, accounts):
        """
        :type accounts: List[List[str]]
        :rtype: List[List[str]]
        """
        def find(ind, par):
            visited[ind] = True
            for acct in accounts[ind][1:]:
                for j in id[acct]:
                    if j!= ind and not visited[j]:
                        find(j, par)
                lookup[par].add(acct)

        n = len(accounts)
        visited = [False]*n
        id = collections.defaultdict(list)
        lookup = collections.defaultdict(set)
        name =  collections.defaultdict()
        for i, account in enumerate(accounts):
            for acct in account[1:]:
                if acct not in name:
                    name[acct] = account[0]
                id[acct].append(i)
        for i, account in enumerate(accounts):
            if not visited[i]:
                find(i,account[1])
        return list(map(lambda kv:[name[kv[0]]]+sorted(kv[1]), lookup.items()))


#Union Find
class DisjointSet:
    def __init__(self):
        self.li = []
        self.index = 0
    
    def getid(self):
        self.li.append(self.index)
        temp = self.index
        self.index += 1
        return temp
        
    
    def find(self,x):
        self.li[x] = (x if self.li[x] == x else self.find(self.li[x]))
        return self.li[x]

    def union(self,a,b):
        root_a, root_b = self.find(a), self.find(b)
        self.li[root_a] = root_b

class Solution:
    def accountsMerge(self, accounts):
        disjset = DisjointSet()
        lookup = collections.defaultdict(set)
        id = collections.defaultdict(int)
        name = collections.defaultdict()
        for i, v in enumerate(accounts):
            for acct in v[1:]:
                if acct not in name:
                    name[acct] = v[0]
                    id[acct] = disjset.getid()
                disjset.union(id[v[1]],id[acct])
        for k,v in id.items():
            index = disjset.find(v)
            lookup[index].add(k)
        return list(map(lambda v: [name[next(iter(v))]]+sorted(v), lookup.values()))


#Rank hueristic

class DisjointSet:
    def __init__(self):
        self.parents = collections.defaultdict(str)
        self.ranks = collections.defaultdict()
        
    def __getitem__(self,x):
        if x not in self.parents:
            self.parents[x] = x
            self.ranks[x] = 0
        elif self.parents[x] != x:
            self.parents[x] = self[self.parents[x]]
        return self.parents[x]
    
    def union(self,x,y):
        px, py = self[x], self[y]
        if px == py:
            return 
        if self.ranks[px] > self.ranks[py]:
            self.parents[py] = px
        elif self.ranks[px] < self.ranks[py]:
            self.parents[px] = py
        else:
            self.parents[py] = px
            self.ranks[px] += 1
    
    def get(self):
        res = collections.defaultdict(list)
        for k, v in self.parents.items():
            p = self[self.parents[v]]
            res[p].append(k)
        return res.values()
        

class Solution:
    def accountsMerge(self, accounts: List[List[str]]) -> List[List[str]]:
        email_name_dic = collections.defaultdict(str)
        ds = DisjointSet()
        for acct in accounts:
            name =acct[0]
            for email in acct[1:]:
                ds.union(acct[1], email)
                email_name_dic[email] = name
        return [ [email_name_dic[e[0]]] + sorted(e) for e in ds.get()]
            
        
        
        
        
        
    
    
    
    
    
    
    
    
    
    
    
    



    class Account:
        def __init__(self, l):
            self.name = l[0]
            self.emails = l[1:]

        def __hash__(self):
            return hash(str(self))

        def __eq__(self, other):
            return self.name == other.name and len(self.emails) == len(other.emails) \
                   and set(self.emails) == set(other.emails)

    def accountsMerge(self, accounts):
        accounts = [self.Account(a) for a in accounts]
        email_dict, visited, finalres = defaultdict(set), set(), []

        for acc in accounts:
            for email in acc.emails:
                email_dict[email].add(acc)

        for acc in accounts:
            if acc in visited: continue
            res = set()
            self.dfs(acc, email_dict, visited, res)
            finalres.append([acc.name] + sorted(res))
        return finalres

    def dfs(self, acc, email_dict, visited, res):
        if acc in visited: return
        visited.add(acc)
        for email in acc.emails:
            res.add(email)
            for a in email_dict[email]:
                self.dfs(a, email_dict, visited, res)
