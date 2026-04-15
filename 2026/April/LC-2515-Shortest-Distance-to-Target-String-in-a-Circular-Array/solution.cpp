class Solution {
    public:
        int closestTarget(vector<string>& words, string target, int startIndex) {
            int n = words.size();
            if (words[startIndex] == target) return 0;
            int ans = n + 1;
            for (int i = 1; i <= n / 2; i++) {
                if ((words[(startIndex - i + n) % n]) == target) {
                    ans = min(ans, i);
                } else if ((words[(startIndex + i) % n]) == target) {
                    ans = min(ans, i);
                }
            }
            return (ans == n + 1) ? -1 : ans;
        }
    };