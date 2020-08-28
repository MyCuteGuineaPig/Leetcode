

/*

Get more point:
    所有数 当从 0 到 A[n-1] 得到一分

Lose point:
    change[i] 表示当rotate 到第i次时, lose 1 point,  
    change[ ( i - A[i] + 1 + N)%N] ++ 比如 N = 6,  i = 3, A[i] = 2,  change[2]++, 表示当rotate step 为2( 2 到index = 1), lose 1 point 
                                       比如 N = 6, i = 2, A[i] = 4,  change[5]++, 表示当rotate step 为5， lose 1 point (4 移到了 index 3)

0 情况特殊, 比如 N = 6, i = 3, A[i] = 0, change[4]++, 表示rotate step 为4 (0 移动到最后一位,), lose 1 point，
    因为所有数当 0 到A[n-1] 都get one point, 0到 A[n-1] lose 1 point, 抵消

*/

class Solution {
public:
    int bestRotation(vector<int>& A) {
        const int N = A.size();
        int change[N] = {0};
        for(int i = 0; i<N; i++)
            change[(i - A[i] + 1 + N)%N]--;
        for(int i = 1; i<N; i++)
            change[i] += change[i-1] + 1;
        return distance(change, max_element(change, change+N));
    }
};


class Solution {
public:
    int bestRotation(vector<int>& A) {
        int N = A.size();
        int counter[N] = {0};
        for (int i = 0; i < N; i++) {
            counter[(i + 1) % N]++;
            counter[(i - (A[i] - 1) + N) % N]--;
            if (i >= A[i]) counter[0]++; //算0的sum
        }
        
        int max = counter[0], bestK = 0;
        for (int i = 1; i < N; i++) {
            counter[i] += counter[i - 1];
            if (counter[i] > max) {
                max = counter[i];
                bestK = i;
            }
        }
        
        return bestK;
    }
};


//2020
class Solution {
public:
    int bestRotation(vector<int>& A) {
        unordered_map<int,int>lose;
        int point = 0, n = A.size();
        for(int i = 0; i<A.size(); ++i){
            if(A[i] <= i) ++point;
            lose[(i-A[i] + n)%n]++;
        }
        int maxRotate = 0, maxPoint = point;
        for(int r = 0; r<n-1; ++r){
            point += 1;
            point -= lose[r];
            if(point > maxPoint){
                maxPoint = point;
                maxRotate = r+1;
            }
        }
        return maxRotate;
    }
};


class Solution {
public:
    int bestRotation(vector<int>& A) {
        unordered_map<int,int>count;
        int n = A.size();
        for(int i = 0; i<A.size(); ++i){
            if(A[i]<=i){
                count[0] += 1; //不用转 得一分
                int j = (i - A[i] + 1) % n;
                count[j] -= 1;
            }
            else{
                int j =  (n - A[i] + i +  1) % n;
                count[j] -= 1;
            }
            count[i+1] += 1; //当这个数移动到最后一位时
        }

        int maxPoint = count[0], point = count[0];
        int bestRotate = 0;
        for(int i = 1; i<n; ++i){
            point += count[i];
            if(point > maxPoint){
                maxPoint = point; 
                bestRotate = i;            
            }
        }
        return bestRotate;
    }
};