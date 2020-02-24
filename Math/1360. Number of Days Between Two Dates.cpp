class Solution {
public:
    int days[12] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
    int daysBetweenDates(string d1, string d2) {
        return abs(daysFrom1971(d1) - daysFrom1971(d2));
    }
    bool isLeap(int y) { 
        return y % 4 == 0 && (y % 100 != 0 || y % 400 == 0); 
    }
    int daysFrom1971(string dt) {
        int y = stoi(dt.substr(0, 4)), m = stoi(dt.substr(5, 2)), d = stoi(dt.substr(8));
        for (int iy = 1971; iy < y; ++iy) 
            d += isLeap(iy) ? 366 : 365;
        return d + (m > 2 && isLeap(y)) + accumulate(begin(days), begin(days) + m - 1, 0);
    }  
};