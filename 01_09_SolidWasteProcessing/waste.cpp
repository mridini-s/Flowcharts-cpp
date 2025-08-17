#include <iostream>
#include <string>

using namespace std;

class WasteManagement {
public:
    void processWaste() {
        string type;
        cout << "\n--- Waste Management System ---\n";
        cout << "Enter type of waste (organic / non-organic): ";
        cin >> type;

        if (type == "organic" || type == "Organic") {
            string energy;
            cout << "Does it have high energy content? (yes/no): ";
            cin >> energy;
            if (energy == "yes" || energy == "Yes") {
                cout << "Waste converted to Bio-fuel.\n";
            } else {
                cout << "Waste converted to Organic Fertilizer.\n";
            }
        } 
        else {
            string reusable;
            cout << "Is the waste reusable? (yes/no): ";
            cin >> reusable;

            if (reusable == "yes" || reusable == "Yes") {
                cout << "Waste reused for other applications.\n";
            } else {
                string recyclable;
                cout << "Is the waste recyclable? (yes/no): ";
                cin >> recyclable;

                if (recyclable == "yes" || recyclable == "Yes") {
                    cout << "Waste recycled for other applications.\n";
                } else {
                    cout << "Waste sent to Landfill.\n";
                }
            }
        }
    }
};

int main() {
    WasteManagement wm;
    wm.processWaste();
    return 0;
}
