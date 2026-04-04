// Problem Link: https://leetcode.com/problems/decode-the-slanted-ciphertext/

class Solution {
    public:
        string decodeCiphertext(string encodedText, int rows) {
            bool isEmpty = true;
            for (char c : encodedText) {
                if (c != ' ') isEmpty = false;
            }
            if (isEmpty) return "";
            int cols = encodedText.length() / rows;
            string res = "";
            for (int col = 0; col < cols; col++) {
                int r = 0, c = col;
                while (r < rows && c < cols) {
                    res += encodedText[r * cols + c];
                    r++;
                    c++;
                }
            }
            int k = res.length() - 1;
            while (res[k] == ' ') {
                k--;
            }
            return res.substr(0, k + 1);
        }
    };