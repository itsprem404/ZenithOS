#include <iostream>
#include <limits>
#include "../include/tools.h"

using namespace std;

void runCalculator();
void showCalendar();

void showToolsMenu()
{
    int choice;

    do
    {
        cout << "\n═══════════════════════════════\n";
        cout << "     🛠 ZenithOS — Tools\n";
        cout << "═══════════════════════════════\n";
        cout << " [1] 🖩 Calculator\n";
        cout << " [2] 📅 Calendar\n";
        cout << " [0] ← Back\n";
        cout << "═══════════════════════════════\n";
        cout << "zenith@tools:~$ ";
        cin >> choice;

        switch (choice)
        {
        case 1:
            runCalculator();
            break;
        case 2:
            showCalendar();
            break;
        case 0:
            break;
        default:
            cout << "❌ Invalid option.\n";
        }

    } while (choice != 0);
}

void runCalculator()
{
    double a, b;
    char op;

    cout << "\n🖩 Simple Calculator\n";
    cout << "Enter expression (example: 5 + 3)\n";
    cout << "zenith@calc:~$ ";

    cin >> a >> op >> b;

    switch (op)
    {
    case '+':
        cout << "Result: " << a + b << endl;
        break;
    case '-':
        cout << "Result: " << a - b << endl;
        break;
    case '*':
        cout << "Result: " << a * b << endl;
        break;
    case '%':
        cout << "Result: " << (int)a % (int)b << endl;
        break;
    case '/':
        if (b == 0)
            cout << "❌ Cannot divide by zero\n";
        else
            cout << "Result: " << a / b << endl;
        break;
    default:
        cout << "❌ Invalid operator\n";
    }
}

bool isLeapYear(int year)
{
    if ((year % 4 == 0 && year % 100 != 0) || year % 400 == 0)
        return true;
    return false;
}

void showCalendar()
{
    int month, year;

    cout << "\n📅 ZenithOS Calendar\n";
    cout << "Enter Month (1-12): ";
    cin >> month;
    cout << "Enter Year: ";
    cin >> year;

    int daysInMonth;

    switch (month)
    {
    case 1:
    case 3:
    case 5:
    case 7:
    case 8:
    case 10:
    case 12:
        daysInMonth = 31;
        break;
    case 4:
    case 6:
    case 9:
    case 11:
        daysInMonth = 30;
        break;
    case 2:
        daysInMonth = isLeapYear(year) ? 29 : 28;
        break;
    default:
        cout << "❌ Invalid Month\n";
        return;
    }

    cout << "\nSun Mon Tue Wed Thu Fri Sat\n";

    // Zeller’s Congruence for first day
    int m = month;
    int y = year;

    if (m < 3)
    {
        m += 12;
        y--;
    }

    int k = y % 100;
    int j = y / 100;

    int firstDay = (1 + (13 * (m + 1)) / 5 + k + k / 4 + j / 4 + 5 * j) % 7;
    firstDay = (firstDay + 6) % 7; // Adjust to Sunday=0

    for (int i = 0; i < firstDay; i++)
        cout << "    ";

    for (int day = 1; day <= daysInMonth; day++)
    {
        cout.width(3);
        cout << day << " ";

        if ((day + firstDay) % 7 == 0)
            cout << endl;
    }

    cout << endl;
}