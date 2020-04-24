class Solution:
    def entityParser(self, text: str) -> str:
        dic = {"&quot;":"\"", "&apos;":"'", "&amp;": "&","&gt;":">", "&lt;":"<", "&frasl;": "/"}
        for i, v in dic.items():
            text = text.replace(i,v)
        return text

# Time:  O(n)
# Space: O(1)
class Solution2(object):
    def entityParser(self, text):
        """
        :type text: str
        :rtype: str
        """
        patterns = ["&quot;", "&apos;", "&amp;", "&gt;", "&lt;", "&frasl;"]
        chars = ["\"", "'", "&", ">", "<", "/"]
        result = []
        i, j = 0, 0
        while i != len(text):
            if text[i] != '&':                    
                result.append(text[i])
                i += 1
            else:
                for j, pattern in enumerate(patterns):
                    if pattern == text[i:i+len(pattern)]:
                        result.append(chars[j])
                        i += len(pattern)
                        break
                else:
                    result.append(text[i])
                    i += 1
        return "".join(result)


class Solution:
    def entityParser(self, text: str) -> str:
        entities = [('&quot;', '\"'),  ('&apos;', '\''), ('&gt;', '>'), ('&lt;', '<'), ('&frasl;', '/'),('&amp;', '&')]
                        
        for pat, repl in entities:
            text = re.sub(pat, repl,text)
                
        return text

class Solution:
    def entityParser(self, text: str) -> str:
        replaceDict={"&quot;":'"',"&apos;":"'","&amp;":"&","&gt;":">","&lt;":"<","&frasl;":"/"}
        replaceMode=False
        keyword=[]
        out=[]
        for c in text:
            if c=="&":
                replaceMode=True
                keyword=["&"]
            elif replaceMode:
                keyword.append(c)
                if c==";":
                    keyword=''.join(keyword)
                    out.append(replaceDict.get(keyword,keyword)) #if it wasn't found in dict, just add the existing word
                    replaceMode=False
            else:
                out.append(c)
        if replaceMode:
            out+=keyword
        return ''.join(out)


# Suffix Trie
class Solution:
    def entityParser(self, text: str) -> str:
        def add(entity: str, symbol: str):
            node = trie
            for c in entity:
                node = node.setdefault(c, {})
            node['#'] = symbol

        def check(idx: int) -> tuple:
            node = trie
            while text[idx] in node:
                node = node[text[idx]]
                idx += 1
                if '#' in node: return node['#'], idx
            return False, idx

        def parse():
            i = 0
            while i < len(text):
                if text[i] in trie:
                    symbol, j = check(i)
                    yield symbol or text[i:j]
                    i = j
                else:
                    yield text[i]
                    i += 1

        trie = {}
        entities = [('&quot;', '"'), ('&apos;', "'"), ('&amp;', '&'), ('&gt;', '>'), ('&lt;', '<'), ('&frasl;', '/')]
        for entity, symbol in entities:
            add(entity, symbol)
        return ''.join(parse())


# Time:  O(n + m + z) = O(m), n is the total size of patterns
#                           , m is the total size of query string
#                           , z is the number of all matched strings
#                           , O(n) = O(1), O(z) = O(m) in this problem
# Space: O(t) = O(1), t is the total size of ac automata trie
#                   , O(t) = O(1) in this problem

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
