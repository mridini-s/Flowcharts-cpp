#include <iostream>
#include <string>
#include <chrono>
#include <thread>
using namespace std;

bool askYesNo(string question) {
    char choice;
    cout << question << " (y/n): ";
    cin >> choice;
    return (choice == 'y' || choice == 'Y');
}

void ringAlarm() {
    cout << "Alarm rings loudly!\n";
}

void snooze(int minutes) {
    cout << "Snoozing for " << minutes << " minutes...\n";
    this_thread::sleep_for(chrono::seconds(1)); // Simulate wait
}

bool readyToWake() {
    return askYesNo("Are you ready to wake up?");
}

bool willBeLate() {
    return askYesNo("Will you be late if you keep sleeping?");
}

void leaveBed() {
    cout << "You get up from bed.\n";
}

void turnOffAlarm() {
    cout << "Alarm turned off.\n";
}

void wakeUpProcess() {
    int snoozeCount = 0;
    const int maxSnoozes = 3;

    // Edge case: woke up before alarm
    if (askYesNo("Did you wake up before alarm?")) {
        cout << "Good! No need to snooze.\n";
        leaveBed();
        turnOffAlarm();
        return;
    }

    // Alarm loop
    while (true) {
        ringAlarm();

        if (readyToWake()) {
            leaveBed();
            turnOffAlarm();
            break;
        }

        if (willBeLate()) {
            cout << "You’ll be late!\n";
            leaveBed();
            turnOffAlarm();
            break;
        }

        if (snoozeCount >= maxSnoozes) {
            cout << "Max snoozes reached! You must wake up now.\n";
            leaveBed();
            turnOffAlarm();
            break;
        }

        snoozeCount++;
        snooze(5);
    }
}

int main() {
    wakeUpProcess();
    return 0;
}
