
# Time:  O(n^2 * l^2), n is the number of strings
# Space: O(1)        , l is the max length of strings

class Solution:
    def stringMatching(self, words: List[str]) -> List[str]:
        result = []
        for i, pattern in enumerate(words):
            for j, text in enumerate(words):
                if i != j and pattern in text:
                    result.append(pattern)
                    break
        return result


class Solution(object):
    def stringMatching(self, words):
        arr = ' '.join(words)
        return [i for i in words if arr.count(i) >= 2]
        



# KMP 
# Time:  O(n^2 * l), n is the number of strings
# Space: O(l)      , l is the max length of strings

class Solution:
    def stringMatching(self, words: List[str]) -> List[str]:
        def getPrefix(word):
            prefix = [0]
            j = 0
            for s in word[1:]:
                while j and s != word[j]:
                    j = prefix[j-1]
                if s == word[j]:
                    j += 1
                prefix += j, 
            return prefix 
        
        def kmp(word, pattern, prefix):
            if len(word) < len(pattern):
                return False
            i = j = 0
            for s in word:
                while j and pattern[j] != s:
                    j = prefix[j-1]
                if pattern[j] == s:
                    j += 1
                if j == len(pattern):
                    return True
            return False
            
        res = []
        for i, pattern in enumerate(words):
            prefix = getPrefix(pattern)
            for j, word in enumerate(words):
                if j != i and kmp(word, pattern, prefix):
                    res += pattern, 
                    break
        return res


class Solution:
    def stringMatching(self, words: List[str]) -> List[str]:
        def add(word: str):
            node = trie
            for c in word:
                node = node.setdefault(c, {})

        def get(word: str) -> bool:
            node = trie
            for c in word:
                if (node := node.get(c)) is None: return False
            return True

        words.sort(key=len, reverse=True)
        trie, result = {}, []
        for word in words:
            if get(word): result.append(word)
            for i in range(len(word)):
                add(word[i:])
        return result


# Time:  O(n + m + z) = O(n), n is the total size of patterns
#                           , m is the total size of query string
#                           , z is the number of all matched strings
#                           , O(n) = O(m) = O(z) in this problem
# Space: O(t), t is the total size of ac automata trie

import collections

class AhoNode(object):
    def __init__(self):
        self.children = collections.defaultdict(AhoNode)
        self.indices = []
        self.suffix = None
        self.output = None
        
class AhoTrie(object):

    def step(self, letter):
        while self.__node and letter not in self.__node.children:
            self.__node = self.__node.suffix
        self.__node = self.__node.children[letter] if self.__node else self.__root
        return self.__get_ac_node_outputs(self.__node)
    
    def reset(self):
        self.__node = self.__root
    
    def __init__(self, patterns):
        self.__root = self.__create_ac_trie(patterns)
        self.__node = self.__create_ac_suffix_and_output_links(self.__root)
    
    def __create_ac_trie(self, patterns):  # Time:  O(n), Space: O(t)
        root = AhoNode()
        for i, pattern in enumerate(patterns):
            node = root
            for c in pattern:
                node = node.children[c]
            node.indices.append(i)
        return root

    def __create_ac_suffix_and_output_links(self, root):  # Time:  O(n), Space: O(t)
        queue = collections.deque()
        for node in root.children.values():
            queue.append(node)
            node.suffix = root

        while queue:
            node = queue.popleft()
            for c, child in node.children.items():
                queue.append(child)
                suffix = node.suffix
                while suffix and c not in suffix.children:
                    suffix = suffix.suffix
                child.suffix = suffix.children[c] if suffix else root
                child.output = child.suffix if child.suffix.indices else child.suffix.output
                
        return root

    def __get_ac_node_outputs(self, node):  # Time:  O(z)
        result = []
        for i in node.indices:
            result.append(i)
        output = node.output
        while output:
            for i in output.indices:
                result.append(i)
            output = output.output
        return result
    
    
class Solution(object):
    def stringMatching(self, words):
        """
        :type words: List[str]
        :rtype: List[str]
        """
        trie = AhoTrie(words)
        lookup = set()
        for i in range(len(words)):
            trie.reset()
            for c in words[i]:
                for j in trie.step(c):
                    if j != i:
                        lookup.add(j)
        return [words[i] for i in lookup]
