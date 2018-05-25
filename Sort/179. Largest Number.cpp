/*
179. Largest Number

Given a list of non negative integers, arrange them such that they form the largest number.

Example 1:

Input: [10,2]
Output: "210"
Example 2:

Input: [3,30,34,5,9]
Output: "9534330"
Note: The result may be very large, so you need to return a string instead of an integer.



*/
class Solution {
public:
    string largestNumber(vector<int>& nums) {
        sort(nums.begin(),nums.end(),[](const int &a, const int &b){
            return to_string(a)+to_string(b)>to_string(b)+to_string(a);});
        if(nums[0] == 0) return "0";
        string res;
        for(auto i: nums) res+=to_string(i);
        return res;
    }
};


class Solution {
public:
    string largestNumber(vector<int>& nums) {
        vector<string> str;
        for(int i=0;i<nums.size();i++){
            str.push_back(to_string(nums[i]));
        }
        sort(str.begin(), str.end(), comp);
        string result;
        if(str[0] == "0") return "0";
        for(int i=0;i<str.size();i++){
            result += str[i];
        }
        return result;
    }
private:
    static bool comp(string& s1, string& s2){
        return s1+s2>s2+s1;//very important!!
    }
};


class Solution {
public:
    string largestNumber(vector<int>& nums) {
        if(nums.empty()) return "";
        int len = nums.size()-1;
        vector<string> numstr;
        for(int i=0; i<=len; ++i) numstr.push_back(std::to_string(nums[i]));
        quickSort(numstr, 0, len);
        if(numstr[len]=="0") return "0";
        string longest("");
        for(int i=len; i>=0; i--) longest+= numstr[i];
        return longest;
    }
    void quickSort(vector<string>& numstr, int low, int high){
        if(low<high){
            int pivot = partition(numstr, low, high);
            quickSort(numstr, low, pivot-1);
            quickSort(numstr, pivot+1, high);
        }
    }
    int partition(vector<string>& numstr, int low, int high){
        string pivot = numstr[high]; int i=low;
        for(int j=low; j<high; j++){
            if( (numstr[j]+pivot)<=(pivot+numstr[j])) {swap(numstr[i++],numstr[j]);}
        }
        swap(numstr[i],numstr[high]);
        return i;
    }
};