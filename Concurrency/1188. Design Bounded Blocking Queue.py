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
              execute(item)（not wait            (in wait())
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
        self.cv = threading.Condition()
        self.q = collections.deque()
        self.capa = capacity
        self.count = 0

    def enqueue(self, element: int) -> None:
        with self.cv:
            while self.count == self.capa:
                self.cv.wait()
            self.q.append(element)
            self.count += 1
            self.cv.notify()

    def dequeue(self) -> int:
        val = 0
        with self.cv:
            while self.count == 0:
                self.cv.wait()
            val = self.q.popleft()
            self.count -= 1
            self.cv.notify()
        return val
            
    def size(self) -> int:
        with self.cv:
            return len(self.q)




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




