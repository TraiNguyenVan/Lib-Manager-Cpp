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
│
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
## Development Guideline can be found in the corespond project [here](https://github.com/users/TraiNguyenVan/projects/2/views/2) (though it is not well organized, please create issues to help us know how to improve)