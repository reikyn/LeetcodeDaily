from bisect import bisect_left, bisect_right
import math

class Solution:
    def maxWalls(self, robots: list[int], distance: list[int], walls: list[int]) -> int:
        n = len(robots)

        # 1. Pair robots with distance and sort
        robo_range = sorted(zip(robots, distance))
        walls.sort()

        # 2. Helper: count walls in [L, R]
        def count_walls(L, R):
            if L > R:
                return 0
            l = bisect_left(walls, L)
            r = bisect_right(walls, R)
            return r - l

        def overlap_walls(L1, R1, L2, R2):
            L = max(L1, L2)
            R = min(R1, R2)
            return count_walls(L, R)

        # 3. Store ranges for each robot, left and right
        left_range = [None] * n
        right_range = [None] * n
        for i in range(n):
            pos, d = robo_range[i]

            # left
            left_bound = robo_range[i-1][0] + 1 if i > 0 else -math.inf
            left_range[i] = (max(pos - d, left_bound), pos)

            # right
            right_bound = robo_range[i+1][0] - 1 if i + 1 < n else math.inf
            right_range[i] = (pos, min(pos + d, right_bound))

        # 4. DP arrays
        dp = [[0, 0] for _ in range(n)]

        # base case for first robot
        dp[0][0] = count_walls(*left_range[0])
        dp[0][1] = count_walls(*right_range[0])

        # 5. Process each robot
        for i in range(1, n):
            L1, R1 = left_range[i]
            L2, R2 = right_range[i]

            walls_left  = count_walls(L1, R1)
            walls_right = count_walls(L2, R2)

            # left shot
            from_left  = dp[i-1][0] + walls_left  - overlap_walls(L1, R1, *left_range[i-1])
            from_right = dp[i-1][1] + walls_left  - overlap_walls(L1, R1, *right_range[i-1])
            dp[i][0] = max(from_left, from_right)

            # right shot
            from_left2  = dp[i-1][0] + walls_right - overlap_walls(L2, R2, *left_range[i-1])
            from_right2 = dp[i-1][1] + walls_right - overlap_walls(L2, R2, *right_range[i-1])
            dp[i][1] = max(from_left2, from_right2)

        return max(dp[n-1])