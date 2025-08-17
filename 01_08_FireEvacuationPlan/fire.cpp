#include <iostream>
#include <string>

using namespace std;

bool alarmTriggered = false;
bool inBuilding = false;
bool doorHot = false;
bool smokeSeeping = false;
bool strongSmoke = false;
bool escapedBuilding = false;
bool reachedBalcony = false;

void contactFireDepartment() {
    cout << "Contacting fire department...\n";
    cout << "Provide location, trapped people count, and hazards.\n";
    cout << "If phone unavailable, use flashlight/wave cloth at window.\n";
}

void waitForRescue() {
    cout << "Waiting for rescue...\n";
    cout << "Signal periodically, stay calm, conserve oxygen.\n";
}

void smokeEscapeFlow() {
    cout << "Sealing all cracks with wet towels.\n";
    contactFireDepartment();
    cout << "Waving from windows to identify survivors.\n";
    cout << "Finding safe room and closing doors.\n";
    waitForRescue();
}

void balconyEscapeFlow() {
    cout << "Going upstairs towards balcony...\n";
    if (reachedBalcony) {
        waitForRescue();
    } else {
        cout << "Balcony blocked! Returning to smoke escape flow.\n";
        smokeEscapeFlow();
    }
}

void checkDoorAndExit() {
    if (doorHot || smokeSeeping) {
        cout << "Door is hot or smoke is seeping in.\n";
        smokeEscapeFlow();
    } else {
        if (!strongSmoke) {
            cout << "Exiting building via safe route...\n";
            escapedBuilding = true;
            cout << "Escaped building successfully!\n";
        } else {
            cout << "Strong smoke detected! Switching to smoke escape flow.\n";
            smokeEscapeFlow();
        }
    }
}

void inBuildingResponse() {
    cout << "Pushing fire alarm trigger.\n";
    cout << "Bringing keys, wallet, phone, wet towels.\n";
    checkDoorAndExit();
}

void detectFireOrSmoke(bool youSeeFire, bool someoneElseSeesFire, bool smokeDetectorTriggered) {
    if (youSeeFire || someoneElseSeesFire) {
        if (inBuilding) {
            inBuildingResponse();
        } else {
            contactFireDepartment();
        }
    }

    if (smokeDetectorTriggered) {
        alarmTriggered = true;
        cout << "Smoke detector triggers alarm.\n";
        inBuildingResponse();
    }
}

int main() {
    inBuilding = true;
    doorHot = false;
    smokeSeeping = false;
    strongSmoke = false;
    reachedBalcony = true;

    cout << "Fire Evacuation Simulation Started\n";
    detectFireOrSmoke(true, false, false);
    cout << "Simulation Ended\n";

    return 0;
}
