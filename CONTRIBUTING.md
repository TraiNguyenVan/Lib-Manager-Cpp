# Contributing to Lib-Manager-Cpp

Thank you for your interest in contributing! This guide will help you get started.

## Getting Started

1. **Fork** the repository on GitHub
2. **Clone** your fork locally:
   ```sh
   git clone https://github.com/<your-username>/Lib-Manager-Cpp.git
   cd Lib-Manager-Cpp
   ```
3. **Build** the project:
   ```sh
   make build
   ```

## Development Workflow

1. Create a new branch from `main`:
   ```sh
   git checkout -b feature/your-feature-name
   ```
2. Make your changes
3. Format your code with clang-format (see below)
4. Test your changes by building and running:
   ```sh
   make run
   ```
5. Commit with a clear, descriptive message
6. Push to your fork and open a Pull Request

## Code Style

This project uses **clang-format** to enforce consistent formatting. The configuration is in `.clang-format`.

**You must format your code before committing.** Any PR with unformatted code will need revisions.

```sh
# Format a single file
clang-format -i src/myfile.cpp

# Format all source files
clang-format -i src/*.cpp include/*.hpp main.cpp
```

### Style Guidelines

- Use **17**-style C++ (C++17 standard)
- Header guards follow the pattern: `FILENAME_HPP` (e.g., `BOOK_HPP`)
- Class names are `PascalCase`
- Member variables are `snake_case`
- Methods are `camelCase` for private, `camelCase` or `PascalCase` for public
- Keep methods concise and well-structured
- Avoid unnecessary comments; let the code speak for itself

## Project Structure

```
src/          # Implementation (.cpp files)
include/      # Public headers (.hpp files)
data/         # Sample data files
docs/         # Additional documentation
main.cpp      # Entry point
```

- **Headers** go in `include/`
- **Implementations** go in `src/`
- Each class typically has a matching `.hpp` and `.cpp` pair
- Data files for testing go in `data/`

## Commit Messages

- Use clear, descriptive commit messages
- Start with a verb in imperative mood (e.g., "Add book search", "Fix date calculation")
- Reference issues when applicable (e.g., "Fix #12: incorrect leap year handling")

## Reporting Issues

- Use [GitHub Issues](https://github.com/TraiNguyenVan/Lib-Manager-Cpp/issues) to report bugs or request features
- Include steps to reproduce for bug reports
- Mention your OS, compiler, and CMake version when reporting build issues

## Code of Conduct

- Be respectful and constructive
- Focus on the code, not the person
- Help newcomers learn and improve

## Questions?

If you are unsure about anything, open an issue to ask. We are happy to help!
