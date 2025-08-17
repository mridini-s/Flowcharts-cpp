#include <bits/stdc++.h>
using namespace std;

struct Taxi {
    int id;
    double x, y;      // location
    bool available;
};

struct Order {
    int id;
    string customer;
    double pickupX, pickupY;
    time_t pickupTime;
};

class TaxiBookingSystem {
    vector<Taxi> taxis;
    vector<Order> orders;
    int orderCounter = 0;

public:
    TaxiBookingSystem() {
        // sample taxis
        taxis.push_back({1, 10.0, 10.0, true});
        taxis.push_back({2, 15.0, 12.0, true});
        taxis.push_back({3, 25.0, 30.0, true});
    }

    // Step 1: Customer places order
    void startBooking(const string& customer, double px, double py, time_t pickupTime) {
        Order o{++orderCounter, customer, px, py, pickupTime};
        orders.push_back(o);
        cout << "Order #" << o.id << " received from " << customer << "\n";
        processOrder(o);
    }

private:
    // Step 2-3: Check pickup time
    void processOrder(Order& o) {
        time_t now = time(nullptr);
        double minutesToPickup = difftime(o.pickupTime, now) / 60.0;

        if (minutesToPickup > 30) {
            cout << "Pickup is more than 30 minutes away. Waiting...\n";
            return; // In real system, we’d schedule it later
        }

        findTaxi(o);
    }

    // Step 4: Search taxis
    void findTaxi(Order& o) {
        Taxi* chosen = nullptr;
        for (auto& t : taxis) {
            if (t.available && distance(o.pickupX, o.pickupY, t.x, t.y) <= 10.0) {
                chosen = &t;
                break;
            }
        }

        if (!chosen) {
            cout << "No taxi available nearby. Retrying...\n";
            // In real system: wait 1 min and retry
            return;
        }

        assignRide(o, *chosen);
    }

    // Step 5: Assign ride
    void assignRide(Order& o, Taxi& t) {
        t.available = false;
        cout << "Assigned Taxi #" << t.id << " to Order #" << o.id << "\n";
        completeRide(o, t);
    }

    // Step 6: Complete ride
    void completeRide(Order& o, Taxi& t) {
        cout << "Ride started for " << o.customer << "...\n";
        cout << "Ride completed for " << o.customer << "!\n";
        t.available = true;
        cout << "Taxi #" << t.id << " is now available again.\n";
    }

    static double distance(double x1, double y1, double x2, double y2) {
        return sqrt((x1-x2)*(x1-x2) + (y1-y2)*(y1-y2));
    }
};

int main() {
    TaxiBookingSystem system;

    // Order within 30 minutes
    time_t pickupSoon = time(nullptr) + 10*60; // 10 min later
    system.startBooking("Alice", 12.0, 11.0, pickupSoon);

    cout << "\n";

    // Order too far in future
    time_t pickupLater = time(nullptr) + 90*60; // 90 min later
    system.startBooking("Bob", 20.0, 20.0, pickupLater);

    return 0;
}