/*
min(n1, size/2) 是nums1 去了一半 如果n1 < size /2 =>  nums -> n1 把所有nums1的duplicate 都remove了
min(n2, size/2) 是nums2 去了一半
min(n1, size/2) + min(n2, size/2)  肯定小于等于n
但是min(n1, size/2) + min(n2, size/2) 可能在两个set里都有，所以和union集合 取最小的size

*/

class Solution {
public:
    int maximumSetSize(vector<int>& nums1, vector<int>& nums2) {
        unordered_set<int>s1;
        unordered_set<int>s2;
        unordered_set<int>both;
        for(auto i: nums1){
            s1.insert(i);
            both.insert(i);
        }
        for(auto i: nums2){
            s2.insert(i);
            both.insert(i);
        }
        int size = nums1.size();
        int n1 = s1.size();
        int n2 = s2.size();
        int all = both.size();
        return min(min(n1, size/2) + min(n2, size/2), all);
    }
};

/*
Step 1:
assume 移除所有duplicate 并且，移除nums1 和nums2 所有出现过的数
比如
nums1 = [1,2,1,2,5,6]
nums2 = [1,1,1,1,2,2]
移除后 s1 = [5, 6], s2 = [0]

Step 2: 比较,
Case 1: 
n1 - c >= n/2 
n2 - c >= n/2 
比如 
nums1 = [1,2,3,9],   step1移除后nums1 = [1,3,9], 还需多移除一个数
nums2 = [3,5,6,8]    step1移除后nums1 = [5,6,8], 还需多移除一个数

nums1, nums2 remove common的，还比需要n/2的多, 所以再移除一些数，再移除的数肯定不在common中
result =  n/2 + n/2 

Case 2:
n1 - c >= n/2 
n2 - c < n/2 
比如 
nums1 = [1,2,3,9],   step1移除后nums1 = [1,3,9], 还需多移除一个数, 再移除的数不在common中
nums2 = [2,2,3,5]    step1移除后nums1 = [5], 需要加回common,

nums1 remove common后，还比需要n/2的多, 所以再移除一些数，再移除的数肯定不在common中， result = n/2
nums2 移除多了, 需要补回来一点, min(n2, n/2), 因为可能对所有nums2的set已经小于n/2, 因为n1 keep的数都不在common中，所以n2中的数即使有common也无所谓
result = n/2 + min(n2, n/2)

Case 3: 
n1 - c < n/2
n2 - c >= n/2
与case 2同理
result = min(n1, n/2) + n2/

case 4:
n1 - c < n/2
n2 - c < n/2
比如 
nums1 = [1,2,3,3],   step1移除后nums1 = [1], 
nums2 = [2,2,3,2]    step1移除后nums1 = [], 
min(n1, n/2) = min(3, 2) = 2
min(n2, n/2) = min(2, 2) = 2
n1 + n2 - c = 3 + 2 - 2 = 3
result = min(3, 2 + 2) = 3 (因为2, 3都在set1, set2, 所以减去common的数得到union)

n1， n2 都需要加一些common的数回来 但是加common数有可能造成n1, n2中的数有重复
为了保证没有重复，n1+n2 - c是n1 和 n2 的交集
result = min(n1+n2 - c, min(n1, n/2) + min(n2, n/2));

*/

class Solution {
public:
    int maximumSetSize(vector<int>& nums1, vector<int>& nums2) {
        unordered_set<int> s1(nums1.begin(), nums1.end());
        unordered_set<int> s2(nums2.begin(), nums2.end());
        unordered_set<int> common;
        for (int x: s1) {
            if (s2.find(x) != s2.end()) {
                common.insert(x);
            }
        }
        int n = nums1.size(), n1 = s1.size(), n2 = s2.size(), c = common.size();
        cout<<n<<" n1 "<<n1<<" n2 "<<n2 << "  c " <<c<<endl;
        if (n1 - c >= n/2 && n2 - c >= n/2){
            return n;
        }
        if (n1 - c >= n/2 && n2 - c < n/2){
            return n/2 + min(n2, n/2);
        }
        if (n1 - c < n/2 && n2 - c > n/2){
            return n/2 + min(n1, n/2);
        }
        return min(n1+n2 - c, min(n1, n/2) + min(n2, n/2));
    }
};


https://leetcode.com/problems/maximum-size-of-a-set-after-removals/solutions/4520990/c-java-python-set-difference/
class Solution {
public:
    int maximumSetSize(vector<int>& nums1, vector<int>& nums2) {
        unordered_set<int> s1(nums1.begin(), nums1.end());
        unordered_set<int> s2(nums2.begin(), nums2.end());
        unordered_set<int> common;
        for (int x: s1) {
            if (s2.find(x) != s2.end()) {
                common.insert(x);
            }
        }
        int n = nums1.size(), n1 = s1.size(), n2 = s2.size(), c = common.size();
        return min(n, min(n1 - c, n / 2) + min(n2 - c, n / 2) + c);
    }
};