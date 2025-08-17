#include <iostream>
#include <string>

class TrainJourney {
public:
    void run() {
        startJourney();
        buyTicket();

        if (needReservation()) {
            selectSeat();
        } else if (wantReservation()) {
            selectSeat();
        }

        collectTicket();

        boardTrain();

        if (haveReservation()) {
            lookForAssignedSeat();
        } else {
            lookForUnassignedSeat();
        }

        ticketCheckedByInspector();

        if (isDiscounted()) {
            showValidDocumentation();
        }

        while (!arriveDestination()) {
            travel();
        }

        leaveTrain();
        endJourney();
    }

private:
    void startJourney() { log("Journey started."); }
    void buyTicket() { log("Ticket purchased."); }
    bool needReservation() { return true; }  // assume required
    bool wantReservation() { return false; } // optional branch
    void selectSeat() { log("Seat reserved."); }

    void collectTicket() {
        std::string method = "machine"; // "mail" or "machine"
        if (method == "mail") {
            checkLetterBoxIn3Days();
        } else {
            collectFromMachine();
        }
    }

    void checkLetterBoxIn3Days() { log("Ticket arrives in mail after 3 days."); }
    void collectFromMachine() { log("Ticket collected from machine."); }

    void boardTrain() { log("Boarded the train."); }

    bool haveReservation() { return true; }
    void lookForAssignedSeat() { log("Found assigned seat."); }
    void lookForUnassignedSeat() { log("Searched for unassigned seat."); }

    void ticketCheckedByInspector() { log("Ticket checked by inspector."); }
    bool isDiscounted() { return true; }
    void showValidDocumentation() { log("Valid discount documentation shown."); }

    bool arriveDestination() {
        static int stops = 0;
        stops++;
        return stops >= 3; // simulate arriving after 3 iterations
    }
    void travel() { log("Train is traveling..."); }

    void leaveTrain() { log("Passenger left the train."); }
    void endJourney() { log("Journey ended."); }

    void log(const std::string& msg) {
        std::cout << msg << std::endl;
    }
};

int main() {
    TrainJourney journey;
    journey.run();
    return 0;
}