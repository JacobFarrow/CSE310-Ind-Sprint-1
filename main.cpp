#include <iostream>
#include <vector>
#include <string>

// Data blueprint
struct Transaction {
    std::string name;
    std::string category;
    double amount;
};

int main() {
    // A vector is like a smart array that grows as you add items
    std::vector<Transaction> ledger;

    std::cout << "--- Welcome to your C++ Budget Tracker ---" << std::endl;
    
    int choice = 0;

    while (true) {
        std::cout << "\nMenu:" << std::endl;
        std::cout << "1. Add Transaction" << std::endl;
        std::cout << "2. View Transactions" << std::endl;
        std::cout << "3. Quit" << std::endl;
        std::cout << "Choose an option: ";
        std::cin >> choice;

        if (choice == 1) {
            Transaction t;
            
            std::cout << "Enter transaction name: ";
            std::cin >> t.name;

            std::cout << "Enter category (Food, Rent, Fun, etc.): ";
            std::cin >> t.category;

            std::cout << "Enter amount ($): ";
            std::cin >> t.amount;

            ledger.push_back(t); 
            std::cout << "Transaction added!" << std::endl;

        } else if (choice == 2) {
            std::cout << "\n--- Your Transactions ---" << std::endl;
        }

        else if (choice == 3) {
            std::cout << "Goodbye!" << std::endl;
            break;
        } else {
            std::cout << "Invalid option, please try again." << std::endl;
        }
    }

    return 0;
}