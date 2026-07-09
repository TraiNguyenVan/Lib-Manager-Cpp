## Quick notes
- Hello this no vibe code this thing yea?
- Well this thing still super new and definitely not well organized yet, so we are accepting any changes to improve this project
- Fix, replace anything that you think it will make this code better!
- Defenitely remember to make it a new commit or branch
- please dont `git push --force`, only do it if you know exactly what is happening like you want to reset the remote head back to a few commits.

## Features
- List avaliable commands by using `/help`
- Be able to load and save basic library data from a .txt file through command `/load <filename>` and `/save <filename>` 
- Can list avaliable data with `/list <datatype>` with `<datatype>` are .eg `books`, (more will comming soon)...
- Clear screen using `/clear` and quit the program with `/quit`
    
## How to use
**Pre-built binary:**
```sh
./lib-manager
```
You can get the binary from [Release page]()(comming soon!)

**Build from source:**
```sh
make run       # build (incremental) + run
make build     # build only
make fresh     # full clean rebuild (redownloads deps)
make clean     # just remove build/
```

## Project structure 
```
Lib-Manager-Cpp/
├── CMakeLists.txt          # Build configuration
├── Makefile                # Convenience commands (run, build, fresh, clean)
├── database.txt            # Persistence data
│
├── include/                # Public headers
│   ├── api.hpp             # Translate the input from the TUI to specific method with the Library
│   ├── book.hpp            
│   ├── library.hpp          
│   ├── student.hpp         
│   ├── transaction.hpp     
│   └── tui.hpp             # Terminal UI (FTXUI)
│
└── src/                    # Implementation
    ├── main.cpp
    ├── api.cpp
    ├── book.cpp
    ├── library.cpp
    ├── student.cpp
    ├── transaction.cpp
    └── tui.cpp
```
