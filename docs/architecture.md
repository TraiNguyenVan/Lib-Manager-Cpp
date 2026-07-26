# Architecture

This document describes the design and architecture of Lib-Manager-Cpp.

## Overview

Lib-Manager-Cpp is a console-based library management system built in C++17. It follows a simple object-oriented design with five core classes and a flat text-file persistence layer.

## Class Design

### Book

**File:** `include/book.hpp`, `src/book.cpp`

Represents a single book in the library catalog.

```
Book
├── ISBN        (string)   — Unique identifier
├── title       (string)   — Book title
├── author      (string)   — Author name
└── available_copies (int) — Copies currently available for checkout
```

- Immutable after construction (all getters are `const`, no setters)
- Identified by ISBN (used as the map key in Library)

### Student

**File:** `include/student.hpp`, `src/student.cpp`

Represents a student who can borrow books.

```
Student
├── id                (string)          — Unique student ID
├── name              (string)          — Full name
├── phone             (string)          — Contact phone
├── borrowedBooks     (int)             — Count of borrowed books
└── borrowedBookISBNs (vector<string>)  — ISBNs of borrowed books
```

- Identified by student ID
- Stores the list of currently borrowed book ISBNs

### Date

**File:** `include/date.hpp`, `src/date.cpp`

A calendar date class with full arithmetic support. Used for tracking due dates and calculating overdue periods.

```
Date
├── day   (int)
├── month (int)
└── year  (int)
```

**Key internals:**

- `toDayCount()` / `fromDayCount()` — Converts dates to/from a linear day count (since year 0) for arithmetic
- `daysInMonth()` — Returns days in a given month, accounting for leap years
- `isLeapYear()` — Standard leap year check (divisible by 4, not by 100, unless by 400)
- `CalculateDays()` — Calculates total days from a 1950-01-01 epoch (used in legacy `daysSinceDeadline`)
- `CalculateLeapYears()` — Counts leap years in a range

**Supported operators:**

| Operator | Description |
|---|---|
| `==`, `!=` | Equality |
| `<`, `>`, `<=`, `>=` | Ordering |
| `+` (int) | Add days |
| `-` (int) | Subtract days |
| `-` (Date) | Days between dates |
| `<<` | Output as `DD/MM/YYYY` |

### Library

**File:** `include/library.hpp`, `src/library.cpp`

The central manager class that holds all data and provides the main API.

```
Library
├── id          (int)                        — Library ID
├── name        (string)                     — Library name
├── Books       (unordered_map<string,Book>) — ISBN → Book
├── IDList      (map<string,Student>)        — StudentID → Student
├── ClassList   (map<string,vector<string>>) — ClassName → [StudentIDs]
└── transactions (vector<Transaction>)       — (placeholder)
```

**Data storage:**

- `Books` is an `unordered_map` keyed by ISBN for O(1) lookup
- `IDList` is an ordered `map` for student lookup by ID
- `ClassList` maps class names to lists of student IDs (public, used for debugging)

### Transaction

**File:** `include/transaction.hpp`, `src/transaction.cpp`

Currently a placeholder class. Planned to record borrowing history with checkout/return timestamps, due dates, and fine calculations.

## Data Flow

### Load Phase

```
Text File ──loadBooks()──► Library.Books
Text File ──loadStudents()──► Library.IDList + Library.ClassList
```

Books and students are loaded from flat text files into in-memory maps. The file format is line-based with a count header (see README.md for format details).

### Operations Phase

```
User Input ──► Library.checkOutBook() / returnBook() / searchBooks() / addBook()
                    │
                    ├── Modifies Books (available_copies)
                    ├── Modifies IDList (student borrowed lists)
                    └── Returns status enum
```

All operations happen in-memory against the loaded data structures.

### Save Phase

```
Library.Books ──saveBooks()──► Text File
Library.IDList ──saveStudents()──► Text File
```

Data is serialized back to the same text format for persistence.

## Design Decisions

1. **Flat text files** — Simple, human-readable format. Easy to debug and edit manually. No external database dependencies.

2. **ISBN as primary key** — Books are identified by ISBN, which is a natural unique identifier for books.

3. **Enum-based status codes** — Operations like checkout return strongly-typed enums (`CheckoutStatus`, `InsertionStatus`) instead of exceptions, making error handling explicit.

4. **Date arithmetic via day count** — Dates are converted to a linear day count for reliable comparison and arithmetic, avoiding month-end edge cases.

5. **Header/Source separation** — Each class has a `.hpp` header and `.cpp` implementation file, following standard C++ project conventions.

## Future Directions

- **Transaction history** — The `Transaction` class is stubbed out; implementing it will enable borrowing history, due date tracking, and fine calculation.
- **Remove `saveStudents()`** — Currently missing from the Library class (only `loadStudents` is implemented).
- **Phone numbers** — Student phone numbers are not loaded from data files yet (passed as empty string).
- **GUI or web interface** — The current console UI could be extended.
- **Database backend** — Replace flat files with SQLite or similar for concurrent access and better querying.
