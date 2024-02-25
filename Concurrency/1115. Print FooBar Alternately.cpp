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





/*

atomic variables atomic<T> have mutex locks embedded in them.

The idea is that, if a thread acquires the lock, no other thread can acquire it (ie. modify it) until it is released.

Well just how to tell the program to lock/unlock?
Use this_thread::yield(), which, after a job (printFoo or printBar) is done, 
will reschedule the same job of that thread, allowing other threads to run.

*/

class FooBar {
private:
    int             n;
    atomic<bool>    alt; // added

public:
    FooBar(int n)
    {
        this->n = n;
        alt = false;
    }

    void foo(function<void()> printFoo) {
        
        for (int i = 0; i < n; i++)
        {
		/* solution part start */
		while (alt)
		{
			this_thread::yield();
		}
		/* end */

		// printFoo() outputs "foo". Do not change or remove this line.
		printFoo();

		alt = !alt; // added
        }
    }

    void bar(function<void()> printBar) {
        
        for (int i = 0; i < n; i++)
        {
		/* solution part start */
		while (!alt)
		{
			this_thread::yield();
		}
		/* end */

		// printBar() outputs "bar". Do not change or remove this line.
		printBar();

		alt = !alt; // added
        }
    }
};