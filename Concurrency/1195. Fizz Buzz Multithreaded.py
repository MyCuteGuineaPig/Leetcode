import threading
class FizzBuzz:
    def __init__(self, n: int):
        self.n = n
        self.cv = threading.Condition()
        self.count = 1

    # printFizz() outputs "fizz"
    def fizz(self, printFizz: 'Callable[[], None]') -> None:
        while True:
            with self.cv:
                while (self.count % 3 != 0 or self.count % 5 ==0)  and self.count <= self.n:
                    self.cv.wait()
                if self.count > self.n:
                    return
                printFizz()
                self.count +=  1
                self.cv.notifyAll()

    # printBuzz() outputs "buzz"
    def buzz(self, printBuzz: 'Callable[[], None]') -> None:
        while True:
            with self.cv:
                while (self.count % 3 == 0 or self.count % 5 !=0)  and self.count <= self.n:
                    self.cv.wait()
                if self.count > self.n:
                    return
                printBuzz()
                self.count +=  1
                self.cv.notifyAll()

    # printFizzBuzz() outputs "fizzbuzz"
    def fizzbuzz(self, printFizzBuzz: 'Callable[[], None]') -> None:
        while True:
            with self.cv:
                while (self.count % 3 != 0 or self.count % 5 !=0 ) and self.count <= self.n:
                    self.cv.wait()
                if self.count > self.n:
                    return
                printFizzBuzz()
                self.count +=  1
                self.cv.notifyAll()

    # printNumber(x) outputs "x", where x is an integer.
    def number(self, printNumber: 'Callable[[int], None]') -> None:
        while True:
            with self.cv:
                while (self.count % 3 == 0 or self.count % 5 ==0)  and self.count <= self.n:
                    self.cv.wait()
                if self.count > self.n:
                    return
                printNumber(self.count)
                self.count +=  1
                self.cv.notifyAll()



import threading

class FizzBuzz:
    def __init__(self, n):
        self.n = n
        self.f = threading.Lock()
        self.b = threading.Lock()
        self.fb = threading.Lock()
        self.main = threading.Lock()        
        self.f.acquire()
        self.b.acquire()
        self.fb.acquire()

    # printFizz() outputs "fizz"
    def fizz(self, printFizz):
        for i in range (self.n // 3 - self.n // 15):
            self.f.acquire()
            printFizz()
            self.main.release()
            
    # printBuzz() outputs "buzz"
    def buzz(self, printBuzz):
        for i in range (self.n // 5 - self.n // 15):
            self.b.acquire()
            printBuzz()
            self.main.release()

    # printFizzBuzz() outputs "fizzbuzz"
    def fizzbuzz(self, printFizzBuzz):
        for i in range (self.n // 15):
            self.fb.acquire()
            printFizzBuzz()
            self.main.release()        

    # printNumber(x) outputs "x", where x is an integer.
    def number(self, printNumber):
        for i in range(1, self.n + 1):         
            self.main.acquire()        
            if i % 15 == 0:
                self.fb.release()
            elif i % 3 == 0:
                self.f.release()
            elif i % 5 == 0:
                self.b.release()
            else:
                printNumber(i)
                self.main.release()   






import threading

class FizzBuzz:
    def __init__(self, n: int):      
        self.n = n
        self.f = threading.Lock()
        self.b = threading.Lock()
        self.fb = threading.Lock()
        self.f.acquire()
        self.b.acquire()
        self.fb.acquire()
        self.main = threading.Lock()

    # printFizz() outputs "fizz"
    def fizz(self, printFizz: 'Callable[[], None]') -> None:
        while True:
            self.f.acquire()
            if self.n == 0 :
                return
            printFizz()
            self.main.release()

    # printBuzz() outputs "buzz"
    def buzz(self, printBuzz: 'Callable[[], None]') -> None:
        while True:
            self.b.acquire()
            if self.n == 0:
                return
            printBuzz()
            self.main.release()

    # printFizzBuzz() outputs "fizzbuzz"
    def fizzbuzz(self, printFizzBuzz: 'Callable[[], None]') -> None:
        while True:
            self.fb.acquire()
            if self.n == 0:
                return
            printFizzBuzz()
            self.main.release()

    # printNumber(x) outputs "x", where x is an integer.
    def number(self, printNumber: 'Callable[[int], None]') -> None:
        for i in range(1, self.n+1):
            #print("number:",i)
            self.main.acquire()
            if i % 15 == 0:
                self.fb.release()
            elif i % 3 == 0:
                self.f.release()
            elif i % 5 == 0:
                self.b.release()
            else:
                printNumber(i)
                self.main.release()

        self.main.acquire() 
        self.n = 0
        self.f.release()
        self.b.release()
        self.fb.release()
        return
