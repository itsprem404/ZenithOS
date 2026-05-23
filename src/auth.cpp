#include "../include/auth.h"
#include "../include/utils.h"

#include <iostream>
#include <fstream>
#include <string>
#include <functional>
#include <conio.h>

std::string Auth::hashPassword(const std::string &password)
{
    std::hash<std::string> hasher;
    return std::to_string(hasher(password));
}

void Auth::ensureDefaultUser()
{
    std::ifstream check("data/users.txt");

    if (check.good())
    {
        check.close();
        return;
    }

    check.close();

    std::ofstream file("data/users.txt");
    file << "admin:" << hashPassword("admin123") << "\n";
    file.close();
}

bool Auth::userExists(const std::string &username)
{
    std::ifstream file("data/users.txt");
    std::string line;

    while (std::getline(file, line))
    {
        size_t pos = line.find(':');
        if (pos == std::string::npos)
            continue;

        std::string storedUser = line.substr(0, pos);
        if (storedUser == username)
            return true;
    }

    return false;
}

void Auth::registerUser()
{
    Utils::clearScreen();
    std::cout << "======= REGISTER =======\n\n";

    std::string username = Utils::getInput("New Username: ");

    if (userExists(username))
    {
        std::cout << "Username already exists.\n";
        Utils::sleep(1500);
        return;
    }

    std::cout << "New Password: ";
    std::string password;
    char ch;

    while ((ch = _getch()) != '\r')
    {
        if (ch == '\b')
        {
            if (!password.empty())
            {
                password.pop_back();
                std::cout << "\b \b";
            }
        }
        else
        {
            password += ch;
            std::cout << "*";
        }
    }
    std::cout << "\n";

    std::ofstream file("data/users.txt", std::ios::app);
    file << username << ":" << hashPassword(password) << "\n";
    file.close();

    std::cout << "User registered successfully!\n";
    Utils::sleep(1500);
}

bool Auth::login()
{
    ensureDefaultUser();

    while (true)
    {
        Utils::clearScreen();

        std::cout << "======= LOGIN =======\n";
        std::cout << "1. Login\n";
        std::cout << "2. Register\n";
        std::cout << "0. Exit\n\n";

        int choice = Utils::getIntInput("Choice: ");

        if (choice == 2)
        {
            registerUser();
            continue;
        }

        if (choice == 0)
        {
            exit(0);
        }

        std::ifstream file("data/users.txt");
        if (!file.is_open())
        {
            std::cout << "User database error.\n";
            Utils::sleep(1500);
            return false;
        }

        std::string username = Utils::getInput("Username: ");

        std::cout << "Password: ";
        std::string password;
        char ch;

        while ((ch = _getch()) != '\r')
        {
            if (ch == '\b')
            {
                if (!password.empty())
                {
                    password.pop_back();
                    std::cout << "\b \b";
                }
            }
            else
            {
                password += ch;
                std::cout << "*";
            }
        }
        std::cout << "\n";

        std::string hashedInput = hashPassword(password);

        std::string line;
        while (std::getline(file, line))
        {
            size_t pos = line.find(':');
            if (pos == std::string::npos)
                continue;

            std::string storedUser = line.substr(0, pos);
            std::string storedPass = line.substr(pos + 1);

            if (storedUser == username && storedPass == hashedInput)
            {
                std::cout << "Login successful!\n";
                Utils::sleep(1500);
                return true;
            }
        }

        std::cout << "Invalid credentials.\n";
        Utils::sleep(1500);
    }
}