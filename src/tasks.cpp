#include "../include/tasks.h"
#include "../include/utils.h"

#include <iostream>
#include <fstream>

TaskManager::TaskManager()
{
    nextId = 1;
    loadFromFile();
}

void TaskManager::loadFromFile()
{
    std::ifstream file("data/tasks.txt");

    if (!file.is_open())
        return;

    Task task;
    std::string line;

    while (std::getline(file, line))
    {
        if (line.substr(0, 3) == "ID:")
        {
            task.id = std::stoi(line.substr(3));
        }
        else if (line.substr(0, 6) == "TITLE:")
        {
            task.title = line.substr(6);
        }
        else if (line.substr(0, 12) == "DESCRIPTION:")
        {
            task.description = line.substr(12);
        }
        else if (line.substr(0, 8) == "DUEDATE:")
        {
            task.dueDate = line.substr(8);
        }
        else if (line.substr(0, 7) == "STATUS:")
        {
            task.status = line.substr(7);
            tasks.push_back(task);

            if (task.id >= nextId)
                nextId = task.id + 1;
        }
    }

    file.close();
}

void TaskManager::saveToFile()
{
    std::ofstream file("data/tasks.txt");

    for (const auto &task : tasks)
    {
        file << "ID:" << task.id << "\n";
        file << "TITLE:" << task.title << "\n";
        file << "DESCRIPTION:" << task.description << "\n";
        file << "DUEDATE:" << task.dueDate << "\n";
        file << "STATUS:" << task.status << "\n";
        file << "---\n";
    }

    file.close();
}

void TaskManager::addTask()
{
    Utils::clearScreen();

    Task task;
    task.id = nextId++;

    task.title = Utils::getInput("Enter Task Title: ");
    task.description = Utils::getInput("Enter Description: ");
    task.dueDate = Utils::getInput("Enter Due Date: ");
    task.status = "Pending";

    tasks.push_back(task);
    saveToFile();

    std::cout << "\nTask added successfully!\n";
    Utils::sleep(1500);
}

void TaskManager::viewTasks()
{
    Utils::clearScreen();

    if (tasks.empty())
    {
        std::cout << "No tasks available.\n";
    }
    else
    {
        for (const auto &task : tasks)
        {
            std::cout << "ID: " << task.id << "\n";
            std::cout << "Title: " << task.title << "\n";
            std::cout << "Due Date: " << task.dueDate << "\n";
            std::cout << "Status: " << task.status << "\n";
            std::cout << "---------------------------\n";
        }
    }

    std::cout << "\nPress Enter to continue...";
    std::cin.get();
}

void TaskManager::markTaskDone()
{
    Utils::clearScreen();

    int id = Utils::getIntInput("Enter Task ID to mark as done: ");

    for (auto &task : tasks)
    {
        if (task.id == id)
        {
            task.status = "Completed";
            saveToFile();
            std::cout << "Task marked as completed!\n";
            Utils::sleep(1500);
            return;
        }
    }

    std::cout << "Task not found.\n";
    Utils::sleep(1500);
}

void TaskManager::run()
{
    while (true)
    {
        Utils::clearScreen();

        std::cout << "====== TASK MANAGER ======\n";
        std::cout << "1. Add Task\n";
        std::cout << "2. View Tasks\n";
        std::cout << "3. Mark Task Completed\n";
        std::cout << "0. Back\n\n";

        int choice = Utils::getIntInput("Enter choice: ");

        if (choice == 1)
            addTask();
        else if (choice == 2)
            viewTasks();
        else if (choice == 3)
            markTaskDone();
        else if (choice == 0)
            return;
    }
}
int TaskManager::getTaskCount() const
{
    return tasks.size();
}

int TaskManager::getPendingCount() const
{
    int count = 0;
    for (const auto &task : tasks)
        if (task.status == "Pending")
            count++;
    return count;
}

int TaskManager::getCompletedCount() const
{
    int count = 0;
    for (const auto &task : tasks)
        if (task.status == "Completed")
            count++;
    return count;
}