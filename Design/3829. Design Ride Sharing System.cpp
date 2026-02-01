class RideSharingSystem {
public:
    RideSharingSystem() {
        
    }
    
    void addRider(int riderId) {
        if(rider.count(riderId)) return;
        rider.insert(riderId);
        q_rider.push(riderId);
    }
    
    void addDriver(int driverId) {
        if(driver.count(driverId)) return;
        driver.insert(driverId);
        q_driver.push(driverId);
    }
    
    vector<int> matchDriverWithRider() {
        while(q_driver.size() && q_rider.size()) {
            int top_rider = q_rider.front();
            q_rider.pop();
            if(rider.count(top_rider) == 0) continue;
            rider.erase(top_rider);
            int top_driver = q_driver.front(); q_driver.pop(); 
            driver.erase(top_driver);
            return {top_driver, top_rider};
        }
        return {-1, -1};
    }
    
    void cancelRider(int riderId) {
        if(rider.count(riderId)){
            rider.erase(riderId);
        }
    }

private:
    queue<int>q_rider;
    queue<int>q_driver;
    unordered_set<int>rider;
    unordered_set<int>driver;
};

/**
 * Your RideSharingSystem object will be instantiated and called as such:
 * RideSharingSystem* obj = new RideSharingSystem();
 * obj->addRider(riderId);
 * obj->addDriver(driverId);
 * vector<int> param_3 = obj->matchDriverWithRider();
 * obj->cancelRider(riderId);
 */