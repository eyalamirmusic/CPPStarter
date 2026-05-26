set(CMAKE_FOLDER Tests)

find_package(NanoTest REQUIRED)

nano_add_executable(CPPStarterTests
        SOURCES ExampleTests.cpp
        TARGETS CPPStarter)

target_link_libraries(CPPStarterTests PRIVATE cppstarter_warnings)
