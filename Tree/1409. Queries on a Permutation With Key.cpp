/**
 * 
 * BIT TREE: 
  
  1
  |
  v
  2         
  |   3
  v  /    5
  4     /  
  |   6
  v  / 
  8  <- 7
比如一个tree 有8个节点，更新时候
更新1 ->2 ->4 ->8
更新2 ->4 -> 8
更新3(11) -> 4(11+1 = 100)->8
更新4 (100) ->8(100+100 = 1000)
更新5 -> 6 -> 8
更新6(110) ->8 (110 + 10 = 1000)
更新7->8
如果左面连续都是1，直接上最左面bit的下一位 比如110 -> 1000, 1110 -> 10000, 1100 -> 10000
原因: 左侧的1已经存了需要的sum，比如110， 100 存了前4，所以110-> 1000 保证8拥有(5,6的和)，
     比如111->1000， 因为110存了（5，6的和), 100(存了1-4的和），也因为8已经存了5和6的和，so 111 只存第7个
求sum 
求1:  1
求2:  2
求3:  3 + 2 (11, 10)
求4:  4
求5:  5 + 4 (101, 100)
求6:  6 + 4 (110, 100)
求7:  7 + 6 + 4 （111， 110， 100）
求8， 8
BIT index n只存最小bit下面的和
比如1110 有的和是1110 + 1101 
比如1100， 有和的是1001 + 1010 + 1011 + 1100
比如100 有的和是1， 10, 100,
 */

class FenwickTree{
    private: 
        int size; 
        vector<int>data;
    public:
        FenwickTree(int n){
            size = n*2 + 1;
            data.resize(n*2 + 1, 0);
        }
    
        void update(int i, int x){
            while( i < size){
                data[i] += x;
                i += i & -i;
            }
        }
        
        int sum(int i){
            int s = 0;
            while(i){
                s += data[i];
                i -= i & -i;
            }
            return s;
        }
};


class Solution {
public:
    vector<int> processQueries(vector<int>& queries, int m) {
        unordered_map<int,int>indexMap;
        FenwickTree tree(m);
        for(int i = 1; i<=m; ++i){
            tree.update(i+m, 1);
            indexMap[i] = i + m;
        }
        vector<int>res;
        for(auto q : queries){
            res.push_back(tree.sum(indexMap[q]-1)); //-1 前面有几个数
            
            tree.update(indexMap[q], -1);
            tree.update(m, 1);
            indexMap[q] = m--;
        }
        return res;
    }
};



/*
Time Complexity: O((n + m) log (n + m)) → O(m log m)
Space Complexity: O(n + m) → O(m)
Where n is the number of queries and m is the number of positive integers. We can bound by m as the constraints specify n ≤ m.
 */


class FenwickTree {
private:
	std::vector<int> ft;
public:
	FenwickTree(int n) : ft(n + 1) {}

	int LSB(int x) {
		return x & (-x);
	}

	void add(int i, int val) {
		while (i < ft.size()) {
			ft[i] += val;
			i += LSB(i);
		}
	}

	int rsq(int i) {
		int sum = 0;
		while (i) {
			sum += ft[i];
			i -= LSB(i);
		}
		return sum;
	}
};

class Solution {
public:
    vector<int> processQueries(vector<int>& queries, int m) {
		int n = queries.size();
		vector<int> res(n);
		FenwickTree ft(n + m + 1);
		unordered_map<int, int> mp;

		// initialize the range [n + 1, n + m + 1] by adding 1 for each number
		for (int i = 1; i <= m; i++) {
			ft.add(n + i, 1);
			mp[i] = n + i;
		}

		for (int i = 0; i < queries.size(); i++) {
			int q = queries[i];
			res[i] = ft.rsq(mp[q]) - 1;		// rank = number of elements before x, -1 to exclude x
			ft.add(mp[q], -1);				// remove x from it's previous position by adding -1
			ft.add(n - i, 1);				// move x to position n - i by adding 1
			mp[q] = n - i;					// keep track of new position of x in map
		}

		return res;
    }
};