class UndergroundSystem:

    def __init__(self):
        self.start = {}
        self.end = {}
        self.avg = {}

    def checkIn(self, id: int, stationName: str, t: int) -> None:
        self.start[id] = [stationName, t]

    def checkOut(self, id: int, stationName: str, t: int) -> None:
        b = self.start[id]
        if b[0] not in self.avg:
            self.avg[b[0]] = {}
        if stationName not in self.avg[b[0]]:
            self.avg[b[0]][stationName] = [t - b[1], 1]
        else:
            h = self.avg[b[0]][stationName]
            self.avg[b[0]][stationName] = [(h[0] * h[1] + t - b[1]) / (h[1] + 1), h[1] + 1]

    def getAverageTime(self, startStation: str, endStation: str) -> float:
        return self.avg[startStation][endStation][0]


class UndergroundSystem:
    def __init__(self):
        self.__live = {}
        self.__statistics = collections.defaultdict(lambda: [0, 0])
        

    def checkIn(self, id, stationName, t):
        """
        :type id: int
        :type stationName: str
        :type t: int
        :rtype: None
        """
        self.__live[id] = (stationName, t)

    def checkOut(self, id, stationName, t):
        """
        :type id: int
        :type stationName: str
        :type t: int
        :rtype: None
        """
        startStation, startTime = self.__live.pop(id)
        self.__statistics[startStation, stationName][0] += t-startTime
        self.__statistics[startStation, stationName][1] += 1
        
    def getAverageTime(self, startStation, endStation):
        """
        :type startStation: str
        :type endStation: str
        :rtype: float
        """
        total_time, cnt = self.__statistics[startStation, endStation]
        return float(total_time) / cnt
