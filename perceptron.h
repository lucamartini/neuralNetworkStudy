#pragma once

#include <vector>

#include "random_helper.h"

class Perceptron
{
public:
    Perceptron(float parameters, float learning_constant);
    void initWeights();
    int feedforward(std::vector<float> inputs);
    void train(std::vector<float> inputs, int desired);

private:
    std::vector<float> weights;
    float c;
    RandomHelper rh;

    int activate(float sum);
};

