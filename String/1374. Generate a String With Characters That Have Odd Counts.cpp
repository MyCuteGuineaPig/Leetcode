class Solution {
public:
    string generateTheString(int n) {
        return "b" + string(n - 1, 'a' + n % 2);
    }
};

class Solution {
public:
    string generateTheString(int n) {
        return n % 2 ? string(n, 'a') : string(n - 1, 'a') + 'b';
    }
};