#include "../include/files.h"
#include "../include/utils.h"

#include <iostream>
#include <filesystem>
#include <algorithm>
#include <iomanip>

namespace fs = std::filesystem;

FileOrganizer::FileOrganizer()
{
    currentPath = fs::current_path().string();
}

std::string FileOrganizer::getFileExtension(const std::string &filename)
{
    size_t pos = filename.rfind('.');
    if (pos == std::string::npos)
        return "";
    return filename.substr(pos + 1);
}

std::string FileOrganizer::getFileType(const std::string &ext)
{
    std::string lowerExt = Utils::toLower(ext);

    if (lowerExt == "cpp" || lowerExt == "c" || lowerExt == "h" || lowerExt == "hpp" ||
        lowerExt == "py" || lowerExt == "java" || lowerExt == "js" || lowerExt == "cs")
        return "Code";
    if (lowerExt == "txt" || lowerExt == "doc" || lowerExt == "docx" || lowerExt == "pdf" || lowerExt == "md")
        return "Document";
    if (lowerExt == "jpg" || lowerExt == "jpeg" || lowerExt == "png" || lowerExt == "gif" || lowerExt == "bmp" || lowerExt == "svg")
        return "Image";
    if (lowerExt == "mp4" || lowerExt == "avi" || lowerExt == "mkv" || lowerExt == "mov" || lowerExt == "wmv")
        return "Video";
    if (lowerExt == "mp3" || lowerExt == "wav" || lowerExt == "flac" || lowerExt == "aac" || lowerExt == "ogg")
        return "Audio";
    if (lowerExt == "zip" || lowerExt == "rar" || lowerExt == "7z" || lowerExt == "tar" || lowerExt == "gz")
        return "Archive";
    if (lowerExt == "exe" || lowerExt == "msi" || lowerExt == "app")
        return "Executable";
    return "Other";
}

std::string FileOrganizer::getFileSize(const std::string &path)
{
    try
    {
        if (!fs::exists(path) || fs::is_directory(path))
            return "-";

        auto size = fs::file_size(path);
        if (size < 1024)
            return std::to_string(size) + " B";
        if (size < 1024 * 1024)
            return std::to_string(size / 1024) + " KB";
        if (size < 1024 * 1024 * 1024)
            return std::to_string(size / (1024 * 1024)) + " MB";
        return std::to_string(size / (1024 * 1024 * 1024)) + " GB";
    }
    catch (...)
    {
        return "N/A";
    }
}

std::string FileOrganizer::getFileIcon(const std::string &type)
{
    if (type == "Directory")
        return "📂";
    if (type == "Code")
        return "💻";
    if (type == "Document")
        return "📄";
    if (type == "Image")
        return "🖼️";
    if (type == "Video")
        return "🎬";
    if (type == "Audio")
        return "🎵";
    if (type == "Archive")
        return "📦";
    if (type == "Executable")
        return "⚙️";
    return "📁";
}

void FileOrganizer::listFiles()
{
    Utils::clearScreen();

    std::cout << "Listing files in: " << currentPath << "\n";
    std::cout << "----------------------------------------\n";

    int count = 0;
    try
    {
        for (const auto &entry : fs::directory_iterator(currentPath))
        {
            std::string name = entry.path().filename().string();
            std::string type = entry.is_directory() ? "Directory" : getFileType(getFileExtension(name));
            std::string size = entry.is_regular_file() ? getFileSize(entry.path().string()) : "-";

            std::cout << getFileIcon(type) << " " << name << " [" << type << "] " << size << "\n";
            count++;
        }
    }
    catch (const std::exception &e)
    {
        std::cout << "Error: " << e.what() << "\n";
    }

    std::cout << "----------------------------------------\n";
    std::cout << "Total: " << count << " items\n\n";
    std::cout << "Press Enter to continue...";
    std::cin.get();
}

void FileOrganizer::createDirectory()
{
    Utils::clearScreen();

    std::string name = Utils::getInput("Enter directory name: ");
    if (name.empty())
        return;

    try
    {
        fs::create_directory(currentPath + "/" + name);
        std::cout << "Directory created: " << name << "\n";
    }
    catch (...)
    {
        std::cout << "Failed to create directory.\n";
    }

    Utils::sleep(1500);
}

void FileOrganizer::deleteFile()
{
    Utils::clearScreen();

    std::string name = Utils::getInput("Enter file/folder name to delete: ");
    if (name.empty())
        return;

    try
    {
        fs::remove_all(currentPath + "/" + name);
        std::cout << "Deleted: " << name << "\n";
    }
    catch (...)
    {
        std::cout << "Failed to delete.\n";
    }

    Utils::sleep(1500);
}

void FileOrganizer::organizeByType()
{
    Utils::clearScreen();

    std::cout << "Organizing files by type...\n";

    std::vector<std::string> categories = {"Documents", "Images", "Videos", "Audio", "Code", "Archives", "Others"};

    for (const auto &cat : categories)
    {
        fs::create_directory(currentPath + "/" + cat);
    }

    int moved = 0;
    try
    {
        for (const auto &entry : fs::directory_iterator(currentPath))
        {
            if (!entry.is_regular_file())
                continue;

            std::string name = entry.path().filename().string();
            std::string ext = getFileExtension(name);
            std::string type = getFileType(ext);
            std::string destFolder;

            if (type == "Document")
                destFolder = "Documents";
            else if (type == "Image")
                destFolder = "Images";
            else if (type == "Video")
                destFolder = "Videos";
            else if (type == "Audio")
                destFolder = "Audio";
            else if (type == "Code")
                destFolder = "Code";
            else if (type == "Archive")
                destFolder = "Archives";
            else
                destFolder = "Others";

            fs::rename(entry.path(), currentPath + "/" + destFolder + "/" + name);
            moved++;
        }
    }
    catch (...)
    {
    }

    std::cout << "Organized " << moved << " files.\n";
    Utils::sleep(2000);
}

void FileOrganizer::showCurrentPath()
{
    Utils::clearScreen();
    std::cout << "Current Path: " << currentPath << "\n\n";
    std::cout << "Press Enter...";
    std::cin.get();
}

void FileOrganizer::run()
{
    while (true)
    {
        Utils::clearScreen();

        std::cout << "====== FILE ORGANIZER ======\n";
        std::cout << "1. List Files\n";
        std::cout << "2. Create Directory\n";
        std::cout << "3. Delete File/Folder\n";
        std::cout << "4. Organize by Type\n";
        std::cout << "5. Show Current Path\n";
        std::cout << "0. Back\n\n";

        int choice = Utils::getIntInput("Choice: ");

        if (choice == 1)
            listFiles();
        else if (choice == 2)
            createDirectory();
        else if (choice == 3)
            deleteFile();
        else if (choice == 4)
            organizeByType();
        else if (choice == 5)
            showCurrentPath();
        else if (choice == 0)
            return;
    }
}