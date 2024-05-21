def diff_print(diffs):
    # print the diff array and actual pair counts for k for comparison
    return f"\n\t\tdiffs = {diffs}. pair counts = {list(accumulate(diffs))}"

def print_house_diff_array(house):
    # print the diff array contributed by this house including the changes to the diff array by each adjustment
    B = [0] * n
    print(f"house {house} start. {diff_print(B)}")
    B[0] += 2  # go left and right
    print(f"go left and right. B[0] += 2. {diff_print(B)}")
    B[min(house - 1, abs(house - y) + x)] -= 1  # reach 1 then stop
    print(f"reach 1 then stop. B[min({house - 1}, {abs(house - y) + x})] = B[{min(house - 1, abs(house - y) + x)}] -= 1. {diff_print(B)}")
    B[min(n - house, abs(house - x) + 1 + n - y)] -= 1  # reach n then stop
    print(f"reach n then stop. B[min({n - house}, {abs(house - x) + 1 + n - y})] = B[{min(n - house, abs(house - x) + 1 + n - y)}] -= 1. {diff_print(B)}")
    B[min(abs(house - x), abs(y - house) + 1)] += 1  # reach x then split
    print(f"reach x then split. B[min({abs(house - x)}, {abs(y - house) + 1})] = B[{min(abs(house - x), abs(y - house) + 1)}] += 1. {diff_print(B)}")
    B[min(abs(house - x) + 1, abs(y - house))] += 1  # reach y then split
    print(f"reach y then split. B[min({abs(house - x) + 1}, {abs(y - house)})] = B[{min(abs(house - x) + 1, abs(y - house))}] += 1. {diff_print(B)}")
    r = max(x - house, 0) + max(house - y, 0)
    print(f"r = max({x - house}, 0) + max({house - y}, 0) = {max(x - house, 0) + max(house - y, 0)}")
    B[r + (y - x + 0) // 2] -= 1  # house -> x -> y <- x
    print(f"house -> x -> y <- x. B[{r + (y - x + 0) // 2}] -= 1. {diff_print(B)}")
    B[r + (y - x + 1) // 2] -= 1  # house -> y -> x <- y
    print(f"house -> y -> x <- y. B[{r + (y - x + 1) // 2}] -= 1. {diff_print(B)}")
    print(f"house {house} done. {diff_print(B)}.", end="\n\n")

class Solution:
    def countOfPairs(self, n: int, x: int, y: int) -> List[int]:
        # set x and y such that x <= y. simplifies the code.
        x, y = min(x, y), max(x, y)
        
        # A is a differences array which is not the answer array! Differences array represents an array using differences as the values. It's an alternate form with a speed benefit.
        # What's the difference?
        #     answer_array[k] = the total number of pairs of houses such that the min streets to move between the 2 houses in each pair is k.
        #     diff_array[k] = ALL k's >= this k have this many more/less pairs of houses such that the min streets to move between the 2 houses in each pair is k. This value affects ALL k's >= this k.
        #     Example to see the difference
        #         array      = [0, 1, 1, 1, 0, 0]
        #         diff_array = [0, 1, 0, 0, -1, 0]
        #         These 2 arrays are equivalent. The 1 at diff_array[1] means that all k's from k = 2 to n have 1 additional pair. Remember that each value in a diff array affects all later indices. The -1 at diff_array[4] cancels out the effect of the earlier 1 starting from that point to the end.
        # What's the benefit?
        #     We are able to change a value at a single index and affect ALL indices after it. If we wanted to add 1 at all indices, we'd add 1 to only the 1st index. This is O(1) while adding 1 to every index on a normal array would be O(n).
        # How do we get the answer array from the diff array?
        #     Just build a prefix (cumulative) sum array out of the diff array.

        # A[i] where k = i + 1. e.g., A[0] is for k = 1.
        A = [0] * n

        # This loop computes the changes in pairs for each k due to each house and updates a single differences array A.
        for house in range(1, n + 1):
            # print_house_diff_array(house) # see how each house's diff array is built

            A[0] += 2  # go left and right
            # Any point can always go left and right
            # Even the edge case where we have [1, 2], additional path can be used to go left and right!
            # Adding to [0] because it represents using 1 step in the final array

            A[min(house - 1, abs(house - y) + x)] -= 1  # reach 1 then stop
            # 从 house - y 需要house - y步，y->x 需要1步, x到1 需要x -1
            # For reaching (1), we can either go directly, or use the additional path if it comes in between
                # go directly house -> 1: house - 1 steps
                # use x-y path: abs(house - y) + x steps
                #     house -> y: abs(house - y) steps
                #         Even if house < y, we still go to the right to y. house -> x is never taken (see note below). The only other option is the direct path from house -> 1 which is already considered.
                #     y -> x: 1 step
                #     x -> 1: x - 1 steps
                
                #     Note that we go house -> y. Why not house -> x?
                #         If we did house -> x, we'd then take x -> y (if we didn't we'd just go directly to 1), but x <= y so we wouldn't get closer to 1.
            # What does A[min_dist_from_house_to_1] -= 1 do?
            #     This is actually doing -1 to pairs for all k >= min_dist_from_house_to_1 + 1. If min_dist_from_house_to_1 was 3, A[3] represents k = 4 so all k >= 4 are changed to have 1 less pair. 
            #     Why the -1? We added to A[0] above which means we assume 2 pairs of all k's. We found the min distance to reach 1 and stop. So all k's after that distance should not get a pair from when this house is paired with houses before it. We adjust for this by taking 1 pair back from them all.            
            
            A[min(n - house, abs(house - x) + 1 + n - y)] -= 1  # reach n then stop
            # For reaching (n), we can either go directly, or use the additional path if it comes in between
                # go directly house -> n: n - house steps
                # use x-y path: abs(house - x) + 1 + n - y steps
                #     house -> x: abs(house - x) steps
                #         Even if house < x, we still go to the left to x. house -> y is never taken (see note below). The only other option is the direct path from house -> 1 which is already considered.
                #     x -> y: 1 step
                #     y -> n: n - y steps
                
                #     Note that we go house -> x. Why not house -> y?
                #         If we did house -> y, we'd then take y -> x (if we didn't we'd just go directly to n), but x <= y so we wouldn't get closer to n.
            
            # Similary, after reaching the 'x' or 'y' point, we would split into two paths, so
            # we also need to adjust for this by increasing the count at that many steps.
            # Also: for case when arr=[1, 2], this automatically cancels out the last change we made. 
            
            A[min(abs(house - x), abs(y - house) + 1)] += 1  # reach x then split
            # reach x from house. go directly or use the additional path.
            # go directly house -> x: abs(house - x) steps
            # use x-y path: abs(y - house) + 1 steps
            #     house -> y: abs(y - house) steps
            #     y -> x: 1 step
            # What does A[min_dist_from_house_to_x] += 1 do?
                #     This is actually doing +1 to pairs for all k >= min_dist_from_house_to_x + 1. If min_dist_from_house_to_x was 3, A[3] represents k = 4 so all k >= 4 are changed to have 1 more pair. 
                #     Why the +1? After reaching x, we split into 2 paths so all k's from after that point should have an additional pair.

            A[min(abs(house - x) + 1, abs(y - house))] += 1  # reach y then split
            # reach y from house. go directly or use the additional path.
            # go directly house -> y: abs(house - y) steps
            # use y-x path: abs(x - house) + 1 steps
            #     house -> x: abs(x - house) steps
            #     x -> y: 1 step
            # What does A[min_dist_from_house_to_y] += 1 do?
                #     This is actually doing +1 to pairs for all k >= min_dist_from_house_to_y + 1. If min_dist_from_house_to_y was 3, A[3] represents k = 4 so all k >= 4 are changed to have 1 more pair. 
                #     Why the +1? After reaching y, we split into 2 paths so all k's from after that point should have an additional pair.

            r = max(x - house, 0) + max(house - y, 0)
            # r stores the distance to the closest entry point to the additional path
            # if house > y, r = dist_from_house_to_y. house to right of x-y loop
            # if house < x, r = dist_from_house_to_x. house to left of x-y loop
            # if x <= house <= y, r = 0. already in x-y loop.

            # Then, we calculate the mid point of the loop, and remove 2 more instances
            A[r + (y - x + 0) // 2] -= 1  # house -> x -> y <- x
            A[r + (y - x + 1) // 2] -= 1  # house -> y -> x <- y
            # Previously, we split into 2 paths when reaching x or y. You can go from x -> y using the extra street and then reverse back to x using normal streets but you should stop in the middle. You can also go from x -> y using normal streets but you should stop in the middle. You should stop at the midpoint of the loop since there's a shorter path to nodes after the loop midpoint with the other path. 
            # We need to account for this by removing a pair on each path for all k >= dist_from_house_to_loop_mid_point + 1. 
            
            # But why are we using floored mid formula in one and ceiled mid in another?
            # If the distance between y and x is even, we need to ensure we reduce (2) of same instances
            # And that is exactly what happens. [4//2 == 2 and 5//2 == 2]
            # On the other hand, when we have a odd length gap between x and y, we need to reduce 2 different instances
            # One of length (y-x)//2, and other at (y-x+1)//2.
        
        # return the running sums of A
        return list(accumulate(A))