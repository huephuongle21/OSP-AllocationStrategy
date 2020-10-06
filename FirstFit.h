#ifndef FIRSTFIT_H
#define FIRSTFIT_H

#include <iostream>
#include <string.h>
#include "AllocationStrategy.h"
#include "Utility.h"

class FirstFit : public AllocationStrategy {
    public:

    virtual ~FirstFit();

    virtual bool perform(std::string name);

};

#endif // FIRSTFIT_H