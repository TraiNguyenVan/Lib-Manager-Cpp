# Lib-Manager-Cpp

A C++17 console application for managing a library's book catalog, student records, and borrowing transactions.

## Table of Contents

- [Features](#features)
- [Getting Started](#getting-started)
  - [Prerequisites](#prerequisites)
  - [Build from Source](#build-from-source)
  - [Pre-built Binary](#pre-built-binary)
- [Usage](#usage)
- [Data File Formats](#data-file-formats)
  - [Books Data](#books-data)
  - [Student Data](#student-data)
- [Project Structure](#project-structure)
- [Architecture](#architecture)
  - [Class Overview](#class-overview)
  - [Data Flow](#data-flow)
- [API Reference](#api-reference)
  - [Book](#book)
  - [Student](#student)
  - [Date](#date)
  - [Library](#library)
  - [Enums](#enums)
- [Code Formatter](#code-formatter)
- [Contributing](#contributing)
- [License](#license)

## Features

- **Book Management** -- Add, search, and persist book records with ISBN, title, author, and copy counts
- **Student Management** -- Load and organize student records by class, tracking borrowed books
- **Checkout & Return** -- Check out and return books with status feedback (not found, out of stock, user limit, overdue fines)
- **Date Utilities** -- Full date arithmetic: comparisons, day addition/subtraction, days-since-deadline calculation, leap year support
- **File Persistence** -- Load and save book and student data from/to flat text files
- **Data Formatting** -- Clang-format enforced code style for consistent contributions

## Getting Started

### Prerequisites

- C++17 compatible compiler (GCC, Clang, or MSVC)
- CMake 3.14 or higher
- Make (optional, for convenience commands)

Recommended on Linux, macOS, or WSL. Windows support is untested.

### Build from Source

```sh
# Clone the repository
git clone https://github.com/TraiNguyenVan/Lib-Manager-Cpp.git
cd Lib-Manager-Cpp

# Build and run
make run       # incremental build + run
make build     # build only
make fresh     # full clean rebuild
make clean     # remove build directory
```

Or build manually with CMake:

```sh
cmake -S . -B build
cmake --build build
./build/lib_manager
```

### Pre-built Binary

Download from the [Releases page](https://github.com/TraiNguyenVan/Lib-Manager-Cpp/releases) (coming soon).

```sh
./lib-manager
```

## Usage

The application loads book and student data from text files at startup, then provides an interactive console interface for library operations.

```cpp
// Programmatic example
Library lib(1, "City Library");
lib.loadBooks("./data/books-data.txt.example");
lib.loadStudents("./data/student-data.txt.example");

// Add a new book
Book book("978-0-13-468599-1", "The C++ Programming Language", "Bjarne Stroustrup", 5);
lib.addBook(book);

// Search for books
auto results = lib.searchBooks("C++");

// Check out a book
CheckoutStatus status = lib.checkOutBook("N25DECE086", "978-0-13-468599-1");

// Return a book
bool returned = lib.returnBook("N25DECE086", "978-0-13-468599-1");

// Save updated data
lib.saveBooks("./data/books-data.txt");
```

## Data File Formats

### Books Data

Each book is stored as a 4-line record. The file begins with the total book count.

```
<number of books>
<ISBN>
<title>
<author>
<available copies>
<ISBN>
<title>
...
```

See [`data/books-data.txt.example`](data/books-data.txt.example) for a complete example.

### Student Data

Students are grouped by class. The file begins with the number of classes.

```
<number of classes>
<class name>
<number of students in class>
<student name>
<student ID>
<number of borrowed books>
<borrowed book ISBN>
...
```

See [`data/student-data.txt.example`](data/student-data.txt.example) for a complete example.

## Project Structure

```
Lib-Manager-Cpp/
├── CMakeLists.txt              # Build configuration
├── Makefile                    # Convenience commands (run, build, fresh, clean)
├── main.cpp                    # Entry point
├── README.md                   # This file
├── CONTRIBUTING.md             # Contribution guidelines
├── LICENSE                     # MIT License
├── .clang-format               # Code formatting rules
├── .gitignore
│
├── data/                       # Sample data files
│   ├── books-data.txt.example
│   └── student-data.txt.example
│
├── docs/                       # Detailed documentation
│   └── architecture.md         # Architecture & design docs
│
├── include/                    # Public headers
│   ├── book.hpp
│   ├── date.hpp
│   ├── library.hpp
│   ├── student.hpp
│   └── transaction.hpp
│
└── src/                        # Implementation files
    ├── book.cpp
    ├── date.cpp
    ├── library.cpp
    ├── student.cpp
    └── transaction.cpp
```

## Architecture

### Class Overview

| Class | Responsibility |
|---|---|
| **Book** | Represents a book with ISBN, title, author, and available copies |
| **Student** | Represents a student with ID, name, phone, and borrowed book list |
| **Date** | Calendar date with full arithmetic support (add, subtract, compare, days-since-deadline) |
| **Library** | Core manager -- holds books, students, and transactions; handles I/O and checkout/return logic |
| **Transaction** | Placeholder for future borrowing transaction records |

### Data Flow

```
┌─────────────┐     load/save      ┌──────────────┐
│  Text Files  │ ◄──────────────►  │   Library     │
│  (.txt)      │                   │               │
└─────────────┘                    │  ┌──────────┐ │
                                   │  │ Books    │ │  unordered_map<ISBN, Book>
                                   │  ├──────────┤ │
                                   │  │ IDList   │ │  map<StudentID, Student>
                                   │  ├──────────┤ │
                                   │  │ ClassList│ │  map<ClassName, vector<ID>>
                                   │  ├──────────┤ │
                                   │  │ Trans-   │ │  vector<Transaction>
                                   │  │ actions  │ │
                                   │  └──────────┘ │
                                   └──────────────┘
```

## API Reference

### Book

```cpp
Book(string ISBN, string title, string author, int total_copies);
```

| Method | Returns | Description |
|---|---|---|
| `getISBN()` | `string` | The book's ISBN identifier |
| `getTitle()` | `string` | The book's title |
| `getAuthor()` | `string` | The book's author |
| `getAvailableCopies()` | `int` | Number of copies currently available |

### Student

```cpp
Student(string id, string name, string phone, int borrowedBooks, vector<string> borrowedBookISBNs);
```

| Method | Returns | Description |
|---|---|---|
| `getName()` | `string` | Student's full name |
| `getID()` | `string` | Student's unique ID |

### Date

```cpp
Date(int day, int month, int year);
```

| Method | Returns | Description |
|---|---|---|
| `daysSinceDeadline(Date endOfTermDate)` | `int` | Days overdue (0 if on time) |
| `operator+(int days)` | `Date` | Add days to date |
| `operator-(int days)` | `Date` | Subtract days from date |
| `operator-(const Date&)` | `long` | Days between two dates |
| `operator==`, `!=`, `<`, `>`, `<=`, `>=` | `bool` | Date comparisons |
| `operator<<` | `ostream&` | Output as `DD/MM/YYYY` |

### Library

```cpp
Library(int id, string name);
```

**Book Operations:**

| Method | Returns | Description |
|---|---|---|
| `addBook(const Book&)` | `InsertionStatus` | Add a book to the catalog |
| `checkOutBook(string id, string ISBN)` | `CheckoutStatus` | Check out a book to a student |
| `returnBook(string id, string ISBN)` | `bool` | Return a borrowed book |
| `searchBooks(string_view query)` | `vector<Book>` | Search books by query |
| `loadBooks(string filepath)` | `bool` | Load books from file |
| `saveBooks(string filepath)` | `bool` | Save books to file |

**Student Operations:**

| Method | Returns | Description |
|---|---|---|
| `loadStudents(string filepath)` | `bool` | Load students and classes from file |
| `saveStudents(string filepath)` | `bool` | Save students to file |

**Utility Methods:**

| Method | Returns | Description |
|---|---|---|
| `makeBookfromRecord(...)` | `Book` | Create a Book from raw fields |
| `makeRecord(Book&)` | `string` | Serialize a Book to a multi-line record |
| `makeRecords()` | `vector<string>` | Serialize all books |

### Enums

```cpp
enum class CheckoutStatus {
    Success,
    BookNotFound,
    UserNotFound,
    OutOfStock,
    UserLimitReached,
    UserHasOverdueFines
};

enum class InsertionStatus {
    Success,
    DuplicateISBN,
    InvalidData
};
```

## Code Formatter

This project uses **clang-format** to enforce consistent code style.

### VS Code

Install the [clang-format extension](https://marketplace.visualstudio.com/items?itemName=xaver.clang-format) or run:

```
ext install xaver.clang-format
```

Set as default formatter: right-click in a C++ file > **Format Document With** > **Configure Default Formatter** > **Clang-format**.

Format with `Ctrl + Shift + I`.

### Command Line

```sh
# Install
# Ubuntu/Debian
sudo apt install clang-format

# Fedora/RHEL
sudo dnf install clang-format

# macOS
brew install clang-format

# Format a file
clang-format -i <filename>
```

See [this issue](https://github.com/TraiNguyenVan/Lib-Manager-Cpp/issues/22) for more details.

## Contributing

See [CONTRIBUTING.md](CONTRIBUTING.md) for guidelines on how to contribute to this project.

## License

This project is licensed under the MIT License. See [LICENSE](LICENSE) for details.
