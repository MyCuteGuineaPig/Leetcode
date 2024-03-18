def findMaxLength(self, nums):
    index = {0: -1}
    balance = maxlen = 0
    for i, num in enumerate(nums):
        balance += num - 0.5
        maxlen = max(maxlen, i - index.setdefault(balance, i))
    return maxlen

#Just for fun as an ugly one-liner:

def findMaxLength(self, nums):
    return reduce(lambda(f,b,m),(i,x):(f,b+x-.5,max(m,i-f.setdefault(b+x-.5,i))),enumerate(nums),({0:-1},0,0))[2]
