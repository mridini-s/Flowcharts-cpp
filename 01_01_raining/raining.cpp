#include <iostream>
#include <string>
using namespace std;

// Function to check if raining
string checkWeather() {
    string weather;
    cout << "Is it raining? (yes/no/unknown): ";
    cin >> weather;
    return weather;
}

// Function to decide on light rain
bool handleLightRain() {
    char choice;
    cout << "It's a light drizzle. Do you still want umbrella? (y/n): ";
    cin >> choice;
    return (choice == 'y' || choice == 'Y');
}

// Function to check if umbrella is found
bool findUmbrella() {
    string found;
    cout << "Did you find an umbrella? (yes/no): ";
    cin >> found;
    return (found == "yes");
}

// Function to check umbrella condition
bool isUmbrellaFunctional() {
    string condition;
    cout << "Is the umbrella functional? (yes/no): ";
    cin >> condition;
    return (condition == "yes");
}

// Function to check for raincoat
bool haveRaincoat() {
    string raincoat;
    cout << "Do you have a raincoat? (yes/no): ";
    cin >> raincoat;
    return (raincoat == "yes");
}

void decideUmbrella() {
    string weather = checkWeather();

    if (weather == "no") {
        cout << "No rain. Don't bring umbrella.\n";
        return;
    } else if (weather == "unknown") {
        cout << "Weather data unavailable. Decide manually.\n";
        return;
    }

    string intensity;
    cout << "Rain intensity (light/heavy): ";
    cin >> intensity;

    if (intensity == "light" && !handleLightRain()) {
        cout << "Skipping umbrella for light rain.\n";
        return;
    }

    if (!findUmbrella()) {
        if (haveRaincoat()) {
            cout << "Bring raincoat.\n";
        } else {
            cout << "No umbrella or raincoat found. You will get wet!\n";
        }
        return;
    }

    if (!isUmbrellaFunctional()) {
        if (haveRaincoat()) {
            cout << "Bring raincoat.\n";
        } else {
            cout << "No working umbrella or raincoat. You will get wet!\n";
        }
    } else {
        cout << "Bring umbrella.\n";
    }
}

int main() {
    decideUmbrella();
    return 0;
}
