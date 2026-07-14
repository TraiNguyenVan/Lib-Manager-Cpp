## Table of content
[1. Quick notes](#quick-notes)
[2. Features](#features)
[3. How to use](#how-to-use)
[4. Project structure](#project-structure)
[5. Code formatter](#code-formatter)
[6. Development Guideline](#development-guideline-can-be-found-in-the-corespond-project-here-though-it-is-not-well-organized-please-create-issues-to-help-us-know-how-to-improve)


## Quick notes
- Hello you shouldnt vibe code this thing yea? you can ask AI but, be resonsible foryour code 🥀
- Well this thing still super new and definitely not well organized yet, so we are accepting any changes to improve this project
- Fix, replace anything that you think it will make this code better!
- Defenitely remember to make it a new commit or branch
- if you are one of the project's contributors, please dont `git push --force`, only do it if you know exactly what is happening like you want to reset the remote head back to a few commits.

## Features
(not yet, the project currently under highly development)
## How to use
**Pre-built binary:**
```sh
./lib-manager
```
You can get the binary from [Release page]()(comming soon!)

**Build from source:**
make sure you have cmake, gcc with c++ 17 supported installed, recommend to run this on wsl, linux or mac, i havent tried Windows yet so if anyone can guarantee this works fine on windows and depends on some specific dependencies then please update this readme.
```sh
make run       # build (incremental) + run
make build     # build only
make fresh     # full clean rebuild
make clean     # just remove build/
```

## Project structure 
```
Lib-Manager-Cpp/
├── CMakeLists.txt          # Build configuration
├── Makefile                # Convenience commands (run, build, fresh, clean)
├── main.cpp                # Entry point
├── lib plan.txt            # Planning notes
├── .gitignore
├── .clang-format
├── data/                   # data for the program to load from/save to
│   ├── books-data.txt.example
│   └── student-data.txt.example
│
├── include/                # Public headers
│   ├── book.hpp
│   ├── date.hpp
│   ├── library.hpp
│   ├── student.hpp
│   └── transaction.hpp
│
└── src/                    # Implementation
    ├── book.cpp
    ├── date.cpp
    ├── library.cpp
    ├── student.cpp
    └── transaction.cpp
```
## Code formatter
### This project will use clang-format as its default code formatter which you **have** to adopt to produce consistent code. The formatter can be installed by the following methods(proably more methods but your job is just to make it work so i dont bother what method do you use that much):

### If your are using Visual Studio Code family editor, you may need to install and use this extension below:

**Installation**

```https://marketplace.visualstudio.com/items?itemName=xaver.clang-format``` **or** type ctrl + p and put this: ```ext install xaver.clang-**format```

**Usage**
1. First set your default formatter to clang-format by: ```Right click on you C++ code > Format Documment With > Configure Default Formatter > Clang-format```
2. Format your code by pressing ```Ctrl + Shift + I```

### If you are not using Visual Studio Code, and lets say you are using linux in general, you must install the following package and run the format command to activate the formatter on your code:

**Installation**

Linux:
- Ubuntu/Debian: ```sudo apt install clang-format```
- Fedora/RHEL: ```sudo dnf install clang-format```

MacOS:
- ```brew install clang-format```
Windows:
- i am genuiely dont know:), [PR](https://github.com/TraiNguyenVan/Lib-Manager-Cpp/pulls) to add the instruction for Windows, push straight if you are project's contributor

**Usage**

Run the following command to format your code:

```clang-format -i <filename>```

### For more info about this section check [this issue](https://github.com/TraiNguyenVan/Lib-Manager-Cpp/issues/22)
---
#### Development Guideline can be found in the corespond project [here](https://github.com/users/TraiNguyenVan/projects/2/views/2) (though it is not well organized, please create issues to help us know how to improve)