#include <iostream>
#include <string>
#include <unordered_map>
using namespace std;

struct User {
    string username;
    string password;
    bool authorized;
    int attempts;
    bool locked;
};

unordered_map<string, User> users = {
    {"alice", {"alice", "alice123", true, 0, false}},
    {"bob",   {"bob", "bob@123", false, 0, false}}
};

bool isLocked(User& user) {
    return user.locked;
}

bool validateCredentials(User& user, const string& password) {
    return user.password == password;
}

void lockAccount(User& user) {
    user.locked = true;
    cout << "Account locked due to 5 failed attempts.\n";
}

void alertUser(const string& msg) {
    cout << "ALERT: " << msg << endl;
}

void grantAccess(User& user) {
    cout << "Access granted to " << user.username << endl;
}

void loginSystem(string username, string password) {
    if (users.find(username) == users.end()) {
        cout << "User not found.\n";
        return;
    }

    User& user = users[username];

    // Step 1: Check if already locked
    if (isLocked(user)) {
        alertUser("Account is locked.");
        return;
    }

    // Step 2: Validate credentials
    if (!validateCredentials(user, password)) {
        user.attempts++;
        alertUser("Invalid credentials. Attempt " + to_string(user.attempts));
        if (user.attempts >= 5) {
            lockAccount(user);
        }
        return;
    }

    // Step 3: Reset attempts after successful login
    user.attempts = 0;

    // Step 4: Authorization check
    if (!user.authorized) {
        alertUser("Account not authorized.");
        return;
    }

    // Step 5: Grant access
    grantAccess(user);
}

int main() {
    // Simulating login attempts
    loginSystem("alice", "wrongpass");
    loginSystem("alice", "wrongpass");
    loginSystem("alice", "alice123"); // success
    loginSystem("bob", "bob@123");    // unauthorized
    return 0;
}
