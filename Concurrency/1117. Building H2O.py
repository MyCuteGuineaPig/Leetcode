import threading
class H2O:
    def __init__(self):
        self.cv = threading.Condition()
        self.h = 0


    def hydrogen(self, releaseHydrogen: 'Callable[[], None]') -> None:
        
        with self.cv:
            while self.h >= 2:
                self.cv.wait()
            
            # releaseHydrogen() outputs "H". Do not change or remove this line.
            releaseHydrogen()
            self.h += 1
            self.cv.notifyAll()


    def oxygen(self, releaseOxygen: 'Callable[[], None]') -> None:
        
        with self.cv:
            while self.h < 2: #可以改为 self.h < 1  也可以
                self.cv.wait()
            
            # releaseOxygen() outputs "O". Do not change or remove this line.
            releaseOxygen()
            self.h -= 2
            self.cv.notifyAll()




class H2O:
    def __init__(self):
        self.b = Barrier(3)
        self.h = Semaphore(2)
        self.o = Semaphore(1)

    def hydrogen(self, releaseHydrogen):
        with self.h:
            self.b.wait()
            releaseHydrogen()

    def oxygen(self, releaseOxygen):
        with self.o:
            self.b.wait()
            releaseOxygen()


from threading import Barrier, Semaphore
class H2O:
    def __init__(self):
        self.b = Barrier(3)
        self.h = Semaphore(2)
        self.o = Semaphore(1)

    def hydrogen(self, releaseHydrogen: 'Callable[[], None]') -> None:
        self.h.acquire()
		self.b.wait()
        # releaseHydrogen() outputs "H". Do not change or remove this line.
        releaseHydrogen()
        self.h.release()

    def oxygen(self, releaseOxygen: 'Callable[[], None]') -> None:
        self.o.acquire()
		self.b.wait()
        # releaseOxygen() outputs "O". Do not change or remove this line.
        releaseOxygen()
        self.o.release()