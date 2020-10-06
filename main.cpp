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
    std::string FF_outputFileName = "firstfit";
    std::string BF_outputFileName = "bestfit";
    std::string WF_outputFileName = "worstfit";
    if(argc == 5) {
        fileName = argv[1];
        FF_outputFileName = argv[2];
        BF_outputFileName = argv[3];
        WF_outputFileName = argv[4];
    } else {
        // Not enough required arguments
    }

    // Read names from file
    std::vector<std::string> names = {};
    readFile(names, fileName);

    unsigned int size = names.size();

    int* randomNumbers = new int[size];
    generateRandomDeletedNumbers(randomNumbers, size);

    AllocationStrategy* FF = new FirstFit();
    AllocationStrategy* BF = new BestFit();
    AllocationStrategy* WF = new WorstFit();

    // Perform
    perform(FF, names, randomNumbers);
    perform(BF, names, randomNumbers);
    perform(WF, names, randomNumbers);

    // Write results to file
    FF->print(FF_outputFileName);
    BF->print(BF_outputFileName);
    WF->print(WF_outputFileName);
}
