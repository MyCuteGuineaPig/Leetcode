/*

n1 = n1.substr(0, i+1) + n1.substr(i, j-i) + n1.substr(j+1);

表示的是

for (auto z = j; z > i; --z) {
    swap(n1[z], n1[z-1]);
}


For example let s=1234567890
let i be 0th character and j be 7th character

so after actual rotation it should be 8123456790
but using that trick we get new n1 = 1123456790

Complexity O(n^3)

*/

class Solution {
public:
    int getMinSwaps(string n, int k) {
        string n1 = n;
        while (--k >= 0)
            next_permutation(begin(n1), end(n1));
        
        int res = 0;
        for(int i = 0; i<n.size(); ++i){
            if(n1[i]!=n[i]){
                for(int j = i + 1; j < n.size(); ++j){
                    if(n1[j] == n[i]){
                        res += j - i;
                        n1 = n1.substr(0, i+1) + n1.substr(i, j-i) + n1.substr(j+1);
                        break;
                    }
                }
            }
        }
        return res;
    }
};



/*
Complexity O(n^3)
*/
class Solution {
public:
    int getMinSwaps(string num, int k) {
        string target(num);
        for (int i = 0; i < k; ++i)
            next_permutation(target.begin(), target.end());
        int res = 0, n = num.size();
        for (int i = 0; i < n; ++i) {
            if (num[i] != target[i]) {
                int j = i + 1;
                while (num[j] != target[i])
                    j++;
                for (; j > i; --j)
                    swap(num[j], num[j - 1]), res++;
            }
        }
        return res;
    }
};

/*
Complexity O(n^2)
*/
class Solution {
public:
    int getMinSwaps(string num, int k) {
        list<char> ls1(num.begin(), num.end());
        for (int i=0; i<k; ++i) {
            next_permutation(num.begin(), num.end());
        }
        list<char> ls2(num.begin(), num.end());
        auto it1 = ls1.begin();
        int ret = 0;
        while(it1!=ls1.end()) {
            auto it2 = ls2.begin();
            int cnt = 0;
            while(*it2 != *it1) {
                it2++;
                cnt++;
            }
            ls2.erase(it2);
            it1 = ls1.erase(it1); 
            //return the iterator after the element get erased
            ret+= cnt;
        }
        return ret;
    }
};