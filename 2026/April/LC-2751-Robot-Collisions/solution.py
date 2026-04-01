from typing import List

class Solution:
    def survivedRobotsHealths(
        self, positions: List[int], healths: List[int], directions: str
    ) -> List[int]:

        n = len(positions)

        # Step 1: Create indices [0, 1, 2, ..., n-1] and sort them
        # by their position values (left → right order).
        # We sort indices instead of the arrays so we can still
        # reference the original index for directions & healths.
        indices = sorted(range(n), key=lambda i: positions[i])

        # Stack stores indices of right-moving ('R') robots
        # waiting for a potential collision.
        stack = []

        # Step 2: Process each robot in left-to-right position order.
        for idx in indices:

            if directions[idx] == 'R':
                # Moving right → no collision yet; push and wait.
                stack.append(idx)

            else:
                # Moving left ('L') → may collide with right-moving
                # robots that are to its left (top of stack).
                while stack and healths[idx] > 0:
                    top = stack[-1]  # last right-moving robot

                    if healths[top] > healths[idx]:
                        # Right robot wins: loses 1 health, left robot dies.
                        healths[top] -= 1
                        healths[idx] = 0          # left robot destroyed

                    elif healths[top] < healths[idx]:
                        # Left robot wins: loses 1 health, right robot dies.
                        healths[idx] -= 1
                        healths[top] = 0          # right robot destroyed
                        stack.pop()

                    else:
                        # Equal health → both are destroyed.
                        healths[idx] = 0
                        healths[top] = 0
                        stack.pop()

        # Step 3: Collect surviving robots in their ORIGINAL order
        # (i = 0 to n-1), keeping only those with health > 0.
        return [healths[i] for i in range(n) if healths[i] > 0]


# ── Quick test ──────────────────────────────────────────────────────────────
if __name__ == "__main__":
    sol = Solution()

    # Example 1
    print(sol.survivedRobotsHealths(
        positions  = [5, 4, 3],
        healths    = [2, 17, 9],
        directions = "RRL"
    ))  # Expected: [2, 17]

    # Example 2
    print(sol.survivedRobotsHealths(
        positions  = [3, 5, 2, 6],
        healths    = [10, 10, 15, 12],
        directions = "RRLL"
    ))  # Expected: [14]