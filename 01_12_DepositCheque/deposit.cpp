#include <iostream>
#include <string>

class ChequeDepositWorkflow {
public:
    void run() {
        if (!insertCard()) return;
        if (!enterBankAccountNumber()) return;
        if (!validateReceiverAccount()) return;

        if (!insertCheque()) return;
        if (!readChequeValue()) return;
        if (!validateSenderAccount()) return;

        if (checkClearingPeriod()) {
            transferToReceiver();
        } else {
            if (!senderReview()) {
                invalidTransaction();
                return;
            }
            if (!senderAuthorize()) {
                invalidTransaction();
                return;
            }
            transferToReceiver();
        }

        endTransaction();
    }

private:
    // ---- Core steps ----
    bool insertCard() {
        log("Card inserted.");
        // Edge case: expired/lost card
        return true;
    }

    bool enterBankAccountNumber() {
        log("Entered receiver bank account number.");
        // Edge case: invalid entry
        return true;
    }

    bool validateReceiverAccount() {
        log("Receiver account validated.");
        // Edge case: account closed/blacklisted
        return true;
    }

    bool insertCheque() {
        log("Cheque inserted.");
        // Edge case: unreadable/damaged
        return true;
    }

    bool readChequeValue() {
        log("Cheque value read successfully.");
        // Edge case: mismatch between written vs. numeric
        return true;
    }

    bool validateSenderAccount() {
        log("Sender account validated.");
        // Edge case: insufficient funds, frozen, fraud
        return true;
    }

    bool checkClearingPeriod() {
        log("Checking clearing period (7 days).");
        return false; // simulate <7 days
    }

    bool senderReview() {
        log("Sender review passed.");
        return true; // simulate approval
    }

    bool senderAuthorize() {
        log("Sender authorized transfer.");
        return true;
    }

    void transferToReceiver() {
        log("Money transferred to receiver.");
    }

    void invalidTransaction() {
        log("Invalid transaction. Aborted.");
    }

    void endTransaction() {
        log("Transaction ended.");
    }

    void log(const std::string &msg) {
        std::cout << msg << std::endl;
    }
};

int main() {
    ChequeDepositWorkflow workflow;
    workflow.run();
    return 0;
}