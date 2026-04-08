#include <bits/stdc++.h>
using namespace std;

class Solution {
private:
    static int calc(pair<int,int> p1, pair<int,int> p2) {
        int x1 = p1.first,  y1 = p1.second;
        int x2 = p2.first,  y2 = p2.second;
        return (x2 - x1) * (x2 - x1) + (y2 - y1) * (y2 - y1);
    }

public:
    int robotSim(vector<int>& commands, vector<vector<int>>& obstacles) {
        // Clockwise: NORTH -> EAST -> SOUTH -> WEST
        vector<pair<int,int>> dirs = {{0,1}, {1,0}, {0,-1}, {-1,0}};

        set<pair<int,int>> obs;
        for (auto& o : obstacles)
            obs.insert({o[0], o[1]});

        int d = 0, dist = 0;
        pair<int,int> curr = {0, 0};

        for (int c : commands) {
            if (c == -2)
                d = (d - 1 + 4) % 4;   // anti-clockwise
            else if (c == -1)
                d = (d + 1) % 4;        // clockwise
            else {
                for (int i = 0; i < c; i++) {
                    pair<int,int> next = {curr.first  + dirs[d].first,
                                         curr.second + dirs[d].second};
                    if (obs.count(next)) break;
                    curr = next;
                }
                dist = max(dist, calc({0, 0}, curr));
            }
        }

        return dist;
    }
};