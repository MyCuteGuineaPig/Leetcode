class ZeroEvenOdd {
private:
    int n;
    int cur  = 1;
    bool zeroprint = true; 
    condition_variable cv;
    mutex mu;
    
public:
    ZeroEvenOdd(int n) {
        this->n = n;
    }


    // printNumber(x) outputs "x", where x is an integer.
    void zero(function<void(int)> printNumber) {
        while(true){
            {
                unique_lock<mutex>lock(mu);
                cv.wait(lock, [&]{
                    return zeroprint || cur >  n;
                });
                if(cur > n)
                    return;
                zeroprint = !zeroprint;
                printNumber(0);
            }
            cv.notify_all();
        }
    }

    void even(function<void(int)> printNumber) {
        while(true){
            {
                unique_lock<mutex>lock(mu);
                cv.wait(lock, [&]{
                    return !zeroprint && cur % 2 ==0 || cur > n;
                });
                if(cur > n)
                    return;
                printNumber(cur);
                zeroprint = !zeroprint;
                ++cur;
            }
            cv.notify_all();
        }
    }

    void odd(function<void(int)> printNumber) {
            while(true){
            {
                unique_lock<mutex>lock(mu);
                cv.wait(lock, [&]{
                    return !zeroprint && cur % 2 ==1 || cur > n;
                });
                if(cur > n)
                    return;
                printNumber(cur);
                zeroprint = !zeroprint;
                ++cur;
            }
            cv.notify_all();
        }
    }
};



class ZeroEvenOdd {
public:
    ZeroEvenOdd(int n) : n_(n) {
    }

    // printNumber(x) outputs "x", where x is an integer.
    void zero(function<void(int)> printNumber) {
        for (int i = 0; i < n_; ++i) { //注意是 < n 
            {
                unique_lock<mutex> l(m_);
                wait_.wait(l, [this]() { return curr_ % 2 == 0; });
                ++curr_;
                printNumber(0);
            }
            wait_.notify_all();
        }
    }

    void even(function<void(int)> printNumber) {
        for (int i = 2; i <= n_; i += 2) { //是 <= n
            {
                unique_lock<mutex> l(m_);
                wait_.wait(l, [this]() { return curr_ % 4 == 3; });
                ++curr_;
                printNumber(i);
            }
            wait_.notify_all();
        } 
    }

    void odd(function<void(int)> printNumber) {
         for (int i = 1; i <= n_; i += 2) {
            {
                unique_lock<mutex> l(m_);
                wait_.wait(l, [this]() { return curr_ % 4 == 1; });
                ++curr_;
                printNumber(i);
            }
            wait_.notify_all();
        } 
    }

private:
    int n_;
    int curr_ = 0;
    mutex m_;
    condition_variable wait_;
};




// Time:  O(n)
// Space: O(1)
class ZeroEvenOdd2 {
public:
    ZeroEvenOdd2(int n) : n_(n) {
        m2_.lock();
        m3_.lock();
    }

    // printNumber(x) outputs "x", where x is an integer.
    void zero(function<void(int)> printNumber) {
        for (int i = 0; i < n_; ++i) {
            m1_.lock();
            printNumber(0);
            if (++curr_ % 2) {
                m2_.unlock();
            } else {
                m3_.unlock();
            }
        }
    }

    void even(function<void(int)> printNumber) {
        for (int i = 2; i <= n_; i += 2) {
            m3_.lock();
            printNumber(curr_);
            m1_.unlock();
        } 
    }

    void odd(function<void(int)> printNumber) {
         for (int i = 1; i <= n_; i += 2) {
            m2_.lock();
            printNumber(curr_);
            m1_.unlock();
        } 
    }

private:
    int n_;
    int curr_ = 0;
    mutex m1_, m2_, m3_;
};
