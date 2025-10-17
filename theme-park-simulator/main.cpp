//
//  main.cpp
//  theme-park-simulator
//
//  Created by Parker Morgan on 10/9/25.
//
#include <iostream>
#include <format>
#include <list>
#include <chrono>

using namespace std;
using namespace chrono;

// CLASS SECTION --------------------------------------------------------------------
// Future Improvements: Create unique class that can hold all types of objects, with built-in functions for displaying the list.

// Ride class to build different rides.
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

// Food class to build different food products.
class Food {
public:
    string name;
    int ticketAmount;
    
    Food(string foodName, int amount) {
        name = foodName;
        ticketAmount = amount;
    }
    
    void Display() {
        cout << format("{}: Tickets required: {}", name, ticketAmount);
    }
};

// Merchandise class.
class Merch {
public:
    string name;
    int ticketAmount;
    
    Merch(string merchName, int amount) {
        name = merchName;
        ticketAmount = amount;
    }
    
    void Display() {
        cout << format("{}: Price: {} tickets.", name, ticketAmount);
    }
};



// END CLASS SECTION ----------------------------------------------------------------

// Final ticket cost calculator function.
int calculateFinalCost(int baseCost, int discount) {
    return max(0, baseCost - discount);
}

int main() {
    // Establish day of the week for discount functionality.
    auto today = floor<days>(system_clock::now());
    weekday wd{today};

    int dayNum = wd.c_encoding();
    
    // Add discount variables.
    int thrillDiscount = 0;
    int darkDiscount = 0;
    int waterDiscount = 0;
    
    int choice = 1;
    int tickets = 100;
    
    // Variables to measure user choice.
    int foodCount = 0;
    int choiceCount = 0;
    int thrillCount = 0;
    int nonThrillCount = 0;
    
    // Establish lists.
    list<Ride> rideList;
    list<Food> foodList;
    list<Merch> merchList;
    
    // Add rides to list.
    rideList.push_back(Ride("Big Thunder", "Thrill", 12));
    rideList.push_back(Ride("Snow White", "Dark Ride", 7));
    rideList.push_back(Ride("Jungle Cruise", "Water Ride", 5));
    
    
    // Add food to list.
    foodList.push_back(Food("Churro", 3));
    foodList.push_back(Food("Corn Dog", 5));
    foodList.push_back(Food("Soda", 2));

    // Add merch to list.
    merchList.push_back(Merch("Spirit Jersey", 10));
    merchList.push_back(Merch("Baseball Cap", 5));
    merchList.push_back(Merch("Keychain", 2));
    
    cout << format("Welcome to the Theme Park Simulator!\n\n");
    cout << ("Here are the following discount days:\n"
             "Mon/Wed/Fri: 3 tickets off of Dark Rides\n"
             "Tue/Thur: 2 tickets off of Water Rides\n"
             "Sat/Sun: 5 tickets off of Thrill Rides\n");
    
    string dayOfWeek;
    switch (dayNum) {
        case 1: dayOfWeek = "Monday"; break;
        case 2: dayOfWeek = "Tuesday"; break;
        case 3: dayOfWeek = "Wednesday"; break;
        case 4: dayOfWeek = "Thursday"; break;
        case 5: dayOfWeek = "Friday"; break;
        case 6: dayOfWeek = "Saturday"; break;
        case 7: dayOfWeek = "Sunday"; break;
    }
    
    
    cout << format("\nToday is {}.\n", dayOfWeek);
    
    // Determine discount.
    if (dayOfWeek == "Monday" || dayOfWeek == "Wednesday"|| dayOfWeek == "Friday") {
        darkDiscount = 3;
        cout << "\nAll Dark Rides are 3 tickets off of posted value.\n";
    } else if (dayOfWeek == "Tuesday" || dayOfWeek == "Thursday") {
        waterDiscount = 2;
        cout << "\nAll Water Rides are 2 tickets off of posted value.\n";
    } else {
        thrillDiscount = 5;
        cout << "\nAll Thrill RIdes are 5 tickets off of posted value.\n";
    }
    
    
    // Begin menu loop
    while (choice != 0 && tickets > 0) {
        cout << format("You have {} Tickets.\n\nSelect an option:\n", tickets);
        cout << "1. Ride Rides\n2. Buy Food\n3. Buy Merchandise\n0. Quit\nEnter your choice here: ";
        cin >> choice;
        
        // Check if the user has done enough options to allow them to eat food again.
        if (choiceCount >= 3 && foodCount >= 3) {
            foodCount = 0;
            choiceCount = 0;
            cout << "\nYour stomach feels much better now\n";
        }
        
        // Ride section.
        if (choice == 1) {
            cout << "\nAvailable Rides:\n\n";
            int rideChoice;
            int index = 1;
            for (Ride& r : rideList) {
                cout << format("{}. ", index);
                r.display();
                cout << "\n";
                index += 1;
            }
            cout << "\nSelect a ride: ";
            cin >> rideChoice;

            if (rideChoice > 0 && rideChoice <= rideList.size()) {
                auto it = rideList.begin();
                advance(it, rideChoice - 1);
                Ride& chosen = *it;

                // Check thrill ride restriction
                if (chosen.type == "Thrill" && thrillCount >= 3) {
                    cout << "You feel dizzy. Try 3 different rides before doing another thrill ride.\n";
                } else {
                    int finalDiscount = chosen.ticketAmount;
                    
                    if (chosen.type == "Thrill" && thrillDiscount > 0) {
                        finalDiscount = calculateFinalCost(chosen.ticketAmount, thrillDiscount);
                    } else if (chosen.type == "Dark Ride" && darkDiscount > 0) {
                        finalDiscount = calculateFinalCost(chosen.ticketAmount, darkDiscount);
                    } else if (chosen.type == "Water Ride" && waterDiscount > 0) {
                        finalDiscount = calculateFinalCost(chosen.ticketAmount, waterDiscount);
                    }
                    
                    tickets -= finalDiscount;

                    if (chosen.type == "Thrill") {
                        thrillCount++;
                        nonThrillCount = 0;
                    } else {
                        nonThrillCount++;
        
                        if (nonThrillCount >= 3 && thrillCount == 3) {
                            thrillCount = 0;
                            nonThrillCount = 0;
                            cout << "Your stomach feels much better, you can go on more thrill rides!\n";
                        }
                    }

                    cout << "You rode " << chosen.name << "! It was fun.\n";
                }
            }
            
            if (foodCount == 0) {
                choiceCount = 0;
            } else {
                choiceCount ++;
            }
           
        // Food section.
        } else if (choice == 2) {
            
            // Check to see if the user has had too much to eat. If so, block option.
            if (foodCount >= 3) {
                cout << "You've had too much to eat! Try another option.\n";
            } else {
                cout << "\nAvailable Food:\n\n";
                int foodChoice;
                int index = 1;
                for (Food& f : foodList) {
                    cout << format("{}. ", index);
                    f.Display();
                    cout << "\n";
                    index += 1;
                }
                cout << "\nYour stomach growls, time to get something to eat. Select an option: ";
                cin >> foodChoice;
                
                if (foodChoice > 0 && foodChoice <= foodList.size()) {
                    auto it = foodList.begin();
                    advance(it, foodChoice - 1);
                    Food& chosen = *it;
                    tickets -= chosen.ticketAmount;
                    
                    cout << "You purchased a " << chosen.name << "! Great choice.\n";
                }
                
                foodCount++;
            }
        } else if (choice == 3) {
            cout << "\nYou chose to buy merchandise!\n\n";
            int merchChoice;
            int index = 1;
            for (Merch& m : merchList) {
                cout << format("{}. ", index);
                m.Display();
                cout << "\n";
                index += 1;
            }
            cout << "\nPurchase an item: ";
            cin >> merchChoice;
            
            if (merchChoice > 0 && merchChoice <= merchList.size()) {
                auto it = merchList.begin();
                advance(it, merchChoice - 1);
                Merch& chosen = *it;
                tickets -= chosen.ticketAmount;
                
                cout << "You purchased a " << chosen.name << "!\n";
            }
            
            if (foodCount == 0) {
                choiceCount = 0;
            } else {
                choiceCount ++;
            }
           
            
        } else if (choice != 0) {
            cout << "\nInvalid input. Please try again.\n\n";
        }
        
    }
    
    cout << format("You have {} Tickets.\n\nHave a magical day!\n", tickets);
    return 0;
}
