cmake_minimum_required(VERSION 3.10)
project(MorseDiaryApp)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

add_executable(app_1
        app_1.cpp
        Date.cpp
        Entry.cpp
        MorseConverter.cpp
        utils.cpp
)

add_executable(app_2
        app_2.cpp
        Date.cpp
        Entry.cpp
        MorseConverter.cpp
        utils.cpp
)

target_include_directories(app_1 PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})
target_include_directories(app_2 PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})