#pragma once

#include <mutex>

class Fork
{
public:
    mutable std::mutex mtx;

    Fork() = default;
    Fork(const std::string& id);
private:
    std::string id;
};
