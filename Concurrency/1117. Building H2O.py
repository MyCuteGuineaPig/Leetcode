## 1. Condition 
class H2O:
    def __init__(self):
        self.cv = threading.Condition()
        self.cnt = 0 
        

    def hydrogen(self, releaseHydrogen: 'Callable[[], None]') -> None:
        
        with self.cv: 
            self.cv.wait_for(lambda: self.cnt != 2)
         # releaseHydrogen() outputs "H". Do not change or remove this line.
            releaseHydrogen()
            self.cnt += 1
            self.cv.notify(2)



    def oxygen(self, releaseOxygen: 'Callable[[], None]') -> None:
        with self.cv:
            self.cv.wait_for(lambda: self.cnt == 2)
            self.cnt -=2
        # releaseOxygen() outputs "O". Do not change or remove this line.
            releaseOxygen()
            self.cv.notify(2)


## 2. Lock 
class H2O:
    def __init__(self):
        self.lock1, self.lock2 = threading.Lock(), threading.Lock()
        self.cnt = 0 
        self.lock2.acquire()
        

    def hydrogen(self, releaseHydrogen: 'Callable[[], None]') -> None:
        self.lock1.acquire()
        releaseHydrogen()
        self.cnt += 1 
        if self.cnt == 2:
            self.lock2.release()
        else:
            self.lock1.release()
        



    def oxygen(self, releaseOxygen: 'Callable[[], None]') -> None:
        self.lock2.acquire()
        releaseOxygen()
        self.cnt -= 2
        self.lock1.release()

## 3. Event: 不能用, 因为几个thread 可能同时call oxygen(), 几个thread会同时release


## 4 Semaphore
class H2O:
    def __init__(self):
        self.semaphore1, self.semaphore2 = threading.Semaphore(1), threading.Semaphore(0)
        self.cnt = 0


    def hydrogen(self, releaseHydrogen: 'Callable[[], None]') -> None:
        self.semaphore1.acquire()
        releaseHydrogen()
        self.cnt += 1 
        if self.cnt != 2:
            self.semaphore1.release()
        else:
            self.semaphore2.release()



    def oxygen(self, releaseOxygen: 'Callable[[], None]') -> None:
        self.semaphore2.acquire()
        releaseOxygen()
        self.cnt -= 2 
        self.semaphore1.release()


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


class H2O:
    def __init__(self):
        self.semaphore = threading.Semaphore(2)
        self.barrier = threading.Barrier(3)
        self.semaphore2 = threading.Semaphore(1)

    def hydrogen(self, releaseHydrogen: 'Callable[[], None]') -> None:
        self.semaphore.acquire() #有两个thread 可以进入
        self.barrier.wait()
        releaseHydrogen()
        self.semaphore.release()
       

    def oxygen(self, releaseOxygen: 'Callable[[], None]') -> None:
        self.semaphore2.acquire()  #只有两个thread 可以进入
        self.barrier.wait()
        releaseOxygen()
        self.semaphore2.release()