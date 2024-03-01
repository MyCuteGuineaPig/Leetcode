class DiningPhilosophers {
public:
    DiningPhilosophers() {
        
    }
        mutex mtx; // 5 philosophers share 1 single mutex

    void wantsToEat(int philosopher,
                    function<void()> pickLeftFork,
                    function<void()> pickRightFork,
                    function<void()> eat,
                    function<void()> putLeftFork,
                    function<void()> putRightFork) {
        mtx.lock();
        pickLeftFork(); pickRightFork(); eat(); putLeftFork();          putRightFork();
        mtx.unlock();
    }
};


class DiningPhilosophers {
private:
    mutex mtxFork[5];
    mutex mtxTable;
    
public:
    DiningPhilosophers() { }
    void wantsToEat(int philosopher, function<void()> pickLeftFork, function<void()> pickRightFork, function<void()> eat, function<void()> putLeftFork, function<void()> putRightFork) {
        int left = philosopher;
        int right = (philosopher + 1) % 5;
		
        unique_lock<mutex> lckTable(mtxTable);//需要这个，否则deadlock, 比如left 选3, right 选4, 另一个thread, right 选4, left 选3
        lock_guard<mutex> lckForkLeft(mtxFork[left]);
        lock_guard<mutex> lckForkRight(mtxFork[right]);
        lckTable.unlock(); // after locking both forks, we can safely unlock table
        
        pickLeftFork(); pickRightFork(); eat(); putRightFork(); putLeftFork();
        // locks will be automatically released due to unique_lock RAII design
    }
};


class DiningPhilosophers {
private:
    mutex mtx[5];
    
public:
    DiningPhilosophers() { }
    void wantsToEat(int philosopher, function<void()> pickLeftFork, function<void()> pickRightFork, function<void()> eat, function<void()> putLeftFork, function<void()> putRightFork) {
        int left = philosopher;
        int right = (philosopher + 1) % 5;
        
        unique_lock<mutex> lck1(mtx[left], defer_lock); // defer_lock: init lck1 without locking mtx
        unique_lock<mutex> lck2(mtx[right], defer_lock);
        
        if(philosopher % 2 == 0){ 
            /*
                如果都用left 在right 会有deadlock
                比如 phi0:  lock[0], lock[1]
                    phi1:  lock[1], lock[2]
                    phi2:  lock[2], lock[3]
                    phi3:  lock[3], lock[4]
                    phi4:  lock[4], lock[0]  如果所有phi 同时进入, 会block
            */ 

            lck1.lock(); // do NOT use std::lock(lck1, lck2)
            lck2.lock();
            pickLeftFork(); pickRightFork();
        }
		else{
            lck2.lock();
            lck1.lock();
            pickLeftFork(); pickRightFork();
        }
        eat(); putRightFork(); putLeftFork();
        // lck1 & lck2 are auto released after this line
    }
};



class Semaphore {
private:
	int count;
    mutex mtx;
    condition_variable cv;
	
public:
    Semaphore(int n = 0) : count(n) { }
    void Set(int n) { count = n; }
    void Signal() {
        unique_lock<mutex> lck(mtx);
        ++count;
        cv.notify_one();
    }
    void Wait() {
        unique_lock<mutex> lck(mtx);
        cv.wait(lck, [&](){ return count > 0; }); // standard format of wait() lambda expression
        --count;
    }
};

class DiningPhilosophers {
private:
    mutex mtx[5];
    Semaphore sem;
    
public:
    DiningPhilosophers() { sem.Set(4); }
    void wantsToEat(int philosopher, function<void()> pickLeftFork, function<void()> pickRightFork, function<void()> eat, function<void()> putLeftFork, function<void()> putRightFork) {
        int left = philosopher;
        int right = (philosopher + 1) % 5;
        
        sem.Wait(); // if there are 4 philosophers eating, thread will wait here

        unique_lock<mutex> lckLeft(mtx[left]);
        unique_lock<mutex> lckRight(mtx[right]);
        
        pickLeftFork(); pickRightFork(); eat(); putRightFork(); putLeftFork();
        
        lckLeft.unlock();
        lckRight.unlock();

        sem.Signal(); // finish eating, release 1 spot for other philosophers
    }
};


//c++ 20 开始支持semaphore
#include <thread>
#include <chrono>
#include <semaphore> // ERROR: compiler unable to find this header

class DiningPhilosophers {
private:
    mutex mtx[5];
    counting_semaphore<4> sem(4);
    
public:
    DiningPhilosophers() { }
    void wantsToEat(int philosopher, function<void()> pickLeftFork, function<void()> pickRightFork, function<void()> eat, function<void()> putLeftFork, function<void()> putRightFork) {
        int left = philosopher;
        int right = (philosopher + 1) % 5;
        
        sem.acquire(); // if there are 4 philosophers eating, thread will wait here

        unique_lock<mutex> lckLeft(mtx[left]);
        unique_lock<mutex> lckRight(mtx[right]);
        
        pickLeftFork(); pickRightFork(); eat(); putRightFork(); putLeftFork();
        
        lckLeft.unlock();
        lckRight.unlock();

        sem.release(); // finish eating, release 1 spot for other philosophers
    }
};