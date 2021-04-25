Trie = lambda: collections.defaultdict(Trie)

class FileSystem(object):
    def __init__(self):
        self.fs = Trie()
        self.fileinfo = collections.defaultdict(str)
        
    def ls(self, path):
        if path in self.fileinfo:
            return path.split('/')[-1:] #return last element as a list

        cur = self.fs
        for token in path.split('/'):
            if token in cur:
                cur = cur[token]
            elif token: # '/abc' split => ['','abc']
                return []

        return sorted(cur.keys())

    def mkdir(self, path):
        cur = self.fs
        for token in path.split('/'):
            if token: cur = cur[token]

    def addContentToFile(self, filePath, content):
        self.mkdir(filePath)
        self.fileinfo[filePath] += content

    def readContentFromFile(self, filePath):
        return self.fileinfo[filePath]



class Node(object):
    def __init__(self):
        self.children = {}
        
    def setdefault(self, token):
        return self.children.setdefault(token, Node())
        
    def get(self, token):
        return self.children.get(token, None)
                          
class FileSystem(object):
    def __init__(self):
        self.root = Node()
        self.fileinfo = collections.defaultdict(str)
        
    def ls(self, path):
        if path in self.fileinfo:
            return path.split('/')[-1:]

        cur = self.root
        for token in path.split('/'):
            if cur and token:
                cur = cur.get(token)

        return sorted(cur.children.keys()) if cur else []

    def mkdir(self, path):
        cur = self.root
        for token in path.split('/'):
            if token: cur = cur.setdefault(token)



from collections import defaultdict
class Node:
    def __init__(self):
        self.child=defaultdict(Node)
        self.content=""
        
class FileSystem(object):

    def __init__(self):
        self.root=Node()
        
    def find(self,path):#find and return node at path.
        curr=self.root
        if len(path)==1:
            return self.root
        for word in path.split("/")[1:]:
            curr=curr.child[word]
        return curr
        
    def ls(self, path):
        curr=self.find(path)
        if curr.content:#file path,return file name
            return [path.split('/')[-1]]
        return sorted(curr.child.keys())
		
    def mkdir(self, path):
        self.find(path)

    def addContentToFile(self, filePath, content):
        curr=self.find(filePath)
        curr.content+=content

    def readContentFromFile(self, filePath):
        curr=self.find(filePath)
        return curr.content