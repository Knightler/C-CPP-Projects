#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>

struct Task {
    int id;
    std::string title;
    std::string description;
    std::string priority; // High / Medium / Low
    bool completed;
    std::string timestamp;
};

std::string getCurrentTime() {
    time_t now = time(0);
    char* dt = ctime(&now);
    std::string timestamp(dt);
    timestamp.pop_back();
    return timestamp;
}

class TaskManager {
private:
    std::vector<Task> tasks;
    int nextId;

public:
    TaskManager();
    void run();
    void addTask();
    void viewTasks() const;
    void completeTask();
    void saveTasks() const;
    void loadTasks();
};

void TaskManager::addTask() {
    std::string title;
    std::string desc;
    int priority;
    bool completed = false;

    std::cout << "Enter the title of the task: ";
    std::cin >> title;
    std::cin.ignore();

    std::cout << "Enter the Description of the task: ";
    std::getline(std::cin, desc);

    std::cout << "Enter the priority of your task (1: High / 2: Medium / 3: Low): ";
    std::cin >> priority;

    std::string priorityStr;
    while (true) {
        if (priority == 1) {
            priorityStr = "High";
            break;
        } else if (priority == 2) {
            priorityStr = "Medium";
            break;
        } else if (priority == 3) {
            priorityStr = "Low";
            break;
        } else {
            std::cout << "Invalid input. Enter 1, 2, or 3: ";
            std::cin >> priority;
        }
    }

    Task t;
    t.id = nextId++;
    t.title = title;
    t.description = desc;
    t.priority = priorityStr;
    t.completed = false;
    t.timestamp = getCurrentTime();
    tasks.push_back(t);

    std::cout << "Task added successfully!\n";
}

void TaskManager::viewTasks() const {
    if (tasks.empty()) {
        std::cout << "No tasks yet!\n";
    }
    for (const Task& t : tasks) {

        std::string status;
        if (t.completed == true) {
            status = "Completed";
        }
        else {
            status = "Not Completed";
        }
        std::cout << "\n--------------------\n\n" << "[ID: " << t.id << "]" << "Title: " << t.title << "\n" << "Priority: " << t.priority << "\n" << "Completion Status: " << status << "\n" << "Added: " << t.timestamp << "\n--------------------\n\n";
    }
}

void TaskManager::completeTask() {

    bool found = false;
    int enteredId;

    std::cout << "Please enter your [ID]: " << "\n";
    std::cin >> enteredId;

    for (Task& t : tasks) {
        if (t.id == enteredId) {
            t.completed = true;
            std::cout << "Task marked as completed!\n";
            found = true;
            break;
        }
    }
    if (!found) {
        std::cout << "Task not found.\n";
    }
}

void TaskManager::saveTasks() const {
    std::ofstream file("tasks.txt");

    if (!file.is_open()) {
        std::cout << "Error saving tasks.";
        return;
    }

    for (const Task& t : tasks) {
        file << t.id << "|" << t.title << "|" << t.description << "|" << t.priority << "|" << (t.completed ? "1" : "0") << "|" << t.timestamp << "\n";
    }
}

void TaskManager::loadTasks() {
    std::ifstream file("tasks.txt");

    if (!file.is_open()) {
        std::cout << "Error loading tasks.";
        return;
    }

    std::string line;
    while (std::getline(file, line)) {
        std::stringstream ss(line);
        std::string idStr, title, desc, priority, completedStr, times;

        std::getline(ss, idStr, '|');
        std::getline(ss, title, '|');
        std::getline(ss, desc, '|');
        std::getline(ss, priority, '|');
        std::getline(ss, completedStr, '|');
        std::getline(ss, times);

        Task t;
        t.id = std::stoi(idStr);
        t.title = title;
        t.description = desc;
        t.priority = priority;
        t.completed = (completedStr == "1");
        t.timestamp = times;

        tasks.push_back(t);

        if (t.id >= nextId) {
            nextId = t.id + 1;
        }
    }
    file.close();
    std::cout << "Tasks loaded successfully.\n";
}

void TaskManager::run() {
    int choice;

    while (true) {
        std::cout << "\n========== TASK MANAGER ==========\n";
        std::cout << "1. Add Task\n";
        std::cout << "2. View Tasks\n";
        std::cout << "3. Completed Task\n";
        std::cout << "4. Save & Exit\n";
        std::cout << "==================================\n";
        std::cout << "Enter your choice (1-4): ";
        std::cin >> choice;

        switch (choice) {
            case 1:
                addTask();
                break;
            case 2:
                viewTasks();
                break;
            case 3:
                completeTask();
                break;
            case 4:
                saveTasks();
                std::cout << "Goodbye!\n";
                break;
            default:
                std::cout << "Invalid option. Try again.\n";
        }
    }
}

int main() {

    TaskManager task;
    task.run();
    
    return 0;
    
}