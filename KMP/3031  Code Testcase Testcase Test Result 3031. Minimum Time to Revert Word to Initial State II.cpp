class Solution {
public:
    int minimumTimeToInitialState(string word, int k) {
        int n = word.size();
        vector<int> kmp(n);
        int  j = 0;
        for(int i = 1; i<n; ++i){
            while(j && word[i] != word[j])
                j = kmp[j-1];
            j = kmp[i] = j + (word[i] == word[j]);
        }
        while (j && (n -j)%k){
            j = kmp[j-1];
        }
        return (n-j ) / k + ((n-j) % k == 0 ? 0: 1);
    }
};

//O(n^2)
//Z function 
/*

Z function 
a a c d e a a c d e 
0 1 0 0 0 5 1 0 0 0
            ^
            |
当 index = 6,  l = 5, r = 10
z[6] = min(z[l- i], r - i) = min (z[1], 4) = 1


a b c a b c a b c a b c 
0 0 0 9 0 0 6 0 0 3 0 0
                  ^  
                  |

当 index = 9,  l = 3, r = 12
z[6] = min(z[l- i], r - i) = min (z[6], 12 - 9) = min(6, 3) = 3 


*/
class Solution {
public:
    int minimumTimeToInitialState(string word, int k) {
        int res = 1, n = word.size();
        auto z = z_function(word);
        for( ;res * k < n ; ++res){
            if (z[res*k] == n - res*k)
                break;
        }
        return res;
    }

    vector<int> z_function(const string & s){
        int n = s.size();
        vector<int>z(n);
        int l = 0, r = 0;
        for(int i = 1; i<n; ++i){
            if (i < r)
                z[i] = min(r - i, z[i-l]);
            while(i + z[i] < n && s[z[i]] == s[i + z[i]])
                ++z[i];
            if (i+z[i] > r){
                l = i;
                r = i + z[i];
            }
        }
        return z;
    }
};