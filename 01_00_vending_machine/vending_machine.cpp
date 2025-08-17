#include <iostream>
using namespace std;

// Ingredient stock
int water = 1000;     // ml
int milk = 800;       // ml
int coffeePowder = 500;  // g
int chocolatePowder = 300; // g

// Check ingredient availability
bool checkStock(int reqWater, int reqMilk, int reqCoffee, int reqChocolate) {
  if (water < reqWater) { cout << "Error: Not enough water.\n"; return false; }
  if (milk < reqMilk) { cout << "Error: Not enough milk.\n"; return false; }
  if (coffeePowder < reqCoffee) { cout << "Error: Not enough coffee powder.\n"; return false; }
  if (chocolatePowder < reqChocolate) { cout << "Error: Not enough chocolate powder.\n"; return false; }
  return true;
}

// Deduct ingredients
void useIngredients(int reqWater, int reqMilk, int reqCoffee, int reqChocolate) {
  water -= reqWater; milk -= reqMilk; coffeePowder -= reqCoffee; chocolatePowder -= reqChocolate;
}

// Coffee steps
void addChocolatePowder() { cout << "Adding chocolate powder...\n"; }
void addFrothedMilk() { cout << "Adding frothed milk...\n"; }
void addHotCoffee() { cout << "Adding hot coffee...\n"; }

// Prepare drink using switch-case
void prepareDrink(int choice) {
  switch (choice) {
    case 1: // Espresso
      if (checkStock(50, 0, 15, 0)) {
        addHotCoffee();
        useIngredients(50, 0, 15, 0);
        cout << "Your Espresso is ready!\n";
      }
      break;

    case 2: // Latte
      if (checkStock(50, 150, 15, 0)) {
        addFrothedMilk();
        addHotCoffee();
        useIngredients(50, 150, 15, 0);
        cout << "Your Latte is ready!\n";
      }
      break;

    case 3: // Mocha
      if (checkStock(50, 100, 15, 20)) {
        addChocolatePowder();
        addFrothedMilk();
        addHotCoffee();
        useIngredients(50, 100, 15, 20);
        cout << "Your Mocha is ready!\n";
      }
      break;

    default:
      cout << "Invalid selection. Please try again.\n";
  }
}

int main() {
  char startChoice;
  cout << "Press 'P' to power on the coffee machine: ";
  cin >> startChoice;

  if (startChoice != 'P' && startChoice != 'p') {
    cout << "Machine remains OFF.\n";
    return 0;
  }

  cout << "Coffee Machine Powered ON!\n";
  bool powerOn = true;

  while (powerOn) {
    cout << "\n---- MENU ----\n";
    cout << "1. Espresso\n2. Latte\n3. Mocha\n5. Power Off\n";
    cout << "Select option: ";
    int option;
    cin >> option;

    if (option == 5) {
      cout << "Powering off...\n";
      powerOn = false;
    } else {
      prepareDrink(option);
    }
  }

  cout << "Machine turned OFF.\n";
  return 0;
}
