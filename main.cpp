#include <stdio.h>
#include <stdlib.h>
#include <sys/queue.h>
#include <unistd.h>
#include <math.h>
#include "BestFit.h"
#include "FirstFit.h"
#include "WorstFit.h"

int main(int argc, char** argv) {
    std::string fileName = "";
    std::string FF_outputFileName = "firstfit.txt";
    std::string BF_outputFileName = "bestfit.txt";
    std::string WF_outputFileName = "worstfit.txt";
    if(argc >= 2) {
        fileName = argv[1];
        if(argc == 5) {
            FF_outputFileName = argv[2];
            BF_outputFileName = argv[3];
            WF_outputFileName = argv[4];
        } else {
            std::cout << "Output filename invalid. Proceeding with default output files." << std::endl;
        }
    } else {
        std::cout << "No input filename" << std::endl;
    }

    // Read names from file
    std::vector<std::string> names = {};
    readFile(names, fileName);

    unsigned int size = names.size();

    // Generate random indexes for dealocating later
    int* randomNumbers = new int[size];
    generateRandomDeletedNumbers(randomNumbers, size);

    // Create 3 allocation strategies
    AllocationStrategy* FF = new FirstFit();
    AllocationStrategy* BF = new BestFit();
    AllocationStrategy* WF = new WorstFit();

    // Perform for each allocation for the data set
    perform(FF, names, randomNumbers);
    perform(BF, names, randomNumbers);
    perform(WF, names, randomNumbers);

    // Write results to file
    FF->print(FF_outputFileName);
    BF->print(BF_outputFileName);
    WF->print(WF_outputFileName);
}
