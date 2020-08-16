class Solution:
    def oddEvenJumps(self, A: List[int]) -> int:
        n = len(A)
        next_higher, next_lower = [0] * n, [0] * n

        stack = []
        for a, i in sorted([a, i] for i, a in enumerate(A)):
            while stack and stack[-1] < i:
                next_higher[stack.pop()] = i
            stack.append(i)

        stack = []
        for a, i in sorted([-a, i] for i, a in enumerate(A)):
            while stack and stack[-1] < i:
                next_lower[stack.pop()] = i
            stack.append(i)

        higher, lower = [0] * n, [0] * n
        higher[-1] = lower[-1] = 1
        for i in range(n - 1)[::-1]:
            higher[i] = lower[next_higher[i]]
            lower[i] = higher[next_lower[i]]
        return sum(higher)




class Solution:
    def oddEvenJumps(self, A: 'List[int]') -> 'int':

        # sort indexes of A by values in A
        sorted_indexes = sorted(range(len(A)), key = lambda i: A[i])
        
        # generate list of indexes we can jump to next on odd jumps
        oddnext = self.makeStack(sorted_indexes)

        # sort indexes of A by reverse order of their value in A
        sorted_indexes.sort(key = lambda i: A[i], reverse = True)

        # generate list of indexes we can jump to next on even jumps
        evennext = self.makeStack(sorted_indexes)

        # initialize odd and even lists that will contain
        # the information of if the end can be reached
		# from the respective index
        odd = [False] * len(A)
        even = [False] * len(A)

        # the last index is always counted
        odd[len(A)-1] = even[len(A)-1] = True

        # iterate through A backwards, starting at next to last element
        for i in range(len(A)-2, -1, -1):

            # if an odd jump is available from current index,
            # check if an even jump landed on the index of the available
            # odd jump and set current index in odd to True if it did
            if oddnext[i] is not None:
                odd[i] = even[oddnext[i]]

            # if an even jump is available from current index,
            # check if an odd jump landed on the index of the available
            # even jump and set current index in even to True if it did
            if evennext[i] is not None:
                even[i] = odd[evennext[i]]

        # return the number of spots marked True in odd
        # we always start with an odd jump, so odd will
        # contain the number of valid jumps to reach the end
        return sum(odd)
    
    # makes monotonic stack
    def makeStack(self, sorted_indexes):
        result = [None] * len(sorted_indexes)
        stack = []
        for i in sorted_indexes:
            while stack and i > stack[-1]:
                result[stack.pop()] = i
            stack.append(i)
        # delete stack as a memory optimization
        del stack
        return resul