import threading

class TrafficLight:
    def __init__(self):
        self.direction = 0
        self.lock = threading.Lock()

    def carArrived(
        self,
        carId: int,                      # ID of the car
        roadId: int,                     # ID of the road the car travels on. Can be 1 (road A) or 2 (road B)
        direction: int,                  # Direction of the car
        turnGreen: 'Callable[[], None]', # Use turnGreen() to turn light to green on current road
        crossCar: 'Callable[[], None]'   # Use crossCar() to make car cross the intersection
    ) -> None:
        with self.lock:
            if (direction > 2) != self.direction:
                self.direction = not self.direction
                turnGreen()
            crossCar()

    import threading

class TrafficLight:
    def __init__(self):
        self.direction = 0
        self.semaphore = threading.Semaphore(1)

    def carArrived(
        self,
        carId: int,                      # ID of the car
        roadId: int,                     # ID of the road the car travels on. Can be 1 (road A) or 2 (road B)
        direction: int,                  # Direction of the car
        turnGreen: 'Callable[[], None]', # Use turnGreen() to turn light to green on current road
        crossCar: 'Callable[[], None]'   # Use crossCar() to make car cross the intersection
    ) -> None:
        self.semaphore.acquire()
        if (direction > 2) != self.direction:
            self.direction = not self.direction
            turnGreen()
        crossCar()
        self.semaphore.release()