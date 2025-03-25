#include <iostream>
#include <string>
#include <vector>

// Transaction structure
struct Transaction {
    std::string type; // Income or Expense
    double amount;
};

void addIncome(double& balance) {
    double income;
    std::cout << "Enter income amount: ";
    std::cin >> income;
    balance += income;
    std::cout << "Income added.\n";
}
void addExpense(double& balance) {
    double expense;
    std::cout << "Enter expense amount: ";
    std::cin >> expense;
    balance -= expense;
    std::cout << "Expense recorded";
}
void showBalance(const double& balance) {
    std::cout << "Current balance: $" << balance << std::endl;
}

int main(){

    std::string name;
    int choice;
    double balance = 0.0;

    std::cout << "Welcome to Personal Finance Tracker!" << std::endl;
    std::cin >> name;
    std::cout << "Hello, " << name << "!";

    while (true){

        // Show the Menu
        std::cout << "\nMenu:\n";
        std::cout << "1. Add Income\n";
        std::cout << "2. Add Expenses\n";
        std::cout << "3. Add Balance\n";
        std::cout << "4. Exit\n";

        // Ask the user to choose an option
        std::cout << "Enter your choice (1-4): ";
        std::cin >> choice;

        // Options conditions
        if (choice==1) {
            addIncome(balance);
        }
        else if (choice==2) {
            addExpense(balance);
        }
        else if (choice==3) {
            showBalance(balance);
        }
        else if (choice==4) {
            std::cout << "Exiting the program. Goodbye, " << name << std::endl;
            break;
        }
        else {
            std::cout << "Invalid choice. Please try again\n";
        }
    }

    return 0;
}