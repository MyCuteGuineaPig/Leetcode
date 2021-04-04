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