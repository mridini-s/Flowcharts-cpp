#include <iostream>
using namespace std;

class ComputerDiagnosis {
public:
    void run() {
        startDiagnosis();

        if (isComputerOn()) {
            if (hasErrorMessage()) {
                performDiagnosis();
            } else {
                goodCondition();
            }
        } else {
            if (isPowerLightOn()) {
                findSpecialist();
            } else {
                if (isPowerPluggedIn()) {
                    findSpecialist();
                } else {
                    plugPowerToWall();
                }
            }
        }

        endDiagnosis();
    }

private:
    void startDiagnosis() { log("Starting computer diagnosis..."); }
    bool isComputerOn() { return false; }  // simulate: computer not on
    bool hasErrorMessage() { return true; } // simulate: error appears
    bool isPowerLightOn() { return false; }
    bool isPowerPluggedIn() { return false; }

    void performDiagnosis() { log("Performing software/hardware diagnosis..."); }
    void goodCondition() { log("Computer is in good condition."); }
    void findSpecialist() { log("Please contact a specialist for repair."); }
    void plugPowerToWall() { log("Plugging the computer into the wall."); }
    void endDiagnosis() { log("Diagnosis finished."); }

    void log(string msg) { cout << msg << endl; }
};

int main() {
    ComputerDiagnosis diag;
    diag.run();
    return 0;
}