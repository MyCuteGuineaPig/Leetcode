

## Depth-First Search

|Title | Time  | Space | Difficulty |  Algorithm Note|
| ------------- | ------------- | ------------- | ------------- | ------------- |
| [112. Path Sum](https://leetcode.com/problems/path-sum/description/) | _O(n)_ |	_O(h)_	| Easy |  write in one function |
| [113	Path Sum II](https://leetcode.com/problems/path-sum-ii/) |	_O(n)_	| _O(h)_ |	Medium |	|
| [199	Binary Tree Right Side View](https://leetcode.com/problems/binary-tree-right-side-view/)	| _O(n)_	| _O(h)_	| Medium		 |  |
| [200	Number of Islands](https://leetcode.com/problems/binary-tree-right-side-view/description/)	| _O(m \* n)_ |	_O(m \* n)_ |	Medium		|   |
| [236	Lowest Common Ancestor of a Binary Tree](https://leetcode.com/problems/lowest-common-ancestor-of-a-binary-tree/description/)	|	_O(n)_ |	_O(h)_ |	Medium	| DFS left, right 如果left，right 各含有p,q</br> 返回current root， 否则返回left or right 同时含有p,q的那个 |
| [257	Binary Tree Paths](https://leetcode.com/problems/binary-tree-paths/description/) | 	_O(n \* h)_ | _O(h)_ | Easy 	| <ul><li>可以用queue，BFS 扫每个level，返回最右侧的 </li> <li>也可以用加上一个null pointer在 每个level</br>  queue 最后面，一旦返回null，知道这层扫完了，</br> append last number </li></ul>|
| [282	Expression Add Operators](https://leetcode.com/problems/expression-add-operators/)	| _O(4^n)_ | _O(n)_ | Hard | DFS，需要cv (cumulative sum), pv(previous sum),</br>  pos 到现在process的index，注意: <ul><li>现在是'\*', cv = cv - pv + p\*n, pv = pv\*n </li> <li>现在是'-', cv = cv - pv + n, pv = -n </li></ul>|
| [301. Remove Invalid Parentheses](https://leetcode.com/problems/remove-invalid-parentheses/description/)	| _O(C(n, c))_	| _O(c)_ | Hard | <ul><li> DFS: 开始DFS前记录left_removed，</br> right_removed, 这样可以保证删除的parenthese 最短，</br> 再记录pair，'(' 时候pair+1, ')'时候pair-1， pair最后等于0， 表示valid</li> <li>BFS: 用unordered_set 记录所有被visited的string，每次取一次char修改 push到queue</li></ul>|
| [329. Longest Increasing Path in a Matrix](https://leetcode.com/problems/longest-increasing-path-in-a-matrix/description/)	| _O(m \* n)_ | _O(m \* n)_ | Hard | DFS: 历遍上下左右四个点，避免到重复点的方法: memoization 记录到这点最多increase</br>  path element数 |
| [332. Reconstruct Itinerary](https://leetcode.com/problems/reconstruct-itinerary/description/)	|	_O(t! / (n1! \* n2! \* ... nk!))_	 |	_O(t)_ |	Medium	|  <ul><li>nodes with odd degree 是entrance/exits </li> <li>The reason we got stuck is because that we hit the exit </li><li>dfs到没有可走的路时候 再append to vector,最后solution 是reverse vector是解</li></ul> |
| [399. Evaluate Division](https://leetcode.com/problems/evaluate-division/description/)	|	_O(q\*\|V\|!)_	|	_O(e)_ |	Medium | |
| [417. Pacific Atlantic Water Flow](https://leetcode.com/problems/pacific-atlantic-water-flow/description/)	|	_O(m \* n)_	|	_O(m \* n)_ |	Medium | 可以用 bit mask |
| [440. K-th Smallest in Lexicographical Order](https://leetcode.com/problems/k-th-smallest-in-lexicographical-order/description/)	|	_O(logn)_	|	_O(logn)_ |	Hard |  |
| [464. Can I Win](https://leetcode.com/problems/can-i-win/description//)	|	_O(n!)_	|	_O(n)_ |	Medium | 📖 把用过的数true，false bool 的array 转化成数是关键 |
| [515. Find Largest Value in Each Tree Row](https://leetcode.com/problems/find-largest-value-in-each-tree-row/description//)	|	_O(n)_	|	_O(h)_ |	Medium | easy one. Both DFS and BFS apply |
| [547. Friend Circles](https://leetcode.com/problems/friend-circles/description/)	|	_O(n^2)_	|	_O(n)_ |	Medium | easy one. |
| [638. Shopping Offers](https://leetcode.com/problems/shopping-offers/description/)	|	_O(n \* 2^n)_	|	_O(n)_ |	Medium | 📖 |
| [690. Employee Importance](https://leetcode.com/problems/employee-importance/description/)	|	_O(n)_	|	_O(h)_ |	Easy |  |
| [733. Flood Fill](https://leetcode.com/problems/flood-fill/description/)	|	_O(m\*n)_	|	_O(m\*n)_ |	Easy |  |
| [753. Cracking the Safe](https://leetcode.com/problems/cracking-the-safe/description/)	|	_O(k^n)_	|	_O(k^n)_ |	Hard |  |
| [756. Pyramid Transition Matrix](https://leetcode.com/problems/pyramid-transition-matrix/description/)	|	_O(a^b)_	|	_O(a^b)_ |	Medium | bottom-up |
| [785. Is Graph Bipartite?](https://leetcode.com/problems/is-graph-bipartite/)	|	_O(\|V+E\|)_	|	_O(\|V\|)_ |	Medium | 用红蓝两色表vertex，如果有任何相邻的vertex表的颜色一样，return false |
| [797. All Paths From Source to Target](https://leetcode.com/problems/all-paths-from-source-to-target/description/)	|	_O(p + r \* n)_	|	_O(n)_ |	Medium |  |
| [802. Find Eventual Safe States](https://leetcode.com/problems/find-eventual-safe-states/description/)	|	_O(\|V+E\|)_	|	_O(\|V\|)_ |	Medium | 需要定义state 0：unvisited, 1 visited not safe, 2 visited safe |

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
| [514. Freedom Trail](https://leetcode.com/problems/freedom-trail/description/)	|	_O(k) ~ O(k \* r^2)_	|	_O(r)_|	Hard | 记录ring每个字母的位置，字母位置push进</br>vector, loop key,把i-1的字母vector作为起始点，</br>把key\[i]字母vector作为现在点, loop，找到最小</br>移动距离，如果ring\[k] = key\[i], update dp\[k]的值 |
| [516. Longest Palindromic Subsequence](https://leetcode.com/problems/longest-palindromic-subsequence/description/)	|	_O(n^2)_	|	_O(n)_|	Medium | 经典dp |
| [546. Remove Boxes](https://leetcode.com/problems/remove-boxes/description/)	|	_O(n^3) ~ O(n^4)_	|	_O(n^3)_|	Hard | 📖 dp\[i]\[j]\[k] 存的是从given k个与j一样的数在j后，从i,到j 最大得数 |
| [552. Student Attendance Record II](https://leetcode.com/problems/student-attendance-record-ii/description/)	|	_O(n)_	|	_O(1)~O(n)_|	Hard | |
| [576. Out of Boundary Paths](https://leetcode.com/problems/student-attendance-record-ii/description/)	|	_O(N \* m \* n)_	|	_O(m \* n)_|	Medium | dp or dfs with memoization |
| [583. Delete Operation for Two Strings](https://leetcode.com/problems/delete-operation-for-two-strings/description/)	|	_O(m\*n)_	|	_O(n)_|	Medium | Edit Distance without replace |
| [600. Non-negative Integers without Consecutive Ones](https://leetcode.com/problems/non-negative-integers-without-consecutive-ones/description/)	|	_O(1)_	|	_O(1)_|	Hard | Fibonacci Sequence, 比如11000 返回fb\[5], 10101 返回 fb\[4]+ fb\[2]+fb\[0]+1 |
| [629. K Inverse Pairs Array](https://leetcode.com/problems/k-inverse-pairs-array/)	|	_O(n\*k)_	|	_O(k)_|	Hard |  |
| [639. Decode Ways II](https://leetcode.com/problems/decode-ways-ii/)	|	_O(n)_	|	_O(1)_|	Hard |  |
| [650. 2 Keys Keyboard](https://leetcode.com/problems/2-keys-keyboard/)	|	_O(sqrt(n))_	|	_O(1)_|	Medium |  |
| [664. Strange Printer](https://leetcode.com/problems/strange-printer/)	|	_O(n^3)_	|	_O(n^2)_|	Hard |  |
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
