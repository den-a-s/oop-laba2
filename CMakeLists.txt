cmake_minimum_required(VERSION 3.0.0)
project(dining-philosophers)

set(SOURCES
    headers/fork.h
    headers/philosopher.h 
    src/fork.cpp 
    src/philosopher.cpp
    src/main.cpp
)

set(THREADS_PREFER_PTHREAD_FLAG ON)
find_package(Threads REQUIRED)

add_executable(${PROJECT_NAME} ${SOURCES})

target_link_libraries(${PROJECT_NAME} PRIVATE Threads::Threads)


