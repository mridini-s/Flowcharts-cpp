#include <iostream>
#include <string>
#include <thread>
#include <chrono>
using namespace std;

// Simulation of environment detection
bool foundFootbridge() { return false; }
bool foundTunnel() { return false; }
bool foundCrossing() { return true; }
bool trafficLightExists() { return true; }
string getTrafficLightColor() { return "Green"; } // or "Red"
bool isCarApproaching() { return false; }

// Actions
void useFootbridge() { cout << "Using the footbridge safely.\n"; }
void useTunnel() { cout << "Using the tunnel safely.\n"; }
void walkAway() { cout << "No safe crossing. Walking away.\n"; }
void crossTraffic() { cout << "Crossing the road safely.\n"; }

int main() {
    if (foundFootbridge()) {
        useFootbridge();
    }
    else if (foundTunnel()) {
        useTunnel();
    }
    else if (!foundCrossing()) {
        walkAway();
    }
    else {
        if (trafficLightExists()) {
            string color = getTrafficLightColor();
            if (color == "Red") {
                cout << "Waiting for green light...\n";
                this_thread::sleep_for(chrono::seconds(3)); // simulate wait
                color = "Green";
            }
            if (color == "Green") {
                if (!isCarApproaching()) {
                    crossTraffic();
                } else {
                    cout << "Car approaching. Waiting...\n";
                }
            }
        }
        else {
            if (!isCarApproaching()) {
                crossTraffic();
            } else {
                cout << "Car approaching. Waiting...\n";
            }
        }
    }
    return 0;
}
