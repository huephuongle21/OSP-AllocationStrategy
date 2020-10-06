#ifndef BESTFIT_H
#define BESTFIT_H

#include <iostream>
#include <string.h>
#include "AllocationStrategy.h"
#include "Utility.h"

class BestFit : public AllocationStrategy {
    public:

    virtual ~BestFit();

    virtual bool perform(std::string name);

};

#endif // BESTFIT_H