/*
621. Task Scheduler
https://leetcode.com/problems/task-scheduler/description/

Given a char array representing tasks CPU need to do. 
It contains capital letters A to Z where different letters represent different tasks.
Tasks could be done without original order. 
Each task could be done in one interval. 
For each interval, CPU could finish one task or just be idle.

However, there is a non-negative cooling interval n that means between two same tasks, 
there must be at least n intervals that CPU are doing different tasks or just be idle.

You need to return the least number of intervals the CPU will take to finish all the given tasks.

Example 1: 
Input: tasks = ["A","A","A","B","B","B"], n = 2
Output: 8
Explanation: A -> B -> idle -> A -> B -> idle -> A -> B.
Note:
The number of tasks is in the range [1, 10000].
The integer n is in the range [0, 100].


*/


/*
First consider the most frequent characters, we can determine their relative positions first and use them as a frame
to insert the remaining less frequent characters. Here is a proof by construction:

Let F be the set of most frequent chars with frequency k.
We can create k chunks, each chunk is identical and is a string consists of chars in F in a specific fixed order.
Let the heads of these chunks to be H_i; then H_2 should be at least n chars away from H_1, and so on so forth;
then we insert the less frequent chars into the gaps between these chunks sequentially one by one ordered by frequency 
in a decreasing order and try to fill the k-1 gaps as full or evenly as possible each time you insert a character.
In summary, append the less frequent characters to the end of each chunk of the first k-1 chunks sequentially and round and round, 
then join the chunks and keep their heads' relative distance from each other to be at least n.

Examples:

AAAABBBEEFFGG 3

here X represents a space gap:

Frame: "AXXXAXXXAXXXA"
insert 'B': "ABXXABXXABXXA" <--- 'B' has higher frequency than the other characters, insert it first.
insert 'E': "ABEXABEXABXXA"
insert 'F': "ABEFABEXABFXA" <--- each time try to fill the k-1 gaps as full or evenly as possible.
insert 'G': "ABEFABEGABFGA"
AACCCBEEE 2

3 identical chunks "CE", "CE CE CE" <-- this is a frame
insert 'A' among the gaps of chunks since it has higher frequency than 'B' ---> "CEACEACE"
insert 'B' ---> "CEABCEACE" <----- result is tasks.length;
AACCCDDEEE 3

3 identical chunks "CE", "CE CE CE" <--- this is a frame.
Begin to insert 'A'->"CEA CEA CE"
Begin to insert 'B'->"CEABCEABCE" <---- result is tasks.length;
ACCCEEE 2

3 identical chunks "CE", "CE CE CE" <-- this is a frame
Begin to insert 'A' --> "CEACE CE" <-- result is (c[25] - 1) * (n + 1) + 25 -i = 2 * 3 + 2 = 8

for the last line (c[25] - 1) * (n + 1) + 25 - i):

c[25]-1: the most frequent letter happen time minus 1
*(n+1): count for the loops for above
+25-i: count for the less frequence letters.
For example:
tasks = ['A','A','A','B','B','B'], n = 2

most frequent letter : A (happen 3 times, let it minus 1= 2)
count loops: (n+1) =3
plus the letters left: A,B.
[A -> B -> idle]*loop1* -> [A -> B -> idle]*loop2* -> A -> B.


*/

class Solution {
public:
    int leastInterval(vector<char>& tasks, int n) {
         unordered_map<char,int>m;
         int maxN = -1;
         for(auto i: tasks)
        {
            m[i]++;
            maxN = max(maxN,m[i]);
        }
        int ans = (n+1)*(maxN-1);
        for(auto itr: m) if(itr.second == maxN) ans++;
        return max(ans,(int)tasks.size());
    }
};