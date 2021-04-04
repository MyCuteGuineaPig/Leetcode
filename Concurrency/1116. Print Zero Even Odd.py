import threading

class ZeroEvenOdd:
    def __init__(self, n):
        self.n = n
        self.cv = threading.Condition()
        self.cur = 1
        
	# printNumber(x) outputs "x", where x is an integer.
    def zero(self, printNumber: 'Callable[[int], None]') -> None:
        while True:
            with self.cv:
                self.cv.wait_for(lambda: self.cur % 2 == 1 or self.cur > 2*self.n)
                if self.cur > 2*self.n:
                    return
                printNumber(0)
                self.cur += 1
                self.cv.notifyAll()
        
        
    def even(self, printNumber: 'Callable[[int], None]') -> None:
        while True:
            with self.cv:
                self.cv.wait_for(lambda: self.cur % 4 == 0 or self.cur > 2*self.n)
                if self.cur > 2*self.n:
                    return
                printNumber(self.cur//2)
                self.cur += 1
                self.cv.notifyAll()

        
    def odd(self, printNumber: 'Callable[[int], None]') -> None:
        while True:
            with self.cv:
                self.cv.wait_for(lambda: self.cur % 4 == 2 or self.cur > 2*self.n)
                if self.cur > 2*self.n:
                    return
                printNumber(self.cur//2)
                self.cur += 1
                self.cv.notifyAll()
        


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

            

from threading import Lock

class ZeroEvenOdd:
    def __init__(self, n):
        self.n = n
        self.ct = 0
        self.gates = [Lock(),Lock(),Lock()]
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


from threading import Event

class ZeroEvenOdd:
    def __init__(self, n):
        self.n = n
        self.ct = 0
        self.print = [Event(),Event(),Event()]
        self.print[2].set()
        
    def zero(self, printNumber):
        for _ in range(self.n):
            self.print[2].wait()
            self.print[2].clear()
            printNumber(0)
            self.ct += 1
            self.print[self.ct % 2].set()
        
    def even(self, printNumber):
        for _ in range(self.n//2):
            self.print[0].wait()
            self.print[0].clear()
            printNumber(self.ct)
            self.print[2].set()
        
    def odd(self, printNumber):
        for _ in range((self.n+1)//2):
            self.print[1].wait()
            self.print[1].clear()
            printNumber(self.ct)
            self.print[2].set()