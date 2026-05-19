#include <semaphore>

class FooBar {
private:
    int n;
    binary_semaphore f{1};
    binary_semaphore b{0};
public:
    FooBar(int n) {
        this->n = n;
    }

    void foo(function<void()> printFoo) {
        
        for (int i = 0; i < n; i++) {
            f.acquire();
        	// printFoo() outputs "foo". Do not change or remove this line.
        	printFoo();
            b.release();
        }
    }

    void bar(function<void()> printBar) {
        
        for (int i = 0; i < n; i++) {
            b.acquire();
        	// printBar() outputs "bar". Do not change or remove this line.
        	printBar();
            f.release();
        }
    }
};

class FooBar {
private:
    int n;
    mutex mu;
    condition_variable cv;
    bool isFoo = true;
public:
    FooBar(int n) {
        this->n = n;
    }

    void foo(function<void()> printFoo) {
        
        for (int i = 0; i < n; i++) {
            {
                unique_lock<mutex>lock(mu);
                cv.wait(lock, [&](){
                   return isFoo; 
                });
                // printFoo() outputs "foo". Do not change or remove this line.
        	    printFoo();
                isFoo = !isFoo;
            }
        	cv.notify_one();
        }
    }

    void bar(function<void()> printBar) {
        
        for (int i = 0; i < n; i++) {
            {
                unique_lock<mutex>lock(mu);
                cv.wait(lock, [&](){
                   return !isFoo; 
                });
                // printBar() outputs "bar". Do not change or remove this line.
        	    printBar();
                isFoo = !isFoo;
            }
        	cv.notify_one();
        }
    }
};



#include <semaphore.h>

class FooBar {
private:
    int n;
    sem_t foo_sem;
    sem_t bar_sem;
    
public:
    FooBar(int n) {
        this->n = n;
        sem_init(&foo_sem, 0, 1); 
        sem_init(&bar_sem, 0, 0);
        /*
int sem_init(sem_t *sem, int pshared, unsigned value); [Option End]

pshared !=0, semaphore is shared between processes;      
pshared ==0, semaphore is shared between threads of the process  
        
        */
    }
    
    ~FooBar() {
        sem_destroy(&foo_sem);
        sem_destroy(&bar_sem);
    }

    void foo(function<void()> printFoo) {
        
        for (int i = 0; i < n; i++) {
                // lock foo semaphore
            sem_wait(&foo_sem); 
        	    // printFoo() outputs "foo". Do not change or remove this line.
        	printFoo();
                // unlock bar semaphore
            sem_post(&bar_sem); 
        }
    }

    void bar(function<void()> printBar) {
        
        for (int i = 0; i < n; i++) {
                // lock bar semaphore
            sem_wait(&bar_sem); 
        	    // printBar() outputs "bar". Do not change or remove this line.
        	printBar();
                // unlock foo semaphore
            sem_post(&foo_sem); 
        }
    }
};




class FooBar {
private:
    int n;
    atomic<bool> f = true;
public:
    FooBar(int n) {
        this->n = n;
    }

    void foo(function<void()> printFoo) {
        
        for (int i = 0; i < n; i++) {
            while (!f.load(std::memory_order_acquire)) {

            }
        	// printFoo() outputs "foo". Do not change or remove this line.
        	printFoo();
            f.store(false, std::memory_order_release);
        }
    }

    void bar(function<void()> printBar) {
        
        for (int i = 0; i < n; i++) {
            while(f.load(std::memory_order_acquire));
        	// printBar() outputs "bar". Do not change or remove this line.
        	printBar();
            f.store(true, std::memory_order_release);
        }
    }
};