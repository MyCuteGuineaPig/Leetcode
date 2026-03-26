
"""

Looks like you're implementing a browser history with “most recent first” ordering + deduplication (very similar to an LRU cache pattern). Let me turn this into interview-style algorithm questions you could be asked based on your code.


Description

Design a data structure to manage a browser’s browsing history with support for retrieving the most recent visits.

The system should track URLs visited by a user and maintain them in most-recent-first order. .

You must implement efficient operations to both record visits and retrieve a subset of the most recent history.

API Specification

Implement the BrowserHistory class with the following methods:

visit(url: str) -> None
Records a visit to the given URL.

getRecent(k: int) -> List[str]
Returns up to k most recently visited URLs.
The result should be ordered from most recent → least recent.
If fewer than k URLs exist, return all available history.

Requirements
Each URL should appear at most once in the history.
The most recently visited URL should always appear at the front.
Operations should be optimized for frequent updates and queries.
Constraints
- 1 ≤ k ≤ 10^5
- Up to 10^5 total calls to visit and getRecent
- URL length ≤ 100 characters
- URLs are case-sensitive


Example
visit("google.com")
visit("youtube.com")
visit("apple.com")
getRecent(3)
# → ["apple.com", "youtube.com", "google.com"]

visit("youtube.com")
getRecent(3)
# → ["youtube.com", "apple.com", "google.com"]

getRecent(2)
# → ["youtube.com", "apple.com"]
"""



# Online Python compiler (interpreter) to run Python online.
# Write Python 3 code in this online editor and run it.

import collections

class LinkedList:
    def __init__(self, val = None, prev = None, next=None):
        self.cur = val 
        self.prev = prev
        self.next = next
     
class BrowseHistory():
    def __init__(self,):
        self.my_map = collections.defaultdict(LinkedList)
        self.head = None
    
    def add(self, url: str):
        if url in self.my_map:
            prev_record = self.my_map[url]
            if prev_record.prev:
                prev_record.prev.next = prev_record.next
            if prev_record.next:
                 prev_record.next.prev = prev_record.prev
        self.my_map[url] = LinkedList(url, self.head)
        if self.head:
            self.head.next = self.my_map[url] 
        self.head = self.my_map[url]
        
        
    def retrieve(self,) -> list[str]:
        record = self.head 
        res = []
        print("retrieve ")
        while record:
            res.append(record.cur)
            print(f"record.cur: {record.cur} ")
            record = record.prev
        return res
        
history = BrowseHistory()
history.add("google.com")
history.add("youtube.com")
history.add("apple.com")
print(history.retrieve())

history.add("youtube.com")
print(history.retrieve())

history.add("google.com")
print(history.retrieve())






