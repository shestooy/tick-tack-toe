#ifndef LAVA_3S_FUNCTION_H
#define LAVA_3S_FUNCTION_H

#include <iostream>
#include <vector>
#include "Fields.h"
#include "Step.h"

class Function {
private:
    Fields board;
public:
    Function();
    double Minimax(Fields& board, int depth);
    std::vector<Step> StepGenerator;
    int Start();
    ~Function();
};


#endif //LAVA_3S_FUNCTION_H
