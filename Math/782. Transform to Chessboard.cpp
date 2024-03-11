class Solution {
public:
    int movesToChessboard(vector<vector<int>>& b) {
        int N = b.size(), rowSum = 0, colSum = 0, rowSwap = 0, colSwap = 0;
        for (int i = 0; i < N; ++i) for (int j = 0; j < N; ++j)
                if (b[0][0]^b[i][0]^b[0][j]^b[i][j]) return -1;
        for (int i = 0; i < N; ++i) {
            rowSum += b[0][i];
            colSum += b[i][0];
            rowSwap += b[i][0] == i % 2;
            colSwap += b[0][i] == i % 2;
        }
        if (rowSum != N / 2 && rowSum != (N + 1) / 2) return -1;
        if (colSum != N / 2 && colSum != (N + 1) / 2) return -1;
        cout<<colSwap<<" rowSwap "<<rowSwap<<endl;


       
        colSwap = min(N - colSwap, colSwap);
            rowSwap = min(N - rowSwap, rowSwap);
        cout<<colSwap<<" rowSwap "<<rowSwap<<endl;
        return (colSwap + rowSwap) / 2;
    }
};

class Solution {
public:
    int movesToChessboard(vector<vector<int>>& board) {
        int n = board.size();
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                // two types of rows if it can transform to a chessboard
                // e.g., if there's a row 01010011
                // then any other row must be either 01010011 or 10101100 (inverse)
                //
                // corollary: the 4 corners of any rectangle inside the board must be one of the following:
                // - 4 zeros
                // - 2 zeros 2 ones
                // - 4 ones
                //
                // checks the top left corner rectangle
                if ((board[0][0] ^ board[i][0] ^ board[0][j] ^ board[i][j]) == 1) {
                    return -1;
                }
            }
        }

        // first row and column
        // sum, i.e. count of one's
        int rowSum = 0, colSum = 0;
        // count of misplaced element
        int rowMisplaced = 0, colMisplaced = 0;
        for (int i = 0; i < n; i++) {
            rowSum += board[0][i];
            colSum += board[i][0];

            // if the final pattern is "1010..."
            if (board[i][0] == i % 2) {//偶数位是0， 奇数为是1
                rowMisplaced++;
            }
            if (board[0][i] == i % 2) {
                colMisplaced++ ;
            }
        }

        // - if n == 2 * k, then count(0) == count(1) == k
        // - if n == 2 * k + 1, then count(0) == k, count(1) == k + 1
        //   or count(0) == k + 1, count(1) == k
        //
        // checking the first row and column is sufficient,
        // because the top left corner rectangle is verified
        if (rowSum != n / 2 && rowSum != (n + 1) / 2) {
            return -1;
        }
        if (colSum != n / 2 && colSum != (n + 1) / 2) {
            return -1;
        }

        if (n % 2 == 1) {
            // when n is odd
            // only one final pattern is possible
            //
            // if misplaced is even
            // then the final pattern is "1010..."
            //
            // if misplaced is odd, (因为一次换两个，不能结果是奇数，只能是偶数)
            // then the final pattern is the inverse of "1010..."
            // i.e. "0101..."
            // and the actual count of misplaced elements is (n - misplace)
            //
            // e.g. "001", misplaced == 1
            // the final pattern should be "010",
            // and the actual count of misplaced elements is 2 == n - misplaced
            //
            // in either case, the actual count of misplaced elements is even
            if (colMisplaced % 2 == 1) {
                colMisplaced = n - colMisplaced;
            }
            if (rowMisplaced % 2 == 1) {
                rowMisplaced = n - rowMisplaced;
            }
        } else {
            // when n is even
            // the final pattern can be either "1010..." or "0101..."
            //
            // if the final pattern is "0101..." (inverse)
            // the misplaced counts for row and col will be
            // (n - rowMisplaced) and (n - colMisplaced) respectively
            //
            // misplaced and (n - misplaced) are both even
            // picks the minimum of them
            colMisplaced = min(n - colMisplaced, colMisplaced);
            rowMisplaced = min(n - rowMisplaced, rowMisplaced);
        }

        // one swap fixes two misplaced elements
        return (colMisplaced + rowMisplaced) / 2;
    }
};