#include <iostream>
#include <filesystem>
#include <vector>
#include <map>
#include <set>
#include <fstream>

using namespace std;
namespace fs = filesystem;

// Class responsible for scanning directories and finding duplicate source files
class DuplicateFileFinder
{
private:
    string rootPath;

    // Stores: filename -> set of project paths
    map<string, set<string>> fileProjects;

    // Stores grouped duplicate files: set of project paths -> list of filenames
    map<set<string>, vector<string>> grouped;

    // Checks whether file extension is valid
    bool isValidExtension(const string &extension)
    {
        static const set<string> validExtensions =
        {
            ".c",
            ".cpp",
            ".h",
            ".rc"
        };

        return validExtensions.find(extension) != validExtensions.end();
    }

    public:
    DuplicateFileFinder(const string &path)
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
            string extension = path.extension().string();

            // Ignore unsupported file types
            if (!isValidExtension(extension))
            {
                continue;
            }

            string fileName = path.filename().string();

            string projectPath = path.parent_path().string();

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
        ofstream outFile("output.txt");

        cout << endl;
        cout << "Duplicate Files Found:" << endl;
        cout << "======================" << endl;
        cout << endl;

        outFile << "Duplicate Files Found:" << endl;
        outFile << "======================" << endl;
        outFile << endl;

        for (const auto &group : grouped)
        {
            if (group.first.size() < 2)
            {
                continue;
            }

            for (const auto &project : group.first)
            {
                cout << project << endl;
                outFile << project << endl;
            }

            for (const auto &fileName : group.second)
            {
                cout << "\t" << fileName << endl;
                outFile << "\t" << fileName << endl;
            }

            cout << endl;
            outFile << endl;
        }

        outFile.close();

        cout << "Results saved to output.txt" << endl;
    }
};

int main(int argc, char *argv[])
{
    // Check command line argument
    if (argc < 2)
    {
        cout << "Usage: app.exe <directory_path>" << endl;
        return 1;
    }

    // Read directory path from command line
    string rootPath = argv[1];

    DuplicateFileFinder finder(rootPath);

    finder.scanFiles();

    finder.groupDuplicates();

    finder.displayAndSaveResults();

    return 0;
}