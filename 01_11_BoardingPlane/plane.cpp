#include <iostream>
#include <vector>
#include <string>
#include <thread>
#include <chrono>

class BoardingWorkflow {
public:
    void run() {
        planeArrivedAtGate();
        startPriorityBoarding();

        if (isFirstClassPassenger()) {
            boardPlane("First Class Passenger");
        } else if (isHalfFirstClassBoarded()) {
            boardAllPassengers();
        }

        fiveMinutesBeforeClose();

        while (!areAllPassengersOnboard()) {
            makeAnnouncement();
            waitFiveMinutes();
        }

        closeGate();
        endBoarding();
    }

private:
    // Step methods
    void planeArrivedAtGate() {
        log("Plane arrived at the gate");
    }

    void startPriorityBoarding() {
        log("Priority boarding started");
    }

    bool isFirstClassPassenger() {
        log("Checking for First Class passenger...");
        return true; // simulation
    }

    bool isHalfFirstClassBoarded() {
        log("Checking if half of First Class has boarded...");
        return false; // simulation
    }

    void boardPlane(const std::string& passenger) {
        log("Boarded: " + passenger);
    }

    void boardAllPassengers() {
        log("All passengers boarding...");
    }

    void fiveMinutesBeforeClose() {
        log("5 minutes before gate closes...");
    }

    bool areAllPassengersOnboard() {
        static int attempt = 0;
        attempt++;
        if (attempt < 2) {
            log("Not all passengers onboard yet.");
            return false;
        }
        log("All passengers onboard.");
        return true;
    }

    void makeAnnouncement() {
        log("Announcement: Final boarding call!");
    }

    void waitFiveMinutes() {
        log("Waiting 5 minutes for late passengers...");
        // simulate wait
        std::this_thread::sleep_for(std::chrono::milliseconds(500));
    }

    void closeGate() {
        log("Gate closed.");
    }

    void endBoarding() {
        log("Boarding process ended.");
    }

    void log(const std::string& msg) {
        std::cout << msg << std::endl;
    }
};

int main() {
    BoardingWorkflow wf;
    wf.run();
    return 0;
}