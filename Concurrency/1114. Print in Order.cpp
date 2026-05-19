class Foo {
public:
    Foo() {}
    int n = 0;
    condition_variable cv;
    mutex mu;

    void first(function<void()> printFirst) {        
        {
            unique_lock<mutex>lock(mu);
            ++n;
            printFirst();
            cv.notify_all();
        }
    }

    void second(function<void()> printSecond) {
        {
            unique_lock<mutex>lock(mu);
            cv.wait(lock, [&](){ return n == 1; });
            printSecond();
            ++n;
            cv.notify_all();
        }
    }

    void third(function<void()> printThird) {
        {
            unique_lock<mutex>lock(mu);
            cv.wait(lock, [&](){ return n == 2; });
            printThird();
            ++n;
        }
    }
};

class Foo {
public:
    Foo() {
        
    }
    int n = 0;
    condition_variable cv;
    mutex mu;
    
    void first(function<void()> printFirst) {
        
        {   
            unique_lock<mutex>lock(mu);
            ++n;
            cv.notify_all();
            printFirst();  // printFirst() outputs "first". Do not change or remove this line.
        }
        cv.notify_all();
    }

    void second(function<void()> printSecond) {
        {
            unique_lock<mutex>lock(mu);
            cv.wait(lock, [&](){return n  == 1; });
            ++n;
            printSecond(); // printSecond() outputs "second". Do not change or remove this line.
        }
        
       cv.notify_all();    
    }

    void third(function<void()> printThird) {
        
        {
            unique_lock<mutex>lock(mu);
            cv.wait(lock, [&](){return n  == 2; });
            ++n;
            printThird(); // printThird() outputs "Third". Do not change or remove this line.
        }
       
    }
};


class Foo {
private:
  std::promise<void> p1;
  std::promise<void> p2;

public:
  void first(function<void()> printFirst) {
    printFirst();
    p1.set_value();
  }

  void second(function<void()> printSecond) {
    p1.get_future().wait();
    printSecond();
    p2.set_value();
  }

  void third(function<void()> printThird) {
    p2.get_future().wait();
    printThird();
  }
};

/*
⚠️ Broken promise
If the promise is destroyed without calling set_value():

wait() still returns
But the future is in a broken state
Calling .get() will throw std::future_error



1. One-shot vs reusable
promise/future:
    ❌ One-time only
    After set_value(), it's done forever
condition_variable:
    ✅ Reusable
    You can wait/notify many times


promise/future:
    Only one future per promise
    ❌ Not good for broadcasting
condition_variable:
    ✅ Many threads can wait
    notify_all() wakes everyone

 */



class Foo {
private: 
    int n;
    atomic<int>order = {1};
public:
    Foo() {
        
    }

    void first(function<void()> printFirst) {
        
        // printFirst() outputs "first". Do not change or remove this line.
        printFirst();
        order.store(2, std::memory_order_release);
    }

    void second(function<void()> printSecond) {
        
        // printSecond() outputs "second". Do not change or remove this line.
        while(order.load(std::memory_order_acquire) != 2) {

        }
        printSecond();
        order.store(3, std::memory_order_release);
    }

    void third(function<void()> printThird) {
        
        // printThird() outputs "third". Do not change or remove this line.
        while(order.load(std::memory_order_release) != 3);
        printThird();
    }
};