#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <sstream> 

// Transaction structure
struct Transaction {
    std::string type; // Income or Expense
    double amount;
    std::string description;
    std::string timestamp;
};

class FinanceTracker {
    private:
        double balance;
        std::vector<Transaction> transactions;
    
    public:
        FinanceTracker();
        void loadTransactions();
        void saveTransactions();
        void addIncome();
        void addExpense();
        void showBalance() const;
        void showTransactionHistory() const;
        void run(); // Menu system
        
    };    

// Helper function
std::string getCurrentTime() {
    time_t now = time(0);
    char* dt = ctime(&now);
    std::string timestamp(dt);
    timestamp.pop_back();
    return timestamp;
}

void FinanceTracker::showTransactionHistory() const {
    std::cout << "\n----------Transaction History----------\n";

    if (transactions.empty()){
        std::cout << "No transaction yet.\n";
        return;
    }

    for (size_t i = 0; i < transactions.size(); ++i) {
        const Transaction& t = transactions[i];
        std::cout << i + 1 << ". " << t.type << " - $" << t.amount << " | " << t.description << " | " << t.timestamp << "\n";
    }
    
    std::cout << "Total transactions: " << transactions.size() << "\n";
}

void FinanceTracker::saveTransactions() {
    std::ofstream file("transactions.txt");

    if (!file.is_open()){
        std::cout << "Error saving transactions.\n";
        return;
    }

    for (const Transaction& t: transactions){
        file << t.type << "|" << t.amount << "|" << t.description << "|" << t.timestamp << std::endl;
    }

    file.close();
}

void FinanceTracker::loadTransactions() {
    std::ifstream file("transactions.txt");

    if (!file.is_open()) {
        std::cout << "No previous transaction. file not found.\n";
        return;
    }

    std::string line;
    while (std::getline(file, line)) {
        std::stringstream ss(line);
        std::string type, amountStr, desc, time;

        std::getline(ss, type, '|');
        std::getline(ss, amountStr, '|');
        std::getline(ss, desc, '|');
        std::getline(ss, time);

        Transaction t;
        t.type = type;
        t.amount = std::stod(amountStr);
        t.description = desc;
        t.timestamp = time;

        transactions.push_back(t);
    }
    file.close();
}

void FinanceTracker::addIncome() {
    double income;
    std::string desc;

    std::cout << "Enter income amount: ";
    std::cin >> income;
    std::cin.ignore();

    std::cout << "Enter income description: ";
    std::getline(std::cin, desc);

    balance += income;

    Transaction t;
    t.type = "Income";
    t.amount = income;
    t.description = desc;
    t.timestamp = getCurrentTime();
    transactions.push_back(t); // Save the transaction

    std::cout << "Income added.\n";
}
void FinanceTracker::addExpense() {
    double expense;
    std::string desc;

    std::cout << "Enter expense amount: ";
    std::cin >> expense;
    std::cin.ignore();

    std::cout << "Enter expense description: ";
    std::getline(std::cin, desc);

    balance -= expense;

    Transaction t;
    t.type = "Expense";
    t.amount = expense;
    t.description = desc;
    t.timestamp = getCurrentTime();
    transactions.push_back(t);

    std::cout << "Expense recorded.\n";
}
void FinanceTracker::showBalance() const {
    std::cout << "Current balance: $" << balance << std::endl;
}

void FinanceTracker::run() {
    int choice;

    while (true) {
        std::cout << "\nMenu:\n";
        std::cout << "1. Add Income\n";
        std::cout << "2. Add Expenses\n";
        std::cout << "3. Show Balance\n";
        std::cout << "4. Exit\n";
        std::cout << "5. View Transaction History\n";

        std::cout << "Enter your choice (1-5): ";
        std::cin >> choice;

        if (choice == 1) {
            addIncome();
        } else if (choice == 2) {
            addExpense();
        } else if (choice == 3) {
            showBalance();
        } else if (choice == 4) {
            std::cout << "Exiting the program. Goodbye!\n";
            saveTransactions();
            break;
        } else if (choice == 5) {
            showTransactionHistory();
        } else {
            std::cout << "Invalid choice. Please try again.\n";
        }
    }
}

FinanceTracker::FinanceTracker() {
    balance = 0.0;
    loadTransactions();

    std::string name;
    std::cout << "Welcome to Personal Finance Tracker!" << std::endl;
    std::cin >> name;
    std::cout << "Hello, " << name << "!" << std::endl;
    
}

int main(){

    FinanceTracker app;

    app.run();
    return 0;
}