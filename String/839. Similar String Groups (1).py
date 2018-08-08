"""
839. Similar String Groups


Two strings X and Y are similar if we can swap two letters (in different positions) of X, so that it equals Y.

For example, "tars" and "rats" are similar (swapping at positions 0 and 2), and "rats" and "arts" are similar, 
but "star" is not similar to "tars", "rats", or "arts".

Together, these form two connected groups by similarity: {"tars", "rats", "arts"} and {"star"}.  
Notice that "tars" and "arts" are in the same group even though they are not similar.  
Formally, each group is such that a word is in the group if and only if it is similar to at least one other word in the group.

We are given a list A of strings.  Every string in A is an anagram of every other string in A.  How many groups are there?

Example 1:

Input: ["tars","rats","arts","star"]
Output: 2
Note:

A.length <= 2000
A[i].length <= 1000
A.length * A[i].length <= 20000
All words in A consist of lowercase letters only.
All words in A have the same length and are anagrams of each other.
The judging time limit has been increased for this question.

"""
class DisjointSet:
    def __init__(self, A):
        self.parent = [i for i in range(len(A))]
        self.size = len(A)
    
    def find(self,A):
        #print("A",A,self.parent)
        if self.parent[A]!= A:
            self.parent[A] = self.find(self.parent[A])
        return self.parent[A]
    
    def join(self,A,B):
        rootA = self.find(A)
        rootB = self.find(B)
        if rootA!=rootB:
            self.parent[rootA] = rootB
            self.size -= 1


class Solution:
    def numSimilarGroups(self, A):
        """
        :type A: List[str]
        :rtype: int
        """
        A = [*set(A)] #要不然会TLE
        def similar(A,B):
            cnt = 0
            for a, b in zip(A,B):
                if a!=b:
                    cnt+=1
                    if cnt>2: return False
            return True
        ds = DisjointSet(A)
        for i, a in enumerate(A[:-1]):
            for j,b in enumerate(A[i+1:],i+1):
                if similar(a,b):
                    ds.join(i,j)
        return ds.size

#rank heuristic  

class DisjointSet:
    def __init__(self, A):
        self.parent = [i for i in range(len(A))]
        self.size = len(A)
        self.rank = [0]*self.size
    def find(self,A):
        #print("A",A,self.parent)
        if self.parent[A]!= A:
            self.parent[A] = self.find(self.parent[A])
        return self.parent[A]
    
    def join(self,A,B):
        rootA = self.find(A)
        rootB = self.find(B)
        if rootA == rootB: return 
        self.size -= 1
        if self.rank[rootA] < self.rank[rootB]:
            self.parent[rootB] = rootA
        else:
            self.parent[rootA] = rootB
        if self.rank[rootA] == self.rank[rootB]:
            self.rank[rootA]  += 1


class Solution:
    def numSimilarGroups(self, A):
        """
        :type A: List[str]
        :rtype: int
        """
        A = [*set(A)] #要不然会TLE
        def similar(A,B):
            cnt = 0
            for a, b in zip(A,B):
                if a!=b:
                    cnt+=1
                    if cnt>2: return False
            return True
        ds = DisjointSet(A)
        for i, a in enumerate(A[:-1]):
            for j,b in enumerate(A[i+1:],i+1):
                if similar(a,b):
                    ds.join(i,j)
        return ds.size

    
# Solution 3

class Solution:
    def numSimilarGroups(self, A):
        A = [*set(A)]
        parents = {x: x for x in A}
        n, m = len(A), len(A[0])
        self.count = n
        def find(x):
            if x != parents[x]: parents[x] = find(parents[x])
            return parents[x]
        def union(x, y):
            x, y = find(x), find(y)
            if x != y:
                parents[x] = y
                self.count -= 1
                return True
            return False

        def similar(x, y):
            return sum(i != j for i, j in zip(x, y)) == 2
	
        ## Real Solution Part ##
        if n < m:
            for x, y in itertools.combinations(A, 2):
                if similar(x, y): union(x, y)
        else:
            for x in A:
                for i, j in itertools.combinations(range(m), 2): #把每个字进行排列组合
                    y = x[:i] + x[j] + x[i + 1:j] + x[i] + x[j + 1:]
                    if y in parents: union(x, y)
        return self.count