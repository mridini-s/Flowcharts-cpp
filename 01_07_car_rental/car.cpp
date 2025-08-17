#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
using namespace std;

vector<vector<string>> readCSV(const string& filename) {
    vector<vector<string>> data;
    ifstream file(filename);
    string line;

    while (getline(file, line)) {
        vector<string> row;
        string cell;
        stringstream ss(line);
        while (getline(ss, cell, ',')) {
            row.push_back(cell);
        }
        data.push_back(row);
    }
    return data;
}

void writeCSV(const string& filename, const vector<vector<string>>& data) {
    ofstream file(filename);
    for (auto& row : data) {
        for (size_t i = 0; i < row.size(); i++) {
            file << row[i];
            if (i < row.size() - 1) file << ",";
        }
        file << "\n";
    }
}

class User {
private:
    string username, password;
public:
    User(string u, string p) : username(u), password(p) {}

    static bool registerUser(const string& u, const string& p, const string& filename) {
        vector<vector<string>> users = readCSV(filename);
        for (auto& row : users) {
            if (row[0] == u) {
                cout << "User already exists!\n";
                return false;
            }
        }
        users.push_back({u, p});
        writeCSV(filename, users);
        cout << "User registered successfully!\n";
        return true;
    }

    static bool login(const string& u, const string& p, const string& filename) {
        vector<vector<string>> users = readCSV(filename);
        for (auto& row : users) {
            if (row[0] == u && row[1] == p) {
                cout << "Login successful! Welcome " << u << "\n";
                return true;
            }
        }
        cout << "Invalid username or password!\n";
        return false;
    }

    static void resetPassword(const string& u, const string& newPass, const string& filename) {
        vector<vector<string>> users = readCSV(filename);
        for (auto& row : users) {
            if (row[0] == u) {
                row[1] = newPass;
                writeCSV(filename, users);
                cout << "Password reset successful!\n";
                return;
            }
        }
        cout << "User not found!\n";
    }
};

class Admin {
private:
    string adminPass = "admin123"; // for demo
public:
    bool login(const string& pass) {
        if (pass == adminPass) {
            cout << "Admin login successful!\n";
            return true;
        }
        cout << "Invalid admin password!\n";
        return false;
    }

    void addCar(const string& car, const string& filename) {
        vector<vector<string>> cars = readCSV(filename);
        cars.push_back({car});
        writeCSV(filename, cars);
        cout << "Car added successfully!\n";
    }

    void viewCars(const string& filename) {
        vector<vector<string>> cars = readCSV(filename);
        cout << "\nCar Library\n";
        for (auto& row : cars) {
            cout << row[0] << endl;
        }
    }
};

void searchCar(const string& keyword, const string& filename) {
    vector<vector<string>> cars = readCSV(filename);
    bool found = false;
    for (auto& row : cars) {
        if (row[0].find(keyword) != string::npos) {
            cout << "Car Found: " << row[0] << endl;
            found = true;
        }
    }
    if (!found) cout << "No car matched your search.\n";
}

int main() {
    string usersFile = "users.csv";
    string carsFile = "cars.csv";

    // Initialize files with headers if empty
    ofstream u(usersFile, ios::app), c(carsFile, ios::app);
    u.close(); c.close();

    int choice;
    cout << "\nCar Rental System:\n";
    cout << "1. Admin\n2. User\nChoose: ";
    cin >> choice;

    if (choice == 1) {
        // Admin flow
        string pass;
        cout << "Enter admin password: ";
        cin >> pass;

        Admin admin;
        if (admin.login(pass)) {
            int adminChoice;
            cout << "\n1. Add Car\n2. View Cars\n3. Logout\nChoose: ";
            cin >> adminChoice;

            if (adminChoice == 1) {
                string car;
                cout << "Enter car name: ";
                cin >> car;
                admin.addCar(car, carsFile);
            } else if (adminChoice == 2) {
                admin.viewCars(carsFile);
            } else {
                cout << "Logging out...\n";
            }
        }
    }
    else if (choice == 2) {
        // User flow
        int userChoice;
        cout << "\n1. Register\n2. Login\n3. Forgot Password\nChoose: ";
        cin >> userChoice;

        if (userChoice == 1) {
            string u, p;
            cout << "Enter username: "; cin >> u;
            cout << "Enter password: "; cin >> p;
            User::registerUser(u, p, usersFile);
        }
        else if (userChoice == 2) {
            string u, p;
            cout << "Enter username: "; cin >> u;
            cout << "Enter password: "; cin >> p;
            if (User::login(u, p, usersFile)) {
                int act;
                cout << "\n1. Search Car\n2. Logout\nChoose: ";
                cin >> act;
                if (act == 1) {
                    string keyword;
                    cout << "Enter car name to search: ";
                    cin >> keyword;
                    searchCar(keyword, carsFile);
                }
            }
        }
        else if (userChoice == 3) {
            string u, newPass;
            cout << "Enter username: "; cin >> u;
            cout << "Enter new password: "; cin >> newPass;
            User::resetPassword(u, newPass, usersFile);
        }
    }
    else {
        cout << "Invalid choice.\n";
    }

    return 0;
}
