"""
599. Minimum Index Sum of Two Lists


Example 1:
Input:
["Shogun", "Tapioca Express", "Burger King", "KFC"]
["Piatti", "The Grill at Torrey Pines", "Hungry Hunter Steakhouse", "Shogun"]
Output: ["Shogun"]
Explanation: The only restaurant they both like is "Shogun".
Example 2:
Input:
["Shogun", "Tapioca Express", "Burger King", "KFC"]
["KFC", "Shogun", "Burger King"]
Output: ["Shogun"]
Explanation: The restaurant they both like and have the least index sum is "Shogun" with index sum 1 (0+1).
"""


class Solution:
    def findRestaurant(self, list1, list2):
        """
        :type list1: List[str]
        :type list2: List[str]
        :rtype: List[str]
        """
        dic = collections.defaultdict(int)
        res, min_ind = [], float('inf')
        for i, v in enumerate(list1):
            dic[v] = i
        for i, v in enumerate(list2):
            if v in dic:
                if min_ind > i + dic[v]:
                    min_ind, res =  i + dic[v], [v]
                elif min_ind == i + dic[v]:
                    res.append(v)
        return res