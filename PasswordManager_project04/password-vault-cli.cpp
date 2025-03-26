#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <fstream>
#include <map>
#include <ctime>

////////// Functions \\\\\\\\\\;
struct PasswordEntry {

    std::string service;
    std::string username;
    std::string password;

};

class PasswordManager {
private:
    std::vector<PasswordEntry*> vault;

public:
    ~PasswordManager();

    void addEntry();
    void viewAll();
    void searchEntry();
    void deleteEntry();
    void saveToFile();
    void loadFromFile();
    void run();

};

////////// Helper Function \\\\\\\\\\;
std::string getCurrentTime() {
    time_t now = time(0);
    char* dt = ctime(&now);
    std::string timestamp(dt);
    timestamp.pop_back();
    return timestamp;
}

void PasswordManager::addEntry() {

    std::string service, username, pass;

    std::cout << "Enter the service: ";
    std::cin >> service;
    
    std::cout << "Enter the username: ";
    std::cin >> username;
    
    std::cout << "Enter the password: ";
    std::cin >> pass;
    
    PasswordEntry* c = new PasswordEntry;
    c->service = service;
    c->username = username;
    c->password = pass;
    
    vault.push_back(c);

    std::cout << "Entry added successfully!\n";

}

void PasswordManager::viewAll() {

    if (vault.empty()) {
        std::cout << "No entry found.\n";
        return;
    }

    for (const PasswordEntry* entry : vault) {    
        std::cout << "Service: " << entry->service << "\n";
        std::cout << "Username: " << entry->username << "\n";
        std::cout << "Password: " << entry->password << "\n";
        std::cout << "----------------------------\n";
    }

}

void PasswordManager::searchEntry() {

    std::string service;
    std::cout << "Please enter the service to search for: " << "\n";
    std::cin >> service;

    for (PasswordEntry* entry : vault) {
        if (entry->service == service) {
            std::cout << "Service: " << entry->service << "\n" << "Username: " << entry->username << "\n" << "Password: " << entry->password << "\n";
            return;
        }
    }

    std::cout << "Service not found in vault.\n";

}

void PasswordManager::deleteEntry() {

    std::string toBeDeleted;
    std::cout << "Please enter the service to be deleted: " << "\n";
    std::cin >> toBeDeleted;

    for (auto it = vault.begin(); it != vault.end(); ++it) {
        if ((*it)->service == toBeDeleted) {
            delete *it;
            vault.erase(it);
            std::cout << "Service has been successfully deleted!\n";
            return;
        }
    }

    std::cout << "Service not found in vault.\n";
}

void PasswordManager::saveToFile() {

    std::ofstream file("vault.txt");

    if (!file.is_open()) {
        std::cout << "Error saving the vault.";
        return;
    }

    for (PasswordEntry* entry : vault) {

        file << entry->service << "|" << entry->username << "|" << entry->password << "\n";

    }

    std::cout << "Vault saved successfully!\n";

}

void PasswordManager::loadFromFile() {

    std::ifstream file("vault.txt");
    if (!file.is_open()) {
        std::cout << "Error loading the vault.";
        return;
    }

    std::string line;
    while (std::getline(file, line)) {
        std::stringstream ss(line);
        std::string service, username, password;
        
        std::getline(ss, service, '|');
        std::getline(ss, username, '|');
        std::getline(ss, password);

        PasswordEntry* e = new PasswordEntry;
        e->service = service;
        e->username = username;
        e->password = password;

        vault.push_back(e);

    }

    std::cout << "Vault loaded successfully!\n";

}

void PasswordManager::run() {

    int choice;

    loadFromFile();

    while(true) {

        std::cout << "\n========== Password Manager ==========\n";
        std::cout << "1. Add vault\n";
        std::cout << "2. View vaults\n";
        std::cout << "3. Search for vault\n";
        std::cout << "4. Delete vault\n";
        std::cout << "5. Save vault and Exit\n";
        std::cout << "======================================\n";
        std::cout << "Enter choice: ";
        std::cin >> choice;

        if (choice==1) {
            addEntry();
        }
        else if (choice==2) {
            viewAll();
        }
        else if (choice==3) {
            searchEntry();
        }
        else if (choice==4) {
            deleteEntry();
        }
        else if (choice==5) {
            std::cout << "Goodbye!\n";
            saveToFile();
            break;
        }
        else {
            std::cout << "Invalid entry, Try again.\n";
        }
    }

}

PasswordManager::~PasswordManager() {
    for (PasswordEntry* entry : vault) {
        delete entry;
    }
}

int main() {

    PasswordManager app;
    app.run();

    return 0;
}