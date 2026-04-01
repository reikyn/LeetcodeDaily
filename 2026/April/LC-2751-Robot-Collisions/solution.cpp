#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    vector<int> survivedRobotsHealths(
        vector<int>& positions,
        vector<int>& healths,
        string directions
    ) {
        int n = positions.size();

        // Step 1: Build an index array [0, 1, 2, ..., n-1].
        // iota fills it with consecutive values starting at 0.
        vector<int> indices(n);
        iota(indices.begin(), indices.end(), 0);

        // Sort indices by their corresponding position (left → right).
        // We sort indices, NOT the arrays, so original index stays intact
        // for looking up directions and healths later.
        sort(indices.begin(), indices.end(), [&](int a, int b) {
            return positions[a] < positions[b];
        });

        // Stack stores indices of right-moving ('R') robots
        // that haven't collided yet.
        stack<int> st;

        // Step 2: Process each robot in left-to-right position order.
        for (int idx : indices) {

            if (directions[idx] == 'R') {
                // Moving right → no one to collide with yet; push and wait.
                st.push(idx);

            } else {
                // Moving left ('L') → collide with right-moving robots
                // on top of the stack (those positioned to the left).
                while (!st.empty() && healths[idx] > 0) {
                    int top = st.top();
                    st.pop();

                    if (healths[top] > healths[idx]) {
                        // Right robot wins: loses 1 health, left robot dies.
                        healths[top] -= 1;
                        healths[idx] = 0;   // left robot destroyed
                        st.push(top);       // right robot survives, put back

                    } else if (healths[top] < healths[idx]) {
                        // Left robot wins: loses 1 health, right robot dies.
                        healths[idx] -= 1;
                        healths[top] = 0;   // right robot destroyed (already popped)

                    } else {
                        // Equal health → both are destroyed.
                        healths[idx] = 0;
                        healths[top] = 0;   // right robot already popped; just zero it
                    }
                }
            }
        }

        // Step 3: Collect survivors in ORIGINAL order (index 0 to n-1).
        // Only include robots whose health is still > 0.
        vector<int> result;
        for (int i = 0; i < n; ++i) {
            if (healths[i] > 0) {
                result.push_back(healths[i]);
            }
        }
        return result;
    }
};