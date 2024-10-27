#pragma once
#ifndef SHARED_DATA_H
#define SHARED_DATA_H

#include <memory>

class SharedData {
public:
    static std::shared_ptr<SharedData> getInstance() {
        static std::shared_ptr<SharedData> instance(new SharedData());
        return instance;
    }

    int getValue() const { return v; }
    void countUp() {
        v++;
    }

private:
    SharedData() : v(0) {}
    int v;
};

#endif // SHARED_DATA_H