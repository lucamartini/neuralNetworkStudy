#pragma once

#include <vector>
#include <memory>
#include "perceptron.h"
#include "linearfunction.h"

class Trainer;
class RandomHelper;
class TEfficiency;

class NeuralNetwork {
public:
    NeuralNetwork(int parameters, float learning_constant, float width, float height, const LinearFunction & linear, int size);
    ~NeuralNetwork();

    void initializeNetwork();

    void createTrainingDataset();

    void train();

    std::shared_ptr<TEfficiency> test(int tries, std::shared_ptr<TEfficiency> eff);

private:
    Perceptron percy;
    std::vector<std::unique_ptr<Trainer>> trainedDataset;
    RandomHelper rh;
    float width;
    float height;
    LinearFunction linear;
    int size;
};
