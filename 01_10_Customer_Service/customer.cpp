#include <iostream>
#include <string>
#include <vector>
#include <optional>
#include <functional>
#include <unordered_set>

enum class Severity { Low, Medium, High, Critical };
enum class CloseReason {
    Resolved, Redirected, Duplicate, SpamAbuse, OutOfScope, InfoTimeout,
    Unsupported, WarrantyExpired, CannotReproduce, CustomerUnreachable
};

struct Issue {
    // Intake
    std::string id;
    std::string customerName;
    std::string language = "en";
    bool consentGiven = true;
    bool suspectedSpam = false;
    bool duplicateOfKnown = false;
    bool inScope = true;
    bool warrantyValid = true;

    // Classification
    bool isInquiry = false;
    bool isSales = false;
    bool isTechnical = false;

    // Environment
    std::string product;
    std::string version;
    std::string platform;

    // Technical path signals
    bool canReproduce = false;
    bool isNewBug = false;      // if not new bug, treat as known issue
    bool fixImplemented = false;
    bool confirmFixedWithCustomer = false;

    // Ops
    Severity severity = Severity::Low;
    bool slaBreached = false;
    bool securityIncident = false;

    // Lifecycle
    bool moreInfoNeeded = false;
    int  infoRequestAttempts = 0;
    int  maxInfoAttempts = 2;

    // Output bookkeeping
    std::vector<std::string> auditTrail;
    std::optional<CloseReason> closedAs;
};

struct DecisionProvider {
    // Plug your own logic or UI here. Defaults use Issue flags.
    virtual ~DecisionProvider() = default;

    virtual bool isAbuseOrSpam(const Issue& i) { return i.suspectedSpam; }
    virtual bool isDuplicate(const Issue& i)   { return i.duplicateOfKnown; }
    virtual bool isInScope(const Issue& i)     { return i.inScope; }
    virtual bool needsLanguageRouting(const Issue& i) { return i.language != "en"; }
    virtual bool classifyInquiry(const Issue& i){ return i.isInquiry; }
    virtual bool classifySales(const Issue& i)  { return i.isSales; }
    virtual bool classifyTechnical(const Issue& i){ return i.isTechnical; }

    virtual bool canRepro(Issue& i)            { return i.canReproduce; }
    virtual bool isNewBug(Issue& i)            { return i.isNewBug; }
    virtual bool implementFix(Issue& i)        { return i.fixImplemented; }
    virtual bool confirmFixed(Issue& i)        { return i.confirmFixedWithCustomer; }

    virtual bool needsEscalation(const Issue& i){
        return i.slaBreached || i.severity >= Severity::High || i.securityIncident;
    }

    virtual bool hasValidWarranty(const Issue& i){ return i.warrantyValid; }
    virtual bool requestMoreInfo(Issue& i){
        i.moreInfoNeeded = true;
        i.infoRequestAttempts++;
        // Simulate customer not replying beyond threshold:
        return (i.infoRequestAttempts <= i.maxInfoAttempts);
    }
};

// Utility to push to audit trail
static void log(Issue& i, const std::string& msg) { i.auditTrail.push_back(msg); }

// The workflow engine with clearly named steps.
class CustomerSupportWorkflow {
public:
    explicit CustomerSupportWorkflow(DecisionProvider& d) : D(d) {}

    void run(Issue& issue) {
        intake(issue);
        if (issue.closedAs) return;

        triage(issue);
        if (issue.closedAs) return;

        if (issue.isInquiry) { handleInquiry(issue); return; }
        if (issue.isSales)   { handleSales(issue);   return; }
        if (issue.isTechnical) { handleTechnical(issue); return; }

        // Fallback: ask for details and re-triage once
        requestMoreInfoAndReroute(issue);
    }

private:
    DecisionProvider& D;

    void close(Issue& i, CloseReason reason, const std::string& msg) {
        i.closedAs = reason;
        log(i, "CLOSED: " + msg);
    }

    // 1) Intake & guardrails
    void intake(Issue& i) {
        log(i, "Intake: create ticket " + i.id);
        if (!i.consentGiven) { close(i, CloseReason::OutOfScope, "No consent"); return; }
        if (D.isAbuseOrSpam(i)) { close(i, CloseReason::SpamAbuse, "Spam/abuse"); return; }
        if (!D.isInScope(i)) { close(i, CloseReason::OutOfScope, "Out of scope"); return; }
        if (D.isDuplicate(i)) { close(i, CloseReason::Duplicate, "Duplicate of existing ticket"); return; }
        if (D.needsLanguageRouting(i)) { log(i, "Routed to language queue: " + i.language); }
    }

    // 2) Triage
    void triage(Issue& i) {
        log(i, "Triage: classify issue");
        if (!(i.isInquiry || i.isSales || i.isTechnical)) {
            log(i, "Insufficient classification; requesting details");
        }
    }

    // 3a) Inquiry/FAQ
    void handleInquiry(Issue& i) {
        answerQuestion(i);
        if (confirmResolution(i)) { collectFeedback(i); survey(i); close(i, CloseReason::Resolved, "Inquiry answered"); }
    }

    // 3b) Sales/Billing
    void handleSales(Issue& i) {
        redirectToSales(i);
        if (confirmResolution(i)) { collectFeedback(i); survey(i); close(i, CloseReason::Redirected, "Handled by Sales/Billing"); }
    }

    // 3c) Technical
    void handleTechnical(Issue& i) {
        contactTechnicalTeam(i);

        // Try to reproduce; if not, loop on info requests
        if (!D.canRepro(i)) {
            while (!D.canRepro(i)) {
                if (!D.requestMoreInfo(i)) { close(i, CloseReason::InfoTimeout, "No customer response"); return; }
                log(i, "Requested more info (attempt " + std::to_string(i.infoRequestAttempts) + ")");
                // In a real system, new info arrives; here we just document the loop.
                if (i.infoRequestAttempts >= i.maxInfoAttempts) break;
            }
            if (!D.canRepro(i)) { close(i, CloseReason::CannotReproduce, "Could not reproduce"); return; }
        }

        // Reproduced: is it a new bug?
        if (D.isNewBug(i)) {
            fileErrorReport(i);
            writeToErrorDB(i);
        } else {
            consultKnowledgeBase(i);
        }

        // Implement or apply workaround
        if (!D.hasValidWarranty(i)) {
            close(i, CloseReason::WarrantyExpired, "Warranty expired; provided alternatives"); return;
        }

        if (!applyFix(i)) {
            // Couldn’t fix immediately
            if (D.needsEscalation(i)) {
                escalate(i);
            } else {
                log(i, "Continuing analysis for next cycle");
            }
        }

        // Validate with customer
        if (confirmResolution(i)) {
            collectFeedback(i);
            survey(i);
            close(i, CloseReason::Resolved, "Technical issue fixed");
        } else {
            // Not fixed or customer unreachable
            if (!D.requestMoreInfo(i)) {
                close(i, CloseReason::CustomerUnreachable, "No confirmation from customer");
            } else {
                log(i, "Looping back to analysis with new info");
                // In a real loop, we would re-enter fix path.
            }
        }
    }

    // Concrete step methods (each logs their action)

    void answerQuestion(Issue& i) {
        log(i, "Provided FAQ/answer and links");
    }

    void redirectToSales(Issue& i) {
        log(i, "Redirected to Sales/Billing support queue");
    }

    void contactTechnicalTeam(Issue& i) {
        log(i, "Contacted Technical Team; starting investigation");
    }

    void fileErrorReport(Issue& i) {
        log(i, "Filed new bug report");
    }

    void writeToErrorDB(Issue& i) {
        log(i, "Persisted error report in Error DB");
    }

    void consultKnowledgeBase(Issue& i) {
        log(i, "Looked up known issue and workaround");
    }

    bool applyFix(Issue& i) {
        log(i, "Performed error analysis and implemented fix/workaround");
        return D.implementFix(i);
    }

    bool confirmResolution(Issue& i) {
        log(i, "Asked customer to confirm resolution");
        return D.confirmFixed(i);
    }

    void collectFeedback(Issue& i) {
        log(i, "Collected feedback (CSAT/NPS)");
    }

    void survey(Issue& i) {
        log(i, "Sent postcase survey");
    }

    void escalate(Issue& i) {
        if (i.securityIncident) {
            log(i, "Escalated to Security Incident Response");
        } else {
            log(i, "Escalated to Tier3/Engineering due to severity/SLA");
        }
    }

    void requestMoreInfoAndReroute(Issue& i) {
        if (!D.requestMoreInfo(i)) {
            close(i, CloseReason::InfoTimeout, "No information to classify"); return;
        }
        log(i, "Received additional info; re‑triage would occur here");
    }
};

// ---- Example usage / simple test harness ----
struct SimpleDecisions : public DecisionProvider { };

int main() {
    SimpleDecisions decisions;

    Issue ex{
        .id = "TCK-1001",
        .customerName = "Alex",
        .language = "en",
        .consentGiven = true,
        .suspectedSpam = false,
        .duplicateOfKnown = false,
        .inScope = true,
        .warrantyValid = true,
        .isInquiry = false,
        .isSales = false,
        .isTechnical = true,
        .product = "WidgetX",
        .version = "2.4.1",
        .platform = "Windows",
        .canReproduce = true,
        .isNewBug = true,
        .fixImplemented = true,
        .confirmFixedWithCustomer = true,
        .severity = Severity::High,
        .slaBreached = false,
        .securityIncident = false
    };

    CustomerSupportWorkflow engine(decisions);
    engine.run(ex);

    std::cout << "=== Audit trail for " << ex.id << " ===\n";
    for (const auto& e : ex.auditTrail) std::cout << " - " << e << "\n";
    std::cout << "Closed as: "
              << (ex.closedAs ? static_cast<int>(*ex.closedAs) : -1)
              << std::endl;

    return 0;
}