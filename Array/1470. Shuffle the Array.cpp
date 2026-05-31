class Solution {
public:
    vector<int> shuffle(vector<int>& nums, int n) {
        for(int i = n; i < 2*n ; ++i) 
        {
            int second = nums[i] << 10; 
            nums[i - n] |= second;
        }

        int one = (1 << 10) -1 ; 
        for(int i = n - 1; i >= 0; --i ) {
            int sec = nums[i] >> 10;
            int first = nums[i] & one; 
            nums[2*i] = first; 
            nums[2*i + 1] = sec;
        }
        return nums;
    }
};


/*

Not O(n) space, but O(1) space
Worst O(n^2)

for example [2,5,1,3,4,7] 

in first while loop,  i = 3, ct = 2, prev = 2
【2, 5, 1, 1, 4, 7] 
 [2, 5, 5, 1, 4, 7]
outside while  
 [2, 3, 5, 1, 4, 7]


in second while loop,  i = 4, ct = 1, prev = 3
 【2, 3, 5, 1, 1, 7] 
outside while  
  [2, 5, 5, 4, 1, 7]




*/

class Solution {
public:
    vector<int> shuffle(vector<int>& nums, int n) {
        for(int i=n;i<2*n;i++)
        {
            int curr=nums[i];
            int prev=i-1;
            int ct=2*n-i-1;
            //cout<<" [cur] i "<<i <<" ct "<<ct <<" prev "<<prev << endl;
            while(ct>0){
                nums[prev+1]=nums[prev];
                //cout<<" [in] i "<<i <<" ct "<<ct <<" prev "<<prev  << endl;

                //for(auto k: nums)
                //    cout<<k<<", ";
                //cout<<endl;
                prev--;
                ct--;
            }
            nums[prev+1]=curr;
        }

        return nums;
    }
};

