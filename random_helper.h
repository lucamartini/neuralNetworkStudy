#pragma once

#include <random>

class RandomHelper {
public:
    RandomHelper();
    float getRandomIn(float from, float to);
private:
    std::random_device rd;
    std::mt19937 e2;
};
