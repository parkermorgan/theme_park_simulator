//
//  main.cpp
//  theme-park-simulator
//
//  Created by Parker Morgan on 10/9/25.
//
#include <iostream>
#include <format>
#include <list>
using namespace std;

class Ride {
public:
    string name;
    string type;
    int ticketAmount;
    
    Ride(string rideName, string rideType, int amount) {
        name = rideName;
        type = rideType;
        ticketAmount = amount;
    }
    
    void display() {
        cout << format("{}: {}, Tickets required: {}", type, name, ticketAmount);
    }
};

int main() {
    int choice = 1;
    int tickets = 100;
    
    list<Ride> rideList;
    
    rideList.push_back(Ride("Big Thunder", "Thrill", 15));
    rideList.push_back(Ride("Snow Whilte", "Dark Ride", 10));
    rideList.push_back(Ride("Jungle Cruise", "Water Ride", 5));
    
    cout << format("Welcome to the Theme Park Simulator!\n\n");
    
    while (choice != 0 && tickets > 0) {
        cout << format("You have {} Tickets.\n\nSelect an option:\n", tickets);
        cout << "1. Ride Rides\n2. Buy Food\n3. Buy Merchandise\n0. Quit\nEnter your choice here: ";
        cin >> choice;

        if (choice == 1) {
            cout << "\nAvailable Rides:\n\n";
            int rideChoice;
            int index = 1;
            for (Ride& r : rideList) {
                cout << format("{}. ", index);
                r.display();
                cout << "\n";
            }
            cout << "\nSelect a ride: ";
            cin >> rideChoice;
            
            if (rideChoice > 0 && rideChoice <= rideList.size()) {
                auto it = rideList.begin();
                advance(it, rideChoice - 1);
                Ride& chosen = *it;
                tickets -= chosen.ticketAmount;
            }
            
            
            
            
        } else if (choice == 2) {
            cout << "\nYou chose to buy food!\n\n";
        } else if (choice == 3) {
            cout << "\nYou chose to buy merchandise!\n\n";
        } else if (choice != 0) {
            cout << "\nInvalid input. Please try again.\n\n";
        }
    }
    
    cout << format("You have {} Tickets.\n\nHave a magical day!\n", tickets);
    return 0;
}
