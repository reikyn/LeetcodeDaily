class Solution {
    public:
        int xorAfterQueries(vector<int>& nums, vector<vector<int>>& queries) {
            int n = nums.size();
            const long long MOD = 1e9 + 7;
    
            for (auto &q : queries) {
                int l = q[0];
                int r = q[1];
                int k = q[2];
                long long v = q[3];
    
                for (int idx = l; idx <= r; idx += k) {
                    nums[idx] = (nums[idx] * v) % MOD;
                }
            }
    
            long long ans = 0;
            for (auto &x : nums) {
                ans ^= x;
            }
    
            return ans;
            
        }
    };