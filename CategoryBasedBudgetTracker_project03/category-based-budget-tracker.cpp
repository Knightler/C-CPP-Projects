#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <map>
#include <ctime>

struct Transaction {
    std::string description;
    double amount;
    std::string timestamp;
};

std::string getCurrentTime() {
    time_t now = time(0);
    char* dt = ctime(&now);
    std::string timestamp(dt);
    timestamp.pop_back();
    return timestamp;
}

////////// Class \\\\\\\\\\;
class BudgetTracker {
    std::map<std::string, std::vector<Transaction*>> data;

public:
    void addTransaction();
    void viewAll();
    void viewByCategory();
    void saveToFile();
    void loadFromFile();
    ~BudgetTracker(); // to clean up memory
    void run();
};

////////// Functions \\\\\\\\\\;
void BudgetTracker::addTransaction() {

    std::string category, desc;
    double amount;
    
    std::cout << "Enter category: " << "\n";
    std::cin >> category;
    std::cin.ignore();

    std::cout << "Enter description: " << "\n";
    std::getline(std::cin, desc);

    std::cout << "Enter amount: " << "\n";
    std::cin >> amount;

    Transaction* t = new Transaction;
    t->description = desc;
    t->amount = amount;
    t->timestamp = getCurrentTime();

    data[category].push_back(t);

    std::cout << "Transaction added successfully.\n";

}
void BudgetTracker::viewAll() {

    if (data.empty()) {
        std::cout << "No transactions yet.\n";
        return;
    }

    std::cout << "\n========= All Transactions =========\n";
    
    for (const auto& [category, transaction] : data) {
        std::cout << "\nCategory: " << category << "\n";

        for (const Transaction* t : transaction) {
            std::cout << "  - " << t->description << " | $" << t->amount << " | " << t->timestamp << "\n";
        }
    }

    std::cout << "====================================\n";

}
void BudgetTracker::viewByCategory() {

    std::string input;
    std::cout << "Please enter category input: ";
    std::cin >> input;

    auto it = data.find(input);


    if (it == data.end()) {
        std::cout << "Didn't find it.\n";
        return;
    }
    
    std::cout << "Found it!\n Transactions in category '" << input << "':\n";
    for (const Transaction* t : it->second) {
        std::cout << "  - " << t->description << " | $" << t->amount << " | " << t->timestamp << "\n";
    }

}
void BudgetTracker::saveToFile() {

    std::ofstream file("budget.txt");

    if (!file.is_open()) {
        std::cout << "Error opening the file for saving.\n";
        return;
    }

    for (const auto& [category, transactions] : data) {
        for (const Transaction* t : transactions){
            file << category << "|" << t->description << "|" << t->amount << "|" << t->timestamp << "\n";
        }
    }

    std::cout << "Data saved successfully.\n";

}
void BudgetTracker::loadFromFile() {

    std::ifstream file("budget.txt");

    if (!file.is_open()) {
        std::cout << "Error loading the file.\n";
        return;
    }

    std::string line;
    while (std::getline(file, line)) {
        std::stringstream ss(line);
        std::string category, desc, amountstr, timestamp;

        std::getline(ss, category, '|');
        std::getline(ss, desc, '|');
        std::getline(ss, amountstr, '|');
        std::getline(ss, timestamp);

        Transaction* t = new Transaction;
        t->description = desc;
        t-> amount = std::stod(amountstr);
        t->timestamp = timestamp;

        data[category].push_back(t);
    }

    std::cout << "Data loaded successfully.\n";

}
void BudgetTracker::run() {

    int choice;

    loadFromFile();

    while (true) {
        std::cout << "\nMenu:\n";
        std::cout << "1. Add Transaction\n";
        std::cout << "2. View All Transaction\n";
        std::cout << "3. Exit\n";
        std::cout << "Enter choice: ";
        std::cin >> choice;

        if (choice == 1) addTransaction();
        else if (choice == 2) viewAll();
        else if (choice == 3) {
            saveToFile();
            std::cout << "Saving & exiting...\n";
            break;
        }
        else std::cout << "invalid option!\n";
    }

}

BudgetTracker::~BudgetTracker() {
    for (auto& [category, transactions] : data) {
        for (Transaction* t : transactions) {
            delete t;
        }
    }
}

////////// Main \\\\\\\\\\;
int main (){

    BudgetTracker app;
    app.run();

    return 0;
}