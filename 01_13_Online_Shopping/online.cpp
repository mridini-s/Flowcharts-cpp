#include <iostream>
#include <vector>
#include <string>

struct Item {
    std::string name;
    bool inWarehouse;
};

class OrderWorkflow {
public:
    void run(const std::vector<Item>& items) {
        orderPlaced();

        for (const auto& item : items) {
            processItem(item);
        }

        sendWarehouseGoodsToCustomer();
        customerCollectsGoods();
        sellerConfirmDelivery();
        endOrderProcess();
    }

private:
    // Core steps
    void orderPlaced() {
        log("Order placed.");
    }

    void processItem(const Item& item) {
        log("Processing item: " + item.name);
        if (isInWarehouse(item)) {
            packWithOtherOrders(item);
        } else {
            contactSellerToShip(item);
            sellerShipToCustomer(item);
        }
    }

    bool isInWarehouse(const Item& item) {
        return item.inWarehouse;
    }

    void packWithOtherOrders(const Item& item) {
        log("Packed item with warehouse orders: " + item.name);
    }

    void contactSellerToShip(const Item& item) {
        log("Contacted seller to ship item: " + item.name);
    }

    void sellerShipToCustomer(const Item& item) {
        log("Seller shipped item directly to customer: " + item.name);
    }

    void sendWarehouseGoodsToCustomer() {
        log("Warehouse shipped packed goods to customer.");
    }

    void customerCollectsGoods() {
        log("Customer received goods.");
    }

    void sellerConfirmDelivery() {
        log("Seller confirmed customer received order.");
    }

    void endOrderProcess() {
        log("Order process ended.");
    }

    void log(const std::string& msg) {
        std::cout << msg << std::endl;
    }
};

// Example usage
int main() {
    std::vector<Item> order = {
        {"Laptop", true},   // In warehouse
        {"Phone Case", false}, // Seller ships
        {"Keyboard", true}
    };

    OrderWorkflow workflow;
    workflow.run(order);

    return 0;
}