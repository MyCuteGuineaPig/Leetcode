## 1. Condition 
import threading
class ZeroEvenOdd:
    def __init__(self, n):
        self.n = n
        self.cv = threading.Condition()
        self.cnt = 0
        
	# printNumber(x) outputs "x", where x is an integer.
    def zero(self, printNumber: 'Callable[[int], None]') -> None:
        for i in range(self.n):
            with self.cv:
                self.cv.wait_for(lambda: self.cnt % 2 == 0)
                printNumber(0)
                self.cnt += 1
                self.cv.notify(2)
        
        
    def even(self, printNumber: 'Callable[[int], None]') -> None:
        for i in range(2, self.n+1, 2):
            with self.cv:
                self.cv.wait_for(lambda: self.cnt % 4 == 3)
                printNumber(i)
                self.cnt += 1
                self.cv.notify(2) 

        
        
    def odd(self, printNumber: 'Callable[[int], None]') -> None:
        for i in range(1, self.n + 1, 2):
            with self.cv:
                self.cv.wait_for(lambda: self.cnt % 4 == 1)
                printNumber(i)
                self.cnt += 1
                self.cv.notify(2)

## 2. Lock()
import threading
class ZeroEvenOdd:
    def __init__(self, n):
        self.n = n
        self.lock1, self.lock2, self.lock3 = threading.Lock(),threading.Lock(),threading.Lock()
        self.lock2.acquire()
        self.lock3.acquire()
        self.cnt = 0
        
        
	# printNumber(x) outputs "x", where x is an integer.
    def zero(self, printNumber: 'Callable[[int], None]') -> None:
        for i in range(self.n):
            self.lock1.acquire()
            printNumber(0)
            if self.cnt % 2 == 0:
                self.lock2.release()
            else:
                self.lock3.release()
            self.cnt += 1
        
        
    def even(self, printNumber: 'Callable[[int], None]') -> None:
        for i in range(2, self.n+1, 2):
            self.lock3.acquire()
            printNumber(i)
            self.lock1.release()
        
        
    def odd(self, printNumber: 'Callable[[int], None]') -> None:
        for i in range(1, self.n + 1, 2):
            self.lock2.acquire()
            printNumber(i)
            self.lock1.release()

## 3. event 
import threading
class ZeroEvenOdd:
    def __init__(self, n):
        self.n = n
        self.event1, self.event2, self.event3 = threading.Event(),threading.Event(),threading.Event()
        self.event1.set()
        self.cnt = 0
        
    def zero(self, printNumber: 'Callable[[int], None]') -> None:
        for i in range(self.n):
            self.event1.wait()
            printNumber(0)
            if self.cnt % 2 == 0:
                self.event2.set()
            else:
                self.event3.set()
            self.cnt += 1
            self.event1.clear()
        
    def even(self, printNumber: 'Callable[[int], None]') -> None:
        for i in range(2, self.n+1, 2):
            self.event3.wait()
            printNumber(i)
            self.event1.set()
            self.event3.clear()
        
    def odd(self, printNumber: 'Callable[[int], None]') -> None:
        for i in range(1, self.n + 1, 2):
            self.event2.wait()
            printNumber(i)
            self.event1.set()
            self.event2.clear()


## 4. Semaphore 
import threading
class ZeroEvenOdd:
    def __init__(self, n):
        self.n = n
        self.sem1, self.sem2, self.sem3  = threading.Semaphore(1), threading.Semaphore(0), threading.Semaphore(0)
        self.cnt = 0
        
        
	# printNumber(x) outputs "x", where x is an integer.
    def zero(self, printNumber: 'Callable[[int], None]') -> None:
        for i in range(self.n):
            self.sem1.acquire()
            printNumber(0)
            if self.cnt % 2 == 0:
                self.sem3.release()
            else:
                self.sem2.release()
            self.cnt += 1
        
        
    def even(self, printNumber: 'Callable[[int], None]') -> None:
        for i in range(2, self.n+1, 2):
            self.sem2.acquire()
            printNumber(i)
            self.sem1.release()
        
        
    def odd(self, printNumber: 'Callable[[int], None]') -> None:
        for i in range(1, self.n + 1, 2):
            self.sem3.acquire()
            printNumber(i)
            self.sem1.release()
        

from threading import Semaphore
class ZeroEvenOdd:
    def __init__(self, n):
        self.n = n
        self.ct = 0
        self.gates = [Semaphore(),Semaphore(),Semaphore()]
        self.gates[0].acquire()
        self.gates[1].acquire()
        
     def zero(self, printNumber):
        for _ in range(self.n):
            self.gates[2].acquire()
            printNumber(0)
            self.ct += 1
            self.gates[self.ct % 2].release()
        
    def even(self, printNumber):
        for _ in range(self.n//2):
            self.gates[0].acquire()
            printNumber(self.ct)
            self.gates[2].release()
        
    def odd(self, printNumber):
        for _ in range((self.n+1)//2):
            self.gates[1].acquire()
            printNumber(self.ct)
            self.gates[2].release()


## 5.Barrier
from threading import Barrier, Lock
class ZeroEvenOdd:
    def __init__(self, n):
        self.n = n
        self.ct = 0
        self.barriers = [Barrier(2),Barrier(2)]
        self.zero_lock = Lock()

    def zero(self, printNumber):
        for _ in range(self.n):
            self.zero_lock.acquire()
            printNumber(0)
            self.ct += 1
            self.barriers[self.ct % 2].wait()
        
    def even(self, printNumber):
        for _ in range(self.n//2):
            self.barriers[0].wait()
            printNumber(self.ct)
            self.zero_lock.release()
        
    def odd(self, printNumber):
        for _ in range((self.n+1)//2):
            self.barriers[1].wait()
            printNumber(self.ct)
            self.zero_lock.release()


        