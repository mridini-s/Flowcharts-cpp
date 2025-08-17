#include <iostream>
#include <fstream>
#include <string>
#include <vector>
using namespace std;

bool isCardValid(const string& cardNumber) {
    return !cardNumber.empty() && cardNumber.size() == 16; // simple check
}

bool hasSufficientFunds(double balance, double amount) {
    return balance >= amount;
}

bool isAccountValid(const string& accountStatus) {
    return accountStatus == "ACTIVE";
}

void updateDatabase(const string& cardNumber, double amount) {
    ofstream db("customer_db.csv", ios::app); // append to CSV
    db << cardNumber << "," << amount << "\n";
    db.close();
}

void generateStatement(const string& cardNumber) {
    cout << "Statement generated for card: " << cardNumber
         << " (End of cycle)\n";
}

void processTransaction(string cardNumber, double balance,
                        string accountStatus, double purchaseAmount) {
    cout << "Order placed by client...\n";
    cout << "Payment verified by card network...\n";

    // Step 1: Card validation
    if (!isCardValid(cardNumber)) {
        cout << "Transaction failed: Invalid card.\n";
        return;
    }

    // Step 2: Funds check
    if (!hasSufficientFunds(balance, purchaseAmount)) {
        cout << "Transaction failed: Insufficient funds.\n";
        return;
    }

    // Step 3: Bank verification
    if (!isAccountValid(accountStatus)) {
        cout << "Transaction failed: Invalid account.\n";
        return;
    }

    // Step 4: Transaction complete
    cout << "Transaction successful!\n";
    updateDatabase(cardNumber, purchaseAmount);

    // Step 5: End of cycle statement
    generateStatement(cardNumber);
}

int main() {
    string cardNumber = "1234567890123456";
    double balance = 5000.0;
    string accountStatus = "ACTIVE";
    double purchaseAmount = 1200.0;

    processTransaction(cardNumber, balance, accountStatus, purchaseAmount);

    return 0;
}