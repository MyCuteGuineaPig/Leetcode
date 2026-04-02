class Solution {
public:
    int secondsToRemoveOccurrences(string s) {
        int zeros = 0, seconds = 0;
        for(int i = 0; i < s.size(); ++i) {
            zeros += s[i] == '0';
            if (s[i] == '1' && zeros > 0) {
                seconds = max(seconds + 1, zeros);
            }
        }
        return seconds;
    }
};

/*


"100111100001"

index	1	2	3	4	5	6	7	8	9	10	11	12
nums	1	0	0	1	1	1	1	0	0	0	0	1
zeros	0	1	2	2	2	2	2	3	4	5	6	6
seconds	0	0	0	2	3	4	5	5	5	5	5	6

*/

