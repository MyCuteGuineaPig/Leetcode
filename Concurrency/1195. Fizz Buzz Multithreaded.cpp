class FizzBuzz {
private:
    int n;
    int i=1;
    condition_variable cv;
    mutex mu;

public:
    FizzBuzz(int n) {
        this->n = n;
    }
    
    void run(function<bool(int)>test, function<void(int)>print){
        while(true){
            unique_lock<mutex>lock(mu);
            cv.wait(lock, [&](){
               return  i > n || test(i);
            });
            if(i > n)
                break;
            print(i++);
            cv.notify_all();
        }
        
    }

    // printFizz() outputs "fizz".
    void fizz(function<void()> printFizz) {
        run([](int i){return i%3==0 && i%5!=0;},[&](int i){ printFizz();});
    }

    // printBuzz() outputs "buzz".
    void buzz(function<void()> printBuzz) {
        run([](int i){return i%3!=0 && i%5 == 0;}, [&](int i){printBuzz();});
    }

    // printFizzBuzz() outputs "fizzbuzz".
	void fizzbuzz(function<void()> printFizzBuzz) {
        run([](int i){return i%3==0 && i%5 == 0;}, [&](int i){printFizzBuzz();});
    }

    // printNumber(x) outputs "x", where x is an integer.
    void number(function<void(int)> printNumber) {
        run([](int i){return i%3!=0 && i%5 != 0;}, printNumber);
    }
};



class FizzBuzz {
private:
    int n;
    int count;
    mutex m;
    condition_variable cv;

public:
    FizzBuzz(int n) {
        this->n = n;
        this->count = 1;
    }

    void fizz(function<void()> printFizz) {
        while (true) {
            unique_lock<mutex> lock(m);
            cv.wait(lock,[&](){
                return count > n || (count % 3 == 0 && count % 5 != 0);
            });
            if (count > n) return;
            printFizz();
            ++count;
            cv.notify_all();
        }
    }

    void buzz(function<void()> printBuzz) {
        while (true) {
            unique_lock<mutex> lock(m);
            cv.wait(lock,[&](){
                return count > n || (count % 3 != 0 && count % 5 == 0);
            });
            if (count > n) return;
            printBuzz();
            ++count;
            cv.notify_all();
        }
    }

	void fizzbuzz(function<void()> printFizzBuzz) {
        while (true) {
            unique_lock<mutex> lock(m);
            cv.wait(lock,[&](){
                return count > n || (count % 5 == 0 && count % 3 == 0);
            });
            if (count > n) return;
            printFizzBuzz();
            ++count;
            cv.notify_all();
        }
    }

    void number(function<void(int)> printNumber) {
        while (true) {
            unique_lock<mutex> lock(m);
            cv.wait(lock,[&](){
                return count > n || (count % 5 != 0 && count % 3 != 0);
            });
            if (count > n) return;
            printNumber(count++);
            cv.notify_all();
        }
    }
};

/*

 //可以更改四个thread 的顺序
比如

 printFizz cv 条件 curr_ % 4 == 1；
 printBuzz cv 条件 curr_ % 4 == 0；
 printFizzBuzz cv 条件 curr % 4 = 3
 printNumber  cv 条件 curr % 4 = 2

 四个thread的wait 让每个i都必须走这四个function一次, 从而按照顺序打印

 比如 
 curr = 0, 先到 printBuzz， i = 1, 不打印 
 curr = 1, 到 printFizz,   i = 1 不打印
 curr = 2, 到 printNumber,  i = 1, 打印
 curr = 3, 到printFizzBuzz， i = 1 不打印

curr = 4, 先到 printBuzz， i = 2, 不打印 
curr = 5, 到 printFizz,   i = 2 不打印
curr = 6, 到 printNumber,  i = 2, 打印
curr = 7, 到printFizzBuzz， i = 2 不打印


curr = 8, 先到 printBuzz， i = 3, 打印
curr = 9, 到 printFizz,   i = 3, 不打印
curr = 10, 到 printNumber,  i = 3, 不打印
curr = 11, 到printFizzBuzz， i = 3 不打印
*/


class FizzBuzz {
public:
    FizzBuzz(int n) : n_(n) {
    }

    // printFizz() outputs "fizz".
    void fizz(function<void()> printFizz) {
        for (int i = 1; i <= n_; ++i) {
            {
                unique_lock<mutex> l(m_);
                cv_.wait(l, [this]() { return curr_ % 4 == 0; });
                ++curr_;
                if (i % 3 == 0 && i % 5 != 0) {
                    printFizz();
                }
            }
            cv_.notify_all();
        }
    }

    // printBuzz() outputs "buzz".
    void buzz(function<void()> printBuzz) {
        for (int i = 1; i <= n_; ++i) {
            {
                unique_lock<mutex> l(m_);
                cv_.wait(l, [this]() { return curr_ % 4 == 1; });
                ++curr_;
                if (i % 3 != 0 && i % 5 == 0) {
                    printBuzz();
                }
            }
            cv_.notify_all();
        }
    }

    // printFizzBuzz() outputs "fizzbuzz".
    void fizzbuzz(function<void()> printFizzBuzz) {
        for (int i = 1; i <= n_; ++i) {
            {
                unique_lock<mutex> l(m_);
                cv_.wait(l, [this]() { return curr_ % 4 == 2; });
                ++curr_;
                if (i % 3 == 0 && i % 5 == 0) {
                    printFizzBuzz();
                }
            }
            cv_.notify_all();
        }
    }

    // printNumber(x) outputs "x", where x is an integer.
    void number(function<void(int)> printNumber) {
        for (int i = 1; i <= n_; ++i) {
            {
                unique_lock<mutex> l(m_);
                cv_.wait(l, [this]() { return curr_ % 4 == 3; });
                ++curr_;
                if (i % 3 != 0 && i % 5 != 0) {
                    printNumber(i);
                }
            }
            cv_.notify_all();
        }
    }

private:
    int n_;
    int curr_ = 0;
    mutex m_;
    condition_variable cv_;
};
