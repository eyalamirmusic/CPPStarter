# CLAUDE.md

This file provides guidance to Claude Code (claude.ai/code) when working with code in this repository.

## Project

CPPStarter is a minimal C++20 / CMake project template. It ships a three-folder layout — `Lib/`, `Apps/`, `Tests/` — wired up with CPM-managed dependencies and NanoTest-based unit tests. The intent is that you copy this repo, rename `CPPStarter` to your project name, and start coding.

## Build Commands

```bash
# Configure and build
cmake -B build
cmake --build build

# Run all tests via CTest
ctest --test-dir build --output-on-failure

# Run a single test by name
./build/Tests/CPPStarterTests --test GreetsByName

# List all tests in an executable
./build/Tests/CPPStarterTests --list-tests

# Run the example app
./build/Apps/ExampleApp/ExampleApp

# Format code
clang-format -i Lib/CPPStarter/*.h Lib/CPPStarter/*.cpp Apps/**/*.cpp Tests/*.cpp
```

## Architecture

Top-level `CMakeLists.txt` configures C++20, exports `compile_commands.json`, and conditionally adds subdirectories:

- `Lib/` — always built. The reusable library (`CPPStarter` static lib). When this repo is consumed as a CPM dependency from another project, only this subdirectory is configured.
- `Apps/` — built when `PROJECT_IS_TOP_LEVEL` or `-DCPPSTARTER_BUILD_APPS=ON`. Each app lives in its own subdirectory (e.g. `Apps/ExampleApp/`).
- `Tests/` — built when `PROJECT_IS_TOP_LEVEL` or `-DCPPSTARTER_BUILD_TESTS=ON`. Uses NanoTest; tests auto-register with CTest via a post-build discovery step.

## Dependencies & CMake helpers

Dependencies are fetched via [CPM.cmake](https://github.com/cpm-cmake/CPM.cmake), vendored at `CMake/CPM.cmake`. Each dependency has a thin `Find<Name>.cmake` wrapper in `CMake/` that calls `CPMAddPackage`, so consumer code just does `find_package(Name REQUIRED)`.

- `CMake/FindMiro.cmake` — pulls in [Miro](https://github.com/eyalamirmusic/miro) (default `Lib/` dependency).
- `CMake/FindNanoTest.cmake` — pulls in [NanoTest](https://github.com/eyalamirmusic/NanoTest), used by `Tests/`.
- `CMake/CPPStarterWarnings.cmake` — defines the `cppstarter_warnings` INTERFACE target (`-Wall -Wextra -Wpedantic` / `/W4`). Link it `PRIVATE` on internal targets.

CMake helper filenames are **prefixed** (`CPPStarterWarnings.cmake`, not `Warnings.cmake`) because `CMAKE_MODULE_PATH` is shared with fetched dependencies — a generic name like `Warnings.cmake` will shadow same-named files in subprojects like Miro and break their configure step. Keep new helpers project-prefixed.

## Adding things

- **New source file in `Lib/`** — add it to the `add_library(CPPStarter ...)` list in `Lib/CMakeLists.txt`.
- **New app** — `mkdir Apps/MyApp/`, add a `CMakeLists.txt` with `add_executable(MyApp Main.cpp)` linking `CPPStarter` and `cppstarter_warnings`, then `add_subdirectory(MyApp)` in `Apps/CMakeLists.txt`.
- **New test file** — add it to `nano_add_executable(CPPStarterTests SOURCES ...)` in `Tests/CMakeLists.txt`. NanoTest's CTest discovery picks up each `nano::test(...)` case automatically.
- **New dependency** — create `CMake/Find<Name>.cmake` with `include(CPM)` + `CPMAddPackage(NAME <Name> GITHUB_REPOSITORY <org/repo> GIT_TAG <tag>)`, then `find_package(<Name> REQUIRED)` in the consuming `CMakeLists.txt`.

## Code Style

- C++20, Allman braces, 4-space indent, 85-column limit, left-aligned pointers (enforced by `.clang-format` and `.clang-tidy` in repo root).
- Use `auto` for variable declarations whenever possible.
- Use explicit return types (not `auto`) on functions.
- Modern RAII; no manual `new`/`delete`.
- No `m_` or `_` prefixes on members. For parameters that would shadow a member, use `xToUse` style (e.g. `nameToUse`).
- Class/struct data members go last, below methods.
- Run `clang-format` after every edit to a `.h` / `.cpp` file.
