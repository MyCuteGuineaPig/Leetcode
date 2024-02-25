## 1. condition 
import threading
class FooBar:
    def __init__(self, n):
        self.n = n
        self.cv = threading.Condition()
        self.isFoo = True

    def foo(self, printFoo: 'Callable[[], None]') -> None:
        
        for i in range(self.n):
            with self.cv:
                self.cv.wait_for(lambda: self.isFoo)
                # printFoo() outputs "foo". Do not change or remove this line.
                printFoo()
                self.isFoo = not self.isFoo
                self.cv.notify();

    def bar(self, printBar: 'Callable[[], None]') -> None:
        
        for i in range(self.n):
            with self.cv:
                self.cv.wait_for(lambda: not self.isFoo)
                # printBar() outputs "bar". Do not change or remove this line.
                printBar()
                self.isFoo = not self.isFoo
                self.cv.notify();


## 2. event
import threading
class FooBar:
    def __init__(self, n):
        self.n = n
        self.e = (threading.Event(), threading.Event())
        self.e[0].set()

    def foo(self, printFoo: 'Callable[[], None]') -> None:
        
        for i in range(self.n):
            self.e[0].wait()
            # printFoo() outputs "foo". Do not change or remove this line.
            printFoo()
            self.e[1].set()
            self.e[0].clear()

    def bar(self, printBar: 'Callable[[], None]') -> None:
        
        for i in range(self.n):
            self.e[1].wait()
            printBar()
            self.e[0].set()
            self.e[1].clear()

    
## 3. Barrier
"""

The barrier solution seems to work on the online judge but failed on my machine. 
From a theoretical point of view, I believe it is incorrect because once both threads reach the barrier 

https://leetcode.com/problems/print-foobar-alternately/solutions/336629/5-python-threading-solutions-barrier-event-condition-lock-semaphore-with-explanation/comments/400635
"""
class FooBar:
    def __init__(self, n):
        self.n = n
        self.barrier = threading.Barrier(2)
        self.isFoo = True
        
    def foo(self, printFoo: 'Callable[[], None]') -> None:
        for i in range(self.n):
            printFoo()
            self.barrier.wait()


    def bar(self, printBar: 'Callable[[], None]') -> None:
        for i in range(self.n):
            self.barrier.wait()
            printBar()

##4.  Semaphore
## acquire decrement value, 直到0, block thread
## release increment value  
class FooBar:
    def __init__(self, n):
        self.n = n
        self.semaphore = [threading.Semaphore(1), threading.Semaphore(0)]
        
    def foo(self, printFoo: 'Callable[[], None]') -> None:
        for i in range(self.n):
            self.semaphore[0].acquire()
            printFoo()
            self.semaphore[1].release()
                


    def bar(self, printBar: 'Callable[[], None]') -> None:
        for i in range(self.n):
            self.semaphore[1].acquire()
            printBar()
            self.semaphore[0].release()

##5. Lock
"""
锁有两种状态： locked（被某一线程拿到）和unlocked（可用状态）
我们有两个方法来操作锁： acquire() 和 release()

如果状态是unlocked， 可以调用 acquire() 将状态改为locked
如果状态是locked， acquire() 会被block直到另一线程调用 release() 释放锁
如果状态是unlocked， 调用 release() 将导致 RuntimError 异常
如果状态是locked， 可以调用 release() 将状态改为unlocked

https://python-parallel-programmning-cookbook.readthedocs.io/zh-cn/latest/chapter2/06_Thread_synchronization_with_Lock_and_Rlock.html
"""
class FooBar:
    def __init__(self, n):
        self.n = n
        self.locks = [threading.Lock(), threading.Lock()] #初始是unlock的状态
        self.locks[1].acquire()

    def foo(self, printFoo: 'Callable[[], None]') -> None:
        for i in range(self.n):
            self.locks[0].acquire()
            printFoo()
            self.locks[1].release()


    def bar(self, printBar: 'Callable[[], None]') -> None:
        for i in range(self.n):
            self.locks[1].acquire()
            printBar()
            self.locks[0].release()
        	