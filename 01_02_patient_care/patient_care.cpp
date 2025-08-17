#include <iostream>
#include <string>
using namespace std;

bool askYesNo(string question) {
    bool answer;
    cout << question << " (1=Yes, 0=No): ";
    cin >> answer;
    return answer;
}

bool waitForAvailability(string resource) {
    char choice;
    cout << resource << " not available. Wait? (y/n): ";
    cin >> choice;
    return (choice == 'y' || choice == 'Y');
}

void registerPatient() {
    cout << "Registering patient...\n";
}

bool nurseAvailable() {
    return askYesNo("Is nurse available?");
}

bool registrationStage() {
    if (!askYesNo("Is patient registered?"))
        registerPatient();

    if (!nurseAvailable()) {
        if (!waitForAvailability("Nurse")) {
            cout << "Patient leaves due to no nurse.\n";
            return false;
        }
    }
    cout << "Recording health condition...\n";
    return true;
}

bool doctorAvailable() {
    return askYesNo("Is doctor available?");
}

void assignDoctor() {
    cout << "Assigning patient to doctor...\n";
}

bool diagnosisStage() {
    if (!doctorAvailable()) {
        if (!waitForAvailability("Doctor")) {
            cout << "Patient leaves due to no doctor.\n";
            return false;
        }
    }
    assignDoctor();
    return true;
}

void arrangeAppointment() {
    cout << "Follow-up appointment arranged.\n";
}

void addToWaitlist() {
    cout << "No slots available, added to waitlist.\n";
}

void givePrescription() {
    cout << "Prescription given to patient.\n";
}

void informShortage() {
    cout << "Medicine not in stock.\n";
}

void postConsultationStage() {
    if (askYesNo("Need follow-up?")) {
        if (askYesNo("Slots available?"))
            arrangeAppointment();
        else
            addToWaitlist();
    }

    if (askYesNo("Need medication?")) {
        if (askYesNo("Medicine in stock?"))
            givePrescription();
        else
            informShortage();
    }

    cout << "Patient leaves.\n";
}

void processPatient() {
    if (!registrationStage()) return;
    if (!diagnosisStage()) return;
    postConsultationStage();
}

int main() {
    processPatient();
    return 0;
}
