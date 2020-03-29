
class UndergroundSystem {
public:
    UndergroundSystem() {
        
    }
    
    void checkIn(int id, string stationName, int t) {
        live_[id] = {stationName, t};
    }
    
    void checkOut(int id, string stationName, int t) {
        const auto [startStation, startTime] = move(live_[id]); live_.erase(id);
        statistics_[startStation][stationName].first += t - startTime;
        ++statistics_[startStation][stationName].second;
    }
    
    double getAverageTime(string startStation, string endStation) {
        const auto& [total_time, cnt] = statistics_[startStation][endStation];
        return double(total_time) / cnt; 
    }

private:
    unordered_map<int, pair<string, int>> live_;
    unordered_map<string, unordered_map<string, pair<int, int>>> statistics_;
};


class UndergroundSystem {
public:
    unordered_map<int, pair<string, int>> m;
    unordered_map<string, pair<int, int>> stats;
    void checkIn(int id, string startStation, int timeIn) {
        m[id] = {startStation, timeIn};
    }
    void checkOut(int id, string endStation, int timeOut) {
        auto &[startStation, timeIn] = m[id];
        auto &[totalDuration, tripsCnt] = stats[startStation + ">" + endStation];
        totalDuration += timeOut - timeIn;
        ++tripsCnt;
    }
    double getAverageTime(string startStation, string endStation) {
        auto &[totalDuration, tripsCnt] = stats[startStation + ">" + endStation];
        return (double)totalDuration / tripsCnt;
    }
};