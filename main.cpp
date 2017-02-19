#include <iostream>
#include <vector>
#include <memory>

#include <TEfficiency.h>
#include <TCanvas.h>

#include "src/neuralnetwork.h"
#include "src/linearfunction.h"

int main(int argc, char *argv[]) {

    // the truth
    LinearFunction linear(1, 2);

    std::vector<int> train_sizes = {0, 1, 10, 100, 1000, 10000};
    int bins = train_sizes.back() + 2;
    float lowEdge = train_sizes.front() - 1;
    float upEdge = train_sizes.back() + 1;
    TEfficiency eff_averaged("eff_averaged", "NN eff;training set;#epsilon", bins, lowEdge, upEdge);

    std::vector<std::shared_ptr<TEfficiency>> effs;
    for (int repetitions = 0; repetitions < 100; repetitions++) {
        std::shared_ptr<TEfficiency> eff = std::make_shared<TEfficiency>("eff", "NN eff;training set;#epsilon", bins, lowEdge, upEdge);
        effs.push_back(eff);

        for (int size : train_sizes) {
            NeuralNetwork nn(3, 0.01, 500, 500, linear, size);

            nn.initializeNetwork();

            nn.createTrainingDataset();

            nn.train();

            int tries = 100;
            nn.test(tries, eff);
        }
        eff_averaged.Add(*eff);
    }

    TCanvas canvas("canvas", "canvas", 400, 400);
    eff_averaged.Draw();
    canvas.SetLogx();
    canvas.Print("nn.pdf");

    return 0;
}

