#include <iostream>
using namespace std;

class AirTravel {
public:
    void run() {
        checkIn();
        baggageDrop();
        securityScreening();

        if (!immigrationCheck()) {
            cout << "Immigration failed. Journey ends." << endl;
            return;
        }

        boardFlight();
        flightDeparts();
        flightLands();

        if (hasConnection()) {
            cout << "Proceed to connecting flight..." << endl;
            run(); // recursive for next flight
            return;
        }

        leaveFlight();

        if (!arrivalImmigration()) {
            sendBackToOrigin();
        } else {
            claimBaggage();
        }

        endJourney();
    }

private:
    void checkIn() { cout << "Checked in at airport." << endl; }
    void baggageDrop() { cout << "Baggage dropped." << endl; }
    void securityScreening() {
        cout << "Security screening complete (restricted/dangerous items handled)." << endl;
    }
    bool immigrationCheck() { return true; } // simulate pass
    void boardFlight() { cout << "Boarded flight." << endl; }
    void flightDeparts() { cout << "Flight departed." << endl; }
    void flightLands() { cout << "Flight landed." << endl; }
    bool hasConnection() { return false; } // simulate no connection
    void leaveFlight() { cout << "Left the aircraft." << endl; }
    bool arrivalImmigration() { return true; } // simulate success
    void sendBackToOrigin() { cout << "No entry permit. Sent back to origin country." << endl; }
    void claimBaggage() { cout << "Claimed baggage successfully." << endl; }
    void endJourney() { cout << "Journey completed." << endl; }
};
int main() {
    AirTravel travel;
    travel.run();
    return 0;
}