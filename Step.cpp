#include "Step.h"
Step::Step() = default;
Step::Step(bool _crossMove, int _y, int _x) : crossMove(_crossMove), y(_y), x(_x) {}
Step::~Step() = default;

bool Step::operator==(Step& step) const {
    return (crossMove == step.crossMove && x == step.x && y == step.y);
}

