# Approach 1:
from typing import List
from collections import defaultdict
class Solution:
    def minimumDistance(self, nums: List[int]) -> int:
        n = len(nums)
        if n <= 2 or len(set(nums)) == n:
            return -1
        ht = defaultdict(list)
        for i, v in enumerate(nums):
            ht[v].append(i)
        mnd = 1000
        for x, f in ht.items():
            l = len(f)
            if l >= 3:
                for i in range(l - 2):
                    for j in range(i + 1, l - 1):
                        for k in range(j + 1, l):
                            mnd = min(
                                mnd,
                                abs(f[i] - f[j]) + abs(f[j] - f[k]) + abs(f[k] - f[i]),
                            )
        return mnd if mnd != 1000 else -1

# Approach 2:
from typing import List
class Solution:
    def minimumDistance(self, nums: List[int]) -> int:
        n = len(nums)
        if n <= 2 or len(set(nums)) == n:
            return -1
        mnd = 1000
        for i in range(n-2):
            for j in range(i + 1, n-1):
                for k in range(j + 1, n):
                    if nums[i] == nums[j] and nums[j] == nums[k]:
                        dist: int = abs(i - j) + abs(j - k) + abs(i - k)
                        mnd: int = min(mnd, dist)
        return mnd if mnd != 1000 else -1

# Approach 3:
from collections import defaultdict

class Solution:
    def minimumDistance(self, nums: list[int]) -> int:
        prev_indexes: defaultdict[int, list[int]] = defaultdict(list)
        result: int = 10 ** 10
        for pos, num in enumerate(nums):
            if len(prev_indexes[num]) >= 2:                
                result = min(result, pos - prev_indexes[num][-2])                
            prev_indexes[num].append(pos)
        if result == 10 ** 10:
            return -1
        return result * 2