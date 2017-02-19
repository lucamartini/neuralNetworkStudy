#include "random_helper.h"

RandomHelper::RandomHelper() :
    rd{},
    e2(rd())
{}

float RandomHelper::getRandomIn(float from, float to) {
    std::uniform_real_distribution<float> dist(from, to);
    return dist(e2);
}
