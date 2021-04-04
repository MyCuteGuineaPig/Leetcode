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