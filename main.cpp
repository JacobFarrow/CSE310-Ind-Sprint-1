#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <cctype>

struct Transaction {
    std::string name;
    std::string category;
    double amount;
};

void saveToFile(const std::vector<Transaction>& ledger, const std::string& filename) {
    std::ofstream file(filename);
    if (!file.is_open()) {
        std::cout << "Error: Unable to open file as file is already open." << std::endl;
        return;
    }

    for (int i = 0; i < ledger.size(); ++i) {
        file << ledger[i].name << "," << ledger[i].category << "," << ledger[i].amount << "\n";
    }

    file.close();
    std::cout << "Data saved to " << filename << std::endl;
}

void loadFromFile(std::vector<Transaction>& ledger, const std::string& filename){
    std::ifstream file(filename);

    if (!file.is_open()) {
        std::cout << "Error: Unable to open file." << std::endl;
        return;
    }

    std::string line;
    while (std::getline(file, line)) {

        std::stringstream ss(line);
        std::string name, category, amountStr;

        std::getline(ss, name, ',');
        std::transform(name.begin(), name.end(), name.begin(), tolower);
        std::getline(ss, category, ',');
        std::transform(category.begin(), category.end(), category.begin(), tolower);
        std::getline(ss, amountStr, ',');

        double amount = std::stod(amountStr);

        Transaction t{name, category, amount};
        ledger.push_back(t);
    }
    file.close();
    std::cout << "Data loaded from " << filename << std::endl;
}

int main() {
    std::vector<Transaction> ledger;

    std::cout << "--- Welcome to your C++ Budget Tracker ---" << std::endl;

    std::string filename = "budget_data.csv";

    loadFromFile(ledger, filename);

    int choice = 0;
    double budgetLimit = 0.0;
    bool budgetSet = false;

    while (true) {
        std::cout << "\nMenu:" << std::endl;
        std::cout << "1. Add Transaction" << std::endl;
        std::cout << "2. View Transactions" << std::endl;
        std::cout << "3. Set Budget Limit" << std::endl;
        std::cout << "4. Quit" << std::endl;
        std::cout << "Choose an option: ";
        std::cin >> choice;

        if (choice == 1) {
            Transaction t;

            std::cout << "Enter transaction name: ";
            std::cin >> t.name;
            std::transform(t.name.begin(), t.name.end(), t.name.begin(), tolower);

            std::cout << "Enter category (Food, Rent, Fun, etc.): ";
            std::cin >> t.category;
            std::transform(t.category.begin(), t.category.end(), t.category.begin(), tolower);

            std::cout << "Enter amount ($): ";
            std::cin >> t.amount;

            ledger.push_back(t);
            std::cout << "Transaction added!" << std::endl;

        } else if (choice == 2) {

            if (ledger.empty()) {
                std::cout << "No transactions to display." << std::endl;
            } else {
                std::cout << "\n--- Your Transactions ---" << std::endl;

                double total = 0.0;

                for (int i = 0; i < ledger.size(); ++i) {
                    std::cout << ledger[i].name
                              << " | " << ledger[i].category
                              << " | $" << ledger[i].amount
                              << std::endl;
                    total += ledger[i].amount;
                }

                std::cout << "Total Spent: $" << total << std::endl;

                if (budgetSet) {
                    if (total > budgetLimit) {
                        double overage = total - budgetLimit;
                        std::cout << "Warning: You are $" << overage << " over your budget limit!" << std::endl;
                    } else {
                        double remaining = budgetLimit - total;
                        std::cout << "You are $" << remaining << " under your budget limit." << std::endl;
                    }
                }

                std::cout << "\n--- Spending by Category ---" << std::endl;

                std::vector<std::string> seenCategories;

                for (int i = 0; i < ledger.size(); ++i) {
                    std::string cat = ledger[i].category;

                    bool alreadySeen = false;
                    for (int j = 0; j < seenCategories.size(); ++j) {
                        if (seenCategories[j] == cat) {
                            alreadySeen = true;
                            break;
                        }
                    }

                    if (!alreadySeen) {
                        seenCategories.push_back(cat);

                        double catTotal = 0.0;

                        for (int k = 0; k < ledger.size(); ++k) {
                            if (ledger[k].category == cat) {
                                catTotal += ledger[k].amount;
                            }
                        }
                        std::cout << cat << ": $" << catTotal << std::endl;
                    }
                }
            }

        } else if (choice == 3) {
            std::cout << "Enter your budget limit ($): ";
            std::cin >> budgetLimit;
            budgetSet = true;
            std::cout << "Budget limit set!" << std::endl;

        } else if (choice == 4) {
            ledger.clear();
            remove(filename.c_str());
            std::cout << "All transactions cleared and file deleted." << std::endl;

        } else if (choice == 5) {
            saveToFile(ledger, filename);
            std::cout << "Goodbye!" << std::endl;
            break;

        } else {
            std::cout << "Invalid option, please try again." << std::endl;
        }
    }

    return 0;
}