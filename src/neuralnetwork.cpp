#include "neuralnetwork.h"
#include "perceptron.h"
#include "trainer.h"
#include "random_helper.h"

#include <TEfficiency.h>

NeuralNetwork::NeuralNetwork(int parameters, float learning_constant, float width, float height, const LinearFunction & linear, int size) :
    percy(parameters, learning_constant),
    trainedDataset(size),
    rh{},
    width(width),
    height(height),
    linear(linear),
    size(size){

}

NeuralNetwork::~NeuralNetwork(){
}

void NeuralNetwork::initializeNetwork() {
    percy.initWeights();
}

void NeuralNetwork::createTrainingDataset() {
    for (int i = 0; i < trainedDataset.size(); i++) {
      float random_x = rh.getRandomIn(-width/2, width/2);
      float random_y = rh.getRandomIn(-height/2, height/2);

      int isPointAbove = (random_y > linear.f(random_x)) ? 1 : -1;

      trainedDataset.at(i) = std::make_unique<Trainer>(random_x, random_y, isPointAbove);
   }
}

void NeuralNetwork::train() {
    for (int i = 0; i < size; i++) {
        percy.train(trainedDataset.at(i)->inputs, trainedDataset.at(i)->answer);
    }
}

std::shared_ptr<TEfficiency> NeuralNetwork::test(int tries, std::shared_ptr<TEfficiency> eff) {
    for (int i = 0; i < tries; i++) {
        std::vector<float> test = {rh.getRandomIn(-width/2, width/2), rh.getRandomIn(-height/2, height/2), 1};
        int guess = percy.feedforward(test);
        int above = test.at(1) > linear.f(test.at(0)) ? 1 : -1;
        bool success = guess * above > 0;
        eff->Fill(success, size);
    }
    return eff;
}
