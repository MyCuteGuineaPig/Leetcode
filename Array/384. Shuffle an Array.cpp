/*
384. Shuffle an Array

Shuffle a set of numbers without duplicates.

Example:

// Init an array with set 1, 2, and 3.
int[] nums = {1,2,3};
Solution solution = new Solution(nums);

// Shuffle the array [1,2,3] and return its result. Any permutation of [1,2,3] must equally likely to be returned.
solution.shuffle();

// Resets the array back to its original configuration [1,2,3].
solution.reset();

// Returns the random shuffling of array [1,2,3].
solution.shuffle();

*/

// Time:  O(n)
// Space: O(n)

class Solution {
public:
    Solution(vector<int> nums) : nums_(nums) {
        
    }
    
    /** Resets the array to its original configuration and return it. */
    vector<int> reset() {
        return nums_;
    }
    
    /** Returns a random shuffling of the array. */
    vector<int> shuffle() {
        vector<int> nums{nums_};
        default_random_engine seed((random_device())());
        for (int i = 0; i < nums.size(); ++i) {
            swap(nums[i],  nums[uniform_int_distribution<int>{
                                i, static_cast<int>(nums.size()) - 1}(seed)]);
        }
        return nums;
    }

private:
    const vector<int> nums_;
};

class Solution {
public:
    Solution(vector<int> nums) {
        m_nums = nums;    
    }
    
    /** Resets the array to its original configuration and return it. */
    vector<int> reset() {
        return m_nums;    
    }
    
    /** Returns a random shuffling of the array. */
    vector<int> shuffle() {
        vector<int> ans(m_nums);
        int n = ans.size();
        for(int i = n-1; i > 0; i--)
        {
            int idx = rand()%(i+1);
            int tmp = ans[idx];
            ans[idx] = ans[i];
            ans[i] = tmp;
        }
        return ans;
    }
    
private:
    vector<int> m_nums;
};


class Solution {
public:
	vector<int> original;

	Solution(vector<int> nums) {
		original = nums;
        //srand(time(NULL));
	}

	/** Resets the array to its original configuration and return it. */
	vector<int> reset() {
		return original;
	}

	/** Returns a random shuffling of the array. */
	vector<int> shuffle() {
		vector<int> newVector = original;
		for (int i = 0; i < newVector.size(); i++)
		{
			int num = i + rand() % (newVector.size() - i);
			int temp = newVector[i];
			newVector[i] = newVector[num];
			newVector[num] = temp;
		}
		return newVector;
	}
};