class Solution {
public:
    long long maxRatings(vector<vector<int>>& units) {
        long long global_min =  1e7;
        long long sum_second_min = 1e7;

        long long baseline_sum = 0;
        long long second_min_baseline_sum =  0; 
        
        for(auto& unit: units ) {
            
            if(unit.size() == 1) {
                baseline_sum += unit[0];
                second_min_baseline_sum += 0;
                global_min = min(global_min, (long long) unit[0]);
            } else {
                sort(unit.begin(), unit.end());
                baseline_sum += unit[0];
                second_min_baseline_sum +=  unit[1];

                global_min = min(global_min, (long long) unit[0]);
                sum_second_min =  min(sum_second_min, (long long) unit[1]);
            }
        }
        // second_min_baseline_sum + global_min - sum_second_min
        // give all the min value to the one which has the second minimum value 
        return max(baseline_sum, second_min_baseline_sum + global_min - sum_second_min);
    }
};