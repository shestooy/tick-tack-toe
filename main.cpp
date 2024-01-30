#include <iostream>
#include <unistd.h>
#include "Function.h"
#include "Tests.h"


int main() {
    system("chcp 65001");
    system("CLS");
    std::cout << "Выберите действие:\n";
    std::cout << "1. Играть в игру\n";
    std::cout << "2. Запустить тесты\n";

    int tmp;
    std::cin >> tmp;

    switch (tmp) {
        case 1: {
            system("CLS");
            Function start;
            break;
        }
        case 2: {
            system("CLS");
            runTest();
            sleep(20);
            break;
        }
        default:
            std::cout << "Invalid tmp. Exiting.\n";
            break;
    }

    return 0;
}
