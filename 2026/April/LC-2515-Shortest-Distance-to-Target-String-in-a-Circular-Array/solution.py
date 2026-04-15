class Solution:
    def closestTarget(self, words: List[str], target: str, startIndex: int) -> int:
        n = len(words)
        if words[startIndex] == target: return 0
        ans = n + 1
        for i in range(1, (n // 2) + 1):
            if words[(startIndex - i + n) % n] == target:
                ans = min(ans, i)
            if words[(startIndex + i) % n] == target:
                ans = min(ans, i)
        return ans if ans != n + 1 else -1