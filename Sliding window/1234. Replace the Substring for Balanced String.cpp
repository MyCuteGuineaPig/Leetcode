/*
One pass the all frequency of "QWER".
Then slide the windon in the string s.

Imagine that we erase all character inside the window,
as we can modify it whatever we want,
and it will always increase the count outside the window.

So we can make the whole string balanced,
as long as max(count[Q],count[W],count[E],count[R]) <= n / 4.

slide window内的可以随便改
 */


class Solution {
public:
    int balancedString(string s) {
        unordered_map<char, int>mp;
        for(auto i: s)
            ++mp[i];
        int n = s.size();
        int k = n/4;
        int res = n  + 1;
        for(int r = 0, l = 0; r < n; ++r){
            --mp[s[r]];
            /*
            注意是 l <= r + 1 或者 l < n 
            比如 "QWER"  在while loop 之后
            l 2 r 0 
            l 3 r 1
            l 4 r 2
            l 5 r 3
            */
            while (l<= r+1 && mp['Q'] <= k && mp['W'] <= k&& mp['E'] <= k&& mp['R'] <= k){
                res = min(res, r -l + 1);
                ++mp[s[l++]];
            }
            //cout<<l<<" r "<<r<<endl;
        }
        return res;
    }
};
