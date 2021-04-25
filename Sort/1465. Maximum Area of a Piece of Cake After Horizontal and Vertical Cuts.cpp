class Solution {
    int getMax(int hh, vector<int> &h) {
        sort(h.begin(), h.end()); 
        int nh = h.size();
        int maxHeight = max(hh-h[nh-1], h[0]);
        for (int i=1; i<nh; i++) {
            maxHeight = max(maxHeight, h[i]-h[i-1]);
        }
        return maxHeight;
    }
public:
    int maxArea(int hh, int ww, vector<int>& h, vector<int>& v) {
        return (int)((long)getMax(hh, h)*getMax(ww, v)%1000000007);
    }
};

class Solution {
public:
    int maxArea(int h, int w, vector<int>& hCuts, vector<int>& vCuts) {
        sort(begin(hCuts), end(hCuts));
        sort(begin(vCuts), end(vCuts));
        auto max_h = max(hCuts[0], h - hCuts.back());
        auto max_v = max(vCuts[0], w - vCuts.back());
        for (auto i = 0; i < hCuts.size() - 1; ++i)
            max_h = max(max_h, hCuts[i + 1] - hCuts[i]);
        for (auto i = 0; i < vCuts.size() - 1; ++i)
            max_v = max(max_v, vCuts[i + 1] - vCuts[i]);        
        return (long)max_h * max_v % 1000000007;
    }
};