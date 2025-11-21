cmake_minimum_required(VERSION 4.0)
project(PF_Final_Project)

set(CMAKE_CXX_STANDARD 20)
find_package(raylib CONFIG REQUIRED)

add_executable(PF_Sample_Implement  "Source Code/main.cpp"
        "Source Code/Spaceship.cpp"
        "Source Code/Obstacles.cpp"
        "Source Code/Bullets.cpp"
        "Source Code/Aliens.cpp"
        "Source Code/Boss.cpp"
        "Source Code/GameData.cpp"
        "Source Code/GameUtilities.cpp"
)
target_link_libraries(PF_Sample_Implement PRIVATE raylib)
# Copying assets so the game can load them
file(COPY "Font" DESTINATION ${CMAKE_BINARY_DIR})
file(COPY "Graphics" DESTINATION ${CMAKE_BINARY_DIR})
file(COPY "Music" DESTINATION ${CMAKE_BINARY_DIR})
