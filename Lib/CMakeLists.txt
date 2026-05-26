find_package(Miro REQUIRED)

set(CMAKE_FOLDER CPPStarter)

add_library(CPPStarter STATIC
        CPPStarter/CPPStarter.cpp)
target_include_directories(CPPStarter PUBLIC ${CMAKE_CURRENT_LIST_DIR})
target_link_libraries(CPPStarter
        PUBLIC Miro
        PRIVATE cppstarter_warnings)
