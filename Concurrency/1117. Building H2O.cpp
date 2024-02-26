class H2O {
public:
    H2O() {
        
    }
    
    condition_variable cv;
    mutex mu;
    int h = 0, o = 0;

    void hydrogen(function<void()> releaseHydrogen) {
        
        unique_lock<mutex>lock(mu);
        cv.wait(lock, [&](){
            return h < 2;
        });
        ++h;
        // releaseHydrogen() outputs "H". Do not change or remove this line.
        releaseHydrogen();
        cv.notify_all();
    }

    void oxygen(function<void()> releaseOxygen) {
        unique_lock<mutex>lock(mu);
        cv.wait(lock, [&](){
            return h >= 2;
        });
        h-= 2;
        // releaseOxygen() outputs "O". Do not change or remove this line.
        releaseOxygen();
        cv.notify_all(); //不可以是notify_one 因为
    }
};

class H2O {
public:
    mutex mu;
    condition_variable cond;
    int cnt = 0;
    H2O() {
        
    }

    void hydrogen(function<void()> releaseHydrogen) {
        unique_lock<mutex>lock(mu);
        cond.wait(lock, [&](){
            return cnt != 2;
        });
        // releaseHydrogen() outputs "H". Do not change or remove this line.
        releaseHydrogen();
        ++cnt;
        cond.notify_all();
    }

    void oxygen(function<void()> releaseOxygen) {
        unique_lock<mutex>lock(mu);
        cond.wait(lock, [&](){
            return cnt % 3 == 2;
        });
        // releaseOxygen() outputs "O". Do not change or remove this line.
        releaseOxygen();
        cnt -= 2;
        cond.notify_all();
    }
};
/*
不可以是notify_one 
比如 H H H H H  O O  O

step 1: process H,  h = 1 -> notify 
step 2: process H,  h = 2 -> notify 
step 3: process H,  wait 
step 4: process H,  wait
step 5: process H,  wait 
step 6: process H,  wait

step 7: process o,  h -= 2 = > h = 0 -> notify 
step 9: 没等其他thread 醒来 process o, h == 0, on hold   (问题出自这里，没等其他的thread 被notify 就acquire the lock了)
step 10: 没等其他thread 醒来 process o, h == 0, on hold 

step 11: step 3的 H wake up (来自step 7), process H, h = 1 -> notify 
step 12: step 4的 H wake up(来自 step 11), process H, h = 2 -> notify 
step 13: step 5的 H wake up (来自step 12), on hold , 因为 h > 2  就卡主了

*/




class H2O {
public:        
    H2O() {
    }

    void hydrogen(function<void()> releaseHydrogen) {
        unique_lock<mutex> l(m_);
        releaseHydrogen_ = releaseHydrogen;
        ++nH_;
        output();
    }

    void oxygen(function<void()> releaseOxygen) {
        unique_lock<mutex> l(m_);
        releaseOxygen_ = releaseOxygen;
        ++nO_;
        output();
    }

private:
    void output() {
        while (nH_ >= 2 && nO_ >= 1) {
            nH_ -= 2;
            nO_ -= 1;
            releaseHydrogen_();
            releaseHydrogen_();
            releaseOxygen_();
        }
    }

    int nH_ = 0;
    int nO_ = 0;
    function<void()> releaseHydrogen_ = nullptr;
    function<void()> releaseOxygen_ = nullptr;
    mutex m_;
};



class H2O3 {
public:
    H2O3(): curr_(2) {
        m2_.lock();
    }

    void hydrogen(function<void()> releaseHydrogen) {
        m1_.lock();
        // releaseHydrogen() outputs "H". Do not change or remove this line.
        releaseHydrogen();
        if (--curr_) {
            m1_.unlock();
        } else {
            m2_.unlock();
        }
    }
    
    void oxygen(function<void()> releaseOxygen) {
        m2_.lock();
        // releaseOxygen() outputs "O". Do not change or remove this line.
        releaseOxygen();
        curr_ = 2;
        m1_.unlock();
    }

private:
    int curr_ = 0;
    mutex m1_, m2_;
};