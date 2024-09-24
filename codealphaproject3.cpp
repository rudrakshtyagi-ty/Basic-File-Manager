#include <iostream>
#include <filesystem> // Requires C++17 or above
#include <fstream>

namespace fs = std::filesystem;

// Function to list files and directories in the current directory
void listDirectory(const fs::path& path) {
    std::cout << "\nContents of " << path << ":\n";
    try {
        for (const auto& entry : fs::directory_iterator(path)) {
            std::cout << (entry.is_directory() ? "[DIR]  " : "[FILE] ") << entry.path().filename().string() << "\n";
        }
    } catch (const fs::filesystem_error& e) {
        std::cout << "Error listing directory: " << e.what() << "\n";
    }
}

// Function to change the current working directory
void changeDirectory(fs::path& currentPath) {
    std::string newDir;
    std::cout << "Enter directory name to navigate (.. for up): ";
    std::cin >> newDir;

    fs::path newPath = currentPath / newDir;
    if (fs::exists(newPath) && fs::is_directory(newPath)) {
        currentPath = fs::canonical(newPath);
        std::cout << "Changed directory to: " << currentPath << "\n";
    } else {
        std::cout << "Invalid directory! Check the path and try again.\n";
    }
}

// Function to create a new directory
void createDirectory(const fs::path& currentPath) {
    std::string dirName;
    std::cout << "Enter new directory name: ";
    std::cin >> dirName;

    fs::path newDirPath = currentPath / dirName;
    try {
        if (fs::create_directory(newDirPath)) {
            std::cout << "Directory created: " << newDirPath << "\n";
        } else {
            std::cout << "Failed to create directory. It may already exist.\n";
        }
    } catch (const fs::filesystem_error& e) {
        std::cout << "Error creating directory: " << e.what() << "\n";
    }
}

// Function to copy a file
void copyFile(const fs::path& currentPath) {
    std::string sourceFile, destFile;
    std::cout << "Enter source file name: ";
    std::cin >> sourceFile;
    std::cout << "Enter destination file name: ";
    std::cin >> destFile;

    fs::path sourcePath = currentPath / sourceFile;
    fs::path destPath = currentPath / destFile;

    try {
        if (fs::exists(sourcePath) && !fs::is_directory(sourcePath)) {
            fs::copy_file(sourcePath, destPath, fs::copy_options::overwrite_existing);
            std::cout << "File copied successfully.\n";
        } else {
            std::cout << "Source file does not exist or is a directory.\n";
        }
    } catch (const fs::filesystem_error& e) {
        std::cout << "Error copying file: " << e.what() << "\n";
    }
}

// Function to move a file
void moveFile(const fs::path& currentPath) {
    std::string sourceFile, destFile;
    std::cout << "Enter source file name: ";
    std::cin >> sourceFile;
    std::cout << "Enter destination file name: ";
    std::cin >> destFile;

    fs::path sourcePath = currentPath / sourceFile;
    fs::path destPath = currentPath / destFile;

    try {
        if (fs::exists(sourcePath) && !fs::is_directory(sourcePath)) {
            fs::rename(sourcePath, destPath);
            std::cout << "File moved successfully.\n";
        } else {
            std::cout << "Source file does not exist or is a directory.\n";
        }
    } catch (const fs::filesystem_error& e) {
        std::cout << "Error moving file: " << e.what() << "\n";
    }
}

int main() {
    fs::path currentPath = fs::current_path(); // Start at the current directory
    int choice;

    while (true) {
        std::cout << "\n--- Basic File Manager ---\n";
        std::cout << "1. List files and directories\n";
        std::cout << "2. Change directory\n";
        std::cout << "3. Create a directory\n";
        std::cout << "4. Copy a file\n";
        std::cout << "5. Move a file\n";
        std::cout << "6. Exit\n";
        std::cout << "Enter your choice: ";
        std::cin >> choice;

        switch (choice) {
            case 1:
                listDirectory(currentPath);
                break;
            case 2:
                changeDirectory(currentPath);
                break;
            case 3:
                createDirectory(currentPath);
                break;
            case 4:
                copyFile(currentPath);
                break;
            case 5:
                moveFile(currentPath);
                break;
            case 6:
                std::cout << "Exiting the file manager.\n";
                return 0;
            default:
                std::cout << "Invalid choice. Please try again.\n";
        }
    }

    return 0;
}
