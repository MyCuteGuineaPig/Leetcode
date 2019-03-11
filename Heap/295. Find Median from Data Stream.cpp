/*
295. Find Median from Data Stream

Median is the middle value in an ordered integer list. If the size of the list is even, 
there is no middle value. So the median is the mean of the two middle value.

For example,
[2,3,4], the median is 3

[2,3], the median is (2 + 3) / 2 = 2.5

Design a data structure that supports the following two operations:

void addNum(int num) - Add a integer number from the data stream to the data structure.
double findMedian() - Return the median of all elements so far.
Example:

addNum(1)
addNum(2)
findMedian() -> 1.5
addNum(3) 
findMedian() -> 2


*/


/*
a max-heap and a min-heap.
 The max heap stores the smaller half of all numbers while the min heap stores the larger half. 
 The sizes of two heaps need to be balanced each time when a new number is inserted so that their size will not be different by more than 1. 
 Therefore each time when findMedian() is called we check if two heaps have the same size. If they do, 
 we should return the average of the two top values of heaps. 
 Otherwise we return the top of the heap which has one more element.


There are several possible situations when a new number is inserted:

1)If both heap are empty, meaning that we are inserting the first number, 
we just arbitrarily inserted it into a heap, let's say, the min-heap.

2)If min-heap has more elements (later we will argue that the size won't be different by more than 1), 
we need to compare the new number with the top of the min-heap. 
If it is larger than that, then the new number belongs to the larger half and it should be added to the min-heap. 
But since we have to balance the heap, we should move the top element of the min-heap to the max-heap. 
For the min-heap, we inserted a new number but removed the original top, its size won't change.
 For the max-heap, we inserted a new element (the top of the min-heap) so its size will increase by 1.

3)If max-heap has more elements, we did the similar thing as 2).

4)If they have the same size, we just compare the new number with one of the top to determine which heap the new number should be inserted. 
We just simply inserted it there.

It can be seen that for each insertion if it was in situation 1) and 4), 
then after insertion the heap size difference will be 1. For 2) and 3), 
the size of the heap with fewer element will increase by 1 to catch up with the heap with more elements. 
Hence their sizes are well-balanced and the difference will never exceeds 1.




*/


class MedianFinder {
    priority_queue<long> small, large;
public:

    void addNum(int num) {
        small.push(num);
        large.push(-small.top());
        small.pop();
        if (small.size() < large.size()) {
            small.push(-large.top());
            large.pop();
        }
    }

    double findMedian() {
        return small.size() > large.size()
               ? small.top()
               : (small.top() - large.top()) / 2.0;
    }
};



class MedianFinder {
public:
    /** initialize your data structure here. */
    MedianFinder() { 
    }
    priority_queue<int>maxheap;
    priority_queue<int,vector<int>,greater<int>>minheap;
    
    void addNum(int num) {
        if(maxheap.empty()) maxheap.push(num);
        else{
            if(maxheap.size() > minheap.size()){
                if(maxheap.top() > num ){
                    minheap.push(maxheap.top());
                    maxheap.pop();
                    maxheap.push(num);
                }   
                else minheap.push(num);
            }else{
                if(num>minheap.top()){
                    maxheap.push(minheap.top());
                    minheap.pop();
                    minheap.push(num);
                }
                else maxheap.push(num);
            }
        }
        
    }
    
    double findMedian() {
        if(maxheap.size()>minheap.size()) return maxheap.top();
        else return static_cast<double>(maxheap.top() + minheap.top())/2;
    }
};



class MedianFinder {
public:
    /** initialize your data structure here. */
    MedianFinder() {
        
    }
    
    void addNum(int num) {
        if(small.empty()||num<small.top()){
            small.push(num);
            if(small.size()>big.size()+1){
                big.push(small.top()); //把small当中最大的给bigger
                small.pop();
            }
        }else{
            big.push(num);
            if(big.size() > small.size()){
                small.push(big.top());//把big当中最小的给small
                big.pop();
            }
        }
    }
    
    double findMedian() {
        return big.size() == small.size() ? 
                static_cast<double>(small.top()+big.top())/2: 
                static_cast<double>(small.top());
            
    }
    
    priority_queue<int,vector<int>, less<int>>small; //maxheap;
    priority_queue<int, vector<int>, greater<int>>big;
};

/**
 * Your MedianFinder object will be instantiated and called as such:
 * MedianFinder obj = new MedianFinder();
 * obj.addNum(num);
 * double param_2 = obj.findMedian();
 */



// BST solution.
class MedianFinder {
public:

    // Adds a number into the data structure.
    void addNum(int num) {
        // Balance smaller half and larger half.
        if(small.empty() || num<*small.begin()){
            small.insert(num);
            if(small.size()>big.size()+1){
                big.insert(*small.begin());
                small.erase(small.begin());
            }
        }else{
            big.insert(num);
            if(big.size()>small.size()){
                small.insert(*big.begin());
                big.erase(big.begin());
            }
        }
    }

    // Returns the median of current data stream
    double findMedian() {
        return big.size() == small.size() ?
                   (*small.begin() + *big.begin()) / 2.0 :
                   *small.begin();
    }

private:
    // min_heap_ stores the larger half seen so far.
    multiset<int, less<int>> big;
    // max_heap_ stores the smaller half seen so far.
    multiset<int, greater<int>> small;
};
