cmake_minimum_required(VERSION 4.0)
project(PF_Final_Project)

set(CMAKE_CXX_STANDARD 20)
find_package(raylib CONFIG REQUIRED)

add_executable(PF_Final_Project main.cpp
        Spaceship.cpp
        Spaceship.h
        Obstacles.cpp
        Obstacles.h
        Bullets.cpp
        Bullets.h
        Aliens.cpp
        Aliens.h
        Boss.cpp
        Boss.h
        GameData.cpp
        GameData.h
        GameUtilities.cpp
        GameUtilities.h
)
target_link_libraries(PF_Final_Project PRIVATE raylib)
