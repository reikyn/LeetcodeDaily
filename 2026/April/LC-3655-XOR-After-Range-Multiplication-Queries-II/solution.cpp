class Solution {
    public:
        const int M = 1e9 + 7;
    
        // Binary Exponentiation for Fermat's Little Theorem -> power(mult, M-2);
        long long power(long long a, long long b) {
            if(b == 0)
                return 1;
    
            long long half   = power(a, b/2);
            long long result = (half * half) % M;
    
            if(b % 2 == 1) {
                result = (result * a) % M;
            }
    
            return result;
        }
    
        int xorAfterQueries(vector<int>& nums, vector<vector<int>>& queries) {
            int n         = nums.size();
            int blockSize = ceil(sqrt(n));
            
            unordered_map<int, vector<vector<int>>> smallKMap;
    
            for(auto& q : queries){
                int L = q[0], R = q[1], k = q[2], v = q[3];
    
                if(k >= blockSize) {
                    for(int i = L; i <= R; i += k) {
                        nums[i] = (1LL * nums[i] * v) % M;
                    }
                } else {
                    smallKMap[k].push_back(q);
                } 
            }
            
            for(auto& [k, allQueries] : smallKMap) {
                vector<long long> diff(n, 1);
    
                for(auto& query : allQueries) {
                    int L = query[0];
                    int R = query[1];
                    int v = query[3];
    
                    diff[L] = (diff[L] * v) % M;
    
                    int steps = (R - L) / k;
                    int next  = L + (steps + 1) * k;
    
                    if(next < n){
                        diff[next] = (diff[next] * power(v, M-2)) % M; //Fermat's Little Theorem
                    }
                }
                
                //Cumulative Product
                for(int i = 0; i < n; i++){
                    if(i-k >= 0) 
                        diff[i] = (diff[i] * diff[i-k]) % M;
                }
    
                //Apply diff to nums
                for(int i = 0; i < n; i++) {
                    nums[i] = (1LL * nums[i] * diff[i]) % M;
                }
            }
    
            int result = 0;
            for(int& num : nums) 
                result ^= num;
    
            return result;    
        }
    };