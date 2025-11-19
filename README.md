# Dsa_Templates_questions

This repository is a collection of Data Structures & Algorithms (DSA) templates, example solutions, and contest-style problem implementations in C++. It's intended as a personal library of reusable code snippets and solved problems to speed up competitive programming and learning.

**Project Overview**

- **Purpose:** Provide ready-to-use algorithm templates and solved problems for practice and quick reference.
- **Main language:** C++ (modern standards like C++17/C++20 are used in examples).

**How to Build & Run (Windows PowerShell)**

- Compile a single file with g++:

```
g++ -std=c++17 -O2 -Wall path\to\file.cpp -o file.exe
```

- Example: compile and run `Segment_Tree_Template.cpp` with `input.txt` redirected:

```
g++ -std=c++17 -O2 -Wall Segment_Tree_Template.cpp -o segment.exe; .\segment.exe < input.txt > output.txt
```

- For files that read from standard input and write to standard output, use input redirection as shown above for testing with `input.txt`.

**Usage & Tips**

- **Quick reuse:** Copy templates from `macros.cpp`, `Segment_Tree_Template.cpp`, or `binary_lifting.cpp` into your working solution file.
- **Modify as needed:** Solutions are often written for clarity and speed — adjust types, limits, or IO methods for specific contests or judge requirements.
- **Test locally:** Use the provided `input.txt` and `output.txt` to verify behavior before submission.

**Contributing**

- Feel free to open issues or submit pull requests to add new templates, fix bugs, or improve documentation.
- When adding a new solution, include a short comment header with the problem name, approach, and complexity.

**Contact / Author**

- Repository owner: `Mahesh3355` (GitHub username). Open an issue or PR for questions or suggestions.

---

Happy coding — use these templates to accelerate your problem solving and learning!
