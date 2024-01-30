#ifndef LAVA_3S_FIELDS_H
#define LAVA_3S_FIELDS_H

#include <vector>
#include "Step.h"


#define SIZE 5


class Fields {
private:
    int _boardFields[SIZE][SIZE]{};
public:

    Fields(); // конструктор

    ~Fields(); // деструктор

    void Set(int _count, int _y, int _x); // вставка фигуры

    int Get(int y, int x);

    double Analysis(); // функция анализа состояния игрового поля: проверка стобцов на условие выйгрыша, строк и диагоналей

    std::vector<Step> generator();

    void Go(Step& step); // ход

    bool CheckVal(Step& step);

    bool Status(); // проверка на окончание игры методом проверки полей на занятость

    bool OrderOfMove = true;


};


#endif //LAVA_3S_FIELDS_H
