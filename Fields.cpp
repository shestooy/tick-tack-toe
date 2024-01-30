
#include "Fields.h"
#include <iostream>
#include <algorithm>
#include <omp.h>

Fields::Fields() {
    for (int _y = 0; _y < SIZE; ++_y) {
        for (int _x = 0; _x < SIZE; ++_x) {
            _boardFields[_y][_x] = 0;
        }
    }
}

Fields::~Fields() = default;


void Fields:: Set(int _count, int _y, int _x) {
    _boardFields[_y][_x] = _count;
}

    double Fields::Analysis() {

        int tmp = (OrderOfMove) ? 1 : -1;

        int count = 0;
        for (int i = 0; i < SIZE; ++i) {
            if (_boardFields[i][i] == 0) {
                break;
            }
            if (_boardFields[i][i] == _boardFields[0][0]) {
                ++count;
            }
        }

        if (count >= SIZE) {
            return (_boardFields[0][0] == 1) ? 1 * tmp : -1 * tmp;
        }

        count = 0;
        for (int i = 0, j = SIZE - 1; i < SIZE; ++i, --j) {
            if (_boardFields[i][j] == 0) {
                break;
            }
            if (_boardFields[i][j] == _boardFields[0][SIZE - 1]) {
                ++count;
            }
        }

        if (count >= SIZE) {
            return (_boardFields[0][SIZE - 1] == 1) ? 1 * tmp : -1 * tmp;
        }



        for (int _y = 0; _y < SIZE; ++_y) {
            int count = 0;
            for (int _x = 0; _x < SIZE; ++_x) {
                if (_boardFields[_y][_x] == 0) { break; }
                if (_boardFields[_y][_x] == _boardFields[_y][0]) { ++count; }
            }

            if (count >= SIZE) {
                return (_boardFields[_y][0] == 1) ? 1 * tmp : -1 * tmp;
            }
        }

        for (int x = 0; x < SIZE; ++x) {
            int count = 0;
            for (int y = 0; y < SIZE; ++y) {
                if (_boardFields[y][x] == 0) { break; }
                if (_boardFields[y][x] == _boardFields[0][x]) { ++count; }
            }

            if (count >= SIZE) {
                return (_boardFields[0][x] == 1) ? 1 * tmp : -1 * tmp;
            }
        }

        return 0;
    }

std::vector<Step> Fields::generator() { //!
    std::vector<Step> result;
    for (int y = 0; y < SIZE; ++y) {
        for (int x = 0; x < SIZE; ++x) {
            if (_boardFields[y][x] == 0) {
                result.push_back(Step(OrderOfMove, y, x));
            }
        }
    }

    return result;
}

void Fields::Go(Step& step) { //!

    int moveValue = (step.crossMove) ? 1 : 2;
    Set(moveValue, step.y, step.x);
    OrderOfMove = !OrderOfMove;
}


bool Fields::CheckVal(Step& step) {
    std::vector<Step> steps = generator();
    for (auto i = 0; i < steps.size(); ++i) {
        if (steps[i] == step) { return true; }
    }

    return false;
}

bool CheckRow(const int* row, int size) {
    for (int j = 0; j < size; ++j) {
        if (row[j] == 0) {
            return false;
        }
    }
    return true;
}

bool Fields::Status() {
    if (Analysis() != 0) {
        return true;
    }

    bool result = true;

#pragma omp parallel for shared(result)
    for (int i = 0; i < SIZE; ++i) {
        if (!CheckRow(_boardFields[i], SIZE)) {
#pragma omp critical
            result = false;
        }
    }

    return result;
}
/*мы используем директиву #pragma omp parallel for для распараллеливания цикла проверки строк.
 * Ключевое слово shared(result) указывает, что переменная result является общей для всех потоков.
 * Директива #pragma omp critical используется для обеспечения атомарности операции записи в result.*/

int Fields::Get(int y, int x) {
    return _boardFields[y][x];
}

