#include <iostream>
#include <filesystem>
#include <vector>
#include <map>
#include <set>
#include <fstream>

namespace fs = std::filesystem;

// Class responsible for scanning directories and finding duplicate source files
class DuplicateFileFinder
{
private:
    std::string rootPath;

    // Stores: filename -> set of project paths
    std::map<std::string, std::set<std::string>> fileProjects;

    // Stores grouped duplicate files: set of project paths -> list of filenames
    std::map<std::set<std::string>, std::vector<std::string>> grouped;

    // Checks whether file extension is valid
    bool isValidExtension(const std::string &extension)
    {
        static const std::set<std::string> validExtensions =
            {
                ".c",
                ".cpp",
                ".h",
                ".rc"};

        return validExtensions.find(extension) != validExtensions.end();
    }

public:
    DuplicateFileFinder(const std::string &path)
    {
        rootPath = path;
    }

    // Recursively scans all files and folders
    void scanFiles()
    {
        for (const auto &entry : fs::recursive_directory_iterator(rootPath))
        {
            // Skip non-regular files
            if (!entry.is_regular_file())
            {
                continue;
            }

            fs::path path = entry.path();

            // Get file extension
            std::string extension = path.extension().string();

            // Ignore unsupported file types
            if (!isValidExtension(extension))
            {
                continue;
            }

            std::string fileName = path.filename().string();

            std::string projectPath = path.parent_path().string();

            // Store: filename -> project path
            fileProjects[fileName].insert(projectPath);
        }
    }

    // Groups files that exist in the same projects
    void groupDuplicates()
    {
        for (const auto &item : fileProjects)
        {
            grouped[item.second].push_back(item.first);
        }
    }

    // Displays duplicate files and saves output to file
    void displayAndSaveResults()
    {
        std::ofstream outFile("output.txt");

        std::cout << std::endl;
        std::cout << "Duplicate Files Found:" << std::endl;
        std::cout << "======================" << std::endl;
        std::cout << std::endl;

        outFile << "Duplicate Files Found:" << std::endl;
        outFile << "======================" << std::endl;
        outFile << std::endl;

        for (const auto &group : grouped)
        {
            if (group.first.size() < 2)
            {
                continue;
            }

            for (const auto &project : group.first)
            {
                std::cout << project << std::endl;
                outFile << project << std::endl;
            }

            for (const auto &fileName : group.second)
            {
                std::cout << "\t" << fileName << std::endl;
                outFile << "\t" << fileName << std::endl;
            }

            std::cout << std::endl;
            outFile << std::endl;
        }

        outFile.close();

        std::cout << "Results saved to output.txt" << std::endl;
    }
};

int main(int argc, char *argv[])
{
    // Check command line argument
    if (argc < 2)
    {
        std::cout << "Usage: app.exe <directory_path>" << std::endl;
        return 1;
    }

    // Read directory path from command line
    std::string rootPath = argv[1];

    DuplicateFileFinder finder(rootPath);

    finder.scanFiles();

    finder.groupDuplicates();

    finder.displayAndSaveResults();

    return 0;
}




