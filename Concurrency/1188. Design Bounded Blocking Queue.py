"""
the notify() and notifyAll() methods don’t release the lock; 
this means that the thread or threads awakened will not return from their wait() call immediately, 
but only when the thread that called notify() or notifyAll() finally relinquishes ownership of the lock.


不能put self.cv.notify outside with self.cv:  比如

        with self.cv:
            while self.count == self.capa:
                self.cv.wait()
            self.q.append(element)
            self.count += 1
        self.cv.notify()   不可以

因为 可能 thread 1 -> release lock;  thread 2-> acquire lock;   thread 1 -> notify thread 2 -> wait ,造成thread 2 miss the notify 

https://stackoverflow.com/questions/46076186/why-does-python-threading-condition-notify-require-a-lock


假如notify after releasel lock 有三个thread, 一个producer, 两个consuemer; cause a scheduling priority inversion; 在wait 的会后执行


The following sequence may occur:

P                         LC                       HC
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
              execute(item)（not wait)            (in wait())
lock()                                  
wq.push(item)
release()
                     acquire()
                     item = wq.pop()
                     release();
notify()
                                                     (wake-up)
                                                     while (wq.empty())
                                                       wait();

Whereas if the notify() happened before release(), LC wouldn't have been able to acquire() before HC had been woken-up. 
This is where the priority inversion occurred. This is the second argument.

In Python, you MUST HOLD the lock while notifying. The internal implementation does not allow the underlying OS to avoid priority inversion
, because it enforces a FIFO order on the waiters. 

The developers of the Python threading module might have specifically wanted a FIFO order for some reason, 
and found that this was somehow the best way of achieving it,
and wanted to establish that as a `Condition` at the expense of the other (probably more prevalent) approaches. 

"""


import threading
class BoundedBlockingQueue(object):
    def __init__(self, capacity: int):
        self.__size = capacity
        self.__q = Deque()
        self.cond = threading.Condition()

    def enqueue(self, element: int) -> None:
        with self.cond:
            self.cond.wait_for(lambda: len(self.__q) < self.__size)
            self.__q.appendleft(element)
            self.cond.notifyAll()

    def dequeue(self) -> int:
        with self.cond:
            self.cond.wait_for(lambda: len(self.__q) != 0)
            ret = self.__q.pop()
            self.cond.notifyAll()
            return ret

    def size(self) -> int:
        with self.cond:
            return len(self.__q)
        
## Semaphore
import threading
class BoundedBlockingQueue(object):

    def __init__(self, capacity: int):
        self.__q = Deque()
        self.pushing = threading.Semaphore(capacity)
        # self.lock = threading.Lock()  
        # deques are threadsafe, no need lock
        self.pulling = threading.Semaphore(0)

    def enqueue(self, element: int) -> None:
        self.pushing.acquire()
        self.__q.appendleft(element)
        self.pulling.release()

    def dequeue(self) -> int:
        self.pulling.acquire()
        val = self.__q.pop()
        self.pushing.release()
        return val

    def size(self) -> int:
        return len(self.__q)
        

import threading

class BoundedBlockingQueue(object):
    def __init__(self, capacity: int):
        self.capacity = capacity
        
        self.pushing = threading.Semaphore(capacity)
        self.pulling = threading.Semaphore(0)
        self.editing = threading.Lock()
      
        self.queue = collections.deque()

    def enqueue(self, element: int) -> None:
      self.pushing.acquire()
      self.editing.acquire()
      
      self.queue.append(element)
      
      self.editing.release()
      self.pulling.release()

    def dequeue(self) -> int:
        self.pulling.acquire()
        self.editing.acquire()
        
        res = self.queue.popleft()
        
        self.editing.release()
        self.pushing.release()
        return res

    def size(self) -> int:
      return len(self.queue)



##3 Lock
class BoundedBlockingQueue(object):

    def __init__(self, capacity: int):
        self.en, self.de = Lock(), Lock()
        self.q = deque()
        self.capacity = capacity
        self.de.acquire()

    def enqueue(self, element: int) -> None:
        self.en.acquire()
        self.q.append(element)
        if len(self.q) < self.capacity:
            self.en.release()
        if self.de.locked():
            self.de.release()

    def dequeue(self) -> int:
        self.de.acquire()
        val = self.q.popleft()
        if len(self.q):
            self.de.release()
        if val and self.en.locked():
            self.en.release()
        return val
        
    def size(self) -> int:
        return len(self.q)