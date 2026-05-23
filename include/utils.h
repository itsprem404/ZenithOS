#ifndef UTILS_H
#define UTILS_H

#include <string>

class Utils
{
public:
    static void clearScreen();
    static void sleep(int milliseconds);

    static std::string getInput(const std::string &prompt);
    static int getIntInput(const std::string &prompt);

    static std::string getCurrentDate();
    static std::string getCurrentTime();
    static std::string getCurrentDateTime();

    static std::string toLower(const std::string &str); // ✅ ADD THIS
};

#endif