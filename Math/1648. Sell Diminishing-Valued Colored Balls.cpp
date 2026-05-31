class Solution {
public:
    int maxProfit(vector<int>& inventory, int ordersLeft) {
        // Sort inventory in descending order to process largest quantities first
        sort(inventory.rbegin(), inventory.rend()); 
        
        long long modulo = 1e9 + 7;
        long long numColors = inventory.size();
        long long maxProfit = 0;
        
        long long currentHeight = inventory[0];
        long long colorIndex = 0;
        
        while (ordersLeft > 0) {
            // Group all columns that share the exact same peak height
            while (colorIndex < numColors && inventory[colorIndex] == currentHeight) {
                colorIndex++;
            }
            
            // Determine the height of the next tallest vertical step
            long long nextHeight = (colorIndex == numColors) ? 0 : inventory[colorIndex];
            long long fullStepHeight = currentHeight - nextHeight;
            
            // Total balls available in this uniform horizontal layer block
            long long totalBallsInLayer = colorIndex * fullStepHeight;
            long long ballsToSell = min((long long)ordersLeft, totalBallsInLayer);
            
            long long actualHeightReduced = fullStepHeight;
            long long remainderBalls = 0;
            
            // If we don't need the entire layer block, calculate partial cuts
            if (ordersLeft < totalBallsInLayer) {
                actualHeightReduced = ordersLeft / colorIndex;
                remainderBalls = ordersLeft % colorIndex;
            }
            
            long long endingHeight = currentHeight - actualHeightReduced;
            
            // Arithmetic Series Math: 
            // Sum of values from (currentHeight) down to (endingHeight + 1)
            long long singleColumnProfit = (currentHeight + (endingHeight + 1)) * actualHeightReduced / 2;
            long long standardBlockProfit = (singleColumnProfit % modulo) * colorIndex;
            
            // The fractional row left over from the division
            long long remainderProfit = remainderBalls * endingHeight;
            
            // Accumulate profit
            maxProfit = (maxProfit + standardBlockProfit + remainderProfit) % modulo;
            
            // Transition states for the next iteration
            ordersLeft -= ballsToSell;
            currentHeight = nextHeight;
        }
        
        return maxProfit;
    }
};



class Solution {
public:
    int maxProfit(vector<int>& inventory, int orders) {
        sort(inventory.rbegin(), inventory.rend());

        long long mod = 1e9 + 7;
        long long numColors = inventory.size();
        long long maxProfit = 0;

        long long currentHeight = inventory[0];
        long long colorIndex = 0;

        while(orders > 0) {
            while (colorIndex < numColors && inventory[colorIndex] == currentHeight) 
                colorIndex++;

            
            long long nextHeight = (colorIndex == numColors) ? 0 : inventory[colorIndex];
            long long fullStepHeight = currentHeight - nextHeight;

            long long totalBallsInLayer = colorIndex * fullStepHeight;
            long long ballToSell = min((long long)orders, totalBallsInLayer);

            long long actualHeightReduced = ballToSell / colorIndex;
            long long remainderBall =  ballToSell % colorIndex;

            long long endingHeight = currentHeight - actualHeightReduced;

            long long singleColumnProfit = (currentHeight + (endingHeight + 1)) * actualHeightReduced / 2;
            long long standardBlockProfit = (singleColumnProfit % mod) * colorIndex;

            long long remainderProfit = remainderBall*endingHeight;

            maxProfit = (maxProfit + standardBlockProfit + remainderProfit) % mod;
            orders -= ballToSell;
            currentHeight = nextHeight;
        }
        return maxProfit;
    }
};

class Solution {
public:
    int maxProfit(vector<int>& inventory, int ordersLeft) {
        // 1. Sort descending to process highest valued balls first
        sort(inventory.rbegin(), inventory.rend());
        inventory.push_back(0); // Dummy floor to handle the last element easily
        
        long long maxProfit = 0;
        long long modulo = 1e9 + 7;
        long long colorIndex = 0; // Represents the width of our current step
        
        // Loop through the columns; whenever a step drops down, we process the row block
        while (ordersLeft > 0) {
            colorIndex++;
            
            // Skip forward if the next elements share the exact same height
            if (inventory[colorIndex] == inventory[colorIndex - 1]) {
                continue;
            }
            
            // 2. Identify dimensions of the available block
            long long currentHeight = inventory[colorIndex - 1];
            long long nextHeight = inventory[colorIndex];
            long long fullStepHeight = currentHeight - nextHeight;
            
            long long totalBallsInLayer = colorIndex * fullStepHeight;
            long long ballsToSell = min((long long)ordersLeft, totalBallsInLayer);
            
            // 3. Calculate full rows and leftover remainder balls to shave off
            long long actualHeightReduced = ballsToSell / colorIndex;
            long long remainderBalls = ballsToSell % colorIndex;
            long long endingHeight = currentHeight - actualHeightReduced;
            
            // 4. Arithmetic Series formula to calculate the layer's profit
            long long singleColumnProfit = (currentHeight + (endingHeight + 1)) * actualHeightReduced / 2;
            long long standardBlockProfit = (singleColumnProfit % modulo) * colorIndex;
            long long remainderProfit = remainderBalls * endingHeight;
            
            // Accumulate profit and decrement orders
            maxProfit = (maxProfit + standardBlockProfit + remainderProfit) % modulo;
            ordersLeft -= ballsToSell;
        }
        
        return maxProfit;
    }
};