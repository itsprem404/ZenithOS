#ifndef FILES_H
#define FILES_H

#include <string>
#include <vector>

struct FileInfo
{
    std::string name;
    std::string type;
    std::string size;
    bool isDirectory;
};

class FileOrganizer
{
private:
    std::string currentPath;

    std::string getFileExtension(const std::string &filename);
    std::string getFileType(const std::string &ext);
    std::string getFileSize(const std::string &path);
    std::string getFileIcon(const std::string &type);

public:
    FileOrganizer();

    void listFiles();
    void createDirectory();
    void deleteFile();
    void organizeByType();
    void showCurrentPath();
    void run();
};

#endif