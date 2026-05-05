#include <iostream>
#include <vector>
#include <string>

// This is your data blueprint
struct Transaction {
    std::string name;
    std::string category;
    double amount;
};

int main() {
    // A vector is like a smart array that grows as you add items
    std::vector<Transaction> ledger;

    std::cout << "--- Welcome to your C++ Budget Tracker ---" << std::endl;
    
    // Hardcode one for testing
    ledger.push_back({"Grocery Store", "Food", 55.20});

    std::cout << "First item: " << ledger[0].name << " | $" << ledger[0].amount << std::endl;

    return 0;
}