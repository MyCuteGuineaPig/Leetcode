</br>
</br>

## Sort
|Title | Time  | Space | Difficulty |  Algorithm Note|
| ------------- | ------------- | ------------- | ------------- | ------------- |
| [315. Count of Smaller Numbers After Self](https://leetcode.com/problems/count-of-smaller-numbers-after-self/description/) | _O(nlogn)_ | _O(n)_	| Hard | MergeSort, BST |
| [327. Count of Range Sum](https://leetcode.com/problems/count-of-range-sum/description/) | _O(nlogn)_ | _O(n)_	| Hard | MergeSort with Count, BST |

## Recursion

|Title | Time  | Space | Difficulty |  Algorithm Note|
| ------------- | ------------- | ------------- | ------------- | ------------- |
| [095. Unique Binary Search Trees II](https://leetcode.com/problems/unique-binary-search-trees-ii/) | _O(4^n / n^(3/2))_ |	_O(4^n / n^(3/2))_	| Medium | Given start/end point. Generate vector of left subtree 和right subtree, 然后排列组合把他们弄在一起 |
| [098. Validate Binary Search Tree](https://leetcode.com/problems/validate-binary-search-tree/description/) | _O(n)_ |	_O(1)_	| Medium | 利用binary search tree的性质 |
| [100. Same Tree](https://leetcode.com/problems/same-tree/) | _O(n)_ |	_O(h)_	| Easy |  |
| [104. Maximum Depth of Binary Tree](https://leetcode.com/problems/maximum-depth-of-binary-tree/description/) | _O(n)_ |	_O(h)_	| Easy | |
| [105. Construct Binary Tree from Preorder and Inorder Traversal](https://leetcode.com/problems/construct-binary-tree-from-preorder-and-inorder-traversal/description/) | _O(n)_ |	_O(h)_	| Medium | preorder 第一个是tree的root, inorder 中root->val左面root的left tree,右面root的right tree,  |
| [106. Construct Binary Tree from Inorder and Postorder Traversal](https://leetcode.com/problems/construct-binary-tree-from-inorder-and-postorder-traversal/description/) | _O(n)_ |	_O(h)_	| Medium | postorder 最后一个是tree的root,postorder从后往前是right tree, 再是left-tree, inorder 中root->val左面root的left tree,右面root的right tree,  |
| [108. Convert Sorted Array to Binary Search Tree](https://leetcode.com/problems/convert-sorted-array-to-binary-search-tree/description/) | _O(n)_ |	_O(logn)_	| Medium | binary tree height 需要balanced |
| [109. Convert Sorted List to Binary Search Tree](https://leetcode.com/problems/convert-sorted-list-to-binary-search-tree/description/) | _O(n)_ |	_O(logn)_	| Medium | 📖 Linked List找中间点用两个pointer，一个每次前进一步，另一个每次前进两部 |
| [110. Balanced Binary Tree](https://leetcode.com/problems/balanced-binary-tree/description/) | _O(n)_ |	_O(h)_	| Medium | 用bottom-up 比top-down 更efficient |
| [111. Minimum Depth of Binary Tree](https://leetcode.com/problems/minimum-depth-of-binary-tree/) | _O(n)_ |	_O(h)_	| Medium | 线找到第一个点既没有left-tree, 也没有right-tree |
| [114. Flatten Binary Tree to Linked List](https://leetcode.com/problems/flatten-binary-tree-to-linked-list/description/) | _O(n)_ |	_O(h)_	| Medium | preorder 的reverse |
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
| [034. Search for a Range](https://leetcode.com/problems/search-for-a-range/) | _O(log(n))_ |	_O(1)_	| Medium | lowerbound + upperbound |
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
| [786. K-th Smallest Prime Fraction](https://leetcode.com/problems/find-smallest-letter-greater-than-target/description/) | _O(nlogr)_ |	_O(1)_	| Hard | <ul><li>用priority_queue, 先push进最小的，每次push前extract当前最小的, 保证push进去的比pop的大，最多max(n,k)次pop+push</li><li> binary search l=0, r=1, 看是不是有n个pair小于等于mid，i=0,增加j,减小A\[i]/\[j]的值，一旦A\[i]/\[j]小于等于mid，增加i,就是增加A\[i]/\[j], 再增加j, 如果count==k, 返回k中最大的那个pair</li><ul> |
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
