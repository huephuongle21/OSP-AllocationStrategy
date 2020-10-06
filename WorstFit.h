#ifndef WORSTFIT_H
#define WORSTFIT_H

#include <iostream>
#include <string.h>
#include "AllocationStrategy.h"
#include "Utility.h"

class WorstFit : public AllocationStrategy {
    public:

    virtual ~WorstFit();

    virtual bool perform(std::string name);

};

#endif // WORSTFIT_H