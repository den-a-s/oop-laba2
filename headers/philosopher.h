#pragma once

#include <random>
#include <thread>
#include <chrono>
#include <iostream>
#include <mutex>
#include <thread>
#include <time.h>
#include <memory>

#include "fork.h"

class Philosopher
{
public:
    Philosopher(
        const std::string &name, 
        int appetite, 
        Fork& leftFork, 
        Fork& rightFork, 
        std::mutex& gLock);
    ~Philosopher();

    void stop();
    void run();
    void join();
private:

    void printAction(const std::string &msg);
    void ponder(int min_sec, int max_sec);
    void eat();
    void think();

    std::string m_name;
    int m_appetite;
    int m_foodEaten;
    Fork& m_leftFork;
    Fork& m_rightFork;
    std::mutex& m_gLock;
    std::thread m_thread;
    std::mt19937 m_range{std::random_device{}()};
    bool m_stopped;
};
