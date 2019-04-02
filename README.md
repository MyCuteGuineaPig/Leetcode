## Catalogue
* [Array](https://github.com/beckswu/Leetcode#array)
* [Greedy](https://github.com/beckswu/Leetcode#greedy) 
* [Tree](https://github.com/beckswu/Leetcode#tree) 
* [Math](https://github.com/beckswu/Leetcode#math) 
* [String](https://github.com/beckswu/Leetcode#string) 
* [Hash Table](https://github.com/beckswu/Leetcode#hash-table) 
* [Bit Manipulation](https://github.com/beckswu/Leetcode#bit-manipulation)
* [Stack](https://github.com/beckswu/Leetcode#stack) 
* [Queue](https://github.com/beckswu/Leetcode#queue) 
* [Heap](https://github.com/beckswu/Leetcode#heap) 
* [Linked List](https://github.com/beckswu/Leetcode#linked-list) 
* [Two Pointer](https://github.com/beckswu/Leetcode#two-pointer) 
* [Sort](https://github.com/beckswu/Leetcode#sort) 
* [Recursion](https://github.com/beckswu/Leetcode#recursion) 
* [Binary Search](https://github.com/beckswu/Leetcode#binary-search) 
* [Binary Search Tree](https://github.com/beckswu/Leetcode#binary-search-tree) 
* [Depth First Search](https://github.com/beckswu/Leetcode#depth-first-search) 
* [Backtracking](https://github.com/beckswu/Leetcode#backtracking) 
* [Dynamic Programming](https://github.com/beckswu/Leetcode#dynamic-programming) 
* [Regular Expression Summary](https://github.com/beckswu/Leetcode#regular-expression-summary)
* [Sliding Window Summary](https://github.com/beckswu/Leetcode#sliding-windows-summary)


Python trick: \* 可以把generator 变成list, 比如\[\*zip(\*matrix)] = list(zip(\*matrix)) </br>
join 可以直接加generator, 比如 "".join(map(func, S))

 😍 好的面试题
 😚 好的面试题 II (low priority)
 🔍 反复看的题
 💡 比较tricky
 🌒 不用太看的题目
 🐸 brainstorming 
  ## Breadth-First Search
|Title | Time  | Space | Difficulty |  Algorithm Note|
| ------------- | ------------- | ------------- | ------------- | ------------- |
| [102. Binary Tree Level Order Traversal](https://leetcode.com/problems/binary-tree-level-order-traversal/) | _O(n)_ | _O(n)_	| Medium | |
| &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; &nbsp;&nbsp;&nbsp; &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;|  |	|  | |
 
 
 ## Array
|Title | Time  | Space | Difficulty |  Algorithm Note|
| ------------- | ------------- | ------------- | ------------- | ------------- |
| [015. 3 Sum](https://leetcode.com/problems/3sum/) | _O(n^2)_ | _O(1)_	| Medium | 🔍问题关键是sort + skip duplicate |
| [016. 3 Sum Closest](https://leetcode.com/problems/3sum-closest/) | _O(n^2)_ | _O(1)_	| Medium | 🔍sort + two pointer，根据three sum 和sorted list移动两个pointers |
| [018. 4 Sum](https://leetcode.com/problems/4sum/) | _O(n^3)_ | _O(1)_	| Medium | 🔍sort + two pointer，思路和[015. 3 Sum](https://leetcode.com/problems/3sum/) 一样 |
| [026. Remove Duplicates from Sorted Array](https://leetcode.com/problems/remove-duplicates-from-sorted-array/) | _O(n)_ | _O(1)_	| Easy | Two pointer |
| [027. Remove Element](https://leetcode.com/problems/remove-element/) | _O(n)_ | _O(1)_	| Easy | Two pointer |
| [031. Next Permutation](https://leetcode.com/problems/next-permutation/) | _O(n)_ | _O(1)_	| Medium | 跟[556.	Next Greater Element III](https://leetcode.com/problems/next-greater-element-iii/) 思路类似, C++可以用is_sorted_until + upper_bound()  |
| [041. First Missing Positive](https://leetcode.com/problems/first-missing-positive/) | _O(n)_ | _O(1)_	| Hard | 🔍先置换, 把每个元素放在合适位置，再看A\[i] == i+1 ? 不等于 return i+1, 最后如果还没return, return size +1 |
| [048. Rotate Image](https://leetcode.com/problems/rotate-image/) | _O(n^2)_ | _O(1)_	| Medium | 🔍<ul><li> 上下左右四个区域，每个区域相互置换 </li><li> 先以左下到右上对角线置换，然后上下换 </li></ul>|
| [054. Spiral Matrix](https://leetcode.com/problems/spiral-matrix/) | _O(m\*n)_ | _O(1)_	| Medium | 🔍定义 up, down, left, right 四个边界，每次loop 在最外围的一圈 |
| [059. Spiral Matrix II](https://leetcode.com/problems/spiral-matrix-ii/) | _O(n^2)_ | _O(1)_	| Medium | 🔍思路跟[048. Rotate Image](https://leetcode.com/problems/rotate-image/)  和 [054. Spiral Matrix](https://leetcode.com/problems/spiral-matrix/) 类似 |
| [066. Plus One](https://leetcode.com/problems/plus-one/) | _O(n)_ | _O(1)_	| Easy | |
| [073. Set Matrix Zeroes](https://leetcode.com/problems/set-matrix-zeroes/) | _O(m\*n)_ | _O(1)_	| Medium | 🔍two pass:1. 把如果matrix\[i]\[j] == 0, 把matrix\[i]\[0] 和matrix\[0]\[j] 设为0, 如果第一列设0之前，有数为0，设col0 = 0。 2.从下往上loop, 碰到matrix\[i]\[0]] or matrix\[0]\[j] 为0, matrix\[i]\[j] = 0, if col0 == 0, matrix\[i]\[0] = 0|
| [080. Remove Duplicates from Sorted Array II](https://leetcode.com/problems/remove-duplicates-from-sorted-array-ii/) | _O(n)_ | _O(1)_	| Medium | |
| [118. Pascal's Triangle](https://leetcode.com/problems/pascals-triangle/) | _O(n^2)_ | _O(1)_	| Easy | |
| [119. Pascal's Triangle II	](https://leetcode.com/problems/pascals-triangle-ii/) | _O(n^2)_ | _O(1)_	| Easy | Easy DP |
| [121. Best Time to Buy and Sell Stock](https://leetcode.com/problems/best-time-to-buy-and-sell-stock/) | _O(n)_ | _O(1)_	| Easy |  |
| [128. Longest Consecutive Sequence](https://leetcode.com/problems/longest-consecutive-sequence/) | _O(n)_ | _O(n)_	| Hard | 🔍 <ul><li>先把所有数放进hash set 然后每次pop一个数n，设lower = n-1, upper = n+1, 持续pop lower--, upper++,直到lower,upper不在set里, 结果是max(res, upper-lower-1) </li><li>Onepass: 用hashmap记录以现在点作为边界点最大连续长，一边loop一边update不同左右边界值</li></ul>|
| [169. Majority Element](https://leetcode.com/problems/majority-element/) | _O(n)_ | _O(1)_	| Easy | |
| [189. Rotate Array](https://leetcode.com/problems/rotate-array/) | _O(n)_ | _O(1)_	| Easy | |
| [209. Minimum Size Subarray Sum](https://leetcode.com/problems/minimum-size-subarray-sum/) | _O(n)_ | _O(1)_	| Medium | 🔍 <ul><li>sliding window: 到sum >= s, 移动左面, 不断减小window且sum>=s, 寻找最小 r-l+1 </li><li>binary search: l = 1, r= size, while l<=r,检查mid作为窗口size是否满足>=s  </li><li>binary search: 建一个新的vector, newsum\[i] 表示nums\[0:i]的sum, 从新的newsum的每个点作为起点找最小满足s的窗口</li></ul> |
| [215.	Kth Largest Element in an Array](https://leetcode.com/problems/kth-largest-element-in-an-array/) | _O(n) ~ O(n^2)_ | _O(1)_	| Medium | 🔍 <ul><li> quick selection(nth_element) </li><li>heap: priority queue / multiset</li></ul> |
| [228. Summary Ranges](https://leetcode.com/problems/summary-ranges/) | _O(n)_ | _O(1)_	| Medium |  |
| [229. Majority Element II](https://leetcode.com/problems/majority-element-ii/) | _O(n)_ | _O(1)_	| Medium | 🔍Boyer-Moore Majority Vote algorithm |
| [238. Product of Array Except Self](https://leetcode.com/problems/product-of-array-except-self/) | _O(n)_ | _O(1)_	| Medium | 🔍res\[i]表示 nums\[0: i-1]的乘积，right 记录从结尾到nums\[i+1: end]的乘积. 最后res\[i] = res\[i] * right; 也可以用left, right One Pass |
| [240. Search a 2D Matrix II](https://leetcode.com/problems/search-a-2d-matrix-ii/) | _O(n+m)_ | _O(1)_	| Medium | 🔍sorted matrix题目的关键是从第一行最后一个开始，如果当前数比想要的大, --col, 如果当前数比想要的小，++row|
| [289. Game of Life](https://leetcode.com/problems/game-of-life/) | _O(m \* n)_ | _O(1)_	| Medium | 🔍跟[238. Product of Array Except Self](https://leetcode.com/problems/product-of-array-except-self/)有一点点类似，先变化matrix到想要的格式, 然后再做transform到结果: 把下一代活的| 2, 个位为1表示现在是活的，十位为1表示下代活的，res把每个cell>>=2 |
| [334. Increasing Triplet Subsequence](https://leetcode.com/problems/increasing-triplet-subsequence/) | _O(n)_ | _O(1)_	| Medium | 🔍用两个数表示b, c, c表示当前最小, b表示当前第二小, 当i都大于这两个数，return true, 不用担心i只更新更新c, 因为答案必须要迈过b |
| [384. Shuffle an Array	](https://leetcode.com/problems/shuffle-an-array/) | _O(n)_ | _O(n)_	| Medium | C++ srand(time(NULL)); rand(); uniform_int_distribution |
| [396. Rotate Function](https://leetcode.com/problems/rotate-function/) | _O(n)_ | _O(1)_	| Medium | 🔍mathematical induction F(k) = F(k-1) + sum - nBk\[-k] |
| [412. Fizz Buzz](https://leetcode.com/problems/fizz-buzz/) | _O(n)_ | _O(1)_	| Easy |  |
| [414. Third Maximum Number](https://leetcode.com/problems/third-maximum-number/) | _O(n)_ | _O(1)_	| Easy |  |
| [419. Battleships in a Board](https://leetcode.com/problems/battleships-in-a-board/) | _O(n\*m)_ | _O(1)_	| Medium | 🔍看源头，if \[i]\[j] = 'X' 且 \[i-1]\[j] 和 \[i]\[j-1] 如果都不是X，count += 1 |
| [442. Find All Duplicates in an Array](https://leetcode.com/problems/find-all-duplicates-in-an-array/) | _O(n)_ | _O(1)_	| Medium | <ul><li>把nums\[i]-1作为Index, 把nums\[index] 变成负数，如果即将变得已经是负数，代表重复</li><li>把nums\[i]-1作为Index,把nums\[i] 通过swap到nums\[index]上, 第二次pass, 如果nums\[i]!=i+1, 表示重复的</li></ul> |
| [448. Find All Numbers Disappeared in an Array](https://leetcode.com/problems/find-all-numbers-disappeared-in-an-array/) | _O(n)_ | _O(1)_	| Medium | 思路与[442. Find All Duplicates in an Array](https://leetcode.com/problems/find-all-duplicates-in-an-array/)一模一样，两种方法也一样  |
| [565. Array Nesting](https://leetcode.com/problems/array-nesting/) | _O(n)_ | _O(1)_	| Medium | DFS, 把visit的点变为-1, nest array是循环，所以起点无论是哪个点进入都可以得到完整的循环, 比如 a->b->c->d->a 不会有 a->b->c->d->b |
| [566. Reshape the Matrix](https://leetcode.com/problems/reshape-the-matrix/) | _O(m\*n)_ | _O(1)_	| Easy |  |
| [581. Shortest Unsorted Continuous Subarray](https://leetcode.com/problems/shortest-unsorted-continuous-subarray/) | _O(n)_ | _O(1)_	| Easy | 🔍<ul><li>从左起, 最后一个小于左侧最大的数为 right,从右起，最后一个大于右侧最小的数为left, res = right - left + 1 </li><li> two pointer, 当有数小于current max, 往回开始找起点start, start只能减小, end只能增加,  res = end - start + 1</li></ul>  |
| [605. Can Place Flowers](https://leetcode.com/problems/can-place-flowers/) | _O(n)_ | _O(1)_	| Easy |  |
| [643.	Maximum Average Subarray I](https://leetcode.com/problems/maximum-average-subarray-i/) | _O(n)_ | _O(1)_	| Easy | 最简单的sliding window |
| [661. Image Smoother](https://leetcode.com/problems/image-smoother/) | _O(n)_ | _O(1)_	| Easy | 跟[289. Game of Life](https://leetcode.com/problems/game-of-life/)思路一样， 一点不一样的是把下一代的数右移8个bit, 之后再第二次pass matrix, 每个点>>8 左移8个bits |
| [665. Non-decreasing Array](https://leetcode.com/problems/non-decreasing-array/) | _O(n)_ | _O(1)_	| Easy | 🔍两种operation: 1.nums\[i-1] = nums\[i] (降), nums\[i] = nums\[i-1] (升), 降优于升 |
| [667. Beautiful Arrangement II](https://leetcode.com/problems/beautiful-arrangement-ii/) | _O(n)_ | _O(1)_	| Meidum | 🔍brainstorm |
| [670. Maximum Swap](https://leetcode.com/problems/maximum-swap/) | _O(n)_ | _O(1)_	| Medium | 🔍<ul><li>Two Pass: 第一个pass 记录每个digit最后出现位置, 第二个pass: 如果有大于当前digit出现, swap & return</li><li>One Pass: 从后往前, 记录最大数的index,如果当前数小于最大数,更新进行swap的两个index，最后</li></ul> |
| [674. Longest Continuous Increasing Subsequence](https://leetcode.com/problems/longest-continuous-increasing-subsequence/) | _O(n)_ | _O(1)_	| Easy |  |
| [697. Degree of an Array](https://leetcode.com/problems/degree-of-an-array/) | _O(n)_ | _O(n)_	| Easy |  |
| [713. Subarray Product Less Than K](https://leetcode.com/problems/subarray-product-less-than-k/) | _O(n)_ | _O(1)_	| Medium | 🔍😍 Sliding Window  |
| &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; &nbsp;&nbsp;&nbsp; &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;|  |	|  | |

 
## Greedy
|Title | Time  | Space | Difficulty |  Algorithm Note|
| ------------- | ------------- | ------------- | ------------- | ------------- |
| [011. Container With Most Water](https://leetcode.com/problems/container-with-most-water/) | _O(n)_ | _O(1)_	| Medium | 🔍要按照高度来动左面和右面pointer, if height\[i]==h -> i++, if height\[j]==h -> j--, 不可以按照height前后大小if height\[i+1] >= height\[i], i++，这样会错失高度 |
| [042. Trapping Rain Water](https://leetcode.com/problems/trapping-rain-water/) | _O(n)_ | _O(1)_	| Hard | 🔍💡<ul><li>一点一点提高safe level, leftmost 代表左面最高值，rightmost表示右面最高值，谁小update 现在高度</li><li>Descending Stack: 当新高度小于现在stack的高度,update water, stack top代表底的高度, bar = stack.pop(); 否则push 现在的高度index,注意pop每次一个，否则有起伏高度不好算 </li></ul> |
| [044. Wildcard Matching](https://leetcode.com/problems/wildcard-matching/) | _O(n\*m)_ | _O(1)_	| Hard | dp or greedy |
| [045. Jump Game II](https://leetcode.com/problems/jump-game-ii/) | _O(n)_ | _O(1)_	| Hard | 🔍 <ul><li>在现有可以jump 的区域里，找这一步加上下一步可以跳的最远的, 下一次index到这个最远的index </li><li>找目前可以跳的范围内(这一跳加上下一跳)最远的点为curfastest, 当到curend时，更新curend最远点为curfast </li></ul> |
| [055. Jump Game](https://leetcode.com/problems/jump-game/) | _O(n)_ | _O(1)_	| Medium | 🔍 只有当nums\[i] = 0时，才会有可能到不了终点，看nums\[i]=0之前的点能不能跨过0点 |
| [122. Best Time to Buy and Sell Stock II](https://leetcode.com/problems/best-time-to-buy-and-sell-stock-ii/) | _O(n)_ | _O(1)_	| Medium |  |
| [134. Gas Station](https://leetcode.com/problems/gas-station/description/) | _O(n)_ | _O(1)_	| Medium | if sum(gas)>sum(cost)有解, 起点是最后一个累计sum为负后的点  |
| [135. Candy](https://leetcode.com/problems/candy/) | _O(n)_ | _O(n) O(1)_	| Hard | 🔍 开始把每个人糖assign为1，从左面和右面各loop一回，如果比邻居rate大，比较现在糖数和邻居值+1，keep大的 |
| [316. Remove Duplicate Letters](https://leetcode.com/problems/remove-duplicate-letters/) | _O(n)_ | _O(k)_	| Hard | 🔍 Ascending Stack, 可以用string 做stack, pop时候看cur char是不是在现在stack中(不重复)，还看后面有没有一样top(有一个再插入) |
| [321.	Create Maximum Number](https://leetcode.com/problems/create-maximum-number/) | _O((m+n)^3)_ | _O(k)_	| Hard | 🔍 💡  tricky, 生成array时，除了考虑后面剩下的可不可以补充上drop，还可以考虑总共要去掉len - k个 |
| [330. Patching Array](https://leetcode.com/problems/patching-array/) | _O(s + logn)_ | _O(1)_	| Hard | 🔍 tricky, 当num <= miss 表示\[0,miss)已经满足, miss+=num; else, miss\*=2, patch++ |
| [376.Wiggle Subsequence](https://leetcode.com/problems/wiggle-subsequence/) | _O(n)_ | _O(1)_	| Medium | 看有几个正负转化💡 可以用dp, python 可以用 |
| [392. Is Subsequence](https://leetcode.com/problems/is-subsequence/) | _O(n)_ | _O(1)_	| Medium | 🔍😍 easy two pointer or C++ iterator; follow-up可以用binary search; Python in iter()  |
| [397. Integer Replacement](https://leetcode.com/problems/integer-replacement/description/) | _O(log(n))_ | _O(1)_	| Medium | 🔍 tricky,如果是奇数, 看第二个bit决定+1, -1 |
| [402.	Remove K Digits](https://leetcode.com/problems/remove-k-digits/) | _O(n)_ | _O(n)_	| Medium | 😍 ascending stack |
| [435.	Non-overlapping Intervals](https://leetcode.com/problems/non-overlapping-intervals/) | _O(nlogn)_ | _O(1)_	| Medium | 💡 不要想最少删除几个，看最多可以有几个构成non-overlap的区间; Python 可以用 iter() |
| [452. Minimum Number of Arrows to Burst Balloons](https://leetcode.com/problems/minimum-number-of-arrows-to-burst-balloons/) | _O(nlogn)_ | _O(1)_	| Medium | 🔍💡  跟[435.	Non-overlapping Intervals](https://leetcode.com/problems/non-overlapping-intervals/), [056. Merge Intervals](https://leetcode.com/problems/merge-intervals/), [057. Insert Interval](https://leetcode.com/problems/insert-interval/) 类似 可以sort start 也可以sort end; Python 可以用 iter() |
| [455. Assign Cookies](https://leetcode.com/problems/assign-cookies/) | _O(nlogn)_ | _O(1)_	| Easy |  |
| [621. Task Scheduler](https://leetcode.com/problems/task-scheduler/) | _O(n)_ | _O(1)_	| Medium |🔍 用最多的字母和cooling interval构建框架, or priority_queue 代表当前可以取的字母个数 + map用于缓存  |
| [630. Course Schedule III](https://leetcode.com/problems/course-schedule-iii/) | _O(nlogn)_ | _O(k)_	| Hard |🔍 💡 移花接木  |
| [646.	Maximum Length of Pair Chain](https://leetcode.com/problems/maximum-length-of-pair-chain/) | _O(nlogn)_ | _O(1)_	| Medium |🔍 跟 [435.	Non-overlapping Intervals](https://leetcode.com/problems/non-overlapping-intervals/)思路一样|
| [649.	Dota2 Senate](https://leetcode.com/problems/dota2-senate/) | _O(n)_ | _O(n)_	| Medium |🔍💡  tricky, 一个一个R和D比，index小的赢，直到一方全军覆没 |
| [659. Split Array into Consecutive Subsequences](https://leetcode.com/problems/split-array-into-consecutive-subsequences/) | _O(n)_ | _O(n)_	| Medium |🔍💡tricky, 先看能不能以append i 到i-1的sequence,再看能不能建立新的起点 |
| [738.	Monotone Increasing Digits](https://leetcode.com/problems/monotone-increasing-digits/) | _O(1)_ | _O(1)_	| Medium |🔍brainstorming |
| [757. Set Intersection Size At Least Two](https://leetcode.com/problems/set-intersection-size-at-least-two/) | _O(nlogn)_ | _O(1)_	| Hard |🔍 💡 判断每个点是不是小于等于largest 和second largest ，如果只小于等于largest, res+=1; 如果都不小，res+=2 |
| [763.	Partition Labels](https://leetcode.com/problems/partition-labels/) | _O(n)_ | _O(n)_	| Medium |🔍😍💡  <ul><li>用hashmap记录最后char的出现位置; loop S时候，取最大的最后位置，当最大最后位置与现在位置吻合，make cut </li><li>sliding window, 前进window当现在s不是最后出现 </li></ul> |
| [767. Reorganize String](https://leetcode.com/problems/reorganize-string/) | _O(n)_ | _O(1)_	| Medium |🔍 💡😍priority_queue  |
| [798. Smallest Rotation with Highest Score](https://leetcode.com/problems/smallest-rotation-with-highest-score/) | _O(n)_ | _O(1)_	| Hard |🔍 每次从0到A.length-1得一分，A\[i]从i到i-1减一分  |
| [843. Guess the Word](https://leetcode.com/problems/guess-the-word/) | _O(n^2)_ | _O(n)_	| Hard |🔍 猜频率最大的词 或者 选取与其他词重合最多个数的中最小bar的 作为guess的单词(最多中最小的，代表分布平均, eliminate时候可以删更多)，然后根据return 值缩小范围 |
| [861. Score After Flipping Matrix](https://leetcode.com/problems/guess-the-word/) | _O(m \* n)_ | _O(1)_	| Medium |🔍 先保证第一列全是1, 然后决定toggle每一列从再最大化每一列 |
| [870. Advantage Shuffle](https://leetcode.com/problems/advantage-shuffle/) | _O(nlogn)_ | _O(n)_	| Medium |🔍😍 sort \ maxheap \ minheap |
| [881. Boats to Save People](https://leetcode.com/problems/boats-to-save-people/) | _O(nlogn)_ | _O(n)_	| Medium | two pointer |
| &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; &nbsp;&nbsp;&nbsp; &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;|  |	|  | |

## Tree
|Title | Time  | Space | Difficulty |  Algorithm Note|
| ------------- | ------------- | ------------- | ------------- | ------------- |
| [094. Binary Tree Inorder Traversal](https://leetcode.com/problems/binary-tree-inorder-traversal/) | _O(n)_ | _O(1)_	| Medium | 🔍Morris Traversal |
| [099	Recover Binary Search Tree](https://leetcode.com/problems/recover-binary-search-tree/) | _O(n)_ | _O(1)_	| Hard | 🔍调换node 之间第一个最错误的（也是最大的prev），和最后一个错误（也是最小的cur），💡顺序一定是inorder，由小到大 |
| [144. Binary Tree Preorder Traversal](https://leetcode.com/problems/binary-tree-preorder-traversal/) | _O(n)_ | _O(1)_	| Medium | Morris Traversal,注意preorder 与inorder push 进vector的顺序的区别 |
| [145. Binary Tree Postorder Traversal](https://leetcode.com/problems/binary-tree-postorder-traversal/) | _O(n)_ | _O(1)_	| Hard | 🔍Morris Traversal |
| [208. Implement Trie (Prefix Tree)](https://leetcode.com/problems/implement-trie-prefix-tree/) | _O(n)_ | _O(1)_	| Medium | Trie |
| [211. Add and Search Word - Data structure design](https://leetcode.com/problems/add-and-search-word-data-structure-design/) | _O(min(n, h))_ | _O(min(n, h))_	| Medium | 🔍Trie + DFS |
| [226.	Invert Binary Tree](https://leetcode.com/problems/invert-binary-tree/) | _O(n)_ | _O(h), O(w))_	| Easy | 🔍swap root left 和right |
| [297. Serialize and Deserialize Binary Tree](https://leetcode.com/problems/serialize-and-deserialize-binary-tree/) | _O(n)_ | _O(h)_	| Hard | 🔍 preorder 或者BFS |
| [307. Range Sum Query - Mutable](https://leetcode.com/problems/range-sum-query-mutable/) | _O(n), O(logn)_ | _O(n)_	| Medium | 🔍 BIT & Segment Tree; BIT tree 需要arr作为参照物,每次根据val-arr\[i]的update, update过后arr\[i] = val |
| [525. Contiguous Array](https://leetcode.com/problems/contiguous-array/) | _O(n)_ | _O(n)_	| Medium | 🔍把所有的0变成-1， 所以当有sum\[i,j] = 0时 => \[i,j]中有同等的1 和 0  |
| [529. Minesweeper](https://leetcode.com/problems/minesweeper/) | _O(m \* n)_ | _O(m + n)_	| Medium | recursion, 遇到数字时，停止，遇到blank持续dfs |
| [538. Convert BST to Greater Tree](https://leetcode.com/problems/convert-bst-to-greater-tree/) | _O(n)_ | _O(h)_	| Easy | postorder reverse的顺序，先loop 右侧的，然后node，然后左侧的, 💡不带ref的解 |
| [543. Diameter of Binary Tree](https://leetcode.com/problems/diameter-of-binary-tree/) | _O(n)_ | _O(h)_	| Easy | 🔍先尽可能dfs，再比较height 会更快 |
| [563. Binary Tree Tilt](https://leetcode.com/problems/binary-tree-tilt/) | _O(n)_ | _O(n)_	| Easy | 思路跟[543. Diameter of Binary Tree](https://leetcode.com/problems/diameter-of-binary-tree/) 一样|
| [572. Subtree of Another Tree](https://leetcode.com/problems/subtree-of-another-tree/) | _O(m \* n)_ | _O(h)_	| Easy | |
| [606. Construct String from Binary Tree](https://leetcode.com/problems/construct-string-from-binary-tree/) | _O(n)_ | _O(h)_	| Easy | |
| [617. Merge Two Binary Trees](https://leetcode.com/problems/merge-two-binary-trees/) | _O(n)_ | _O(h)_	| Easy | |
| [623. Add One Row to Tree](https://leetcode.com/problems/add-one-row-to-tree/) | _O(n)_ | _O(h)_	| Medium | |
| [637. Average of Levels in Binary Tree](https://leetcode.com/problems/average-of-levels-in-binary-tree/) | _O(n)_ | _O(h)_	| Easy | |
| [652. Find Duplicate Subtrees](https://leetcode.com/problems/find-duplicate-subtrees/) | _O(n)_ | _O(n\*h)_	| Medium |🔍 把tree hash 或者serialize, 然后对比hash值或者 serialize是否只出现一次,  |
| [653. Two Sum IV - Input is a BST](https://leetcode.com/problems/two-sum-iv-input-is-a-bst/) | _O(n)_ | _O(h)_	| Easy |🔍two pointer or BST Iterator; Python BSTIterator: property + setter |
| [654. Maximum Binary Tree](https://leetcode.com/problems/maximum-binary-tree/) | _O(n)_ | _O(h)_	| Medium |🔍💡 descending stack: <ul><li> 如果现在数 num\[i] 小于stack top，stack.top->right = new TreeNode(nums\[i]) </li><li> 如果现在num\[i] 大于stack top，就不断pop stack 找最后一个小于nums\[i]的node，把最后的node 作为nums\[i]的left child </li></ul>  |
| [655. Print Binary Tree](https://leetcode.com/problems/print-binary-tree/) | _O(n)_ | _O(h)_	| Medium | 找规律 |
| [662. Maximum Width of Binary Tree](https://leetcode.com/problems/maximum-width-of-binary-tree/) | _O(n)_ | _O(h)_	| Medium | 找规律 |
| [677. Map Sum Pairs](https://leetcode.com/problems/map-sum-pairs/) | _O(n)_ | _O(t)_	| Medium | Trie 注意更新时候，要减去之前的val or map + lower_bound |
| [684. Redundant Connection](https://leetcode.com/problems/redundant-connection/) | _O(n)_ | _O(n)_	| Medium | 🔍Union Find 如果两个node 连接之前发现parent 已经一样，表示之前两个nodes已经连接，如果再连接edge，会构成cycle |
| [685. Redundant Connection II](https://leetcode.com/problems/redundant-connection-ii/) | _O(n)_ | _O(n)_	| Hard | 🔍Union Find 注意构成tree 的条件, 不能有一个child 连上两个parent, 然后去掉这个child一个链，保证都是一个child对应一个parent, 再看有没有cycle, 没有cycle表示去链去成功了, 有cycle 表示去链去错了 |
| [687. Longest Univalue Path](https://leetcode.com/problems/longest-univalue-path/) | _O(n)_ | _O(h)_	| Easy | 🔍DFS |
| [699. Falling Squares](https://leetcode.com/problems/falling-squares/) | _O(nlogn)_ | _O(n)_	| Hard | 🔍💡<ul><li> solution 1: 解法与 [218. The Skyline Problem](https://leetcode.com/problems/the-skyline-problem/)相似, 画出轮廓, 并对比现在高度和最高点 </li><li> 用heights 表示到i点的高度, 再从i点往后，更新后面点的地基 </li><li> Segment Tree using lazy initialization: 需要注意update即使不在范围内，也要返回root.val, update还要更新root.val为max值 </li></ul> |
| [814. Binary Tree Pruning](https://leetcode.com/problems/binary-tree-pruning/) | _O(n)_ | _O(h)_	| Medium | 🔍DFS |
| [850. Rectangle Area II](https://leetcode.com/problems/rectangle-area-ii/description/) | _O(nlogn)_ | _O(h)_	| Hard | 🔍💡跟[699. Falling Squares](https://leetcode.com/problems/falling-squares/)思路有点像, 根据height一层一层的算当层长方体面积,算完面积后更新上一层的底curx |
| [863. All Nodes Distance K in Binary Tree](https://leetcode.com/problems/all-nodes-distance-k-in-binary-tree/) | _O(n)_ | _O(h)_	| Medium | 🔍💡需要DFS + BFS, DFS 找到双向(parent->child, child->parent), BFS 比如距离k, 从target点为起点通过通道找距离k的所有点 |
| [865. Smallest Subtree with all the Deepest Nodes](https://leetcode.com/problems/smallest-subtree-with-all-the-deepest-nodes/) | _O(n)_ | _O(h)_	| Medium | 🔍DFS, left level == right level 返回root, if left level > right level, 返回left dfs的node else返回right dfs的  |
| [889. Construct Binary Tree from Preorder and Postorder Traversal	](https://leetcode.com/problems/construct-binary-tree-from-preorder-and-postorder-traversal/) | _O(n)_ | _O(h)_	| Medium | 🔍💡难点是找到 left 和right的边界 or 用stack: 当back val 与postorder一样是 pop, 当left 没有child,append left, 否则append到 |
| &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; &nbsp;&nbsp;&nbsp; &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;|  |	|  | |



## Math
|Title | Time  | Space | Difficulty |  Algorithm Note|
| ------------- | ------------- | ------------- | ------------- | ------------- |
| [007. Reverse Integer](https://leetcode.com/problems/reverse-integer/) | _O(1)_ | _O(1)_	| Easy |  |
| [009. Palindrome Number](https://leetcode.com/problems/palindrome-number/) | _O(1)_ | _O(1)_	| Easy |  |
| [012. Integer to Roman](https://leetcode.com/problems/integer-to-roman/) | _O(n)_ | _O(1)_	| Medium |  |
| [013. Roman to Integer](https://leetcode.com/problems/roman-to-integer/) | _O(n)_ | _O(1)_	| Easy |  |



## String
|Title | Time  | Space | Difficulty |  Algorithm Note|
| ------------- | ------------- | ------------- | ------------- | ------------- |
| [005.Longest Palindromic Substring](https://leetcode.com/problems/longest-palindromic-substring/) | _O(n)_ | _O(n)_	| Medium | 🔍 manacher(马拉车算法), mx表示当前最长回文外右侧第一点, id是当前回文中心, p\[i]表示当前最长回文, if i<mx, p\[i] = min(p\[2id-i], p\[i]) |
| [006. ZigZag Conversion](https://leetcode.com/problems/zigzag-conversion/) | _O(n)_ | _O(n)_	| Medium | <ul><li>把string 循环push到一个长度为nrow的vector当中</li><li>用step = 2*nrows - 2 控制每次jump step, 到中间行看是否jump step之间有夹的元素</li></ul>|
| [008. String to Integer (atoi)](https://leetcode.com/problems/string-to-integer-atoi/) | _O(n)_ | _O(1)_	| Easy | C++可以用find_first_not_of |
| [014. Longest Common Prefix](https://leetcode.com/problems/longest-common-prefix/) | _O(n)_ | _O(1)_	| Easy | loop所有数第0位到第i位，直到不相同,返回str\[0].substr(0,i) |
| [028. Implement strStr()](https://leetcode.com/problems/implement-strstr/) | _O(n+k)_ | _O(k)_	| Easy | kmp algorithm: prefix array\[i]表示i点的最长的prefix 也是suffix长度 比如"ABA", 第三个a的最长的prefix 也是suffix 的长度是1 A 而prefix array\[i], 作为index, 是当前最长prefix 也是suffix 的下一位|
| [038. Count and Say](https://leetcode.com/problems/count-and-say/) | _O(n \* 2^n)_ | _O(n2^n)_	| Easy | C++ find_if + bind1st|
| [043. Multiply Strings](https://leetcode.com/problems/multiply-strings/) | _O(m\*n)_ | _O(m+n)_	| Medium | C++ transform, 必须都从个位数(也就是string的最后一位开始算, 否则carry可能会超过10), back_inserter, 相当于按照原来从头到尾顺序push back|
| [058. Length of Last Word](https://leetcode.com/problems/length-of-last-word/) | _O(n)_ | _O(1)_	| Easy | C++ find if or find if + bind1st or string find_last_not_of + find_last_of |
| [067. Add Binary	](https://leetcode.com/problems/add-binary/) | _O(n)_ | _O(1)_	| Easy | string 加法, 跟[415. Add Strings](https://leetcode.com/problems/add-strings/) 和[306. Addictive Number](https://leetcode.com/problems/additive-number/) 类似  |
| [068. Text Justification](https://leetcode.com/problems/text-justification/) | _O(n)_ | _O(1)_	| Hard | not a hard question, 跟[725. Split Linked List in Parts](https://leetcode.com/problems/split-linked-list-in-parts/) 类似 |
| [125. Valid Palindrome](https://leetcode.com/problems/valid-palindrome/) | _O(n)_ | _O(1)_	| Easy | C++ 跳过非isalnum的 |
| [151. Reverse Words in a String](https://leetcode.com/problems/reverse-words-in-a-string/) | _O(n)_ | _O(1)_	| Medium | 先reverse所有的, 再reverse单个每个词, 记录总共len,最后用来截取, C++ find_first_not_of + find_first_of |
| [165. Compare Version Numbers](https://leetcode.com/problems/compare-version-numbers/) | _O(n)_ | _O(1)_	| Medium | c++ 算当前version1,2的substr的数，如果其中一个碰到结尾，设当前数位0。 c, 可以用c_str() + strtol; python3 zip(\*itertools.zip_longest(\*splits, fillvalue=0)) |
| [214. Shortest Palindrome](https://leetcode.com/problems/shortest-palindrome/) | _O(n)_ | _O(n)_	| Hard |🔍可以把此题换一种问法: 以index0开始最长的部分palindrome 的长度, 部分最长的pal后面的掉个+s = 答案  <ul><li>KMP: s+"#"+reverse(s), prefix array最后一位是部分最长的pal的长度, kmp prefix 即是suffix，pal是掉个也相等, 所以最后一位是部分最长  </li><li>马拉车(manacher): 不断找最大的回文长，但一边更新右边界时, 只更新mxlen 当p\[i]==i的时候, 最长回文从0开始</li></ul>  |
| [242. Valid Anagram](https://leetcode.com/problems/valid-anagram/) | _O(n)_ | _O(1)_	| Easy | 经典面试题 |
| [273. Integer to English Words](https://leetcode.com/problems/integer-to-english-words/) | _O(1)_ | _O(1)_	| Hard | 无聊的recursion |
| [306. Addictive Number](https://leetcode.com/problems/additive-number/) | _O(n^3)_ | _O(n)_	| Medium | recursion 从index0开始试所有的digit可能性直到成功, 比如开始是一位+两位, 还是三位+两位 , 需要一个string add的help function; python 可以用itertools.combination + startswith, 跟[067. Add Binary	](https://leetcode.com/problems/add-binary/) 和[415. Add Strings](https://leetcode.com/problems/add-strings/) 类似, 只不过多个recursion  |
| [383. Ransom Note](https://leetcode.com/problems/ransom-note/) | _O(n)_ | _O(n)_	| Easy | Hash map |
| [405. Convert a Number to Hexadecimal](https://leetcode.com/problems/convert-a-number-to-hexadecimal/) | _O(n)_ | _O(1)_	| Easy | 最后结果需要reverse，因为先插入最小的，注意负数的, -1>>4 = -1, 所以while加个条件 res.length()!=sizeof(int)\*2 |
| [415. Add Strings](https://leetcode.com/problems/add-strings/) | _O(n)_ | _O(1)_	| Easy | string加法，跟[067. Add Binary	](https://leetcode.com/problems/add-binary/) 和[306. Addictive Number](https://leetcode.com/problems/additive-number/) 类似 |
| [420. Strong Password Checker](https://leetcode.com/problems/strong-password-checker/) | _O(n)_ | _O(1)_	| Hard | Brain Storm 详见C++ code 解释|
| [434. Number of Segments in a String](https://leetcode.com/problems/number-of-segments-in-a-string/) | _O(n)_ | _O(1)_	| Easy | 🔍, 根据s\[i] 和 s\[i-1]判断, or s\[i] 和 s\[i+1]判断 |
| [443. String Compression](https://leetcode.com/problems/string-compression/) | _O(n)_ | _O(1)_	| Easy | two pointer + num reverse |
| [459. Repeated Substring Pattern](https://leetcode.com/problems/repeated-substring-pattern/) | _O(n)_ | _O(n)_	| Easy | KMP |
| [468. Validate IP Address](https://leetcode.com/problems/validate-ip-address/) | _O(1)_ | _O(1)_	| Medium | 注意IPv4 和IPv6的定义(c++ code里), 判断一个char是不是符合十六进制用isxdigit(c) |
| [520. Detect Capital](https://leetcode.com/problems/detect-capital/) | _O(1)_ | _O(1)_	| Easy | C++ count_if; Python istitle()看是不是只有首字母大写 |
| [521. Longest Uncommon Subsequence I](https://leetcode.com/problems/longest-uncommon-subsequence-i/) | _O(min(a, b))_ | _O(1)_	| Easy | 题出的神经病，逗你玩儿 |
| [522. Longest Uncommon Subsequence II](https://leetcode.com/problems/longest-uncommon-subsequence-ii/) | _O(l \* n^2)	_ | _O(1)_	| Medium | 🔍按照字母长度sort, 然后一个一个看str，有没有在list中有subsequence，没有的话, return 这个str长度,直到全部search完, return -1 or C++ equal_range + count_if , python 可以iter()|
| [524.	Longest Word in Dictionary through Deleting](https://leetcode.com/problems/longest-word-in-dictionary-through-deleting/) | _O((d \* l) * logd)_ | _O(1)_	| Medium | 按照字母长度sort,如果长度一样，按照alphabet sort, 找到第一个符合的  🔍python, max with key, min with key, filter,  iter + next with default |
| [539. Minimum Time Difference](https://leetcode.com/problems/minimum-time-difference/) | _O(nlogn)_ | _O(n)_	| Medium | C++ transform 把所有时间变分钟, 然后按minute sort, 答案就出自所有minute\[i+1] - minute\[i] or 1440 +minute\[0] -  minute.back() |
| [541. Reverse String II](https://leetcode.com/problems/reverse-string-ii/) | _O(n)_ | _O(1)_	| Easy |  |
| [551. Student Attendance Record I](https://leetcode.com/problems/student-attendance-record-i/) | _O(n)_ | _O(1)_	| Easy |  |
| [556.	Next Greater Element III](https://leetcode.com/problems/next-greater-element-iii/) | _O(1)_ | _O(1)_	| Medium |  可以用ascending stack or 两个for loop, 寻找i点往后最后一个比i点大的数(也是比i大,最接近i的数)(index j), swap(s\[i], s\[j]), 这样s\[i]后面的数又大到小排序的, 把i往后的数到end全部reverse后变成Int, 就是答案, 跟[031. Next Permutation](https://leetcode.com/problems/next-permutation/)思路类似 |
| [564. Find the Closest Palindrome](https://leetcode.com/problems/find-the-closest-palindrome/) | _O(l)_ | _O(l)_	| Hard | Brain Storm: 最接近的pal只可能5中选一, 100..001(l.size()+1), 99..99(l.size()-1), or string的前半部分 +1, +0, -1 加上前半部分的reverse(如果起始长度是奇数，reverse不包括前半部分最后一个，如果长度是偶数，都包括在内) |
| [591. Tag Validator](https://leetcode.com/problems/tag-validator/) | _O(n)_ | _O(n)_	| Hard | cdata 必须以 已 ]]>结束, recursion 找是不是valid tag, valid cdata, valid tagname  |
| [647. Palindromic Substrings](https://leetcode.com/problems/palindromic-substrings/) | _O(n)_ | _O(n)_	| Medium | 🔍 manacher(马拉车算法), 在snew中 p\[i]表示以id为中心最长回文，到i点，res += p\[i] /2  |
| [648. Replace Words](https://leetcode.com/problems/replace-words/) | _O(n)_ | _O(t)_	| Medium | 🔍 Trie; python 可以用reduce + dict.\_\_getitem__ |
| [657. Judge Route Circle](https://leetcode.com/problems/judge-route-circle/) | _O(n)_ | _O(1)_	| Easy |  |
| [678. Valid Parenthesis String](https://leetcode.com/problems/valid-parenthesis-string/) | _O(n)_ | _O(1)_	| Medium | 🔍Three Solutions<ul><li>用low 和high: low 表示把 '\*' 当成 ')', high: 表示把 '\*' 当成'(', 如果high小于0，表示有太多的')' '(' + '\*' = high < ')' </li><li>用两个stack 分别记录 '(' 和 '\*'的位置, 如果当前是')', 先pop '(' 再pop '\*'; 最后看'(' 有没有对应index往后的的 '\*'可以pop掉, </li><li> Two pass solution 从左向右看是不是所有的')' 都有对应的 '(' 和 '\*', 再从右向左看是不是所有的 '(', 都有对应的 ')' 和' \*' </li></ul> |
| [680. Valid Palindrome II](https://leetcode.com/problems/valid-palindrome-ii/) | _O(n)_ | _O(1)_	| Easy | 🔍两个pointer,  检查s\[i] == s\[j]?, 遇到不等时，再看s\[i+1, j], or s\[i, j-1]是不是pal |
| [686. Repeated String Match](https://leetcode.com/problems/valid-palindrome-ii/) | _O(n+m)_ | _O(n)_	| Easy | 🔍<ul><li>Kmp: 然后两个pointer, 一个pointer i 记录A的位置，一个pointer j记录B的位置，每次对比 A\[(i + j)%A.size()] 是否等于B\[j] 等于就++j., 直到 j =  b.size() return ceil((i+j)/a.size()) </li><li> rabin-karp algorithm, 寻找最短的长度一直到最大长度的hash </li></ul> |
| [696.	Count Binary Substrings](https://leetcode.com/problems/count-binary-substrings/) | _O(n)_ | _O(1)_	| Easy | manacher(马拉车)算法的变形 |
| [720. Longest Word in Dictionary](https://leetcode.com/problems/longest-word-in-dictionary/) | _O(n)_ | _O(t)_	| Easy | Trie or 先按长度sort, 长度越短, 排前面, loop word, loop s\[i]\[0,len), 看是不是每个substr都在，都在话insert to hashset & update result |
| [722. Remove Comments](https://leetcode.com/problems/remove-comments/) | _O(n)_ | _O(k)_	| Medium | |
| [791. Custom Sort String](https://leetcode.com/problems/custom-sort-string/) | _O(n)_ | _O(k)_	| Medium | 可以当经典面试题, 三种解法: <ol><li>Custom Sort (or STL inserter + make_pair)</li><li>Bucket Sort</li><li>Priority Queue</li></ol>|
| [796. Rotate String](https://leetcode.com/problems/rotate-string/) | _O(n)_ | _O(1)_	| Easy | 🔍两种kmp的解, <ul><li>跟[686. Repeated String Match](https://leetcode.com/problems/valid-palindrome-ii/)一样, 详见686的C++ code 解释 </li><li>pattern = B, text = A + A, 看text中有没有pattern </li></ul> |
| [804. Unique Morse Code Words](https://leetcode.com/problems/unique-morse-code-words/) | _O(n)_ | _O(n)_	| Easy | Easy one unordered_set  |
| [806.Number of Lines To Write String](https://leetcode.com/problems/number-of-lines-to-write-string/) | _O(n)_ | _O(1)_	| Easy | Easy one but stupid question description  |
| [809. Expressive Words](https://leetcode.com/problems/expressive-words/) | _O(n+s)_ | _O(1)_	| Medium | Two pointer: 如果word\[i]!=S\[j] 的时候， 看S的j-1, j, j+1是不是连续是三个，若不是，再看过去是不是连续三个，若不是，break |
| [816. Ambiguous Coordinates](https://leetcode.com/problems/ambiguous-coordinates/) | _O(n^3)_ | _O(n)_	| Medium | 🔍选择小数点的关键是 不能左面位0， 右面结束也是0，比如00.1230不可以,但是即使左面等于0， 右面最后也不可以是0|
| [819. Most Common Word](https://leetcode.com/problems/most-common-word/) | _O(n+m)_ | _O(m+n)_	| Easy | |
| [820. Short Encoding of Words](https://leetcode.com/problems/goat-latin/) | _O(n)_ | _O(t)_	| Medium | <ul><li> Trie: 看叶子有没有child </li><li>sort string vector, 只用对比s\[i] 和 s\[i+1]</li></ul>|
| [824. Goat Latin](https://leetcode.com/problems/goat-latin/) | _O(n + w^2)_ | _O(l)_	| Easy | stringstream 作为string output  |
| [831. Masking Personal Information](https://leetcode.com/problems/masking-personal-information/) | _O(1)_ | _O(1)_	| Easy | C++ transform 把所有字母都小写, s\[0] 变成string 可以用 s.substr(0,1) or string(1,S\[0])  |
| [833. Find And Replace in String](https://leetcode.com/problems/find-and-replace-in-string/) | _O(m+n)_ | _O(n)_	| Medium | 先sort indexes,然后从后往前loop S,这样可以保持S前面的index不变, python 可以用zip + startswith  |
| [839. Similar String Groups](https://leetcode.com/problems/similar-string-groups/) | _O(n^2 \* l)_ | _O(n)_	| Easy | 🔍 Union Find Disjoint Set with Rank Heuristic |
| [848. Shifting Letters](https://leetcode.com/problems/shifting-letters/) | _O(n)_ | _O(1)_	| Medium | 加的时候及时%26, 小心overflow  |
| [859. Buddy Strings](https://leetcode.com/problems/buddy-strings/) | _O(n)_ | _O(1)_	| Easy | 判断条件: 1.长度不一样，false，2. 如果a == b，有没有重复的字母，有的话true, 没有false, 3, 如果不一样的位置个数不等于2, 或者a\[diff\[0]]!=b\[diff\[1]] or a\[diff\[1]]!=a\[diff\[1]] 返回false, 否则是true  |
| &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; &nbsp;&nbsp;&nbsp; &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;|  |	|  | |


## Regular Expression Summary
|summary |
| ------------- |
|  <ul><li>regex_match 是从头开始到结尾结束都要match的, 可以用string + regex, regex_match(string, regex()); or Iterator + regex: regex_match ( s.begin(), s.end(), regex()), 返回值match是不是成功 </li><li>regex_search 是寻找entire string, 有没有substring满足regex的, 可以用string + regex, regex_search(string, regex()) or Iterator + regex: regex_search ( s.begin(), s.end(), regex())</li><li> regex_replace 是寻找entire string match pattern的部分,用其他的string代替它, 返回值新生成的string, replace 不会修改原来string s。 regex_replace(s, regex(), "geek"); 或者把替代的生成到另一个新的string: string result; regex_replace(back_inserter(result), s.begin(), s.end(), regex(),  "geek");</li><ul></br> [reference](http://www.runoob.com/regexp/regexp-syntax.html) [reference2](https://www.regular-expressions.info/shorthand.html) <li>+: 前面的子表达式出现一次或多次 ro+b，可以匹配 roob、rob、rooob </li>                                                             <li>\*: 前面的子表达式出现0次、或1次、或多次ro+b，可以匹配 rb、rob、rooob</li>                                                               <li>\?: 前面的子表达式出现0次、或1次 colou?r，可以匹配 color、colour</li>                                                                   <li>{n}	n 是一个非负整数。匹配确定的 n 次。例如，'o{2}' 不能匹配 "Bob" 中的 'o'，但是能匹配 "food" 中的两个 o。</li>                     <li> {n,}	n 是一个非负整数。至少匹配n 次。例如，'o{2,}' 不能匹配 "Bob" 中的 'o'，但能匹配 "foooood" 中的所有 o。'o{1,}' 等价于 'o+'。'o{0,}' 则等价于 'o*'。 </li> <li> {n,m}	m 和 n 均为非负整数，其中n <= m。最少匹配 n 次且最多匹配 m 次。例如，"o{1,3}" 将匹配 "fooooood" 中的前三个 o。'o{0,1}' 等价于 'o?'。请注意在逗号和两个数之间不能有空格。</li>  <li>\|	指明两项之间的一个选择。比如 "A.\|B" 匹配 CAA 也匹配 CB</li>    <li>.	匹配除换行符 \n 之外的任何单字符。 比如A. 匹配AD</li>                                                        <li>^	匹配输入字符串的开始位置，除非在方括号表达式中使用，此时它表示不接受该字符集合。比如^A, 表示字符以A开始, 比如\^[0-9] 表示不含有数字</li>                                                    <li>$	匹配输入字符串的结尾位置。如果设置了 RegExp 对象的 Multiline 属性，则 $ 也匹配 '\n' 或 '\r'。比如C$ 字符串以C结尾</li> <li>\w	匹配任何word character short version for \[A-Za-z0-9_], \W is short for \[^\w]。</li> <li> \s stands for "whitespace character"  \S is the equivalent of \[^\s]</li> <li>  \d is short for \[0-9],\[0-9] is not always equivalent to \d. In python3, \[0-9] matches only 0123456789 characters, while \d matches [0-9] and other digit characters, for example Eastern Arabic numerals ٠١٢٣٤٥٦٧٨٩  \D is the same as \[^\d]</li>  </li></ul></ul> difference between () \[], <ul><li>\[] denotes a character class. () denotes a capturing group.</li> <li>\[a-z0-9] -- One character that is in the range of a-z OR 0-9, (a-z0-9) -- Explicit capture of a-z0-9. No ranges. </li> <li>a -- Can be captured by \[a-z0-9]., a-z0-9 -- Can be captured by (a-z0-9) and then can be referenced in a replacement and/or later in the expression</li> <ul>.|

## Bit Manipulation
|Title | Time  | Space | Difficulty |  Algorithm Note|
| ------------- | ------------- | ------------- | ------------- | ------------- |
| [136. Single Number](https://leetcode.com/problems/single-number/) | _O(n)_ | _O(1)_	| Easy | 用xor ^, Python Reduce one line |
| [137. Single Number II](https://leetcode.com/problems/single-number-ii/) | _O(n)_ | _O(1)_	| Medium | 🔍<ul><li>第一次出现-> save it in "ones", 第二次出现 -> clear "ones" but save it in "twos" for later check,  第三次出现 -> try to save in "ones" but value saved in "twos" clear it.</li><li>loop through 32个bit, 每个bit再loop nums, if bit & nums[i] => c++, 如果c不是3个倍数，最终结果在现在这个bit上位1</li></ul> |
| [190. Reverse Bits](https://leetcode.com/problems/reverse-bits/) | _O(1)_ | _O(1)_	| Easy | 一位一位reverse bit, res每次向左移动一位，n向右移动一位 |
| [191. Number of 1 Bits](https://leetcode.com/problems/number-of-1-bits/) | _O(n)_ | _O(1)_	| Easy | n = n & (n-1); |
| [201. Bitwise AND of Numbers Range](https://leetcode.com/problems/bitwise-and-of-numbers-range/) | _O(1)_ | _O(1)_	| Medium | 一位一位比较digit，直到移动k位m=n, 那么此时的digit是bitwise and的结果, res = m<<k |
| [231. Power of Two](https://leetcode.com/problems/power-of-two/) | _O(1)_ | _O(1)_	| Easy | n = n & (n-1); |
| [260. Single Number III](https://leetcode.com/problems/single-number-iii/) | _O(n)_ | _O(1)_	| Medium | 🔍两个pass,第一个pass, 通过Xor需要区分a 和 b的数 c(是a与b右面第一位不一样的数), 第二次pass, 通过c&nums\[i]判断做xor, 找到a和b (binary 负数) |
| [268. Missing Number](https://leetcode.com/problems/missing-number/) | _O(n)_ | _O(1)_	| Medium | Math, Swap, Xor |
| [318. Maximum Product of Word Lengths](https://leetcode.com/problems/maximum-product-of-word-lengths/) | _O(n^2)_ | _O(n)_	| Medium | 🔍可以用bit来判断两个string是不是有重合的字母, 用数字表示string, a是第一位被set，z是第26位被set, |
| [342. Power of Four](https://leetcode.com/problems/power-of-four/) | _O(1)_ | _O(1)_	| Easy | 4^n = (3+1)^n, 除了判断(n&n-1) , 还要判断n-1 是不是可以整除3 |
| [371. Sum of Two Integers](https://leetcode.com/problems/sum-of-two-integers/) | _O(1)_ | _O(1)_	| Easy | （a&b)<<1 表示需要相加进位的（两个1相加）, a ^ b 表示相加不进位（保留单个1） |
| [389. Find the Difference](https://leetcode.com/problems/find-the-difference/) | _O(1)_ | _O(1)_	| Easy | 🔍找两个string唯一不同不同的char可以通过 xor |
| [393. UTF-8 Validation](https://leetcode.com/problems/utf-8-validation/) | _O(n)_ | _O(1)_	| Easy | 用count判断是不是起点, count==0 是起点 |
| [421. Maximum XOR of Two Numbers in an Array](https://leetcode.com/problems/maximum-xor-of-two-numbers-in-an-array/) | _O(nlogk)_ | _O(n)_	| Medium | 🔍<ul><li>从第32位开始到第0位逐渐缩小范围, 比如第5位有a,b,c,d 四个数xor都是最大的，第四位就可能会缩减到a,c; 利用性质: a ^ b = c =>  a ^ c = b </li><li> Trie </li></ul> |
| [461. Hamming Distance](https://leetcode.com/problems/hamming-distance/) | _O(1)_ | _O(1)_	| Easy | 判断有多少bit, 与[191. Number of 1 Bits](https://leetcode.com/problems/number-of-1-bits/)和 [231. Power of Two](https://leetcode.com/problems/power-of-two/)类似 |
| [462	Minimum Moves to Equal Array Elements II](https://leetcode.com/problems/minimum-moves-to-equal-array-elements-ii/description/) | _O(nlogn)_ | _O(1)_	| Medium | 🔍Meeting point, 先sort，然后逐个用最大减去最小, e.g \[3,6,9], 不管中间点在哪，都要磨平9-3=6的差距 |
| [477. Total Hamming Distance](https://leetcode.com/problems/total-hamming-distance/description/) | _O(nlogk)_ | _O(1)_	| Easy | 由第32位到第0位，loop每个bit，数当前bit位为1的个数为bitcount, 结果 res+= bitcount*(size-countsize), 与[421. Maximum XOR of Two Numbers in an Array](https://leetcode.com/problems/maximum-xor-of-two-numbers-in-an-array/)类似 |
| [645. Set Mismatch](https://leetcode.com/problems/set-mismatch/) | _O(n)_ | _O(1)_	| Easy | <ul><li>bit Xor:与[260. Single Number III](https://leetcode.com/problems/single-number-iii/) 解法一样, 第一次pass,找到两个数的xor = c, c & (-c)是unique的digit, 第二次pass分别找到这两个数，第三次pass调整两个数return的顺序 </li><li>改变nums\[abs(nums\[i])-1] 为负数, 如果发现新找到的已经为负数, 证明是重复的，第二次pass, 如果发现某位为正数, 代表是missing的 </li></ul> |
| [693. Binary Number with Alternating Bits](https://leetcode.com/problems/binary-number-with-alternating-bits/) | _O(1)_ | _O(1)_	| Easy | 🔍 |
| [762. Prime Number of Set Bits in Binary Representation](https://leetcode.com/problems/prime-number-of-set-bits-in-binary-representation/) | _O(R-L)_ | _O(1)_	| Easy | loop\[L,R],数每个数多少个bit，因为log2(10^6) < 16, 事先把所有的prime存到hash set里面, 看现在bit数是不是质数，if so res++, 还可以用 \__builtin_popcountl(n); bitset<32>(n).count() |
| &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; &nbsp;&nbsp;&nbsp; &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;|  |	|  | C++ 0b表示binary number，比如0b10 = 2, 0b111 = 7</br> python 0b表示binary number，比如0b10 = 2, 0b111 = 7 <ul><li>注意运算顺序</li><li> +, - 先于 &, \|, <<, >>; 所以不用括号 n&n-1 </li><li> << >> == 是优于&,\| ; 判断&, 需要加括号,比如(n& n-1) == 0; </li><li> &,\|优于 && \|\| ; (1&2 && 2) = 0 && 2 = false; </li></ul> bit数1的个数，可以用 n&(n-1); \__builtin_popcountl(n); bitset<32>(n).count() |



## Hash Table
|Title | Time  | Space | Difficulty |  Algorithm Note|
| ------------- | ------------- | ------------- | ------------- | ------------- |
| [001	Two Sum](https://leetcode.com/problems/two-sum/) | _O(n)_ | _O(n)_	| Easy | |
| [003. Longest Substring Without Repeating Characters](https://leetcode.com/problems/longest-substring-without-repeating-characters/) | _O(n)_ | _O(n)_	| Medium | |
| [030. Substring with Concatenation of All Words	](https://leetcode.com/problems/substring-with-concatenation-of-all-words/) | _O((m+n)\*k)_ | _O(n\*k)_	| Hard | 🔍k = word\[0]长度, n = 整个words长度, m = S的长度。最快的解是两个map, map1记录words的每个string, | map2记录S的substr，substr每次移动k个, 直到当前window长度 == n\*k, res append(start) |
| [036. Valid Sudoku](https://leetcode.com/problems/valid-sudoku/) | _O(9\*9)_ | _O(9)_	| Medium |🔍 用bit比较快，比如i在横着第2行出现, row\[2] |= 1<<i; 如果row\[i] & id == 1: return false |
| [049. Group Anagrams](https://leetcode.com/problems/group-anagrams/) | _O(n * glogg)_ | _O(n)_	| Medium | 经典 面试题, python list不能作为字典的key,但是tuple可以 |
| [076. Minimum Window Substring](https://leetcode.com/problems/minimum-window-substring/) | _O(n)_ | _O(k)_	| Hard | 🔍sliding windows, 此题没有窗口的size，要去找最小的size，关键是如何确定window valid，记录每次滑到cur char也在T中出现的个数，当个数满足T.size(),证明window valid，然后逐步缩小start与i的距离，找最小点 |
| [149. Max Points on a Line](https://leetcode.com/problems/max-points-on-a-line/) | _O(n^2)_ | _O(n)_	| Hard | 每到一点，算跟别的点的斜率，注意1. 重合的点，2.斜率没有的定义的点, 在每一点都重新建一个hashmap |
| [187. Repeated DNA Sequences](https://leetcode.com/problems/repeated-dna-sequences/) | _O(n)_ | _O(n)_	| Medium |🔍 rolling hash (rabin-karp), <ul><li>A = 00, C = 01, G = 10, T = 11, i大于9后 t>>2 & 0xfffff(2^18-1) 做&运算</li><li>直接把A,C,G,T默认转化成ASCII，与&7, 后三位是unique的，i>9后做 t << 3 & 0x3FFFFFFF</li></ul> |
| [202. Happy Number](https://leetcode.com/problems/happy-number/) | _O(k)_ | _O(k)_	| Easy | 要么是happy number，要么转化过程陷入循环 |
| [204. Count Primes](https://leetcode.com/problems/count-primes/) | _O(n)_ | _O(n)_	| Easy | count从小往大后eliminate，注意要尽可能efficient |
| [205.	Isomorphic Strings ](https://leetcode.com/problems/isomorphic-strings/) | _O(n)_ | _O(1)_	| Easy | 可以记录相同位置字母出现的上一位，或者把s,t字母相互关联起来, python 可以用find+map or zip+set |
| [217. Contains Duplicate ](https://leetcode.com/problems/contains-duplicate/) | _O(n)_ | _O(n)_	| Easy | easy one, 可以用sort + unique |
| [219. Contains Duplicate II](https://leetcode.com/problems/contains-duplicate-ii/) | _O(n)_ | _O(n)_	| Easy | easy one |
| [290. Word Pattern](https://leetcode.com/problems/word-pattern/) | _O(n)_ | _O(n)_	| Easy | 思路和[205.	Isomorphic Strings ](https://leetcode.com/problems/contains-duplicate/)一样|
| [299. Bulls and Cows](https://leetcode.com/problems/bulls-and-cows/) | _O(n)_ | _O(1)_	| Easy | One pass: 如果guess\[i] 和 secret\[i]一样, bull++, 不一样，++m\[sec\[i]], --m\[guess\[i]] python 可以用两个collectons.Counter相减, 得到重合的set|
| [336. Palindrome Pairs](https://leetcode.com/problems/palindrome-pairs/) | _O(n \* k^2)_ | _O(n\*k)_	| Hard |🔍trie  |
| [387. First Unique Character in a String](https://leetcode.com/problems/first-unique-character-in-a-string/) | _O(n)_ | _O(n)_	| Easy | 需要 two pass |
| [388. Longest Absolute File Path](https://leetcode.com/problems/longest-absolute-file-path/) | _O(n)_ | _O(d)_	| Medium | map记录每一层现有的长度,到新的或者原来一层，更新map, res是max(map中含有“.”的一层), 用到string::find, string::find_first_not_of, std::find  |
| [409. Longest Palindrome](https://leetcode.com/problems/longest-palindrome/) | _O(n)_ | _O(1)_	| Easy | 可以用std::count, 或者可以来回flip map, 当map位true +2 |
| [424. Longest Repeating Character Replacement](https://leetcode.com/problems/longest-repeating-character-replacement/) | _O(n)_ | _O(1)_	| Medium | 🔍sliding window: 记录window的初始点, 如果当前长度 - 最大count > k, ++start(保持windows的最大长度), 如果满足，start不变，结果是s.size()-start |
| [438. Find All Anagrams in a String](https://leetcode.com/problems/find-all-anagrams-in-a-string/) | _O(n)_ | _O(1)_	| Easy | sliding window: 跟[567. Permutation in String](https://leetcode.com/problems/permutation-in-string/)思路一样 <ul><li>保持window的长度不变, 用l算p中还剩几个点没有被数过 </li><li>用right和left, 当right和left之间长度 == p的长度,append to result</li><li>用两个map 分别记录s 和p，如果s==p,append to result </li></ul> |
| [447. Number of Boomerangs](https://leetcode.com/problems/number-of-boomerangs/) | _O(n^2)_ | _O(n)_	| Easy | 可以用hypot |
| [454. 4Sum II](https://leetcode.com/problems/4sum-ii/) | _O(n^2)_ | _O(n)_	| Medium | 可以把4sum看成two sum, 把A+B的和绑定，把C+D的和绑定，看-C-D是不是在A+B的map里 |
| [473. Matchsticks to Square](https://leetcode.com/problems/matchsticks-to-square/) | _O(n * s * 2^n)_ | _O(n * (2^n + s))_	| Medium | DFS or Bit Mask |
| [523. Continuous Subarray Sum](https://leetcode.com/problems/continuous-subarray-sum/) | _O(n)_ | _O(k)_	| Medium | 🔍求开始数到所有i的和的余数，如果现在这个的余数之前遇到过，表示，两个数之间有数的和正好整除k |
| [532. K-diff Pairs in an Array](https://leetcode.com/problems/k-diff-pairs-in-an-array/) | _O(n)_ | _O(n)_	| Easy |  🔍one pass解: 两个hashset, lookup 和res, 找的时候既向上数又向下数, 为了避免重复, set(res)只push下限,结果就是res size |
| [554. Brick Wall](https://leetcode.com/problems/brick-wall/) | _O(n)_ | _O(m)_	| Meidum | 相当于求最多经过砖头缝缝 |
| [560. Subarray Sum Equals K](https://leetcode.com/problems/subarray-sum-equals-k/) | _O(n)_ | _O(k)_	| Medium | 🔍用hashmap记录每点的rolling sum(0,i)， 那么只需要找(0,i)的sum - k在不在map中，在的话 表示存在一点\[0,j] + k = (0,i)的sum， res += map\[sum-k] (可能一个sum出现很多遍) |
| [561. Array Partition I](https://leetcode.com/problems/array-partition-i/) | _O(n)_ | _O(n)_	| Easy | Sort or Bucket Sort |
| [575. Distribute Candies](https://leetcode.com/problems/distribute-candies/) | _O(n)_ | _O(n)_	| Easy | 对比set的长度和candies.size()/2的长度, C++可以用bitset |
| [594. Longest Harmonious Subsequence](https://leetcode.com/problems/longest-harmonious-subsequence/) | _O(n)_ | _O(n)_	| Easy |  |
| [599. Minimum Index Sum of Two Lists](https://leetcode.com/problems/minimum-index-sum-of-two-lists/) | _O((m + n) \* l)_ | _O(m \* l)_	| Easy |  |
| [609. Find Duplicate File in System](https://leetcode.com/problems/find-duplicate-file-in-system/) | _O(n \* k)_ | _O(n \* k)_	| Medium |  |
| [721. Accounts Merge](https://leetcode.com/problems/accounts-merge/description/) | _O(nlogn)_ | _O(n)_	| Medium | 🔍 Union Find | 
| [748. Shortest Completing Word](https://leetcode.com/problems/shortest-completing-word/) | _O(n)_ | _O(1)_	| Medium |  |
| [771. Jewels and Stones](https://leetcode.com/problems/jewels-and-stones/) | _O(n+m)_ | _O(n)_	| Easy |  |
| [811. Subdomain Visit Count](https://leetcode.com/problems/subdomain-visit-count/) | _O(n)_ | _O(n)_	| Easy |  |
| [822. Card Flipping Game](https://leetcode.com/problems/card-flipping-game/) | _O(n)_ | _O(n)_	| Medium | 先把front\[i]和end\[i] 一样的插入到hash set, 再loop front & end, 选取不在hash set中最小的 |
| [825. Friends Of Appropriate Ages](https://leetcode.com/problems/friends-of-appropriate-ages/) | _O(n+k^2)_ | _O(k)_	| Medium | 用hash map存age和count, loop两层hashmap, 判断内层和外层key是否满足条件, 满足的话更新结果 |
| &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; &nbsp;&nbsp;&nbsp; &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; &nbsp;&nbsp;&nbsp; &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; &nbsp;&nbsp;&nbsp; &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; &nbsp;&nbsp;&nbsp; &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; &nbsp;&nbsp;&nbsp;  &nbsp;&nbsp;&nbsp;  &nbsp;&nbsp;&nbsp; &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;|  |	|  | |

## sliding windows Summary
|summary |
| ------------- |
| sliding windows: windows都是看以当前字母结尾的window <ul><li>可以记录当前substring的开始位置，</li><li>用数字记录substring的长度 </li><li>用hashset和两个pointer记录当前windows的长度 </li><li> map+pointer <ul><li>1 map + 2 pointers: map先记录比较对象, 对被比较对象只有 __key出现__ 了相加减,  i - j = len -1 是起点</li><li> 1 map + 2 pointers: map先记录比较对象, 被比较对象 __所有字母__ 相加减,  i - j = len -1 是起点 </li><li>2 map + 1 count,对被比较对象只有 __所有字母__ 相加减, count == 0 是windows终点 </li><li> 2 map + 1 count,对被比较对象只有 __key出现__ 了相加减, count == 0 是windows终点 </li><ul><li>  可以用两个map,一个map记录比较对象(T)，一个记录被比较对象(S), 还需要一个count记录S中T出现的个数, start记录windows起始点, 初始化count = len(T); </br>只有当sdict\[s\[i]] < tdict\[s\[i]], count--; 当count == 0, 满足情况,append to res; </br>移动窗口过程中,dict\[s\[start]]--, start++,只有当sdict\[s\[start]] < tdict\[s\[start]]时 ++count, </br>比如[30题 Substring with Concatenation of All Words](https://leetcode.com/problems/substring-with-concatenation-of-all-words/description/), [76题 Minimum Window Substring](https://leetcode.com/problems/minimum-window-substring/)</br>两个题区别是30不能包括多余的string (不可以sdict\[s\[start]] > tdict\[s\[start]]), 76是允许的 </li></ul>  </ul></ul> |

## Stack
|Title | Time  | Space | Difficulty |  Algorithm Note|
| ------------- | ------------- | ------------- | ------------- | ------------- |
| [020. Valid Parentheses](https://leetcode.com/problems/valid-parentheses/) | _O(n)_ | _O(n)_	| Easy | |
| [032. Longest Valid Parentheses](https://leetcode.com/problems/longest-valid-parentheses/) | _O(1)_ | _O(n)_	| Hard |  😍🔍<ul><li> __DP__: dp\[i] 代表以current index结束的最大valid substring的长 </li><li>__Stack__: push的是最近'('的index 和substring的起点 关键点是先pop 再比较 </li></ul>  |
| [071. Simplify Path](https://leetcode.com/problems/simplify-path/) | _O(n)_ | _O(n)_	| Medium |  😚🔍getline可以当做stack, 遇到".." stack pop; vector可以用作stack   |
| [084. Largest Rectangle in Histogram](https://leetcode.com/problems/largest-rectangle-in-histogram/) | _O(n)_ | _O(n)_	| Hard |😍 🔍 <ul><li>__stack__: stack要保证height是由小变大的,当遇到新的height小于stack.top(),pop stack，算area. 关键点是stack top是height, stack.pop() 之后的top 是 现在计算的长方形左边界</li><li> __Divide Conquer__:最小的area来自左面，或者来自右面，或者来自area contain middle point</li></ul> |
| [085. Maximal Rectangle	](https://leetcode.com/problems/maximal-rectangle/) | _O(n\*m)_ | _O(m)_	| Hard | 🔍<ul><li>__stack__:与[084.](https://leetcode.com/problems/simplify-path/) 类似, matrix有n行，问题可以转换成n个Histogram的问题,每个问题就是一个以这一行为底的Histogram问题，上面连续的1的个数就是Height </li><li>__DP__ : height代表从上到下，有几个连续的1, left 代表在现在这个height，左侧边界位置, right:代表在现在这个height,长方形的右侧边界（右侧边界不包括在长方形内，是长方形右外侧第一个点）  </li></ul>|
| [101. Symmetric Tree](https://leetcode.com/problems/symmetric-tree/) | _O(n)_ | _O(h)_	| Easy | push时候先push 左面的，再push右面的, top先top 右面的，再top 左面的，注: left->right算右面，right->left算左面 |
| [150. Evaluate Reverse Polish Notation](https://leetcode.com/problems/evaluate-reverse-polish-notation/) | _O(n)_ | _O(n)_	| Medium | Recursive or Stack(先pop的放符号右边，后pop的放左边)|
| [155. Min Stack](https://leetcode.com/problems/min-stack/) | _O(n)_ | _O(1)_	| Easy | 两个stack,一个用来放正常的顺序，另一个作为min stack用来存最小值(stk中的数是从小到大排序的)，只有当新来的小于等于minstack.top()，再push，pop时候，如果普通stack.top() == minstack.top(),minstack也pop |
| [173. Binary Search Tree Iterator](https://leetcode.com/problems/binary-search-tree-iterator/) | _O(1)_ | _O(h)_	| Medium | 先左后右，每次go left, push into stack, 每次go right 不用push into stack  |
| [232. Implement Queue using Stacks](https://leetcode.com/problems/implement-queue-using-stacks/) | _O(1), amortized_ | _O(n)_	| Easy | 🔍两个stack in & out, in用来push, top: 假如out为空，dump stack in into out(此时out top顺序应该与push时候顺序一样)|
| [224. Basic Calculator](https://leetcode.com/problems/basic-calculator/) | _O(n)_ | _O(n)_	| Hard | 用sign=1记录+, -1记录减, 碰到num乘以res,'('res,sign push进stack, ')'先乘以stack的top(是sign),再加上stack的top(sign之前的res)  |
| [227. Basic Calculator II](https://leetcode.com/problems/basic-calculator-ii/) | _O(n)_ | _O(n)_	| Medium | 用sign=1记录+, -1记录减, sign = 2 记录\*， 3记录除, 上一个sign是乘或除，先进行operation|
| [331. Verify Preorder Serialization of a Binary Tree](https://leetcode.com/problems/verify-preorder-serialization-of-a-binary-tree/) | _O(n)_ | _O(n)_	| Medium | <ul><li>__Stack__: 树的每个node要pop两回，一会是从left child上来，另一个从right child上来, 所以stack遇到新node push2,当# pop时，top为2减1，top为1 pop。 还设一个root node为1，为了保证root不变，可能input是两个valid tree，设root node,保证一遇到第二个tree </li><li>indegree(到parent的) = outdegree（到child的） 每个node 都有一个indegree, 只有不是NULL的node,才有outdegreee</li></ul>  |
| [341. Flatten Nested List Iterator](https://leetcode.com/problems/flatten-nested-list-iterator/) | _O(n)_ | _O(h)_	| Medium | stack + recursion从最后往前loop, queue从前往后loop, 面试不能给constructor O(N)的solution,因为是iterator 不能把所有数push进数据结构 |
| [385. Mini Parser](https://leetcode.com/problems/mini-parser/) | _O(n)_ | _O(h)_	| Medium | 遇到',' ']' 把之前的integer add，  比如\[-1],  \[123,456], 遇到']',把现在这个nested list加入上个nested list |
| [394. Decode String](https://leetcode.com/problems/decode-string/) | _O(n)_ | _O(h)_	| Medium | <ul><li>遇到num, push num 进num stack </li><li>遇到'\[',push “”进pat stack</li><li>遇到string，如果pat stack不为空，append top, 如果为空，append res </li><li> 遇到']',把pattern提出，若pat stack为空，append res, pat stack不为空append top </li></ul> |
| [456. 132 Pattern](https://leetcode.com/problems/132-pattern/) | _O(n)_ | _O(h)_	| Medium | 寻找 s1 < s3 < s2，从后向前，stack是ascending stack, 寻找最大的s2, 一旦有数小于s2, 返回true |
| [636. Exclusive Time of Functions](https://leetcode.com/problems/exclusive-time-of-functions/) | _O(n)_ | _O(n)_	| Medium | stack 存的是上个job的id |
| [682. Baseball Game](https://leetcode.com/problems/baseball-game/) | _O(n)_ | _O(n)_	| Easy |  |
| [726. Number of Atoms](https://leetcode.com/problems/number-of-atoms/) | _O(n^2)_ | _O(n)_	| Hard | 用stack<map<string,int>>, 遇到'(': 把cur push进stack, 遇到')',把cur 与stack top merge|
| [735. Asteroid Collision](https://leetcode.com/problems/asteroid-collision/) | _O(n)_ | _O(n)_	| Medium | 碰撞发生只能是新来的小于0，stack top > 0 |
| [736. Parse Lisp Expression](https://leetcode.com/problems/parse-lisp-expression/) | _O(n)_ | _O(n)_	| Hard | stack需要两个，一个是存string dict(用来储存let的字典), 一个存string vector(用来储存上个string的split), 遇到'(', 如果之前是let, 先存map, 然后push进两个stack, string vector清空，字典不清空 。 遇到')', 算当前的, 把结果push到上个string(stkstring.top()) 的结尾, pop两个stack|
| [739. Daily Temperatures](https://leetcode.com/problems/daily-temperatures/) | _O(n)_ | _O(n)_	| Medium |🔍 Ascending stack, 从后往前loop, 遇到t\[i] >= stack.top(), stack持续pop(), 如果stack不为空,则概数为第一个比t\[i]大的 |
| &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; &nbsp;&nbsp;&nbsp; &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;| |  | | |

## Linked List
|Title | Time  | Space | Difficulty |  Algorithm Note|
| ------------- | ------------- | ------------- | ------------- | ------------- |
| [002. Add Two Numbers](https://leetcode.com/problems/add-two-numbers/) | _O(n)_ | _O(1)_	| Medium | |
| [021. Merge Two Sorted Lists](https://leetcode.com/problems/merge-two-sorted-lists/) | _O(n)_ | _O(1)_	| Easy | |
| [023.	Merge k Sorted Lists](https://leetcode.com/problems/merge-k-sorted-lists/) | _O(nklogk)_ | _O(1)_	| Hard | Heap, Divide Conquer, 注: 不能用一直用0作为l 和r比，这样的话，l的size会增加的很快，到最后l size快成位nk了 |
| [024. Swap Nodes in Pairs](https://leetcode.com/problems/swap-nodes-in-pairs/) | _O(n)_ | _O(1)_	| Easy | 建dummy, 提取往后第二个为nextnext，断第二，三链, nextnext后接上当前的next, 把nextnext接到当前的next, pt往后走两步|
| [025. Reverse Nodes in k-Group](https://leetcode.com/problems/reverse-nodes-in-k-group/) | _O(n)_ | _O(1)_	| Hard | 类似[206	Reverse Linked List](https://leetcode.com/problems/reverse-linked-list/)|
| [061. Rotate List](https://leetcode.com/problems/rotate-list/) | _O(n)_ | _O(1)_	| Medium | |
| [082. Remove Duplicates from Sorted List II](https://leetcode.com/problems/remove-duplicates-from-sorted-list-ii/) | _O(n)_ | _O(1)_	| Medium | |
| [083. Remove Duplicates from Sorted List](https://leetcode.com/problems/remove-duplicates-from-sorted-list/) | _O(n)_ | _O(1)_	| Easy | 不能用recusion, recursion的话会用pass n回linked list，用O(n)space, iterative解space只用O(1),tree可以用recursion原因是它的stack space是O(logn) |
| [138. Copy List with Random Pointer](https://leetcode.com/problems/copy-list-with-random-pointer/) | _O(n)_ | _O(1)_	| Medium | 1. 先把每个node复制一个，把复制的贴在被复制的后面</br> 2. loop node(现在长度是2n), 把cur->next->random = cur->random->next，因为cur->random->next是复制cur->random过来的</br> 3. 最后结果就是把每个偶数位的node连接起来，同时要消除偶数的node(长度由2n变回n)，否则结果是修改了原来的node</br> |
| [147. Insertion Sort List](https://leetcode.com/problems/insertion-sort-list/) | _O(n^2)_ | _O(1)_	| Medium | Sort |
| [148. Sort List](https://leetcode.com/problems/sort-list/description/) | _O(nlogn)_ | _O(logn)_	| Medium | Sort <ul><li>top-down,用两个pointer，一个慢，一个快，去split,然后merge, space: O(logn)</li><li> bottom-up, 第一次只把1和2顺序，3和4顺序，5和6顺序调整，第二次把1，2和3，4顺序调整，5,6和7，8顺序调整，以此类推, space: O(1) </li></ul>  |
| [160. Intersection of Two Linked Lists](https://leetcode.com/problems/intersection-of-two-linked-lists/) | _O(n+m)_ | _O(1)_	| Easy | 利用的是 lA + lB_1 =  lA_1 + lB (lenA + B交点前的长度 = lenB + A交点前的长度),</br> pA，pB 每次都前进一步，pA到end,pA设为Bhead, pB到end,pB设为Aend, </br>这种尾对头只换一次，第二次pA 或者pB到end 返回NULL(就是没有交点) |
| [203. Remove Linked List Elements](https://leetcode.com/problems/remove-linked-list-elements/) | _O(n)_ | _O(1)_	| Easy | |
| [206. Reverse Linked List](https://leetcode.com/problems/reverse-linked-list/) | _O(n)_ | _O(1)_	| Easy | |
| [234. Palindrome Linked List](https://leetcode.com/problems/palindrome-linked-list/) | _O(n)_ | _O(1)_	| Easy | revese list前面部分，然后reverse之后，逐个对比前半部分是否等于后半部分的值 |
| [237. Delete Node in a Linked List](https://leetcode.com/problems/delete-node-in-a-linked-list/) | _O(n)_ | _O(1)_	| Easy | 把node->next的val提到node val然后delete node->next |
| [328. Odd Even Linked List](https://leetcode.com/problems/odd-even-linked-list/description/) | _O(n)_ | _O(1)_	| Medium | <ul><li>把even = head->next, odd = head, 然后逐个先断odd和下个even链 和 even和下个odd链(顺序不能反)</li><li>把even顺序保留，把odd提出来， 断even和odd的链，然后evenhead 接在odd->next上</li></ul> |
| [445. Add Two Numbers II](https://leetcode.com/problems/add-two-numbers-ii/) | _O(n+m)_ | _O(m+n)_	| Medium | 用两个stack,把每个list值push 进stack，最后push进的先算 |
| [725. Split Linked List in Parts](https://leetcode.com/problems/split-linked-list-in-parts/) | _O(n)_ | _O(1)_	| Medium | 每次前进到此次push进vector的最后一位, 然后断链, 第i个vector长度为 n//k + (i< n%k) |
| [817. Linked List Components](https://leetcode.com/problems/linked-list-components/) | _O(n+m)_ | _O(m)_	| Medium | 把vector转化成unordered_set, 然后判断每个val,是不是在unordered_set里面 |
two pointer 1.whiLe(fast->next && fast->Next->next) 是找中点, 比如1-2-3-4-5-6，slow最后等于3 </br> 2.whiLe(fast && fast->Next) 是找中后一点,比如1-2-3-4-5-6，slow最后等于4, 1-2-3-4-5 最后是3


## Queue
|Title | Time  | Space | Difficulty |  Algorithm Note|
| ------------- | ------------- | ------------- | ------------- | ------------- |
| [239. Sliding Window Maximum](https://leetcode.com/problems/sliding-window-maximum/) | _O(n)_ | _O(k)_	| Hard | Monoqueue using Deque<ul><li>deque pair, first是存当前的数, second表示window开始位置到这个数之前，多少个比现在这个数小</br> __push__: 跟back对比, 如果back小, count加上back.second, pop back, 直到比现在这个数大或deque为空, push({val, count}) </br> __pop__: 看top second如果大于0(比当前数小,在windows开始到top的数还存在),top.second-1, 如果是0, pop_front() </li><li>  __deque int__ : 只存单个index, deque中最大数的index存前面（deque是按大小排序的，并且按照出现的前后顺序排序)，且front的index比backindex小，所以pop时候对比front是不是当前windows的 </li></ul> |


## Heap
|Title | Time  | Space | Difficulty |  Algorithm Note|
| ------------- | ------------- | ------------- | ------------- | ------------- |
| [264. Ugly Number II](https://leetcode.com/problems/ugly-number-ii/) | _O(n)_ | _O(1)_	| Medium | 🔍<ul><li>__dp__: 每次用2,3,5指向的pt乘以2，3，5，如果乘后的数 == 2，3，5 pt值的数各自乘以 2，3，5，就前进2，3，5的pt一位</li><li> __heap__ 的解： 每次top返回最小的数p,如果p可以整除2，就push p*2, else if可以整除3，push 3*p 和 2*p(e.g. 否则18不会出现在queue), else push 5*p, 3*p, 2*p(e.g.否则25*2 = 50 不会出现在queue)</li></ul>|
| [295. Find Median from Data Stream](https://leetcode.com/problems/find-median-from-data-stream/) | _O(nlogn)_ | _O(1)_	| Medium | 🔍 用两个heap, __small__: maxheap(返回最小值，存小于median),__big__: minheap(返回最大值，存大于median的)，保证small的size 只能是跟big的size一样或者比big的size 大1 |
| [313. Super Ugly Number](https://leetcode.com/problems/find-median-from-data-stream/) | _O(n\*k)_ | _O(n+k)_	| Medium | 类似 [264. Ugly Number II](https://leetcode.com/problems/ugly-number-ii/),loop n次，每次寻找下个最小的ugly number, 并且记录获得最小ugly number pt的index, 最后把这些index++. </br> __heap__ 的解：注意往heap推送，每次推得都要是unique的，不能推heap中已经有的 |
| [373. Find K Pairs with Smallest Sums](https://leetcode.com/problems/find-k-pairs-with-smallest-sums/) | _O(k * log(min(n, m, k)))_ | _O(min(n, m, k))_	| Medium | |
| [378. Kth Smallest Element in a Sorted Matrix](https://leetcode.com/problems/find-k-pairs-with-smallest-sums/) | _O(k * log(min(n, m, k)))_ | _O(min(n, m, k))_	| Medium | Binary Search, Heap, ZigZag Search |
| [407. Trapping Rain Water II](https://leetcode.com/problems/trapping-rain-water-ii/) | _O(m \* n \* (logm + logn))_ | _O(m\*n)_	| Hard | 把长方形四边所有的cell push进min heap, 然后pop 当前最小的height的cell,loop它的四边,如果边高小于cell高，结果加上这个差，再push进queue(push的height是当前height和cell的最大值) [visualation](https://www.youtube.com/watch?time_continue=80&v=cJayBq38VYw) |
| [632. Smallest Range](https://leetcode.com/problems/smallest-range/) | _O(nklogk)_ | _O(k)_	| Medium | 把所有vector\[i]\[0]的数push进minheap, 然后pop heap, 更新最大值和最小值,如果最大值-最小值<range, 更新range |
| [846. Hand of Straights](https://leetcode.com/problems/hand-of-straights/) | _O(nlogn)_ | _O(n)_	| Medium | 先把所有数push进minheap(multiset), 然后进行m个W次loop,如果top+i不在minheap里，return false, 如果在则erase iterator, 直到把heap所有数都删了, return true |
| &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; &nbsp;&nbsp;&nbsp; &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;| |  | | C++ priority_queue default是max heap，Python的heapq default是min heap. priority_queue\<int, vector\<int>, less\<int>> 是max_heap, greater\<int>是min_heap </br>multiset\<int, greater\<int>> 是max_heap  </br>multiset和priority_queue用的default comparator相反   |



Two pointer 用于<ul><li>detect cycle</li><li>sorted array比大小,一个array一个pointer</li><li>linked list找到middle point</li></ul>
## Two Pointer 
|Title | Time  | Space | Difficulty |  Algorithm Note|
| ------------- | ------------- | ------------- | ------------- | ------------- |
| [019. Remove Nth Node From End of List](https://leetcode.com/problems/remove-nth-node-from-end-of-list/) | _O(n)_ | _O(1)_	| Easy | fast先前进n个，然后slow，fast同时前进，知道fast到null, list总长l, 需要remove的index是l-n, slow要前进到l-n-1, 所以先前进n个，再前进到尾部就是l-n-1 |
| [086. Partition List](https://leetcode.com/problems/partition-list/) | _O(n)_ | _O(1)_	| Medium |  <ul><li>先把head所有小于x的pass掉,slow,head=first大于等于x的node, loop fast 当fast小于x,把这个放在slow上,slow前进一位</li><li> 建两个node，一个small,一个big,把所有小于的head放在small，其他的放在big，最后把所有big挂在small的后面 </li></ul> |
| [141. Linked List Cycle	](https://leetcode.com/problems/linked-list-cycle/) | _O(n)_ | _O(1)_	| Easy | |
| [142. Linked List Cycle II](https://leetcode.com/problems/linked-list-cycle-ii/) | _O(n)_ | _O(1)_	| Medium | |
| [143. Reorder List](https://leetcode.com/problems/reorder-list/) | _O(n)_ | _O(1)_	| Medium | 用fast & slow先找到medium的点，slow到结尾所有的点reverse, 然后p1 = head, p2 = middle后一点，一个p1, 一个p2 插进pointer，就是结果 |
| [167.Two Sum II - Input array is sorted](https://leetcode.com/problems/two-sum-ii-input-array-is-sorted/description/) | _O(n)_ | _O(1)_	| Easy | two pointer, 一个从开始位置，一个从末尾的位置 |
| [283. Move Zeroes](https://leetcode.com/problems/move-zeroes/) | _O(n)_ | _O(1)_	| Easy | |
| [287. Find the Duplicate Number](https://leetcode.com/problems/find-the-duplicate-number/) | _O(n)_ | _O(1)_	| Easy | 类似[142. Linked List Cycle II](https://leetcode.com/problems/linked-list-cycle-ii/) ,有duplicate一定会有cycle<ul><li> 每个数减去1,所有数都在\[0,n-1],从n开始，因为从n开始不会自己循环 </li><li>每个数数都在\[1,n],从0开始</li></ul> |
| [344. Reverse String](https://leetcode.com/problems/reverse-string/) | _O(n)_ | _O(1)_	| Easy | 可以用bit来进行swap |
| [349. Intersection of Two Arrays](https://leetcode.com/problems/intersection-of-two-arrays/) | _O(n+m)_ | _O(min(m, n))_	| Easy | <ul><li> 用hashmap, O(N) </li><li>binary search, 要sort两个vector,然后loop v1, 到v2中找有没有v1\[i]这个数</li><li>two pointer, sort两个vector,it1=v1.begin(), it2=v2.begin(),然后根据it1,it2大小,更新结果和自增it1和it2 </li></ul> |
| [350.Intersection of Two Arrays II](https://leetcode.com/problems/intersection-of-two-arrays-ii/) | _O(n+m)_ | _O(1)_	| Easy | 如果没有sort, space: O(1) complexity O(max(n,n)\*log(max(m,n))的解为binary search, two pointer,  如果有sort, space: O(1) complexity O(m+n)的解为two pointer |
| [457. Circular Array Loop](https://leetcode.com/problems/circular-array-loop/) | _O(n)_ | _O(1)_	| Medium | array loop必须是单向的, 比如1->2, 2->1 不算是loop，循环array每次两个pointer检查有没有loop,如果没有loop,把这次所有走过的点都标成0,下次不用再走了 |
| [567. Permutation in String](https://leetcode.com/problems/permutation-in-string/) | _O(n)_ | _O(1)_	| Medium | sliding Window(长度为len(s1)), 每次移动框,vector减去新来的，加上刚刚pass的，直到l长度为0 |
| [611. Valid Triangle Number](https://leetcode.com/problems/valid-triangle-number/) | _O(n^2)_ | _O(1)_	| Medium |先sort然后两个pointer,每一个都指向一个边 |
| [777. Swap Adjacent in LR String](https://leetcode.com/problems/swap-adjacent-in-lr-string/) | _O(n)_ | _O(1)_	| Medium | R是向前走，L是向后走（swap R 和L都需要X）, 两个pointer，遇到X往前跳 |
| [826. Most Profit Assigning Work](https://leetcode.com/problems/most-profit-assigning-work/) | _O(mlogm + nlogn)_ | _O(1)_	| Medium | <ul><li>sort jobs & work, 两个pt,一个指worker, 一个指jobs, profit记录到worker i之前最大的收益</li><li>用一个size=10001的vector, v\[i]表示第difficulty为i时，最大的profit </li></ul> |
| [828. Unique Letter String](https://leetcode.com/problems/unique-letter-string/) | _O(n)_ | _O(1)_	| Hard | <ul><li>与其算每个unique substring长度，不如算每一个char有多少种方法让它在substring种变成unique, 如果只有这个char是unique在substring中，其他的char不会再发现这个substring,所以结果只会加1</li><li>DP: 用contri记录此点贡献的值, last记录上次出现这个字母的位置，cur是到目前位置所有贡献值的和, 比如现在点为A,contri\[A]=现在点距离上次A出现的位置,contri保证了从上次A的后一位到现在A的位置，A只出现一次在每个substring中，贡献为i-last\[A]</li></ul> |
| [844. Backspace String Compare](https://leetcode.com/problems/backspace-string-compare/) | _O(m+n)_ | _O(1)_	| Easy | 两个pt，都从s,t的尾部开始起，从后往前，while一直到当前不能skip，然后对比两个点是否一样，一样继续往前，不一样return false |
|LinkedList 当head, cur 指向同一点, cur = cur->next; ||||head 不会改变, 但是当cur在head之后，head包含cur, cur = cur->next, head会跳过cur这点|

</br>

## Sort
|Title | Time  | Space | Difficulty |  Algorithm Note|
| ------------- | ------------- | ------------- | ------------- | ------------- |
| [056. Merge Intervals](https://leetcode.com/problems/merge-intervals/) | _O(nlogn)_ | _O(n)_	| Medium | 😍🔍 |
| [057. Insert Interval](https://leetcode.com/problems/insert-interval/) | _O(nlogn)_ | _O(n)_	| Hard | |
| [075. Sort Colors](https://leetcode.com/problems/sort-colors/description/) | _O(n)_ | _O(1)_	| Medium | 🔍 Tri Partition |
| [088. Merge Sorted Array](https://leetcode.com/problems/merge-sorted-array/) | _O(n)_ | _O(1)_	| Easy | 从后往前摆，不用swap |
| [147. Insertion Sort List](https://leetcode.com/problems/insertion-sort-list/) | _O(n^2)_ | _O(1)_	| Medium | |
| [148. Sort List](https://leetcode.com/problems/sort-list/description/) | _O(nlogn)_ | _O(logn)_	| Medium | <ul><li>top-down,用两个pointer，一个慢，一个快，去split,然后merge, space: O(logn)</li><li> bottom-up, 第一次只把1和2顺序，3和4顺序，5和6顺序调整，第二次把1，2和3，4顺序调整，5,6和7，8顺序调整，以此类推, space: O(1) </li></ul>  |
| [164. Maximum Gap](https://leetcode.com/problems/maximum-gap/) | _O(n)_ | _O(n)_	| Hard | 😍🔍 <ul><li>Bucket Sort, minstep = (max-min)/(n-1) = bucket_step, bucket_size = n (i=min, at bucket\[0], i = max, at bucket\[n-1], 结果max gap=相邻两个bucket的min\[i]-max\[i-1]  </li><li>radix sort, res = 最大两个相邻的点, radix sort排序是从后往前loop，因为之前的digit的是sort，大的digit在最后面，count\[i]是从ith-digit的最后一个位置</li></ul> |
| [179. Largest Number](https://leetcode.com/problems/largest-number/) | _O(nlogn)_ | _O(n)_	| Medium | 变成string再sort,string sort会从string的第0位开始比,比如"9">"0", "9">"89", python解定义sort class，因为python中'30'>'3', 而我们希望'3'>'30' |
| [218. The Skyline Problem](https://leetcode.com/problems/the-skyline-problem/) | _O(nlogn)_ | _O(logn)_	| Hard |😚🔍 priority_queue or multiset(看critical point) |
| [274. H-Index](https://leetcode.com/problems/h-index/) | _O(n)_ | _O(n)_	| Medium | 🌒counting Sort |
| [315. Count of Smaller Numbers After Self](https://leetcode.com/problems/count-of-smaller-numbers-after-self/description/) | _O(nlogn)_ | _O(n)_	| Hard | MergeSort, BIT |
| [324. Wiggle Sort II](https://leetcode.com/problems/wiggle-sort-ii/) | _O(n) average_ | _O(1)_	| Medium | 🌒(1 + 2\*index) \% (n \| 1)保证median左面数map奇数位，mediam右面的数map偶数位<ul><li>(1)elements smaller than the 'median' are put into the last even slots</li><li>(2) elements larger than the 'median' are put into the first odd slots</li><li>(3) the medians are put into the remaining slots.</li></ul> |
| [327. Count of Range Sum](https://leetcode.com/problems/count-of-range-sum/description/) | _O(nlogn)_ | _O(n)_	| Hard | MergeSort with Count, BIT |
| [347. Top K Frequent Elements](https://leetcode.com/problems/top-k-frequent-elements/) | _O(n)_ | _O(n)_	| Medium | 😍🔍 Bucket Sort, Quick Select, <ul><li> C++: n-th elements,  priority_queue (maxheap: priority_queue, minheap: multiset), </li><li> python: collections.Count, heapq, most_common(k) </li></ul> |
| [406. Queue Reconstruction by Height](https://leetcode.com/problems/queue-reconstruction-by-height/) | _O(n \* sqrt(n))~O(n^2)_ | _O(n)_	| Medium | 😚🐸 关键是认清sort的顺序 先把height大的安排了，如果height一样再sort k有小到大。 sqrt(n)解是一样的sort，但是把sort之后的插入到不同的组中，每个组不超过sqrt(n)个元素 |
| [462. Minimum Moves to Equal Array Elements II](https://leetcode.com/problems/minimum-moves-to-equal-array-elements-ii/) | _O(nlogn)_ | _O(n)_	| Medium | Medium是最小化Sum of Absolute Deviations; Quick Select: O(n) on average |
| [451. Sort Characters By Frequency](https://leetcode.com/problems/sort-characters-by-frequency/) | _O(n)_ | _O(n)_	| Medium |😍 Bucket Sort, Quick Select(n-th elements) O(nlogn), priority_queue O(nlogn)  |
| [692. Top K Frequent Words](https://leetcode.com/problems/top-k-frequent-words/) | _O(nlogk)_ | _O(n)_	| Medium | Bucket Sort, Quick Select(n-th elements), priority_queue  |
| [853. Car Fleet](https://leetcode.com/problems/car-fleet/) | _O(nlogn)_ | _O(n)_	| Medium |  🐸sort postion又大到小，再sort从position\[i]到target的时间由小到大,一旦后面的时间比前面时间长，就不会catch前面的，再更新cur_time  |
|C++priority_queue<pair<int,int>>pq 先对比first, top是first最大的，</br>constructor: greater\<int>是让top返回最小的数,大的数放后面 |  |	|  | python的heappop()先pop对比first,then second, top是first最小的  |


</br>


## Recursion

|Title | Time  | Space | Difficulty |  Algorithm Note|
| ------------- | ------------- | ------------- | ------------- | ------------- |
| [095. Unique Binary Search Trees II](https://leetcode.com/problems/unique-binary-search-trees-ii/) | _O(4^n / n^(3/2))_ |	_O(4^n / n^(3/2))_	| Medium | 😍 🔍Given start/end point. Generate vector of left subtree 和right subtree, 然后排列组合把他们弄在一起 |
| [098. Validate Binary Search Tree](https://leetcode.com/problems/validate-binary-search-tree/description/) | _O(n)_ |	_O(1)_	| Medium | 😍利用binary search tree的性质 |
| [100. Same Tree](https://leetcode.com/problems/same-tree/) | _O(n)_ |	_O(h)_	| Easy |  |
| [104. Maximum Depth of Binary Tree](https://leetcode.com/problems/maximum-depth-of-binary-tree/description/) | _O(n)_ |	_O(h)_	| Easy | |
| [105. Construct Binary Tree from Preorder and Inorder Traversal](https://leetcode.com/problems/construct-binary-tree-from-preorder-and-inorder-traversal/description/) | _O(n)_ |	_O(h)_	| Medium | preorder 第一个是tree的root, inorder 中root->val左面root的left tree,右面root的right tree,  |
| [106. Construct Binary Tree from Inorder and Postorder Traversal](https://leetcode.com/problems/construct-binary-tree-from-inorder-and-postorder-traversal/description/) | _O(n)_ |	_O(h)_	| Medium | postorder 最后一个是tree的root,postorder从后往前是right tree, 再是left-tree, inorder 中root->val左面root的left tree,右面root的right tree,  |
| [108. Convert Sorted Array to Binary Search Tree](https://leetcode.com/problems/convert-sorted-array-to-binary-search-tree/description/) | _O(n)_ |	_O(logn)_	| Easy | 😍 🔍跟[095. Unique Binary Search Trees II](https://leetcode.com/problems/unique-binary-search-trees-ii/)逻辑一样 binary tree height 需要balanced |
| [109. Convert Sorted List to Binary Search Tree](https://leetcode.com/problems/convert-sorted-list-to-binary-search-tree/description/) | _O(n)_ |	_O(logn)_	| Medium | 📖 Linked List找中间点用两个pointer，一个每次前进一步，另一个每次前进两部 |
| [110. Balanced Binary Tree](https://leetcode.com/problems/balanced-binary-tree/description/) | _O(n)_ |	_O(h)_	| Medium |😍 跟[095. Unique Binary Search Trees II](https://leetcode.com/problems/unique-binary-search-trees-ii/)类似 用bottom-up 比top-down 更efficient |
| [111. Minimum Depth of Binary Tree](https://leetcode.com/problems/minimum-depth-of-binary-tree/) | _O(n)_ |	_O(h)_	| Medium | 线找到第一个点既没有left-tree, 也没有right-tree |
| [114. Flatten Binary Tree to Linked List](https://leetcode.com/problems/flatten-binary-tree-to-linked-list/description/) | _O(n)_ |	 _O(h)_	| Medium | 🔍😍 preorder 的reverse |
| [116. Populating Next Right Pointers in Each Node](https://leetcode.com/problems/populating-next-right-pointers-in-each-node/description/) | _O(n)_ |	_O(1)_	| Medium | <ul><li> 检查有没有left，先把root left 和root right连了，如果root有next，把root right和next left 连了，然后横着走 </li><li> 或者是阶梯式向下connect root1 left和 root1 right & root1 right和root2 left & root2 left和root2 right </li></ul> |
| [124. Binary Tree Maximum Path Sum](https://leetcode.com/problems/binary-tree-maximum-path-sum/) | _O(n)_ |	_O(h)_	| Hard | 先找左面的最大的，再找右面最大的，然后结合看是 l大, or r大, or l+root+r 大，or root 大， 再跟max比 |
| [129. Sum Root to Leaf Numbers](https://leetcode.com/problems/sum-root-to-leaf-numbers/) | _O(n)_ |	_O(h)_	| Medium | 带着之前的root val然后到一点, 到leave就加上val |
| [241. Different Ways to Add Parentheses](https://leetcode.com/problems/different-ways-to-add-parentheses/description/) | _O(n\* 4^n / n^(3/2))_ |	_O(n \* 4^n / n^(3/2))_	| Medium | 算sign前的，算sign后的,然后做前和后的permutation和 |
| [337. House Robber III](https://leetcode.com/problems/house-robber-iii/) | _O(n)_ |	_O(h)_	| Medium | 返回vector, vector\[0]存的是用上一个最大的获取值，vector\[0]存的是不用上一个 最大的获取值 |
| [395. Longest Substring with At Least K Repeating Characters](https://leetcode.com/problems/longest-substring-with-at-least-k-repeating-characters/description/) | _O(n)_ |	_O(n)_	| Medium | Divide-conquer 一旦小于k, 就split成left和right,然后返回left和right的max值 |
| [404. Sum of Left Leaves](https://leetcode.com/problems/sum-of-left-leaves/) | _O(n)_ |	_O(h)_	| Easy |  |
| [437. Path Sum III](https://leetcode.com/problems/path-sum-iii/description/) | _O(n)_ |	_O(h)_	| Easy | unorderedmap 存的在现在点之前的 <prefix sum, frequency> pairs. 从中间某点到现在sum = 从root到现在点sum - root到中间某点的sum |
| [669. Trim a Binary Search Tree](https://leetcode.com/problems/trim-a-binary-search-tree/description/) | _O(n)_ |	_O(h)_	| Easy | |
| [671. Second Minimum Node In a Binary Tree](https://leetcode.com/problems/second-minimum-node-in-a-binary-tree/) | _O(n)_ |	_O(h)_	| Easy | |
| [761. Special Binary String](https://leetcode.com/problems/special-binary-string/description/) | _O(n^2)_ |	_O(n)_	| Hard | Divide-conquer, 把每个special string 再分成小的special string,然后sort |

</br>
</br>

## Binary Search
|Title | Time  | Space | Difficulty |  Algorithm Note|
| ------------- | ------------- | ------------- | ------------- | ------------- |
| [004. Median of Two Sorted Arrays](https://leetcode.com/problems/median-of-two-sorted-arrays/description/) | _O(log(min(m, n)))_ |	_O(1)_	| Hard | 更新A的ilow 和ihigh, j = (m+n+1)/2-1,<ul><li>if i<m && B\[j-1]>A\[i]: ilow=i+1(A\[i]太小)</li><li> if i>0 && A\[i]>B\[j]：ihigh = i-1 (A\[i]太大)</li></ul> |
| [033. Search in Rotated Sorted Array](https://leetcode.com/problems/search-in-rotated-sorted-array/) | _O(log(n))_ |	_O(1)_	| Medium | <ul><li>if t>A[mid] 想往左走，只能是A\[l]到A\[mid]有turn且A\[l]<=t</li><li>if t<A[mid] 想往右走，只能是A\[mid]到A\[r]有turn且A\[r]>=t</li></ul>  |
| [034. Find First and Last Position of Element in Sorted Array](https://leetcode.com/problems/find-first-and-last-position-of-element-in-sorted-array/submissions/) | _O(log(n))_ |	_O(1)_	| Medium | lowerbound + upperbound |
| [35. Search Insert Position](https://leetcode.com/problems/search-insert-position/) | _O(log(n))_ |	_O(1)_	| Easy | lowerbound |
| [069. Sqrt(x)](https://leetcode.com/problems/sqrtx/description/) | _O(log(n))_ |	_O(1)_	| Easy | Newton Method |
| [074. search a 2D Matrix](https://leetcode.com/problems/search-a-2d-matrix/description/) | _O(logm + logn)_ |	_O(1)_	| Medium | <ul><li> 对row一次lowerbound， 对coloumn 一次lowerbound  </li><li> 把2D matrix不当成2D,当成一个大的sorted array</li></ul>|
| [081. Search in Rotated Sorted Array II](https://leetcode.com/problems/search-in-rotated-sorted-array-ii/description/) | _O(logn)_ |	_O(1)_	| Medium | remove duplicate from left and right |
| [153. Find Minimum in Rotated Sorted Array](https://leetcode.com/problems/find-minimum-in-rotated-sorted-array/description/) | _O(logn)_ |	_O(1)_	| Medium | 与033. Search in Rotated Sorted Array logic 类似 |
| [154. Find Minimum in Rotated Sorted Array II](https://leetcode.com/problems/find-minimum-in-rotated-sorted-array-ii/description/) | _O(logn) ~ O(n)_ |	_O(1)_	| Hard | 与081. Search in Rotated Sorted Array II logic 类似 |
| [162. Find Peak Element](https://leetcode.com/problems/find-peak-element/description/) | _O(logn)_ |	_O(1)_	| Medium | find local maximum |
| [222. Count Complete Tree Nodes](https://leetcode.com/problems/count-complete-tree-nodes/description/) | _O((logn)^2)_ |	_O(1)_	| Medium |  |
| [275. H-Index II](https://leetcode.com/problems/h-index-ii/description/) | _O(logn)_ |	_O(1)_	| Medium | citations\[index] >= length(citations) - index = h, 找符合的最小的index，最大的h |
| [278. First Bad Version](https://leetcode.com/problems/first-bad-version/) | _O(logn)_ |	_O(1)_	| Easy | |
| [300. Longest Increasing Subsequence](https://leetcode.com/problems/longest-increasing-subsequence/) | _O(nlogn)_ |	_O(n)_	| Medium | tail\[i] 存的是递增subarray长度为i+1，组成该长度最小的尾部数字, 比如tail = \[2,5] 代表当increasing subarray长度为2是，组成递增subarray 末尾最后一位数最小是5   |
| [354. Russian Doll Envelopes](https://leetcode.com/problems/russian-doll-envelopes/description/) | _O(nlogn)_ |	_O(n)_	| Hard | 按照width由小到达排序，再把同样width，把height由大到小排序，dp\[i] 存组成递增subarray长度为i+1时，末尾最小数(也就是最小height) |
| [363. Max Sum of Rectangle No Larger Than K](https://leetcode.com/problems/max-sum-of-rectangle-no-larger-than-k/description/) | _O(min(m, n)^2 * max(m, n) * logn(max(m, n)))_ |	_O(max(m, n))_	| Hard | 如果row多，外面两个outer loop是col(vice versa), 利用binary search(set) |
| [367. Valid Perfect Square](https://leetcode.com/problems/valid-perfect-square/) | _O(logn)_ |	_O(1)_	| Easy | Newton Method |
| [374. Guess Number Higher or Lower](https://leetcode.com/problems/guess-number-higher-or-lower/) | _O(logn)_ |	_O(1)_	| Easy | |
| [378. Kth Smallest Element in a Sorted Matrix](https://leetcode.com/problems/kth-smallest-element-in-a-sorted-matrix/description/) | _O(n * log(MAX - MIN)_ |	_O(1)_	| Medium | l=m\[0]\[0], r=m\[-1]\[-1], binary search 是否至少有k个数小于等于mid |
| [410. Split Array Largest Sum](https://leetcode.com/problems/split-array-largest-sum/description/) | _O(nlogn)_ |	_O(1)_	| Hard | 答案在\[maxnum, totsum]之间，binary search这个interval |
| [436. Find Right Interval](https://leetcode.com/problems/find-right-interval/) | _O(nlogn)_ |	_O(n)_	| Medium | 把每个interval start put in set, 然后interval找end的lower bound |
| [475. Heaters](https://leetcode.com/problems/find-right-interval/) | _O((m + n) * logn)_ |	_O(1)_	| Easy | <ul><li>sort heater + lower_bound</li><li> sort house sort heaters,逐渐递增index</li></ul> |
| [540. Single Element in a Sorted Array](https://leetcode.com/problems/single-element-in-a-sorted-array/description/) | _O(logn)_ |	_O(1)_	| Medium | |
| [658. Find K Closest Elements](https://leetcode.com/problems/find-k-closest-elements/description/) | _O(logn+k)_ |	_O(1)_	| Medium | x-arr\[left-1]<=arr\[right]-x 保证left一定是起点，right是最后数后面一位 |
| [668. Kth Smallest Number in Multiplication Table](https://leetcode.com/problems/kth-smallest-number-in-multiplication-table/description/) | _O(log(mn)*min(n,n))_ |	_O(1)_	| Hard | binary search \[1,m\*n], isValid判断是否有至少有k个element在乘法表中 |
| [719. Find K-th Smallest Pair Distance](https://leetcode.com/problems/find-k-th-smallest-pair-distance/description/) | _O(nlogn + nlogw)_ |	_O(1)_	| Hard | sort nums, l=0, r = nums\[-1]-nums\[0], binary search是否有k个数大于等于mid在num中 |
| [744. Find Smallest Letter Greater Than Target](https://leetcode.com/problems/find-smallest-letter-greater-than-target/description/) | _O(logn)_ |	_O(1)_	| Easy | 判断最后一个字母是不是大于target, 大于的话用upperbound，否则返回第一个char |
| [786. K-th Smallest Prime Fraction](https://leetcode.com/problems/k-th-smallest-prime-fraction/) | _O(nlogr)_ |	_O(1)_	| Hard | <ul><li>用priority_queue, 先push进最小的，每次push前extract当前最小的, 保证push进去的比pop的大，最多max(n,k)次pop+push</li><li> binary search l=0, r=1, 看是不是有n个pair小于等于mid，i=0,增加j,减小A\[i]/\[j]的值，一旦A\[i]/\[j]小于等于mid，增加i,就是增加A\[i]/\[j], 再增加j, 如果count==k, 返回k中最大的那个pair</li><ul> |
| [793.Preimage Size of Factorial Zeroes Function](https://leetcode.com/problems/preimage-size-of-factorial-zeroes-function/description/) | _O((logk)^2)_ |	_O(1)_	| Hard | l = 0, r=5\*k, binary search mid是否有k个零的0，有的话r=mid, 否则l = mid+1, 最后再判断l是否有k个0, 有的话返回5,没有的话返回0 |



</br>
</br>



## Binary Search Tree

|Title | Time  | Space | Difficulty |  Algorithm Note|
| ------------- | ------------- | ------------- | ------------- | ------------- |
| [220. Contains Duplicate III](https://leetcode.com/problems/contains-duplicate-iii/description/) | _O(nlogn)_ |	_O(n)_	| Medium | set/multiset lower_bound  或者python OrderedDict, 每次popitem(false) pop 最先insert的 |
| [230	Kth Smallest Element in a BST](https://leetcode.com/problems/kth-smallest-element-in-a-bst/description/) | _O(max(h, k))_ |	_O(min(h, k))_	| Medium | inorder traversals(从最小的travel到最大的) / stack  |
| [235. Lowest Common Ancestor of a Binary Search Tree](https://leetcode.com/problems/lowest-common-ancestor-of-a-binary-search-tree/description/) | _O(h)_ |	_O(1)_	| Easy | 利用 binary search tree的性质 |
| [352. Data Stream as Disjoint Intervals](https://leetcode.com/problems/data-stream-as-disjoint-intervals/description/) | _O(logn)_ |	_O(n)_	| Hard | |
| [449. Serialize and Deserialize BST](https://leetcode.com/problems/serialize-and-deserialize-bst/) | _O(n)_ |	_O(h)_	| Medium | preorder traversals |
| [450. Delete Node in a BST](https://leetcode.com/problems/delete-node-in-a-bst/description/) | _O(h)_ |	_O(h)_	| Medium | <ul><li>swap key 和比key大的最小值，然后recursively删除swap的值 </li><li> 把key的left tree 挂在key->right的leftmost tree下面（比key大的最小数下面）</li></ul>  |
| [530. Minimum Absolute Difference in BST	](https://leetcode.com/problems/minimum-absolute-difference-in-bst/description/) | _O(n)_ |	_O(h)_	| Easy | 利用binary search tree的性质 或者inorder traversal 带着前面prev的node val |
| [783. Minimum Distance Between BST Nodes](https://leetcode.com/problems/minimum-distance-between-bst-nodes/description/) | _O(n)_ |	_O(h)_	| Easy | 利用binary search tree的性质 或者inorder traversal 带着前面prev的node val(与530题 解法一样) |

</br>
</br>

## Depth-First Search

|Title | Time  | Space | Difficulty |  Algorithm Note|
| ------------- | ------------- | ------------- | ------------- | ------------- |
| [112. Path Sum](https://leetcode.com/problems/path-sum/description/) | _O(n)_ |	_O(h)_	| Easy |  write in one function |
| [113	Path Sum II](https://leetcode.com/problems/path-sum-ii/) |	_O(n)_	| _O(h)_ |	Medium |	|
| [199	Binary Tree Right Side View](https://leetcode.com/problems/binary-tree-right-side-view/)	| _O(n)_	| _O(h)_	| Medium		 |  用NULL 可以作为queue的层和层间隔  |
| [200	Number of Islands](https://leetcode.com/problems/binary-tree-right-side-view/description/)	| _O(m \* n)_ |	_O(m \* n)_ |	Medium		|   |
| [236	Lowest Common Ancestor of a Binary Tree](https://leetcode.com/problems/lowest-common-ancestor-of-a-binary-tree/description/)	|	_O(n)_ |	_O(h)_ |	Medium	| 🔍 DFS left, right 如果left，right 各含有p,q</br> 返回current root， 否则返回left or right 同时含有p,q的那个;关键是: 不一定p,q都会经过，比如p是q的parent，到p直接返回，不会经过q |
| [257	Binary Tree Paths](https://leetcode.com/problems/binary-tree-paths/description/) | 	_O(n \* h)_ | _O(h)_ | Easy 	| <ul><li>可以用queue，BFS 扫每个level，返回最右侧的 </li> <li>也可以用加上一个null pointer在 每个level</br>  queue 最后面，一旦返回null，知道这层扫完了，</br> append last number </li></ul>|
| [282	Expression Add Operators](https://leetcode.com/problems/expression-add-operators/)	| _O(4^n)_ | _O(n)_ | Hard | DFS，需要cv (cumulative sum), pv(previous sum),</br>  pos 到现在process的index，注意: <ul><li>现在是'\*', cv = cv - pv + p\*n, pv = pv\*n </li> <li>现在是'-', cv = cv - pv + n, pv = -n </li></ul> 🌒|
| [301. Remove Invalid Parentheses](https://leetcode.com/problems/remove-invalid-parentheses/description/)	| _O(C(n, c))_	| _O(c)_ | Hard | <ul><li> DFS: 开始DFS前记录left_removed，</br> right_removed, 这样可以保证删除的parenthese 最短，</br> 再记录pair，'(' 时候pair+1, ')'时候pair-1， pair最后等于0， 表示valid</li> <li>BFS: 用unordered_set 记录所有被visited的string，每次取一次char修改 push到queue</li></ul>|
| [329. Longest Increasing Path in a Matrix](https://leetcode.com/problems/longest-increasing-path-in-a-matrix/description/)	| _O(m \* n)_ | _O(m \* n)_ | Hard | 😍 DFS: 历遍上下左右四个点，避免到重复点的方法: memoization 记录到这点最多increase</br>  path element数 |
| [332. Reconstruct Itinerary](https://leetcode.com/problems/reconstruct-itinerary/description/)	|	_O(t! / (n1! \* n2! \* ... nk!))_	 |	_O(t)_ |	Medium	|  😍🔍 <ul><li>nodes with odd degree 是entrance/exits </li> <li>The reason we got stuck is because that we hit the exit </li><li>dfs到没有可走的路时候 再append to vector,最后solution 是reverse vector是解</li></ul> |
| [399. Evaluate Division](https://leetcode.com/problems/evaluate-division/description/)	|	_O(q\*\|V\|!)_	|	_O(e)_ |	Medium | DFS with memiozation 用unordered_map, vector, unordered_set记录是否经过， 跟[329. Longest Increasing Path in a Matrix](https://leetcode.com/problems/longest-increasing-path-in-a-matrix/description/)类似|
| [417. Pacific Atlantic Water Flow](https://leetcode.com/problems/pacific-atlantic-water-flow/description/)	|	_O(m \* n)_	|	_O(m \* n)_ |	Medium | 😍 可以用 bit mask, 可以 dimension vector 用作visited，记录是否visited 过 |
| [440. K-th Smallest in Lexicographical Order](https://leetcode.com/problems/k-th-smallest-in-lexicographical-order/description/)	|	_O(logn)_	|	_O(logn)_ |	Hard | 🌒🐸 |
| [464. Can I Win](https://leetcode.com/problems/can-i-win/description//)	|	_O(n!)_	|	_O(n)_ |	Medium | 😚🔍 把用过的数true，false bool 的array 转化成数是关键 |
| [515. Find Largest Value in Each Tree Row](https://leetcode.com/problems/find-largest-value-in-each-tree-row/description//)	|	_O(n)_	|	_O(h)_ |	Medium | easy one. Both DFS and BFS apply |
| [547. Friend Circles](https://leetcode.com/problems/friend-circles/description/)	|	_O(n^2)_	|	_O(n)_ |	Medium | Union Find😍 |
| [638. Shopping Offers](https://leetcode.com/problems/shopping-offers/description/)	|	_O(n \* 2^n)_	|	_O(n)_ |	Medium | 📖 |
| [690. Employee Importance](https://leetcode.com/problems/employee-importance/description/)	|	_O(n)_	|	_O(h)_ |	Easy | 😍 |
| [733. Flood Fill](https://leetcode.com/problems/flood-fill/description/)	|	_O(m\*n)_	|	_O(m\*n)_ |	Easy |  |
| [749. Contain Virus](https://leetcode.com/problems/contain-virus/)	|	_O((m \* n)^(4/3))_		|	_O(m \* n)_ |	Hard |  |
| [753. Cracking the Safe](https://leetcode.com/problems/cracking-the-safe/description/)	|	_O(k^n)_	|	_O(k^n)_ |	Hard |  |
| [756. Pyramid Transition Matrix](https://leetcode.com/problems/pyramid-transition-matrix/description/)	|	_O(a^b)_	|	_O(a^b)_ |	Medium | bottom-up, bit mask |
| [785. Is Graph Bipartite?](https://leetcode.com/problems/is-graph-bipartite/)	|	_O(\|V+E\|)_	|	_O(\|V\|)_ |	Medium | 😍🔍 用红蓝两色表vertex，如果有任何相邻的vertex表的颜色一样，return false |
| [797. All Paths From Source to Target](https://leetcode.com/problems/all-paths-from-source-to-target/description/)	|	_O(p + r \* n)_	|	_O(n)_ |	Medium |  😍 比较easy的 |
| [802. Find Eventual Safe States](https://leetcode.com/problems/find-eventual-safe-states/description/)	|	_O(\|V+E\|)_	|	_O(\|V\|)_ |	Medium | 😍🔍 需要定义state 0：unvisited, 1 visited not safe, 2 visited safe， 注意不能用visited 的value 代替boolean 的value |

</br>
</br>

## Backtracking
|Title | Time  | Space | Difficulty |  Algorithm Note|
| ------------- | ------------- | ------------- | ------------- | ------------- |
| [017. Letter Combinations of a Phone Number](https://leetcode.com/problems/letter-combinations-of-a-phone-number/)	|	_O(n \* 4^n)_	|	_O(n)_ |	Medium |  |
| [022. Generate Parentheses](https://leetcode.com/problems/find-eventual-safe-states/description/)	|	_O(4^n \/ n^(3\/2))_	|	_O(n)_ |	Medium |  |
| [037. Sudoku Solver](https://leetcode.com/problems/sudoku-solver/)	|	_O((9!)^9)_	|	_O(1)_ |	Hard |  recussion return 和 不return的区别， <ul><li>return 代表loop检查完毕,不进行下面的loop</li><li>不return 代表loop没有走全，需要继续</li></ul> |
| [039. Combination Sum](https://leetcode.com/problems/combination-sum/)	|	_O(k \* n^k)_	|	_O(k)_ |	Medium | 需要sort, 每次backtrack 不增加index，因为数可以用两遍 |
| [040. Combination Sum II](https://leetcode.com/problems/combination-sum-ii/)	|	_O(n \* n!)_	|	_O(n)_ |	Medium |  |
| [216. Combination Sum III](https://leetcode.com/problems/combination-sum-iii/description/)	|	_O(k \* C(n, k))_	|	_O(k)_ |	Medium |  |
| [046. Permutations](https://leetcode.com/problems/permutations/)	|	_O(\n * n!)_	|	_O(n)_ |	Medium | <ul><li>可以用next_permutation</li><li> 可以用backtracking + swap</li> <li> 可以用recursive insert value</li></ul> |
| [047. Permutations II](https://leetcode.com/problems/permutations-ii/)	|	_O(\n * n!)_	|	_O(n)_ |	Medium |  <ul><li>可以用backtracking + swap, swap前</br>须check i是不是第一个从begin开始这样的数值</li> <li> 可以用recursive insert value, </br>insert前需要知道此数在list中第一个position index</li></ul>  |
| [051. N-Queens	](https://leetcode.com/problems/n-queens/)	|	_O(n!)_	|	_O(n)_ |	Hard | not hard 经典backtracking |
| [052. N-Queens-II](https://leetcode.com/problems/n-queens-ii/)	|	_O(n!)_	|	_O(n)_ |	Hard |  |
| [077. Combinations](https://leetcode.com/problems/combinations/)	|	_O(k \* C(n, k))_	|	_O(k)_ |	Medium | 经典backtracking 可recursive 可iterative |
| [079. Word Search](https://leetcode.com/problems/word-search/description/)	|	_O(m \* n \* l)_	|	_O(l)_ |	Medium | smart way: 用bitmask 把visited的^ 变为为字母 |
| [093. Restore IP Addresses](https://leetcode.com/problems/restore-ip-addresses/description/)	|	_O(1)_	|	_O(1)_ |	Medium | recursive & iterative |
| [078. Subsets](https://leetcode.com/problems/subsets/)	|	_O(n \* 2^n)_	|	_O(1)_ |	Medium | recursive & iterative, 可以用bit trick</br>第一个数每2次出现1次，第二个数每4次出现2次，第二个数每8次出现4次 |
| [090. Subsets II](https://leetcode.com/problems/subsets-ii/)	|	_O(n \* 2^n)_	|	_O(1)_ |	Medium | recursive & iterative（插数） |
| [126. Word Ladder II](https://leetcode.com/problems/word-ladder-ii/description/)	|	_O(n \* d)_	|	_O(d)_ |	Hard | two end pointer BFS |
| [131. Palindrome Partitioning](https://leetcode.com/problems/palindrome-partitioning/description/)	|	_O(n^2) ~ O(2^n)_	|	_O(n^2)_ |	Medium |  |
| [140. Word Break II](https://leetcode.com/problems/word-break-ii/)	|	_O(n \* l^2 + n \* r)_	|	_O(n^2)_ |	Hard | backtracking with Memoization </br>(backtracking function return vector\<string\>) |
| [212. Word Search II](https://leetcode.com/problems/word-search-ii/)	|	_O(m * n * l)_	|	_O(l)_ |	Hard | backtracking using suffix trie |
| [526. Beautiful Arrangement](https://leetcode.com/problems/beautiful-arrangement/description/)	|	_O(n!)_	|	_O(n)_ |	Medium | swap, top down |
| [676. Implement Magic Dictionary](https://leetcode.com/problems/implement-magic-dictionary/description/)	|	_O(n)_	|	_O(d)_ |	Medium | instead search every chars from A-Z, search hello as *ello, h*llo |
| [679. 24 Game](https://leetcode.com/problems/24-game/description/)	|	_O(1)_	|	_O(1)_ |	Hard | Complexity: upper bound of 12\* 6 \* 2 \* 4 \* 4 \* 4 = 9216 possibilities| 
| [698. Partition to K Equal Sum Subsets](https://leetcode.com/problems/partition-to-k-equal-sum-subsets/)	|	_O(n\* 2^n)_	|	_O(2^n)_ |	Medium | 要有start index, 否则time out |  
| [718. Maximum Length of Repeated Subarray](https://leetcode.com/problems/maximum-length-of-repeated-subarray/)	|	_O(m \* n)_	|	_O(min(m, n))_ |	Medium | DP  |
| [784. Letter Case Permutation](https://leetcode.com/problems/letter-case-permutation/description/)	|	_O(n \* 2^n)	_	|	_O(1)_ |	Easy |  |
 
</br>
</br>

DFS 是看有没有path，DP是看有几个path
 ## Dynamic Programming 
 |Title | Time  | Space | Difficulty |  Algorithm Note|
| ------------- | ------------- | ------------- | ------------- | ------------- |
| [010. Regular Expression Matching](https://leetcode.com/problems/regular-expression-matching/description/)	|	_O(m\*n)_	|	_O(n)_ |	Hard |  |
| [053. Maximum Subarray](https://leetcode.com/problems/maximum-subarray/)	|	_O(n)_	|	_O(1)_ |	Easy |  |
| [062. Unique Paths](https://leetcode.com/problems/unique-paths/)	|	_O(m \* n)_	|	_O(m + n)_ |	Medium |  |
| [063. Unique Paths II](https://leetcode.com/problems/unique-paths-ii/description/)	|	_O(m \* n)_	|	_O(m + n)_ |	Medium |  |
| [064. Minimum Path Sum](https://leetcode.com/problems/minimum-path-sum/)	|	_O(m \* n)_	|	_O(m + n)_ |	Medium | |
| [070. Climbing Stairs](https://leetcode.com/problems/climbing-stairs/description/)	|	_O(n)_	|	_O(1)_ |	Easy |  |
| [072. Edit Distance](https://leetcode.com/problems/edit-distance/)	|	_O(m\*n)_	|	_O(m+n)_ |	Hard |  |
| [087. Scramble String](https://leetcode.com/problems/scramble-string/description/)	|	_O(n^4)_	|	_O(n^3)_ |	Hard | BackTrack with DP |
| [091. Decode Ways](https://leetcode.com/problems/decode-ways/description/)	|	_O(n)_	|	_O(1)_ |	Medium | 📖 |
| [096. Unique Binary Search Trees	](https://leetcode.com/problems/unique-binary-search-trees/description/)	|	_O(n)_	|	_O(1)_ |	Medium | 📖 cartesian product</br> 作为root，sum(#left + #right) Catalan number |
| [097. Interleaving String](https://leetcode.com/problems/interleaving-string/)	|	_O(m\*n)_	|	_O(m+n)_ |	Hard | <ul><li>s1\[i-1] == s3\[i+j-1] 代表s3\[i+j-1] 来自S1 </li> <li>s2\[j-1] == s3\[i+j-1] 代表 s3\[i+j-1] 来自S2 </li></ul> |
| [115. Distinct Subsequences](https://leetcode.com/problems/distinct-subsequences/)	|	_O(n^2)_	|	_O(n)_ |	Hard | 弄清删除\[i-1\]\[j\] 还是用\[i-1\]\[j-1\] char关系 |
| [120. Triangle](https://leetcode.com/problems/triangle/)	|	_O(m\*n)_	|	_O(n)_ |	Medium | Bottom-up DP  |
| [123. Best Time to Buy and Sell Stock III	](https://leetcode.com/problems/best-time-to-buy-and-sell-stock-iii/)	|	_O(n)_	|	_O(n)_ |	Hard | 每个新loop后的profit 是基于前i-1个</br>transaction的,而每个loop 只会增加一个</br> transaction，因为每个loop 的原则是</br> 找到新的最低点，买进，找最高点再卖出 |
| [132. Palindrome Partitioning II](https://leetcode.com/problems/palindrome-partitioning-ii/description/)	|	_O(n^2)_	|	_O(n) </br>~O(n)_ |	Hard | 需要dp记录到i为止的mincut<ul><li>O(n^2): 需要一个vector记录</br>substring从i到j是否为pal</li> <li>O(n): 从中间向两边(odd,even)判断</br>是不是pal，不是pal就停止记录</br>最短的i+j点的mincut</li></ul> |
| [139. Word Break](https://leetcode.com/problems/word-break/description/)	|	_O(n^2)_	|	_O(n)_ |	Medium | 看substr\[i,j]在不在dict， 优化可以长度</br>小的substring看，一旦到true，break，</br>减小运行时间 dp\[i] = (j == 0)\|\| dp\[j-1]) </br> 也可以用DFS， with memoization |
| [152. Maximum Product Subarray](https://leetcode.com/problems/maximum-product-subarray/)	|	_O(n)_	|	_O(1)_ |	Medium | Localmin, Localmax, 最小的负数</br>乘以一个负数可能变成最大的，</br>最大的正数乘以个负数可能变成最小的 |
| [174. Dungeon Game](https://leetcode.com/problems/dungeon-game/)	|	_O(n+m)_	|	_O(n)~O(1)_ |	Hard | bottom-up DF，若need<=0, set it to 1 |
| [188. Best Time to Buy and Sell Stock IV](https://leetcode.com/problems/best-time-to-buy-and-sell-stock-iv/description/)	|	_O(k*n)_	|	_O(n)_ |	Hard | 如果 k>prices.size() profit = max(p\[i]-p\[i-1],0) |
| [198. House Robber](https://leetcode.com/problems/house-robber/)	|	_O(n)_	|	_O(1)_ |	Easy | 三个variables，一个记录现在profit,</br>一个记录上一个profit，</br> 一个记录上上一个profit |
| [213. House Robber II](https://leetcode.com/problems/house-robber-ii/)	|	_O(n)_	|	_O(1)_ |	Medium | 分成另个house rob问题，<ul><li>Rob houses 0 to n - 2 </li> <li>Rob houses 1 to n - 1</li></ul> |
| [221. Maximal Square](https://leetcode.com/problems/maximal-square/)	|	_O(n^2)_	|	_O(n)_ |	Medium | dp记录到（i,j) 最大正方形边长</br> d\[i,j] = min(d\[i-1,j]+ d\[i,j-1] + d\[i-1,j-1])+ 1 |
| [279. Perfect Squares](https://leetcode.com/problems/perfect-squares/description/)	|	_O(n \* sqrt(n)_	|	_O(n)_ |	Medium | static dynamic programming 会更快 |
| [304. Range Sum Query 2D - Immutable](https://leetcode.com/problems/range-sum-query-2d-immutable/)	|	_ctor: O(m * n), lookup: O(1)_	|	_O(m+n)_ |	Medium |  |
| [309. Best Time to Buy and Sell Stock with Cooldown](https://leetcode.com/problems/perfect-squares/description/)	|	_O(n)_	|	_O(1)_ |	Medium | 两个vector，一个track最低买点</br>一个track最高卖点, buy需要带着之前买的利润<ul><li>buy\[i] = max(sell\[i-2]-price, buy\[i-1])</li> <li>sell\[i] = max(buy\[i-1]+price, sell\[i-1])</li></ul>|
| [312. Burst Balloons](https://leetcode.com/problems/burst-balloons/description/)	|	_O(n^3)_	|	_O(n^2)_ |	Hard | dp\[i]\[j] 代表从i到jburst最大数 |
| [322. Coin Change](https://leetcode.com/problems/coin-change/description/)	|	_O(n\*k)_	|	_O(k)_ |	Medium | similar to [279. Perfect Squares](https://leetcode.com/problems/perfect-squares/description/) : DP, BFS, DFS |
| [357. Count Numbers with Unique Digits](https://leetcode.com/problems/count-numbers-with-unique-digits/description/)	|	_O(n)_	|	_O(1)_ |	Medium | DP, Static DP, backtracking |
| [368. Largest Divisible Subset](https://leetcode.com/problems/largest-divisible-subset/)	|	_O(n^2)_	|	_O(n)_ |	Medium | 先sort，然后后面的大的，只要除以subset中最大的数，就可以append进subset,再用一个parent vector,放新放数得上一个数的位置 |
| [375. Guess Number Higher or Lower II](https://leetcode.com/problems/guess-number-higher-or-lower-ii/description/)	|	_O(n^2)_	|	_O(n^2)_ |	Medium | dp\[i]\[j]存的是n从1到j，最小的guarantee cost|
| [377. Combination Sum IV](https://leetcode.com/problems/combination-sum-iv/description/)	|	_O(nlogn + n \* t)_	|	_O(t)_ |	Medium | backtracking会timeout，因为一个一个数|
| [403. Frog Jump](https://leetcode.com/problems/frog-jump/description/)	|	_O(n)_	|	_O(n)_ |	Hard | 需要dp，普通DFS， backtracking 会 timeout, python 把list变成set，much faster|
| [416. Partition Equal Subset Sum](https://leetcode.com/problems/partition-equal-subset-sum/description/)	|	_O(n\*s)_	|	_O(s)_ |	Medium | backtracking（更快） 或DP（要loop nums: loop target:1) |
| [446. Arithmetic Slices II - Subsequence](https://leetcode.com/problems/arithmetic-slices-ii-subsequence/description/)	|	_O(n^2)_	|	_O(n\*d)_ |	Hard | 📖 每个位置在string都要建一个字典，key是i-j 的差, dict\[i]\[diff] += dict\[j]\[diff]  |
| [466. Count The Repetitions](https://leetcode.com/problems/count-the-repetitions/description/)	|	_O(s1 \* min(s2, n1))_	|	_O(s2)_ |	Hard | 📖 找到pattern 然后跳过重复的部分 |
| [467. Unique Substrings in Wraparound String](https://leetcode.com/problems/count-the-repetitions/description/)	|	_O(n)_	|	_O(1)_ |	Medium |  |
| [472. Concatenated Words](https://leetcode.com/problems/concatenated-words/description/)	|	_O(n \* l^2)_	|	_O(l)_ |	Medium |  |
| [474. Ones and Zeroes](https://leetcode.com/problems/ones-and-zeroes/)	|	_O(s \*m \* n)_	|	_O(s \*m \* n)_|	Medium | 经典knapsack |
| [514. Freedom Trail](https://leetcode.com/problems/freedom-trail/description/)	|	_O(k) ~ O(k \* r^2)_	|	_O(r)_|	Hard |  <ul><li> dp\[i]\[k]代表当key\[i] = ring\[j],从j到k的需要步数(为下一步做准备). </li><li> dp\[k]代表在key\[i]是到达k最小的距离, 外loop是0: key-1, 中loop是 key\[i-1]在ring中出现的位置, 内loop是key\[i]在ring中出现的位置</li></ul> |
| [516. Longest Palindromic Subsequence](https://leetcode.com/problems/longest-palindromic-subsequence/description/)	|	_O(n^2)_	|	_O(n)_|	Medium | 经典dp |
| [546. Remove Boxes](https://leetcode.com/problems/remove-boxes/description/)	|	_O(n^3) ~ O(n^4)_	|	_O(n^3)_|	Hard | 📖 dp\[i]\[j]\[k] 存的是从given k个与j一样的数在j后，从i,到j 最大得数 |
| [552. Student Attendance Record II](https://leetcode.com/problems/student-attendance-record-ii/description/)	|	_O(n)_	|	_O(1)~O(n)_|	Hard | |
| [576. Out of Boundary Paths](https://leetcode.com/problems/student-attendance-record-ii/description/)	|	_O(N \* m \* n)_	|	_O(m \* n)_|	Medium | dp or dfs with memoization or 每次进入只能从 (i+j)%2 = 1 进入(i+j)%2 = 0 或者 从 (i+j)%2 = 0 进入(i+j)%2 = 1 |
| [583. Delete Operation for Two Strings](https://leetcode.com/problems/delete-operation-for-two-strings/description/)	|	_O(m\*n)_	|	_O(n)_|	Medium | Edit Distance without replace |
| [600. Non-negative Integers without Consecutive Ones](https://leetcode.com/problems/non-negative-integers-without-consecutive-ones/description/)	|	_O(1)_	|	_O(1)_|	Hard | Fibonacci Sequence, 比如11000 返回fb\[5], 10101 返回 fb\[4]+ fb\[2]+fb\[0]+1 |
| [629. K Inverse Pairs Array](https://leetcode.com/problems/k-inverse-pairs-array/)	|	_O(n\*k)_	|	_O(k)_|	Hard |  |
| [639. Decode Ways II](https://leetcode.com/problems/decode-ways-ii/)	|	_O(n)_	|	_O(1)_|	Hard |  |
| [650. 2 Keys Keyboard](https://leetcode.com/problems/2-keys-keyboard/)	|	_O(sqrt(n))_	|	_O(1)_|	Medium |  |
| [664. Strange Printer](https://leetcode.com/problems/strange-printer/)	|	_O(n^3)_	|	_O(n^2)_|	Hard | 📖dp\[i]\[j] 表示从i到j，最少print的次数 |
| [673. Number of Longest Increasing Subsequence](https://leetcode.com/problems/number-of-longest-increasing-subsequence/)	|	_O(n^2)_	|	_O(n)_|	Medium |  |
| [688. Knight Probability in Chessboard](https://leetcode.com/problems/knight-probability-in-chessboard/)	|	_O(k\*n^2)_	|	_O(k\*n^2)</br>~O(n^2)_|	Medium | DP or DFS + Memoization |
| [689. Maximum Sum of 3 Non-Overlapping Subarrays](https://leetcode.com/problems/maximum-sum-of-3-non-overlapping-subarrays/description/)	|	_O(n)_	|	_O(n)_|	Hard | W记录每个点往后k个sum, left, right记录到j点左面和右面最大k个sum的index, 这样可以O(n) 完成 |
| [691. Stickers to Spell Word](https://leetcode.com/problems/stickers-to-spell-word/description/)	|	_O(2^T\*S\*T)_	|	_O(2^T)_|	Hard | 一个长度为2^T array, array的j位记录此binary number的i位为1的,在target中被set 需要最小sticker数，比如target长度为4，array长度为16，j = 5(1001) dp\[5] 表示当第0位和第三位在target中被set 所需最小sticker数 |
| [712. Minimum ASCII Delete Sum for Two Strings](https://leetcode.com/problems/minimum-ascii-delete-sum-for-two-strings/)	|	_O(m*n)_	|	_O(m\*n)</br>~O(n)_|	Medium | Edit Distance |
| [730. Count Different Palindromic Subsequences](https://leetcode.com/problems/count-different-palindromic-subsequences/description/)	|	_O(n^2)_	|	_O(n)_|	Hard | dp\[len]\[i]\[x] 存的是在i 往后,starting index 为x, 长度为len的Palindromic |
| [740. Delete and Earn](https://leetcode.com/problems/delete-and-earn/description/)	|	_O(n)_	|	_O(n)_|	Medium | 相当于house robbery，不能同时rob两个邻居的, dp\[i] = max(dp\[i-2]+dp\[i], dp\[i-1]); |
| [741. Cherry Pickup](https://leetcode.com/problems/cherry-pickup/description/)	|	_O(n^3)_	|	_O(n^2)_|	Hard |两个人同时从(0，0) 出发，到达(N-1, N-1), k为此时距(0,0)距离, dp\[i]\[j]代表 距离为k时person1到i,k-i, person2到j,k-j, 一共可以pick up最多cherry，dp\[i]\[j] = grid\[i]\[k-i]+grid\[j]\[k-j]+max( <ul><li> dp\[i]\[j], //person1 向右走，person2 向右走</li><li> dp\[i-1]\[j]), //person1 向下走, person2 向右走</li><li> dp\[i]\[j-1]), //person1 向右走，person2 向下走</li><li> dp\[i-1]\[j-1]), //person1 向下走，person2 向下走) </li></ul> |
| [746. Min Cost Climbing Stairs](https://leetcode.com/problems/min-cost-climbing-stairs/)	|	_O(n)_	|	_O(1)_|	Easy | take or skip |
| [764. Largest Plus Sign](https://leetcode.com/problems/largest-plus-sign/description/)	|	_O(n^2)_	|	_O(n^2)_|	Medium | Maximal Square, 从左到右，从上到下，从右到左，从下到上,更新最小的count |
| [788. Rotated Digits](https://leetcode.com/problems/largest-plus-sign/description/)	|	_O(n)~O(logn)_	|	_O(n)~O(logn)_|	Easy |<ul><li>O(logn) 算所有比当前digit减1是good number的所有的数，比如24 i = 1, 算的是0-19是good number的，算所有valid的，减去自己rotate还是自己的 i=1 算20-24 </li><li> O(n), 记录if i==good number, dp\[i] = 2, i==self rotate, dp\[i]=1, else dp\[i]=0</li></ul> |
| [790. Domino and Tromino Tiling](https://leetcode.com/problems/domino-and-tromino-tiling/)	|	_O(n)_	|	_O(n)~O(1)_|	Medium |  dp\[n]=2*dp\[n-1]+dp\[n-3] |
| [799. Champagne Tower](https://leetcode.com/problems/champagne-tower/)	|	_O(n^2)_	|	_O(n^2)~O(n)_|	Medium | |
| [801. Minimum Swaps To Make Sequences Increasing](https://leetcode.com/problems/minimum-swaps-to-make-sequences-increasing/description/)	|	_O(n)_	|	_O(1)_|	Medium | |
| [805. Split Array With Same Average](https://leetcode.com/problems/split-array-with-same-average/description/)	|	_O(n^4)_	|	_O(n^3)_|	Hard | totalSum/n = Asum/k = Bsum/(n-k), where k = A.size() and 1 <= k <= n/2; |
| [808. Soup Servings](https://leetcode.com/problems/soup-servings/description/)	|	_O(1)_	|	_O(1)_|	Medium | Memoization |
| [813. Largest Sum of Averages](https://leetcode.com/problems/largest-sum-of-averages/)	|	_O(k\*n^2)_	|	_O(n)_|	Hard | dp\[k]\[i] 表示在A\[:i] 中最多分k次 所得的平均数最大和 dp\[k]\[i] = max(dp\[k]\[i], dp\[k-1]\[j] + (sum\[i]-sum\[j])/(i-j))  |
| [818. Race Car](https://leetcode.com/problems/largest-sum-of-averages/)	|	_O(nlogn)_	|	_O(n)_|	Hard | <ul><li>if i=2^n-1, dp\[i]=n, </li><li>else dp\[i] = min(n + 1 + dp\[(1 << n)-1 - i], n-1+2+k+dp\[i-((1 << (n-1)) - (1 << k))] for j in \[0,n] ), </li><li>n + 1 + dp\[(1 << n)-1 - i]是先到2^n-1的用n步, +1是做reverse(停)</li><li> n-1+2+k+dp\[i-((1 << (n-1)) - (1 << k))] 是先到之前2^(n-1)-1的点, 接着+1做reverse(停),然后往回走(2^k-1)点，+1做reverse(停)，再从那个点到点i </ul></li>|
| [823. Binary Trees With Factors](https://leetcode.com/problems/binary-trees-with-factors/)	|	_O(n^2)_	|	_O(n)_|	Medium | 找规律  |
