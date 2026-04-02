// Problem link: https://leetcode.com/problems/maximum-amount-of-money-robot-can-earn/description/

#include<vector>
using namespace std;
class Solution {
    private:
        int dp[501][501][3];
    public:
        int solve(vector<vector<int>>& grid, int i, int j, int neu) {
            int rows = grid.size();
            int cols = grid[0].size();
    
            //reached destination
            if (i == rows - 1 && j == cols - 1) {
                if (grid[i][j] < 0 && neu > 0) {
                    return 0; // neutralize the robber
                }
                return grid[i][j];
            }
    
            // Out of bounds
            if (i >= rows || j >= cols) {
                return INT_MIN;
            }
    
            // Already computed
            if (dp[i][j][neu] != INT_MIN) {
                return dp[i][j][neu];
            }
    
            //Take the current cell value
            int moveDown  = solve(grid, i + 1, j, neu);
            int moveRight = solve(grid, i, j + 1, neu);
    
            int take = grid[i][j] + max(moveDown, moveRight);
    
            //Neutralize (only if negative and we have chances left)
            int skip = INT_MIN;
            if (grid[i][j] < 0 && neu > 0) {
                int skipDown  = solve(grid, i + 1, j, neu - 1);
                int skipRight = solve(grid, i, j + 1, neu - 1);
    
                skip = max(skipDown, skipRight);
            }
    
            // Store and return best result
            return dp[i][j][neu] = max(take, skip);
        }
    
        int maximumAmount(vector<vector<int>>& coins) {
            for (int i = 0; i < 501; i++) {
                for (int j = 0; j < 501; j++) {
                    for (int k = 0; k < 3; k++) {
                        dp[i][j][k] = INT_MIN;
                    }
                }
            }
    
            return solve(coins, 0, 0, 2);
        }
    };