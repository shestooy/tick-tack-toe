
#ifndef LAVA_3S_STEP_H
#define LAVA_3S_STEP_H


class Step {

    public:
        bool crossMove;
        int y, x;
    Step();
    Step(bool _crossMove, int _y, int _x);
    ~Step();
    bool operator==(Step& step) const;

};

#endif //LAVA_3S_STEP_H
