#ifndef DASHBOARD_H
#define DASHBOARD_H

#include <string>

#include "notes.h"
#include "tasks.h"
#include "files.h"
#include "auth.h"
#include "tools.h" // ✅ keep this include

class Dashboard
{
private:
    NotesManager notes;
    TaskManager tasks;
    FileOrganizer files;
    Auth auth;

    std::string currentUser;

    void showHeader();
    void showMenu();
    void handleChoice(int choice);

public:
    void run();
};

#endif