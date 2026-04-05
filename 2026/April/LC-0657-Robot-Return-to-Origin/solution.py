# Problem Link: https://leetcode.com/problems/robot-return-to-origin/

from collections import Counter
class Solution:
    def judgeCircle(self, moves: str) -> bool:
        freq = Counter(moves)
        return freq['L'] == freq['R'] and freq['U'] == freq['D']