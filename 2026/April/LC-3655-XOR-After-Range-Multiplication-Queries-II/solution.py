import math
from collections import defaultdict

class Solution:
    M = 10**9 + 7

    def power(self, a: int, b: int) -> int:
        if b == 0:
            return 1
        half = self.power(a, b // 2)
        result = (half * half) % self.M
        if b % 2 == 1:
            result = (result * a) % self.M
        return result

    def xorAfterQueries(self, nums: list[int], queries: list[list[int]]) -> int:
        n = len(nums)
        block_size = math.ceil(math.sqrt(n))

        small_k_map = defaultdict(list)

        for q in queries:
            L, R, k, v = q[0], q[1], q[2], q[3]

            if k >= block_size:
                for i in range(L, R + 1, k):
                    nums[i] = (nums[i] * v) % self.M
            else:
                small_k_map[k].append(q)

        for k, all_queries in small_k_map.items():
            diff = [1] * n

            for query in all_queries:
                L, R, _, v = query[0], query[1], query[2], query[3]

                diff[L] = (diff[L] * v) % self.M

                steps = (R - L) // k
                next_idx = L + (steps + 1) * k

                if next_idx < n:
                    diff[next_idx] = (diff[next_idx] * self.power(v, self.M - 2)) % self.M

            # Cumulative product
            for i in range(n):
                if i - k >= 0:
                    diff[i] = (diff[i] * diff[i - k]) % self.M

            # Apply diff to nums
            for i in range(n):
                nums[i] = (nums[i] * diff[i]) % self.M

        result = 0
        for num in nums:
            result ^= num

        return result