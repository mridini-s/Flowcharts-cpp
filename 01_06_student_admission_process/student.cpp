#include <iostream>
#include <fstream>
#include <vector>
#include <string>
using namespace std;

class Candidate {
private:
    string name;
    bool documentsVerified;
    bool eligible;
    bool testPassed;
    bool seatAvailable;
    string admissionStatus;
    int rollNumber;

public:
    Candidate(string n, bool doc, bool elig, bool test, bool seat)
        : name(n), documentsVerified(doc), eligible(elig),
          testPassed(test), seatAvailable(seat),
          admissionStatus("Pending"), rollNumber(-1) {}

    bool verifyDocuments() { return documentsVerified; }
    bool checkEligibility() { return eligible; }
    bool conductTest() { return testPassed; }
    bool checkSeatAvailability() { return seatAvailable; }

    void assignRollNumber(int r) { rollNumber = r; }
    void setStatus(string status) { admissionStatus = status; }

    string getName() const { return name; }
    string getStatus() const { return admissionStatus; }
    int getRollNumber() const { return rollNumber; }

    void saveToCSV(const string& filename) {
        ofstream file(filename, ios::app);
        if (!file.is_open()) {
            cerr << "Error opening file!" << endl;
            return;
        }
        file << name << ","
             << (documentsVerified ? "Yes" : "No") << ","
             << (eligible ? "Yes" : "No") << ","
             << (testPassed ? "Pass" : "Fail") << ","
             << (seatAvailable ? "Yes" : "No") << ","
             << admissionStatus << ","
             << (rollNumber == -1 ? "NA" : to_string(rollNumber))
             << "\n";
        file.close();
    }
};

void admissionProcess(vector<Candidate>& candidates, const string& filename) {
    ofstream file(filename); // create/overwrite with header
    file << "Name,DocumentsVerified,Eligible,TestResult,SeatAllotted,AdmissionStatus,RollNumber\n";
    file.close();

    int rollCounter = 1000;

    for (auto& c : candidates) {
        cout << "\nProcessing candidate: " << c.getName() << endl;

        if (!c.verifyDocuments()) {
            c.setStatus("Rejected (Invalid Documents)");
            c.saveToCSV(filename);
            continue;
        }

        if (!c.checkEligibility()) {
            c.setStatus("Rejected (Not Eligible)");
            c.saveToCSV(filename);
            continue;
        }

        if (!c.conductTest()) {
            c.setStatus("Rejected (Test Fail)");
            c.saveToCSV(filename);
            continue;
        }

        if (!c.checkSeatAvailability()) {
            c.setStatus("Waitlisted (No Seats)");
            c.saveToCSV(filename);
            continue;
        }

        // If passed all
        c.assignRollNumber(rollCounter++);
        c.setStatus("Admitted");
        c.saveToCSV(filename);
    }

    cout << "\nAdmission process completed. Check " << filename << " for details.\n";
}

int main() {
    vector<Candidate> candidates = {
        Candidate("Alice", true, true, true, true),     // Successful
        Candidate("Bob", false, true, true, true),      // Invalid Documents
        Candidate("Charlie", true, false, true, true),  // Not Eligible
        Candidate("David", true, true, false, true),    // Test Fail
        Candidate("Eva", true, true, true, false)       // No Seats
    };

    admissionProcess(candidates, "admissions.csv");

    return 0;
}
