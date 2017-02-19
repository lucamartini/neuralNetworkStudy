#pragma once

#include <vector>

class Trainer
{
public:
    Trainer(float x, float y, int a);

    // A "Trainer" object stores the inputs and the correct answer.
    std::vector<float> inputs;
    int answer;
};

