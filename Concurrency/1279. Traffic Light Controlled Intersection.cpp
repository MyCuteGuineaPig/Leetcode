class TrafficLight {
private:
    mutex mu;
    int direction = 0;
public:
    TrafficLight() {
        
    }

    void carArrived(
        int carId,                   // ID of the car
        int roadId,                  // ID of the road the car travels on. Can be 1 (road A) or 2 (road B)
        int direction,               // Direction of the car
        function<void()> turnGreen,  // Use turnGreen() to turn light to green on current road
        function<void()> crossCar    // Use crossCar() to make car cross the intersection
    ) {
        lock_guard<mutex>lock(mu);
        if ((direction > 2) != this->direction ){
            this->direction = !this->direction;
            turnGreen();
        }
        crossCar();
    }
};

class TrafficLight 
{
    public:
    mutex m;
    int light=1; //which light is currently on
    TrafficLight() 
    {}

    void carArrived(int carId,int roadId,int direction,function<void()> turnGreen,function<void()> crossCar) 
    {
        m.lock();
        if(light!=roadId) //if the light is not green on the current road, we should switch the light
		{
			turnGreen();
			light=roadId;
		}
        crossCar();
        m.unlock();
    }