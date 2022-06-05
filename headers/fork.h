#pragma once

#include <mutex>

class Fork
{
public:
    // мьютекс вилки
    mutable std::mutex mtx;

    Fork() = default;
    Fork(const std::string& id);
private:
    std::string id;
};
