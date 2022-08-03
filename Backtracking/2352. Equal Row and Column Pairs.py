class Solution:                 # Consider this grid for an example:
                                #           grid = [[1,2,1,9]
                                #                   [2,8,9,2]
                                #                   [1,2,1,9]
                                #                   [9,2,6,3]]
    
                                # Here's the plan:

                                #   • Determine tpse, the transpose of grid (using zip(*grid)):
                                #           tspe = [[1,2,1,9] 
                                #                   [2,8,2,2]
                                #                   [1,9,1,6]
                                #                   [9,2,9,3]] 
                                #     The problem now is to determine the pairs of 
                                #     identical rows, one row in tpse and the other in grid.

                                #   • We hash grid and tspe:
                                #
                                #           Counter(tuple(grid)):
                                #               {(1,2,1,9): 2, (2,8,9,2): 1, (9,2,6,3): 1}
                                #  
                                #           Counter(zip(*grid)):
                                #            {(1,2,1,9): 1, (2,8,2,2): 1, (1,9,1,6): 1, (9,2,9,3): 1}
                                #
                                #   • We determine the number of pairs:
                                #       (1,2,1,9): 2 and (1,2,1,9): 1    => 2x1 = 2
                                
    def equalPairs(self, grid: List[List[int]]) -> int:

        tpse = Counter(zip(*grid))                  # <-- determine the transpose
                                                    #     and hash the rows

        grid = Counter(map(tuple,grid))             # <-- hash the rows of grid. (Note the tuple-map, so
                                                    #     we can compare apples w/ apples in next step.)

        return  sum(tpse[t]*grid[t] for t in tpse)  # <-- compute the number of identical pairs
		
		                                            # https://leetcode.com/submissions/detail/755717162/