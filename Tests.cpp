#include "Tests.h"


void test1(){
    Fields field;
    field.Set(1, 0, 0);
    int value = field.Get(0, 0);
    assert(value == 1);
}

void test2(){
    Fields field;
    field.Set(1, 0, 0);
    field.Set(1, 0, 1);
    field.Set(1, 0, 2);
    double result = field.Analysis();
    assert(result == 1.0);
}

void test3(){
    Fields field;
    field.Set(1, 0, 0);
    field.Set(2, 1, 1);
    field.Set(1, 2, 2);

    std::vector<Step> moves = field.generator();
    assert(moves.size() == 6);

    for (const auto& move : moves) {
        assert(field.Get(move.y, move.x) == 0);
    }
}

void test4()
{
    Fields field;
    Step move{true, 1, 1};
    field.Go(move);
    assert(field.Get(1, 1) == 1);
}

void test5(){
    Fields field;
    field.Set(1, 0, 0);
    field.Set(2, 0, 1);
    field.Set(1, 0, 2);
    field.Set(2, 1, 0);
    field.Set(1, 1, 1);
    field.Set(2, 1, 2);
    field.Set(1, 2, 0);
    field.Set(2, 2, 1);
    field.Set(1, 2, 2);

    assert(field.Status());
}


void runTest(){
    test1();
    std::cout<<"Тест 1 пройден"<<std::endl;
    test2();
    std::cout<<"Тест 2 пройден"<<std::endl;
    test3();
    std::cout<<"Тест 3 пройден"<<std::endl;
    test4();
    std::cout<<"Тест 4 пройден"<<std::endl;
    test5();
    std::cout<<"Тест 5 пройден"<<std::endl;
}