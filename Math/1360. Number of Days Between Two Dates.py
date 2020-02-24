class Solution:
    def daysBetweenDates(self, date1: str, date2: str) -> int:
        def f(date):
            year, month, day = [*date]
            #-1 是算之前一年的
            days = (year-1) * 365 + (year-1) // 4 - (year-1) // 100 + (year-1) // 400 
            for i in range(1, month):
                print(i, days)
                if i in set([1,3,5,7,8,10]):
                    days += 31
                elif i in set([4,6,9,11]):
                    days += 30
                elif year % 4 == 0 and year% 100 != 0 or year%400 == 0:
                        days += 29 
                else:
                    days += 28
            return days + day 
        return  abs(f(map(int, date1.split('-'))) - f(map(int, date2.split('-'))))
                