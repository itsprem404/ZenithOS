#ifndef TASKS_H
#define TASKS_H

#include <string>
#include <vector>

struct Task
{
    int id;
    std::string title;
    std::string description;
    std::string dueDate;
    std::string status; // NEW
};

class TaskManager
{
private:
    std::vector<Task> tasks;
    int nextId;

    void loadFromFile();
    void saveToFile();

public:
    TaskManager();

    void addTask();
    void viewTasks();
    void markTaskDone(); // NEW
    int getTaskCount() const;
    int getPendingCount() const;
    int getCompletedCount() const;
    void run();
};

#endif