

/*

比如: 
["http://news.yahoo.com","http://news.yahoo.com/news","http://news.yahoo.com/news/topics/","http://news.google.com","http://news.yahoo.com/us"]
[[2,0],[2,1],[3,2],[3,1],[0,4]]
"http://news.yahoo.com/news/topics/"

比如有4个thread

Step 1:  下面用index 表示url

thread 0:   condition 因为 q.size() > 0, 继续  get 2 (q.top()) （release lock 让 2,3,4 开始）->  call getUrls -> push 2的friend 1 & 0  => notify_all
thread 1:  wait， 因为 q.size = 0
thread 2:  wait  因为 q.size = 0
thread 3:  wait  因为 q.size = 0


step2: 没有等待 thread 1 ,2 ,3 醒过来，thread 0开始下一轮工作,

thread 0: condition 因为 q.size() > 0, 继续  ;get 1 (q.top())  ->  call urls  (release lock 让 thread 1 可以开始)   
thread 1: wake up ->  发现 q size > 0,  get 2 (q.top()) -> call urls( release lock, 让3,4 可以开始)
thread 2: wake up ->  q.size = 0 -> sleep
thread 3: wake up ->  q.size = 0 -> sleep
thread 0: -> (check 3,4 过后) lock again ->  push 1的friend 4  => notify_all

step3: 没有等待 thread 1 ,2 ,3 醒过来，thread 0开始下一轮工作,

thread 0:  condition 因为 q.size() > 0, 继续  ; get 4 (q.top())  ->  call urls  (release lock 让 thread 1,2,3 可以开始) -> 
               
thread 2: wake up (来自step 2的notify_all) ->  q.size = 0  -> sleep 
thread 3: wake up (来自step 2的notify_all) ->  q.size = 0 -> sleep
thread 1: 从step 2中 lock again ->  2没有friend => notify all, 还有等到下一轮 thread 1工作, thread 0 先获取lock
thread 0:  (check 3,4 过后) 且 thread 1 完成后 lock again -> 4没有friend => notifyall 并更新done = true


step4: 没有等待 thread 1 ,2 ,3 醒过来，thread 0开始下一轮工作,

thread 0:   done = true, return  
thread 2:  wake up->   done = true, return  
thread 3: wake up->    done = true, return  
thread 1: wake up->     done = true, return  

注上面每一步thread 0, 1, 2,3 激活顺序不固定，

*/



/**
 * // This is the HtmlParser's API interface.
 * // You should not implement it, or speculate about its implementation
 * class HtmlParser {
 *   public:
 *     vector<string> getUrls(string url);
 * };
 */
class Solution {
private: 
    string hostname;
    int thread_num;
    queue<string>q; 
    unordered_set<string>seen;
    int working= 0;
    bool done;
    mutex m;
    condition_variable cv;
    
    string extract(const string& url){
        int start = url.find('/') + 2;
        int end = url.find('/',start);
        if(end == string::npos)
            return url.substr(start);
        return url.substr(start, end-start);
    }
     vector<thread>workers;
    
public:
    
    void worker(HtmlParser& parser, int threadNum){
        while(true){
            unique_lock<mutex>ul(m);
            cv.wait(ul, [&](){
               return q.size() > 0 || done;  
            });//被notify called后, 如果条件为true, 继续下面的，否则继续sleep
            if(done)
                return;
            working++;
            string cur = q.front(); q.pop();
            ul.unlock();
            
            auto nxt = parser.getUrls(cur);
            ul.lock();
            for(auto & url: nxt){
                if(seen.count(url) || extract(url)!=hostname)
                    continue;
                seen.insert(url);
                q.push(url);
            }
            working--;
            if(working == 0 && q.empty())
                done = true;
            cv.notify_all();
            
        }
        
        
    }
    
    vector<string> crawl(string startUrl, HtmlParser htmlParser) {
        hostname = extract(startUrl);
        done = false;
        thread_num = thread::hardware_concurrency();
        q.push(startUrl);
        seen.insert(startUrl);
        for(int i = 0; i < thread_num; i++){
            workers.emplace_back(&Solution::worker, this, ref(htmlParser), i); //每个thread 就开始工作了
        }
        
        // join those threads so that crawl is a blocking call 
        for(auto &t : workers){
            t.join();
        }
        // return every unique processed string
        return vector<string>(seen.begin(), seen.end());

    }
   
};

/**
 * // This is the HtmlParser's API interface.
 * // You should not implement it, or speculate about its implementation
 * class HtmlParser {
 *   public:
 *     vector<string> getUrls(string url);
 * };
 */
class Solution {

    mutex mu;
    condition_variable cv;
    queue<string>q;
    unordered_set<string>lookup;
    string host;
    int work_count = 0;
    vector<thread>threads;
    
    string extract(const string& url){
        int start = url.find('/') + 2;
        int end = url.find('/',start);
        if(end == string::npos)
            return url.substr(start);
        return url.substr(start, end-start);
    }
    
    void work(HtmlParser& htmlParser){
        while(true){
            string curUrl;
            {
                unique_lock<mutex>lock(mu);
                cv.wait(lock, [&](){return !q.empty() || work_count == 0;});
                if(q.empty() && work_count == 0)
                    break;
                ++work_count;
                curUrl = q.front();
                q.pop();
            }
            for(auto nxt: htmlParser.getUrls(curUrl)){
                if(extract(nxt)!=host) continue;
                {
                    unique_lock<mutex>lock(mu);
                    if(lookup.count(nxt) == 0){
                        q.push(nxt);
                        lookup.insert(nxt);
                        cv.notify_one(); //notify_one 就可以了 更efficient 只呼叫一个等待的thread
                    }
                }
            }
            {
                unique_lock<mutex>lock(mu);
                --work_count;
                if(q.empty() && work_count == 0)
                    cv.notify_all();
            }
        }
    }
    
    
public:
    vector<string> crawl(string startUrl, HtmlParser htmlParser) {
        host = extract(startUrl);
        q.push(startUrl);
        lookup.insert(startUrl);
        
        int numThreads = thread::hardware_concurrency();
        for(int i = 0; i<numThreads; ++i){
            threads.emplace_back(&Solution::work, this, ref(htmlParser));
        }
        for(int i = 0; i<numThreads; ++i)
            threads[i].join();
        return vector<string>(lookup.begin(),lookup.end());
    }
};


// Time:  O(|V| + |E|)
// Space: O(|V|)

/*

比如: 
["http://news.yahoo.com","http://news.yahoo.com/news","http://news.yahoo.com/news/topics/","http://news.google.com","http://news.yahoo.com/us"]
[[2,0],[2,1],[3,2],[3,1],[0,4]]
"http://news.yahoo.com/news/topics/"

比如有4个thread

Step 1:  下面用index 表示url

thread 0:  lock 1 acquire ->  get 2 (q.top()) -> ++ work_count  release lock get URL  
thread 1:  wait(relase lock)， 因为 q.size = 0
thread 2:  wait(relase lock)  因为 q.size = 0
thread 3:  wait(relase lock)  因为 q.size = 0
main:     lock 0 wait-> 因为 work_count > 0
thread 0: lock 2 acquire -> push 0 (2的friend)  => notifyall 
thread 0: 没等 其他thread wake up  lock 2 acquire -> push 1 (2的friend)  => notifyall 


step2: 

thread 3: wake up(Step 1 thread 0 的 notify_all) ->  lock 1 acquire ->  get 0 (q.top()) -> ++ work_count  release lock 1 get URL 
thread 1: wake up(Step 1 thread 0的 notify_all) ->  lock 1 acquire ->  get 1 (q.top()) -> ++ work_count   release lock 1 get URL
thread 0: lock 3 acquire -> --work_count ->  release lock 3 
          lock 1 ->  sleep 因为 qsize = 0  wait (relase lock1)
thread 2: wake up(Step 1的 notify_all)  因为 q.size = 0 -> 继续wait 
main:     lock 0 wait-> 因为 work_count > 0 


step 3：

thread 3: lock 2 acquire -> push 4 (0的friend)  => notifyall 
thread 0: wake up(step 3 thread 3的 notify_all) ->  lock 1 acquire -> get 4 (q.top()) ->  ++ work_count release lock get URL 
thread 3: lock 3 acquire -> --work_count ->  release lock 3 
          lock 1 ->  sleep 因为 qsize = 0  wait (relase lock1)
thread 2:  wait (step 3 thread 3的 notify_all)  因为 q.size = 0 -> 继续wait
thread 1: lock 2 acquire -> 1没有friend 不push 
          lock 3 acquire -> --work_count ->  release lock 3 
          lock 1 ->  sleep 因为 qsize = 0  wait (relase lock1)  


Step 4: 
thread 0: lock 2 acquire -> 1没有friend 不push 
          lock 3 acquire -> --work_count ->  release lock 3 
          因为 work_count == 0 且 workcount == 0: => notify_all
thread 1; wait (step 4 thread 0的 notify_all)  因为 q.size = 0 -> 继续wait
main:  waitup, lock 0 acquire -> push 四个空的 string 进 q

thread 2: wakeup -> cur = 空 return 
thread 1: wakeup -> cur = 空 return 
thread 3: wakeup -> cur = 空 return 
thread 0: wakeup -> cur = 空 return 



注上面每一步thread 0, 1, 2,3 激活顺序不固定，

*/


class Solution {
public:
    vector<string> crawl(string startUrl, HtmlParser htmlParser) {
        q_.emplace(startUrl);
        unordered_set<string> lookup = {startUrl};
        vector<thread> workers;
        for (int i = 0; i < NUMBER_OF_WORKERS; ++i) {
            workers.emplace_back(bind(&Solution::worker, this, &htmlParser, &lookup));
        }
        {
            unique_lock<mutex> lock{m_};  //lock 0
            cv_.wait(lock, [this]() { return q_.empty() && !working_count_; });
            for (const auto& t : workers) {
                q_.emplace();
            }
            cv_.notify_all();
        }
        for (auto& t : workers) {
            t.join();
        }
        return vector<string>(lookup.cbegin(), lookup.cend());
    }

private:
    void worker(HtmlParser *htmlParser, unordered_set<string> *lookup) {
        while (true) {
            string from_url;
            {
                unique_lock<mutex> lock{m_};  //lock 1
                cv_.wait(lock, [this]() { return !q_.empty(); });
                from_url = q_.front(); q_.pop();
                if (from_url.empty()) {
                    break;
                }
                ++working_count_;
            }
            const auto& name = hostname(from_url);
            for (const auto& to_url: htmlParser->getUrls(from_url)) {
                if (name != hostname(to_url)) {    
            // The function hostname itself is safe to call. It becomes dangerous if they're all trying to operate on the same variable.
                    continue;
                }
                unique_lock<mutex> lock{m_}; //lock 2
                if (!lookup->count(to_url)) {
                    lookup->emplace(to_url);
                    q_.emplace(to_url);
                    cv_.notify_all();
                }
            }
            {
                unique_lock<mutex> lock{m_}; // //lock 3
                --working_count_;
                if (q_.empty() && !working_count_) {
                    cv_.notify_all();
                }
            }
        }
    }
    
    string hostname(const string& url) {
        static const string scheme = "http://";
        return url.substr(0, url.find('/', scheme.length()));
    }

    static const int NUMBER_OF_WORKERS = 4;
    queue<string> q_;
    int working_count_ = 0;
    mutex m_;
    condition_variable cv_;
};




// Time:  O(|V| + |E|)
// Space: O(|V|)

/**
 * // This is the HtmlParser's API interface.
 * // You should not implement it, or speculate about its implementation
 * class HtmlParser {
 *   public:
 *     vector<string> getUrls(string url);
 * };
 */
class Solution {
public:
    vector<string> crawl(string startUrl, HtmlParser htmlParser) {
        q_.emplace(startUrl);
        unordered_set<string> lookup = {startUrl};
        vector<thread> workers;
        const auto& worker = [this](HtmlParser *htmlParser, unordered_set<string> *lookup) {
            while (true) {
                string from_url;
                {
                    unique_lock<mutex> lock{m_};
                    cv_.wait(lock, [this]() { return !q_.empty(); });
                    from_url = q_.front(); q_.pop();
                    if (from_url.empty()) {
                        break;
                    }
                    ++working_count_;
                }
                const auto& name = hostname(from_url);
                for (const auto& to_url: htmlParser->getUrls(from_url)) {
                    if (name != hostname(to_url)) {
                        continue;
                    }
                    unique_lock<mutex> lock{m_};
                    if (!lookup->count(to_url)) {
                        lookup->emplace(to_url);
                        q_.emplace(to_url);
                        cv_.notify_all();
                    }
                }
                {
                    unique_lock<mutex> lock{m_};
                    --working_count_;
                    if (q_.empty() && !working_count_) {
                        cv_.notify_all();
                    }
                }
            }
        };
        for (int i = 0; i < NUMBER_OF_WORKERS; ++i) {
            workers.emplace_back(worker, &htmlParser, &lookup);
        }
        {
            unique_lock<mutex> lock{m_};
            cv_.wait(lock, [this]() { return q_.empty() && !working_count_; });
            for (const auto& t : workers) {
                q_.emplace();
            }
            cv_.notify_all();
        }
        for (auto& t : workers) {
            t.join();
        }
        return vector<string>(lookup.cbegin(), lookup.cend());
    }

private:
    string hostname(const string& url) {
        static const string scheme = "http://";
        return url.substr(0, url.find('/', scheme.length()));
    }

    static const int NUMBER_OF_WORKERS = 4;
    queue<string> q_;
    int working_count_ = 0;
    mutex m_;
    condition_variable cv_;
};
