#include <cmath>
#include "Function.h"
#include <SFML/Graphics.hpp>
#include <unistd.h>

Function::Function() {Start();}
Function::~Function() = default;

double Function::Minimax(Fields& board, int depth) {
    if (board.Status() || depth >= 5 ) {
        return board.Analysis();
    }

    double max = -INFINITY;
    std::vector<Step> steps = board.generator();

    Fields saved = board;
    Step local_move;

    for (int i = 0; i < steps.size(); ++i) {
        board.Go(steps[i]);
        double tmp = -Minimax(board, depth + 1);
        board = saved;

        if (tmp > max) {
            max = tmp;
            local_move = steps[i];
        }
    }

    if (depth == 0) {
        if (steps.size() > 0) {
            board.Go(local_move);
        }
    }

    return max;
}



int Function::Start() {
        int pos;
        int num_moves = 0;

        std::cout << "Выберите сторону:" << std::endl << "X - нажмите 1 "<<std::endl<< "0 - нажмите 0 "<< std::endl << "Первыми ходят Х"<< std::endl;
        int you;
        std::cin >> you;
        if (you == 0) {
            you = -1;
        }

        sf::RenderWindow window(sf::VideoMode(100*SIZE, 100*SIZE), "Tic-Tac-Toe");
        sf::RectangleShape cells[SIZE][SIZE];
        sf::Font font;
        if (!font.loadFromFile("C:/Users/kmkm2/CLionProjects/lava_3s/libs/arialmt.ttf")) {
            return -1;
        }
        while (window.isOpen()) {
            if (you == 1) {
                sf::Event event;
                while (window.pollEvent(event)) {

                    if (event.type == sf::Event::Closed) {
                        window.close();
                    } else if (event.type == sf::Event::MouseButtonPressed) {
                        if (event.mouseButton.button == sf::Mouse::Left) {
                            sf::Vector2i mousePos = sf::Mouse::getPosition(window);
                            int x = mousePos.x / 100;
                            int y = mousePos.y / 100;
                            Step step = Step(board.OrderOfMove, x , y );
                            std::cout << "Clicked coordinates: (" << x << ", " << y << ")" << std::endl;
                            if (board.CheckVal(step)) {
                                board.Go(step);
                                ++num_moves;
                                you = -you;
                            }
                        }
                    }
                }
            } else {
                Minimax(board, 0);
                ++num_moves;
                you = -you;
            }
            window.clear(sf::Color::White);

            // отрисовка поля by Kislov
            int cellSize = 100;
            for (int i = 0; i < SIZE; ++i) {
                for (int j = 0; j < SIZE; ++j) {
                    cells[i][j].setSize(sf::Vector2f(cellSize, cellSize));
                    cells[i][j].setPosition(sf::Vector2f(i * cellSize, j * cellSize));
                    cells[i][j].setOutlineThickness(1);
                    cells[i][j].setOutlineColor(sf::Color::Black);
                    cells[i][j].setFillColor(sf::Color::Transparent);
                    window.draw(cells[i][j]);
                }
            }

            // Отрисовка ноликов by Kislov
            sf::Text text;
            text.setFont(font);
            text.setCharacterSize(80);
            text.setFillColor(sf::Color::Black);
            for (int i = 0; i < SIZE; ++i) {
                for (int j = 0; j < SIZE; ++j) {
                    if (board.Get(i,j) == 1) {
                        text.setString("X");
                        text.setPosition(sf::Vector2f(i * cellSize + 20, j * cellSize));
                        window.draw(text);
                    }
                    else if (board.Get(i,j) == 2) {
                        text.setString("O");
                        text.setPosition(sf::Vector2f(i * cellSize + 20, j * cellSize));
                        window.draw(text);
                    }
                }
            }

            window.display();

            if (num_moves >= SIZE * SIZE) {
                std::cout << "Ничья!\n";
                sleep(3);
                window.close();
                sleep(20);
                return 0;
            }

            if (board.Analysis() * you > 0) {
                std::cout << "Ты победил машину!\n";
                sleep(3);
                window.close();
                sleep(20);
                return 0;
            }
            else if (board.Analysis() * you < 0) {
                std::cout << "Машина победила!\n";
                sleep(3);
                window.close();
                sleep(20);
                return 0;
            }
        }

        return 0;
}
