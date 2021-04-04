import threading
class Foo:
    def __init__(self):
        self.cv = threading.Condition()
        self.n = 0
        self.waitone = lambda :  self.n == 1
        self.waittwo = lambda :  self.n == 2
        
    def first(self, printFirst: 'Callable[[], None]') -> None:
        with self.cv:
            # printFirst() outputs "first". Do not change or remove this line.
            printFirst()
            self.n += 1
            self.cv.notifyAll();

    def second(self, printSecond: 'Callable[[], None]') -> None:
        with self.cv:
            self.cv.wait_for(self.waitone)
            # printSecond() outputs "second". Do not change or remove this line.
            printSecond()
            self.n += 1
            self.cv.notifyAll();


    def third(self, printThird: 'Callable[[], None]') -> None:
        with self.cv: 
            self.cv.wait_for(self.waittwo)
            # printThird() outputs "third". Do not change or remove this line.
            printThird()
        

from threading import Barrier

class Foo:
    def __init__(self):
        self.first_barrier = Barrier(2)
        self.second_barrier = Barrier(2)
            
    def first(self, printFirst):
        printFirst()
        self.first_barrier.wait()
        
    def second(self, printSecond):
        self.first_barrier.wait()
        printSecond()
        self.second_barrier.wait()
            
    def third(self, printThird):
        self.second_barrier.wait()
        printThird()



class Foo:
    def __init__(self):
        self.locks = (Lock(),Lock())
        self.locks[0].acquire()
        self.locks[1].acquire()
        
    def first(self, printFirst):
        printFirst()
        self.locks[0].release()
        
    def second(self, printSecond):
        with self.locks[0]:
            printSecond()
            self.locks[1].release()
            
            
    def third(self, printThird):
        with self.locks[1]:
            printThird()

"""

 An event manages a flag that can be set to true with the set() method and
  reset to false with the clear() method. 
  The wait() method blocks until the flag is true. The flag is initially false.


"""

from threading import Event

class Foo:
    def __init__(self):
        self.done = (Event(),Event())
        
    def first(self, printFirst):
        printFirst()
        self.done[0].set()
        
    def second(self, printSecond):
        self.done[0].wait()
        printSecond()
        self.done[1].set()
            
    def third(self, printThird):
        self.done[1].wait()
        printThird()



from threading import Semaphore

class Foo:
    def __init__(self):
        self.gates = (Semaphore(0),Semaphore(0))
        
    def first(self, printFirst):
        printFirst()
        self.gates[0].release()
        
    def second(self, printSecond):
        with self.gates[0]:
            printSecond()
            self.gates[1].release()
            
    def third(self, printThird):
        with self.gates[1]:
            printThird()




from threading import Condition

class Foo:
    def __init__(self):
        self.exec_condition = Condition()
        self.order = 0
        self.first_finish = lambda: self.order == 1
        self.second_finish = lambda: self.order == 2

    def first(self, printFirst):
        with self.exec_condition:
            printFirst()
            self.order = 1
            self.exec_condition.notify(2)

    def second(self, printSecond):
        with self.exec_condition:
            self.exec_condition.wait_for(self.first_finish)
            printSecond()
            self.order = 2
            self.exec_condition.notify()

    def third(self, printThird):
        with self.exec_condition:
            self.exec_condition.wait_for(self.second_finish)
            printThird()