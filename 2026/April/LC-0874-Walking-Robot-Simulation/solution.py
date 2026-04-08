class Solution:
    @staticmethod
    def __calc(p1: tuple[int], p2: tuple[int]) -> int:
        x1, y1 = p1
        x2, y2 = p2
        return (x2 - x1) ** 2 + (y2 - y1) ** 2

    def robotSim(self, commands: List[int], obstacles: List[List[int]]) -> int:
        dirs = [(0, 1), (1, 0), (0, -1), (-1, 0)]  # N, E, S, W

        obs = {(x, y) for x, y in obstacles}

        dist = 0
        curr = (0, 0)
        d = 0  # start facing NORTH
        for c in commands:
            if c == -2:
                d = (d - 1) % 4  # turn left
            elif c == -1:
                d = (d + 1) % 4  # turn right
            else:
                for _ in range(c):
                    next_pos = (curr[0] + dirs[d][0], curr[1] + dirs[d][1])
                    if next_pos in obs:
                        break
                    curr = next_pos
                dist = max(dist, self.__calc((0, 0), curr))

        return dist