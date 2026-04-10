// Approach 1:
class Solution {
    public:
        int minimumDistance(vector<int>& nums) {
            int n=nums.size(),mini=1e9;
    
            for(int i=0;i<n-2;i++){
                for(int j=i+1;j<n-1;j++){
                    for(int k=j+1;k<n;k++){
                        if(nums[i]==nums[j] && nums[j]==nums[k]){
                            int dist=abs(i-j)+abs(j-k)+abs(k-i);
                            mini=min(mini,dist);
                        }
                    }
                }
            }
    
            return mini==1e9?-1:mini;
        }
    };

// Approach 2:
class Solution {
    public:
        int minimumDistance(vector<int>& nums) {
            int min_diff = 201;
            unordered_map<int, vector<int>> indices;
            for (int i = 0; i < nums.size(); i++) {
                int n = indices[nums[i]].size();
                if (n >= 2) {
                    min_diff = min(min_diff, i - indices[nums[i]][n - 2]);
                }
                indices[nums[i]].push_back(i);
            }
            return (min_diff != 201) ? min_diff * 2 : -1;
        }
    };