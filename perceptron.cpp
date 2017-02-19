#include "perceptron.h"

#include <stdexcept>
#include <iostream>

#include "random_helper.h"

Perceptron::Perceptron(float parameters, float learning_constant) :
    weights(parameters),
    c(learning_constant),
    rh{}{
}

void Perceptron::initWeights() {
    for (auto && w : weights) {
        w = rh.getRandomIn(-1, 1);
    }
}

// Provide the inputs and known answer.
void Perceptron::train(std::vector<float> inputs, int desired) {

  // Guess according to those inputs.
  int guess = feedforward(inputs);

  // Compute the error
  float error = desired - guess;

  // Adjust all the weights according to the error and learning constant.
  for (int i = 0; i < weights.size(); i++) {
    weights[i] += c * error * inputs.at(i);
  }
}

int Perceptron::feedforward(std::vector<float> inputs) {
    if (inputs.size() != weights.size()) {
        throw std::length_error("size is different!");
    }
    float sum = 0;
    for (int i = 0; i < weights.size(); i++) {
        sum += inputs.at(i)*weights.at(i);
    }
    // Result is the sign of the sum, -1 or +1.
    // Here the perceptron is making a guess.
    // Is it on one side of the line or the other?
    return activate(sum);
}

int Perceptron::activate(float sum) {
  if (sum > 0) return 1;
  else return -1;
}


