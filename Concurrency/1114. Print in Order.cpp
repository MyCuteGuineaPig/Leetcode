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