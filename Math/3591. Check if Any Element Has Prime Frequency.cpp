//check prime number (prime_number)

class Solution {
public:
    bool checkprime(int num){
        if(num == 1) return false;
        for(int i = 2; i <= sqrt(num) ; i++){
            if(num % i == 0) return false;
        }
        return true;
    }
    bool checkPrimeFrequency(vector<int>& nums) {
        unordered_map<int, int> freq;
        for(int i = 0; i < nums.size(); i++){
            freq[nums[i]]++;
        }
        for(auto &it : freq){
            if(checkprime(it.second) == true){
                return true;
            }
        }
        return false;
    }
};

class Solution {
public:
    bool checkPrimeFrequency(vector<int>& nums) {
        unordered_map<int, int>counts;
        for(auto i: nums)
            ++counts[i];
        for(const auto& [k, v]: counts){
            if (v == 2 || v == 3 || v == 5 || v == 7) return true;
            else if (v == 1 || v%2 == 0 || v %3 == 0 || v%5 == 0 || v%7 == 0) continue;
            return true;
        }
        return false;
    }
};

