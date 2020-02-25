/*

753. Cracking the Safe

There is a box protected by a password. The password is n digits, where each letter can be one of the first k digits 0, 1, ..., k-1.

You can keep inputting the password, the password will automatically be matched against the last n digits entered.

For example, assuming the password is "345", I can open it when I type "012345", but I enter a total of 6 digits.

Please return any string of minimum length that is guaranteed to open the box after the entire string is inputted.

Example 1:
Input: n = 1, k = 2
Output: "01"
Note: "10" will be accepted too.
Example 2:
Input: n = 2, k = 2
Output: "00110"
Note: "01100", "10011", "11001" will be accepted too.
Note:
n will be in the range [1, 4].
k will be in the range [1, 10].
k^n will be at most 4096.


*/



//from the big to small, but start with 000 
/*
这个算法从000...0出发，每次末尾追加一个在{k-1,k-2,...,2,1,0}里，第一个让密码不重复的数字。
visited记录了添加过的密码。
{k-1,k-2,...,2,1,0} 本质上只要 0 在最后，前面的顺序无所谓。
但这个顺序在程序里一定要固定下来。

一个疑问是，这个算法是否走进死胡同？
比如说，k=4,n=3 ，序列进行到了...123，
但是在后面追加0,1,2,3都不行，因为123(0) ,123(1), 123(2), 123(3) 都在visited里出现过。
*/

class Solution {
public:
    string crackSafe(int n, int k) {
        string ans = string(n, '0');
        //string ans = string(n-1, '0'); 也ok
        /*
        如果start with the biggest, string ans = string(n, '0' + k -1 );
        会有deadlock 
        比如 n = 2, k =3 
        it generate             "221202"  //因为开始是2, 到02, 不会包括结束找不到 00, 
        but correct answer is "0022120110"  //02 是最开始的, 所以不会end到 02, 会到01, 
        */
        unordered_set<string>visited;
        visited.insert(ans);
        for(int i = 0; i<pow(k, n); ++i){ //一共k^n 可能性
            string prev = ans.substr(ans.size()-n+1);
            for(int j = k-1; j>=0; j--){
                if(visited.count(prev + to_string(j)) == 0){
                    ans += to_string(j);
                    visited.insert(prev +to_string(j) );
                    break; 
                    //break 很重要, n=3, k = 3 比如prev = 01, 012不在, after append 2,  ans back 是012
                    //如果继续loop 不break, 发现121 也不在, append 1-> 0121, 但是这忽略掉了 122, 不是Greedy，可能找不到所有的解
                }
            }
            
        }
        return ans;
    }
};


//from the small to big, but start with the biggest 
class Solution {
public:
    string crackSafe(int n, int k) {
        unordered_set<string>set;
        string result(n, '0' + k - 1); 
        set.insert(result);
        const int total = pow(k,n);
        while(set.size()<total){
            const string prefix = result.substr(result.size()-n+1);
            for(int i = 0; i<k; i++){
                if(set.find(prefix+to_string(i)) == set.end()){
                    //cout<<prefix+to_string(i)<<"string "<<result<<endl;
                    set.insert(prefix+to_string(i));
                    result += to_string(i);
                    break;
                }
            }
        }
        return result;
    }
};


/*
BFS
*/
class Solution {
public:
    string crackSafe(int n, int k) {
        unordered_set<string>set;
        string result(n, '0');
        set.insert(result);
        const int total = pow(k,n);
        while(set.size()<total){
            const string prefix = result.substr(result.size()-n+1);
            for(int i = k-1; i>=0; i--){
                if(set.find(prefix+to_string(i)) == set.end()){
                    set.insert(prefix+to_string(i));
                    result += to_string(i);
                    break;
                }
            }
        }
        return result;
    }
};
