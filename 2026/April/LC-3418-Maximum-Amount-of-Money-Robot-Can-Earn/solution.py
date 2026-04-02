# Problem Link: https://leetcode.com/problems/maximum-amount-of-money-robot-can-earn/description/

from typing import List
import math
class Solution:
    def __init__(self):
        self.m  = 0
        self.n  = 0
        self.dp = []
    def __solve(self, coins, i: int, j: int, k: int) -> float:
        if i >= self.m or j >= self.n:
            return -math.inf
        if i == self.m-1 and j == self.n-1:
            if coins[i][j] < 0 and k > 0:
                return 0
            return coins[i][j]
        if self.dp[i][j][k] != -math.inf:
            return self.dp[i][j][k]
        
        down  = self.__solve(coins, i + 1, j, k)
        right = self.__solve(coins, i, j + 1, k)
        take  = coins[i][j] + max(down, right)

        skip = -math.inf
        if coins[i][j] < 0 and k > 0:
            skip_down  = self.__solve(coins, i + 1, j, k - 1)
            skip_right = self.__solve(coins, i, j + 1, k - 1)
            skip = max(skip_down, skip_right)
        
        self.dp[i][j][k] = max(take, skip)
        return self.dp[i][j][k]
    def maximumAmount(self, coins: List[List[int]]) -> int:
        self.m = len(coins)
        self.n = len(coins[0])
        self.dp = [[[-math.inf]*3 for _ in range(self.n)] for _ in range(self.m)]
        return int(self.__solve(coins, 0, 0, 2))