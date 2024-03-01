"""
The ProcessPoolExecutor class is an Executor subclass that uses a pool of processes to execute calls asynchronously.

 ProcessPoolExecutor uses the multiprocessing module, which allows it to side-step the Global Interpreter Lock 
 
 but also means that only picklable objects can be executed and returned.


An Executor subclass that executes calls asynchronously using a pool of at most max_workers processes. 
If max_workers is None or not given, it will default to the number of processors on the machine. 
If max_workers is less than or equal to 0, then a ValueError will be raised. 

bookkeeping of the seen urls are centralized in the main thread, therefore eliminates the need for a lock,
 which is necessary if worker threads also bookkeep seen urls.



Trying to understand this a bit especially inside for loop, here we are blocking the main thread till the url which is at the beginning of the deque 

is fully crawled. Won't there be cases where subsequent ones are done may be in which case you will be done faster crawling the ones

 from the ones with result as completed? Should we be using something like this?
 
  for task in concurrent.futures.as_completed(tasks):

"""
from concurrent import futures

class Solution:
    def crawl(self, startUrl: str, htmlParser: 'HtmlParser') -> List[str]:
        hostname = lambda url: url.split('/')[2]
        seen = {startUrl}
    
        with futures.ThreadPoolExecutor(max_workers=16) as executor:
            tasks = deque([executor.submit(htmlParser.getUrls, startUrl)])
            while tasks:
                for url in tasks.popleft().result():
                    if url not in seen and hostname(startUrl) == hostname(url):
                        seen.add(url)
                        tasks.append(executor.submit(htmlParser.getUrls, url))
        
        return list(seen)


https://leetcode.com/problems/web-crawler-multithreaded/solutions/929995/python3-using-concurrent-futures-threadpoolexecutor-with-error-handling/

from concurrent.futures import ThreadPoolExecutor, as_completed
class Solution:
    def process_url(self, url):
        urls = set(u for u in self.htmlParser.getUrls(url) if u.startswith(self.hostname))
        not_visited = urls - self.seen
        for u in not_visited:
            self.submit_to_executor(u)

    def submit_to_executor(self, url):
        self.seen.add(url)
        self.pending.append(self.executor.submit(self.process_url, url))

    def crawl(self, startUrl, htmlParser):
        self.seen = set()
        self.hostname = '/'.join(startUrl.split('/', 3)[:3])
        self.htmlParser = htmlParser
        self.pending = []

        with ThreadPoolExecutor(max_workers=64) as self.executor:
            self.submit_to_executor(startUrl)
            while self.pending:
                pending_so_far, self.pending = self.pending, []
                for fut in as_completed(pending_so_far):
                    if e := fut.exception():
                        raise RuntimeError("Future failed with an exception") from e

        return self.seen



import threading 
import collections


class Solution:
    def __init__(self):
        self.NUM_Threads = 4
        self.__cv = threading.Condition()
        self.__q = collections.deque()
        self.__working_count = 0
        self.__lookup = set()
        
    def crawl(self, startUrl: str, htmlParser: 'HtmlParser') -> List[str]:
        hostname = lambda url: url.split('/')[2]
        self.__q.append(startUrl)
        self.__lookup.add(startUrl)
        
        def worker(htmlParser):
            while True:
                with self.__cv:
                    while not self.__q and self.__working_count != 0:
                        self.__cv.wait()
                    if len(self.__q) == 0 and self.__working_count == 0:
                        return
                    from_url = self.__q.popleft()
                    if from_url is None:
                        break
                    self.__working_count += 1
                name = hostname(from_url)
                for to_url in htmlParser.getUrls(from_url):
                    if name != hostname(to_url):
                        continue
                    with self.__cv:
                        if to_url not in self.__lookup:
                           self.__lookup.add(to_url)
                           self.__q.append(to_url)
                           self.__cv.notify()
                with self.__cv:
                    self.__working_count -= 1
                    if not self.__q and not self.__working_count:
                        self.__cv.notifyAll()

        workers = []
        self.__q = collections.deque([startUrl])
        lookup = set([startUrl])
        for i in range(self.NUM_Threads):
            t = threading.Thread(target=worker, args=(htmlParser,))
            t.start()
            workers.append(t)

        for t in workers:
            t.join()
        return list(self.__lookup)    










import threading
from queue import Queue

class Solution:
    def crawl(self, startUrl: str, htmlParser: 'HtmlParser') -> List[str]:
        def hostname(url):
            start = len("http://")
            i = start
            while i < len(url) and url[i] != "/":
                i += 1
            return url[start:i]
        
        queue = Queue()
        seen = {startUrl}
        start_hostname = hostname(startUrl)
        seen_lock = threading.Lock()
        
        def worker():
            while True:
                url = queue.get()
                if url is None:
                    return

                for next_url in htmlParser.getUrls(url):
                    if next_url not in seen and hostname(next_url) == start_hostname:
                        seen_lock.acquire()
                        # Acquire lock to ensure urls are no enqueed multiple times
                        if next_url not in seen:
                            seen.add(next_url)
                            queue.put(next_url)
                        seen_lock.release()
                queue.task_done()
        
        num_workers = 8
        workers = []
        queue.put(startUrl)
        
        for i in range(num_workers):
            t = threading.Thread(target=worker)
            t.start()
            workers.append(t)
        
        # Wait until empty
        queue.join()
        
        for i in range(num_workers):
            queue.put(None)
        for t in workers:
            t.join()
        
        return list(seen)