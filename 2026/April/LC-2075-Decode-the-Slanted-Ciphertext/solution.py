# Problem Link: https://leetcode.com/problems/decode-the-slanted-ciphertext/


class Solution:
    def decodeCiphertext(self, encodedText: str, rows: int) -> str:
        res = ""
        cols = len(encodedText) // rows
        for col in range(cols):
            r, c = 0, col
            while r < rows and c < cols:
                res += encodedText[r*cols + c]
                r += 1
                c += 1
        return res.rstrip()