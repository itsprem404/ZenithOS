#include "../include/dashboard.h"
#include "../include/utils.h"
#include "../include/tools.h"

#include <iostream>
#include <cstdlib>
#include <limits>

void Dashboard::showHeader()
{
    Utils::clearScreen();

    std::string date = Utils::getCurrentDate();
    std::string time = Utils::getCurrentTime();

    std::cout << "╔══════════════════════════════════════════════════════╗\n";
    std::cout << "║  🖥️  ZenithOS v1.0                                   ║\n";

    // USER LINE
    std::string userLine = "║  👤 User: " + currentUser;
    int userPadding = 54 - userLine.length();
    if (userPadding < 0)
        userPadding = 0;

    std::cout << userLine;
    for (int i = 0; i < userPadding; i++)
        std::cout << " ";
    std::cout << "║\n";

    // DATE + TIME LINE
    std::string dateTimeLine = "║  📅 " + date + "   ⏰ " + time;
    int datePadding = 54 - dateTimeLine.length();
    if (datePadding < 0)
        datePadding = 0;

    std::cout << dateTimeLine;
    for (int i = 0; i < datePadding; i++)
        std::cout << " ";
    std::cout << "║\n";

    std::cout << "╚══════════════════════════════════════════════════════╝\n\n";
}

void Dashboard::showMenu()
{
    std::cout << "══════════════════════════════\n";
    std::cout << "  [1] 📝 Notes\n";
    std::cout << "  [2] ✅ Tasks\n";
    std::cout << "  [3] 📁 File Organizer\n";
    std::cout << "  [4] 🛠️  Tools\n";
    std::cout << "  [0] 🚪 Exit\n";
    std::cout << "══════════════════════════════\n\n";
}

void Dashboard::handleChoice(int choice)
{
    switch (choice)
    {
    case 1:
        notes.run();
        break;

    case 2:
        tasks.run();
        break;

    case 3:
        files.run();
        break;

    case 4:
        showToolsMenu(); // ✅ Correct (function-based)
        break;

    case 0:
        std::cout << "\nExiting ZenithOS...\n";
        exit(0);

    default:
        std::cout << "\n❌ Invalid choice. Press Enter to continue...";
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cin.get();
    }
}

void Dashboard::run()
{
    // Login loop
    while (!auth.login())
    {
    }

    // Since Auth doesn't expose username, ask once
    currentUser = Utils::getInput("Enter your username again for session display: ");

    while (true)
    {
        showHeader();
        showMenu();

        int choice = Utils::getIntInput("zenith@dashboard:~$ ");
        handleChoice(choice);
    }
}