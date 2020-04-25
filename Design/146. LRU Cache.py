#python OrderedDict
class LRUCache:
    
    def __init__(self, capacity: int):
        self.cache = collections.OrderedDict()
        self.capacity = capacity

    def get(self, key: int) -> int:
        if key not in self.cache:
            return -1
        val = self.cache.pop[key]
        self.cache[key] = val
        return val

    def put(self, key: int, value: int) -> None:
        if key in self.cache:
            del self.cache[key]
        elif len(self.cache) == self.capacity:
            self.cache.popitem(last = False)
        self.cache[key] = value



class LRUCache:
    def __init__(self, MSize):
        self.size = MSize
        self.cache = {}
        self.next, self.before = {}, {}
        self.head, self.tail = '#', '$'
        self.connect(self.head, self.tail)

    def connect(self, a, b):
        self.next[a], self.before[b] = b, a

    def delete(self, key):
        self.connect(self.before[key], self.next[key])
        del self.before[key], self.next[key], self.cache[key]

    def append(self, k, v):
        self.cache[k] = v
        self.connect(self.before[self.tail], k)
        self.connect(k, self.tail)
        if len(self.cache) > self.size:
            self.delete(self.next[self.head])

    def get(self, key):
        if key not in self.cache: return -1
        val = self.cache[key]
        self.delete(key)
        self.append(key, val)
        return val

    def put(self, key, value):
        if key in self.cache: self.delete(key)
        self.append(key, value)






#Push in tail, delete from head
class ListNode:
    def __init__(self,key, val):
        self.key = key
        self.val = val
        self.next = None 
        self.prev = None 
        
class LinkedList:
    def __init__(self,):
        self.head = None 
        self.tail = None 
        
    def insert(self, node):
        node.next, node.prev = None, None 
        if self.head:
            self.tail.next = node 
            node.prev = self.tail
        else:
            self.head = node 
        self.tail = node
        
    def delete(self,node):
        if node.prev:
            node.prev.next = node.next 
        else:
            self.head = node.next 
        if node.next:
            node.next.prev = node.prev
        else:
            self.tail = node.prev
        node.next, node.prev = None, None 

        

class LRUCache:

    def __init__(self, capacity: int):
        self.List = LinkedList()
        self.dic = {}
        self.capacity = capacity
 
    def __insert(self,key, val):
        if key in self.dic:
            self.List.delete(self.dic[key])
        node = ListNode(key,val)
        self.List.insert(node)
        self.dic[key] = node

    def get(self, key: int) -> int:
        if key not in self.dic:
            return -1
        val = self.dic[key].val
        self.__insert(key, val)
        return val

    def put(self, key: int, value: int) -> None:
        if len(self.dic) == self.capacity and key not in self.dic:
            #print("del ",self.List.head.key)
            del self.dic[self.List.head.key]
            self.List.delete(self.List.head)
        self.__insert(key,value)


#Push in head, delete from tail
class ListNode:
    def __init__(self,key, val):
        self.key = key
        self.val = val
        self.next = None 
        self.prev = None 
        
class LinkedList:
    def __init__(self,):
        self.head = None 
        self.tail = None 
        
    def insert(self, node):
        node.next, node.prev = None, None 
        if not self.tail:
            self.tail = node
        if self.head:
            node.next = self.head
            self.head.prev = node
        self.head = node 
        
    def delete(self,node):
        if node.prev:
            node.prev.next = node.next 
        else:
            self.head = node.next 
        if node.next:
            node.next.prev = node.prev
        else:
            self.tail = node.prev
        node.next, node.prev = None, None 

        

class LRUCache:

    def __init__(self, capacity: int):
        self.List = LinkedList()
        self.dic = {}
        self.capacity = capacity
 
    def __insert(self,key, val):
        if key in self.dic:
            self.List.delete(self.dic[key])
        node = ListNode(key,val)
        self.List.insert(node)
        self.dic[key] = node

    def get(self, key: int) -> int:
        if key not in self.dic:
            return -1
        val = self.dic[key].val
        self.__insert(key, val)
        return val

    def put(self, key: int, value: int) -> None:
        if len(self.dic) == self.capacity and key not in self.dic:
            #print("del ",self.List.tail.key)
            del self.dic[self.List.tail.key]
            self.List.delete(self.List.tail)
        self.__insert(key,value)
    