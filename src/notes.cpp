#include "../include/notes.h"
#include "../include/utils.h"

#include <iostream>
#include <fstream>

NotesManager::NotesManager()
{
    nextId = 1;
    loadFromFile();
}

void NotesManager::loadFromFile()
{
    std::ifstream file("data/notes.txt");
    if (!file.is_open())
        return;

    Note note;
    std::string line;

    while (std::getline(file, line))
    {
        if (line.substr(0, 3) == "ID:")
            note.id = std::stoi(line.substr(3));
        else if (line.substr(0, 6) == "TITLE:")
            note.title = line.substr(6);
        else if (line.substr(0, 8) == "CONTENT:")
            note.content = line.substr(8);
        else if (line.substr(0, 5) == "DATE:")
        {
            note.date = line.substr(5);
            notes.push_back(note);
            if (note.id >= nextId)
                nextId = note.id + 1;
        }
    }

    file.close();
}

void NotesManager::saveToFile()
{
    std::ofstream file("data/notes.txt");

    for (const auto &note : notes)
    {
        file << "ID:" << note.id << "\n";
        file << "TITLE:" << note.title << "\n";
        file << "CONTENT:" << note.content << "\n";
        file << "DATE:" << note.date << "\n";
        file << "---\n";
    }

    file.close();
}

void NotesManager::addNote()
{
    Utils::clearScreen();

    Note note;
    note.id = nextId++;
    note.title = Utils::getInput("Title: ");
    note.content = Utils::getInput("Content: ");
    note.date = Utils::getCurrentDate();

    notes.push_back(note);
    saveToFile();

    std::cout << "Note saved.\n";
    Utils::sleep(1500);
}

void NotesManager::viewNotes()
{
    Utils::clearScreen();

    if (notes.empty())
    {
        std::cout << "No notes available.\n";
    }
    else
    {
        for (const auto &note : notes)
        {
            std::cout << "ID: " << note.id << "\n";
            std::cout << "Title: " << note.title << "\n";
            std::cout << "Date: " << note.date << "\n";
            std::cout << "Content: " << note.content << "\n";
            std::cout << "----------------------\n";
        }
    }

    std::cin.get();
}

void NotesManager::editNote()
{
    Utils::clearScreen();

    int id = Utils::getIntInput("Enter Note ID to edit: ");

    for (auto &note : notes)
    {
        if (note.id == id)
        {
            note.title = Utils::getInput("New Title: ");
            note.content = Utils::getInput("New Content: ");
            saveToFile();

            std::cout << "Note updated.\n";
            Utils::sleep(1500);
            return;
        }
    }

    std::cout << "Note not found.\n";
    Utils::sleep(1500);
}

void NotesManager::deleteNote()
{
    Utils::clearScreen();

    int id = Utils::getIntInput("Enter Note ID to delete: ");

    for (auto it = notes.begin(); it != notes.end(); ++it)
    {
        if (it->id == id)
        {
            notes.erase(it);
            saveToFile();
            std::cout << "Note deleted.\n";
            Utils::sleep(1500);
            return;
        }
    }

    std::cout << "Note not found.\n";
    Utils::sleep(1500);
}

void NotesManager::run()
{
    while (true)
    {
        Utils::clearScreen();

        std::cout << "====== NOTES MANAGER ======\n";
        std::cout << "1. Add Note\n";
        std::cout << "2. View Notes\n";
        std::cout << "3. Edit Note\n";
        std::cout << "4. Delete Note\n";
        std::cout << "0. Back\n\n";

        int choice = Utils::getIntInput("Choice: ");

        if (choice == 1)
            addNote();
        else if (choice == 2)
            viewNotes();
        else if (choice == 3)
            editNote();
        else if (choice == 4)
            deleteNote();
        else if (choice == 0)
            return;
    }
}
int NotesManager::getNoteCount() const
{
    return notes.size();
}