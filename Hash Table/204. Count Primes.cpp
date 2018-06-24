/*
204. Count Primes

Count the number of prime numbers less than a non-negative number, n.

Example:

Input: 10
Output: 4
Explanation: There are 4 prime numbers less than 10, they are 2, 3, 5, 7.
*/




class Solution {
public:
    int countPrimes(int n) {
        if(n<=2) return 0;
        vector<int>notprime(n);
        int count = 1, upper = sqrt(n);
        for(int i = 3; i<n; i+=2){
            if(!notprime[i]){
                count++;
                if(i > upper) continue;
                for(int j = i*i; j<n; j += 2*i){ //i*i以下的已经被算过了，比如 7， 7*5 在i=5的时候已经算过了
                    notprime[j] = 1;
                }
            }
        }
        return count;
    }
};



class Solution {
public:
    int countPrimes(int n) {
        if (n<=2) return 0;
        int sqr = sqrt(n);
        vector<bool> t(n, false);
        int count = n/2; //除去可以整除2个数，比如10，可以整除2的有5个， 把1算成可以整除2的，2不算成可以整除2的
        for (int i = 3; i <= sqr; i+=2) {
            if (t[i]) continue;
            for (int j = i*i; j < n; j+=2*i)
                if (!t[j]) {
                    count--;
                    t[j] = true;
                }
        }
        return count;
        
    }
};


class Solution {
public:
    int countPrimes(int n) {
        vector<bool> prime(n, true);
        prime[0] = false, prime[1] = false;
        for (int i = 0; i < sqrt(n); ++i) {
            if (prime[i]) {
                for (int j = i*i; j < n; j += i) {
                    prime[j] = false;
                }    
            }    
        }
        return count(prime.begin(), prime.end(), true);
    }
};