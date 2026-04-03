class Solution {
    public:
        int maxWalls(vector<int>& robots, vector<int>& distance, vector<int>& walls) {
            int n = robots.size(), m = walls.size();
    
            // 1. Pair robots with distance and sort
            vector<pair<int,int>> robo_range;
            for (int i = 0; i < n; i++) {
                robo_range.push_back({robots[i], distance[i]});
            }
            sort(robo_range.begin(), robo_range.end());
            sort(walls.begin(), walls.end());
    
            // 2. Helper: count walls in [L, R]
            auto countWalls = [&](int L, int R) {
                if (L > R) return 0;
                int l = lower_bound(walls.begin(), walls.end(), L) - walls.begin();
                int r = upper_bound(walls.begin(), walls.end(), R) - walls.begin();
                return r - l;
            };
    
            auto overlapWalls = [&](int L1, int R1, int L2, int R2) {
                int L = max(L1, L2);
                int R = min(R1, R2);
                return countWalls(L, R);
            };
    
            // 3. Store ranges for each robo_ranget, left and right
            vector<pair<int,int>> leftRange(n), rightRange(n);
            for (int i = 0; i < n; i++) {
                int pos = robo_range[i].first, d = robo_range[i].second;
    
                // left
                int left_bound = (i > 0 ? robo_range[i-1].first + 1 : INT_MIN);
                leftRange[i] = {max(pos - d, left_bound), pos};
    
                // right
                int right_bound = (i+1 < n ? robo_range[i+1].first - 1 : INT_MAX);
                rightRange[i] = {pos, min(pos + d, right_bound)};
            }
    
            // 4. DP arrays
            vector<vector<int>> dp(n, vector<int>(2, 0));
    
            // base case for first robot
            dp[0][0] = countWalls(leftRange[0].first, leftRange[0].second);
            dp[0][1] = countWalls(rightRange[0].first, rightRange[0].second);
    
            // 5. Process each robot
            for (int i = 1; i < n; i++) {
                int L1 = leftRange[i].first,  R1 = leftRange[i].second;
                int L2 = rightRange[i].first, R2 = rightRange[i].second;
    
                int wallsLeft  = countWalls(L1, R1);
                int wallsRight = countWalls(L2, R2);
    
                // left shot
                int fromLeft  = dp[i-1][0] + wallsLeft  - overlapWalls(L1, R1, leftRange[i-1].first,  leftRange[i-1].second);
                int fromRight = dp[i-1][1] + wallsLeft  - overlapWalls(L1, R1, rightRange[i-1].first, rightRange[i-1].second);
                dp[i][0] = max(fromLeft, fromRight);
    
                // right shot
                int fromLeft2  = dp[i-1][0] + wallsRight - overlapWalls(L2, R2, leftRange[i-1].first,  leftRange[i-1].second);
                int fromRight2 = dp[i-1][1] + wallsRight - overlapWalls(L2, R2, rightRange[i-1].first, rightRange[i-1].second);
                dp[i][1] = max(fromLeft2, fromRight2);
            }
    
            return max(dp[n-1][0], dp[n-1][1]);
        }
    };