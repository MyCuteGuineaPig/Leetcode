

## Depth-First Search

|Title | Time  | Space | Difficulty |  Algorithm Note|
| ------------- | ------------- | ------------- | ------------- | ------------- |
| [112. Path Sum](https://leetcode.com/problems/path-sum/description/) | _O(n)_ |	_O(h)_	| Easy |  write in one function |
| [113	Path Sum II](https://leetcode.com/problems/path-sum-ii/) |	_O(n)_	| _O(h)_ |	Medium |	|
| [199	Binary Tree Right Side View](https://leetcode.com/problems/binary-tree-right-side-view/)	| _O(n)_	| _O(h)_	| Medium		 |  |
| [200	Number of Islands](https://leetcode.com/problems/binary-tree-right-side-view/description/)	| _O(m \* n)_ |	_O(m \* n)_ |	Medium		|   |
| [236	Lowest Common Ancestor of a Binary Tree](https://leetcode.com/problems/lowest-common-ancestor-of-a-binary-tree/description/)	|	_O(n)_ |	_O(h)_ |	Medium	| DFS left, right 如果left，right 各含有p,q 返回 current root， 否则返回left or right 同时含有p,q的那个 |
| [257	Binary Tree Paths](https://leetcode.com/problems/binary-tree-paths/description/) | 	_O(n \* h)_ | _O(h)_ | Easy 	| <ul><li>可以用queue，BFS 扫每个level，返回最右侧的 </li> <li>也可以用加上一个null pointer在 每个levle queue 最后面，一旦返回null，知道这层扫完了，append last number </li></ul>|
| [282	Expression Add Operators](https://leetcode.com/problems/expression-add-operators/)	| _O(4^n)_ | _O(n)_ | Hard | DFS，需要cv (cumulative sum), pv(previous sum), pos 到现在process的index，注意: <ul><li>现在是'\*', cv = cv - pv + p\*n, pv = pv\*n </li> <li>现在是'-', cv = cv - pv + n, pv = -n </li></ul>|
| [301. Remove Invalid Parentheses](https://leetcode.com/problems/remove-invalid-parentheses/description/)	| _O(C(n, c))_	| _O(c)_ | Hard | <ul><li> DFS: 开始DFS前记录left_removed，right_removed, 这样可以保证删除的parenthese 最短，再记录pair，'(' 时候pair+1, ')'时候pair-1， pair最后等于0， 表示valid</li> <li>BFS: 用unordered_set 记录所有被visited的string，每次取一次char修改 push到queue</li></ul>|
| [329. Longest Increasing Path in a Matrix](https://leetcode.com/problems/longest-increasing-path-in-a-matrix/description/)	| _O(m \* n)_ | _O(m \* n)_ | Hard | DFS: 历遍上下左右四个点，避免到重复点的方法: memoization 记录到这点最多increase path element数 |
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
| [802. Find Eventual Safe States](https://leetcode.com/problems/find-eventual-safe-states/description/)	|	_O(\|V+E\|)_	|	_O(\|V\|)_ |	Medium |  |

##Backtracking
|Title | Time  | Space | Difficulty |  Algorithm Note|
| ------------- | ------------- | ------------- | ------------- | ------------- |
