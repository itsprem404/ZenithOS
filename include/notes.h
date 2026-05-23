#ifndef NOTES_H
#define NOTES_H

#include <string>
#include <vector>

struct Note
{
    int id;
    std::string title;
    std::string content;
    std::string date;
};

class NotesManager
{
private:
    std::vector<Note> notes;
    int nextId;

    void loadFromFile();
    void saveToFile();

public:
    NotesManager();

    void addNote();
    void viewNotes();
    void editNote();
    void deleteNote();
    int getNoteCount() const;
    void run();
};

#endif