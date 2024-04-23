cmake_minimum_required(VERSION 3.14)
project(SFML_GameV3)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES main.cpp
        Entity.cpp
        Entity.h
        Player.cpp
        Player.h
        Enemy.cpp
        Enemy.h
        ShootingSystem.cpp
        ShootingSystem.h
        Bullet.cpp
        Bullet.h
        ShootingSystemV2.cpp
        ShootingSystemV2.h
        BulletV2.cpp
        BulletV2.h
        ShootingSystemV3.cpp
        ShootingSystemV3.h
        SpawnHandler.cpp
        SpawnHandler.h
)
add_executable(SFML_GameV3 ${SOURCE_FILES})
include_directories(/usr/local/include)

find_package(SFML 2.5 COMPONENTS system window graphics network audio REQUIRED)
include_directories(${SFML_INCLUDE_DIRS})
target_link_libraries(SFML_GameV3 sfml-system sfml-window sfml-graphics sfml-audio sfml-network)