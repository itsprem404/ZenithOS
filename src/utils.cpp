#include "../include/utils.h"

#include <iostream>
#include <thread>
#include <chrono>
#include <ctime>

void Utils::clearScreen()
{
    system("cls");
}

void Utils::sleep(int milliseconds)
{
    std::this_thread::sleep_for(std::chrono::milliseconds(milliseconds));
}

std::string Utils::getInput(const std::string &prompt)
{
    std::cout << prompt;
    std::string input;
    std::getline(std::cin, input);
    return input;
}

int Utils::getIntInput(const std::string &prompt)
{
    while (true)
    {
        std::cout << prompt;
        int value;
        if (std::cin >> value)
        {
            std::cin.ignore(10000, '\n');
            return value;
        }
        std::cin.clear();
        std::cin.ignore(10000, '\n');
        std::cout << "Invalid number. Try again.\n";
    }
}

std::string Utils::getCurrentDate()
{
    time_t now = time(nullptr);
    tm *ltm = localtime(&now);
    char buffer[30];
    strftime(buffer, sizeof(buffer), "%d %b %Y", ltm);
    return std::string(buffer);
}

std::string Utils::getCurrentTime()
{
    time_t now = time(nullptr);
    tm *ltm = localtime(&now);
    char buffer[30];
    strftime(buffer, sizeof(buffer), "%I:%M:%S %p", ltm);
    return std::string(buffer);
}
#include <algorithm>
#include <cctype>

std::string Utils::toLower(const std::string &str)
{
    std::string result = str;
    std::transform(result.begin(), result.end(), result.begin(),
                   [](unsigned char c)
                   { return std::tolower(c); });
    return result;
}