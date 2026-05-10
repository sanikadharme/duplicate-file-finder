#include <iostream>
#include <filesystem>
#include <vector>
#include <map>
#include <set>
#include <fstream>

using namespace std;
namespace fs = filesystem;

class DuplicateFileFinder
{
private:
    string rootPath;

    map<string, set<string>> fileProjects;

    map<set<string>, vector<string>> grouped;

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

    void scanFiles()
    {
        for (const auto &entry : fs::recursive_directory_iterator(rootPath))
        {
            if (!entry.is_regular_file())
            {
                continue;
            }

            fs::path path = entry.path();

            string extension = path.extension().string();

            if (!isValidExtension(extension))
            {
                continue;
            }

            string fileName = path.filename().string();

            string projectPath = path.parent_path().string();

             fileProjects[fileName].insert(projectPath);
        }
    }

    void groupDuplicates()
    {
        for (const auto &item : fileProjects)
        {
            grouped[item.second].push_back(item.first);
        }
    }

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
    if (argc < 2)
    {
        cout << "Usage: app.exe <directory_path>" << endl;
        return 1;
    }

    string rootPath = argv[1];

    DuplicateFileFinder finder(rootPath);

    finder.scanFiles();

    finder.groupDuplicates();

    finder.displayAndSaveResults();

    return 0;
}