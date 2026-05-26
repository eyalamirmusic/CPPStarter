# CPPStarter

A minimal C++20 / CMake project template.

## What you get

- CMake package management via [CPM.cmake](https://github.com/cpm-cmake/CPM.cmake).
- [Miro](https://github.com/eyalamirmusic/miro) wired in as a default dependency.
- Unit tests via [NanoTest](https://github.com/eyalamirmusic/NanoTest), auto-registered with CTest.
- `.gitignore`, `.clang-format`, `.clang-tidy`, MIT `LICENSE.txt` ready to go.
- A three-folder layout: `Lib/`, `Apps/`, `Tests/`.

## Layout

```
.
├── CMake/                # CPM + Find scripts + warnings
├── Lib/                  # Reusable library — always built
│   └── CPPStarter/
├── Apps/                 # Executables — top-level builds only
│   └── ExampleApp/
└── Tests/                # NanoTest suite — top-level builds only
```

## Build

```sh
cmake -B build
cmake --build build
ctest --test-dir build --output-on-failure
```

## Use as a dependency

When this project is added via `CPMAddPackage` (or `add_subdirectory`) from
another CMake project, only `Lib/` is configured. `Apps/` and `Tests/` are
gated on `PROJECT_IS_TOP_LEVEL`, so consumers don't pay for them. Pass
`-DCPPSTARTER_BUILD_TESTS=ON` or `-DCPPSTARTER_BUILD_APPS=ON` to force them on.

## Rename for your project

1. Replace `CPPStarter` with your project name in `CMakeLists.txt`, the
   `Lib/CPPStarter/` directory, the namespace, and the option prefixes.
2. Update `LICENSE.txt` with your copyright holder.
