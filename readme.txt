----------------------------------------
PROJECT: Duplicate File Finder 
----------------------------------------

----------------------------------------
DESCRIPTION
----------------------------------------

This program recursively scans a directory tree and identifies duplicate source files based on filename.

Supported file types:
- .c
- .cpp
- .h
- .rc

Files that exist in exactly the same projects/folders are grouped together and displayed in the output.

The program uses:
- Object-Oriented Programming
- STL containers (map, set, vector)
- C++17 filesystem library

Results are displayed on the console and also saved to output.txt.

----------------------------------------
USAGE
----------------------------------------

Compile:

g++ -std=c++17 main.cpp -o output

Run:

./output <directory_path>

Example:

./output /home/Projects

----------------------------------------
OUTPUT FORMAT
----------------------------------------

Example:

Duplicate Files Found:
======================

Projects/App1
Projects/App2
    main.cpp
    util.h

Projects/App1
Projects/App2
Projects/App3
    config.h

Results saved to output.txt

----------------------------------------
LIMITATIONS AND CONSIDERATIONS
----------------------------------------

1. Duplicate detection is based only on filename.

2. File contents are not compared.

3. Files with same name but different contents are still treated as duplicates.

4. Very large directory structures may increase memory usage and traversal time.

5. The current implementation is single-threaded.

----------------------------------------
MULTITHREADING NOTE
----------------------------------------

The program could be modified to support multithreading by scanning multiple subdirectories in parallel.

----------------------------------------
PERFORMANCE NOTES
----------------------------------------

1. STL containers provide efficient insertion and lookup operations.

2. std::set automatically removes duplicate project paths.

3. The program is designed to handle thousands of files and projects.

4. Performance mainly depends on filesystem speed and storage performance.

5. Extremely large repositories may require additional optimization and parallel processing for better scalability.

----------------------------------------
CM&L CODING GUIDE NOTES
----------------------------------------

The implementation attempts to follow clean and readable coding practices:

- Meaningful variable and function names
- Object-oriented structure
- Modular design
- Use of standard C++17 features
- STL usage instead of platform-specific code
- Simple and readable implementation

Some advanced exception handling and enterprise-level abstractions were intentionally omitted to keep the solution concise and readable for the scope of this task.
