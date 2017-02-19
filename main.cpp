#include <iostream>
#include <vector>

#include "random_helper.h"
#include "perceptron.h"
#include "trainer.h"

#include <TEfficiency.h>
#include <TCanvas.h>

RandomHelper rh;

float width(500);
float height(500);

// the truth
float f(float x) {
  return 2*x+1;
}

//float f(float x) {
//  return 0;
//}

std::vector<Trainer*> createTrainingDataset (int size) {

    std::vector<Trainer*> training(size);

    for (int i = 0; i < training.size(); i++) {
      float random_x = rh.getRandomIn(-width/2, width/2);
      float random_y = rh.getRandomIn(-height/2, height/2);

      int isPointAbove = (random_y > f(random_x)) ? 1 : -1;

      training.at(i) = new Trainer(random_x, random_y, isPointAbove);
   }
    return training;
}

int main(int argc, char *argv[]) {

    std::vector<int> train_sizes = {0, 1, 10, 100, 1000, 10000};
    TEfficiency eff_averaged("eff_averaged", "NN eff;training set;#epsilon", train_sizes.back() + 2, train_sizes.front() - 1, train_sizes.back() + 1);

    std::vector<TEfficiency *> effs;
    for (int repetitions = 0; repetitions < 100; repetitions++) {
        TEfficiency * eff = new TEfficiency("eff", "NN eff;training set;#epsilon", train_sizes.back() + 2, train_sizes.front() - 1, train_sizes.back() + 1);
        effs.push_back(eff);
        for (int size : train_sizes) {
            Perceptron percy(3, 0.01);
            percy.initWeights();
            std::vector<Trainer*> trainedDataset = createTrainingDataset(size);

            /// train
            for (int i = 0; i < size; i++) {
                percy.train(trainedDataset.at(i)->inputs, trainedDataset.at(i)->answer);
            }

            /// test
            int tries = 100;
            for (int i = 0; i < tries; i++) {
                std::vector<float> test = {rh.getRandomIn(-width/2, width/2), rh.getRandomIn(-height/2, height/2), 1};
                int guess = percy.feedforward(test);
                int above = test.at(1) > f(test.at(0)) ? 1 : -1;
                bool success = guess * above > 0;
                eff->Fill(success, size);
            }

            /// clean memory
            for (int i = 0; i < size; i++) {
                delete trainedDataset.at(i);
            }
        }
        eff_averaged.Add(*eff);
    }

    TCanvas canvas("canvas", "canvas", 400, 400);
    eff_averaged.Draw();
    canvas.SetLogx();
    canvas.Print("nn.pdf");

    for (int repetitions = 0; repetitions < 100; repetitions++) {
        delete effs.at(repetitions);
    }

    return 0;
}

