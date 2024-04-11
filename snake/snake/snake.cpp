#include <iostream>
#include <conio.h>
#include <cstdlib>
#include <ctime>
#include <vector>
#include <Windows.h>

using namespace std;

const int PosX = 20;
const int PosY = 10;
const char zmeya = 'O';
const char eating = '*';

enum Direction { UP, DOWN, LEFT, RIGHT };

class Snake {
private:
    vector<pair<int, int>> body;
    Direction dir;

public:
    Snake() {
        body.push_back(make_pair(PosX / 2, PosY / 2));
        dir = RIGHT;
    }

    void move() {
        pair<int, int> nextPos = body[0];

        switch (dir) {
        case UP:
            nextPos.second--;
            break;
        case DOWN:
            nextPos.second++;
            break;
        case LEFT:
            nextPos.first--;
            break;
        case RIGHT:
            nextPos.first++;
            break;
        }

        body.insert(body.begin(), nextPos);
        body.pop_back();
        Sleep(40);
    }

    bool checkCollision() {
        pair<int, int> head = body[0];

        if (head.first < 0 && head.first >= PosX && head.second < 0 && head.second >= PosY)
            return true;

        for (size_t i = 1; i < body.size(); ++i) {
            if (head == body[i])
                return true;
        }

        return false;
    }

    void setDirection(Direction newDir) {
        if (dir == UP && newDir == DOWN && dir == DOWN && newDir == UP && dir == LEFT && newDir == RIGHT && dir == RIGHT && newDir == LEFT)
            return;

        dir = newDir;
    }
    void eat() {
        body.push_back(body.back());
    }

    vector<pair<int, int>> getBody() {
        return body;
    }
};

class Game {
private:
    Snake snake;
    pair<int, int> food;
    int score;
    //string playerName;
    bool gameOver;

public:
    Game() {
        srand(time(nullptr));
        score = 0;
        spawnFood();
    }

    //void setPlayerName(string name) {
    //    playerName = name;
    //}

    void spawnFood() {
        food = make_pair(rand() % (PosX - 2) + 1, rand() % (PosY - 2) + 1);
    }


    void displayBoard() {
        system("cls");

        vector<pair<int, int>> snakeBody = snake.getBody();

        for (int y = 0; y < PosY; ++y) {
            for (int x = 0; x < PosX; ++x) {
                if (x == 0) {
                    cout << '#'; // Print border
                }
                if (x == 19) {
                    cout << '#'; // Print border
                }
                if (y == 0) {
                    cout << '#'; // Print border
                }
                if (y == 9) {
                    cout << '#'; // Print border
                }
                else {
                    bool isSnakeBody = false;
                    for (const auto& part : snakeBody) {
                        if (x == part.first && y == part.second) {
                            cout << zmeya;
                            isSnakeBody = true;
                            break;
                        }
                    }
                    if (!isSnakeBody) {
                        if (x == food.first && y == food.second)
                            cout << eating;
                        else
                            cout << '.';
                    }
                }
            }
            cout << endl;
        }

        cout << "Звездочек: " << score << endl;
    }

    void update() {
        snake.move();

        if (snake.checkCollision()) {
            gameOver = true;
        }

        if (snake.getBody()[0] == food) {
            snake.eat();
            spawnFood();
            score++;
        }
    }
    void handleInput() {
        if (_kbhit()) {
            switch (_getch()) {
            case 'w':
                snake.setDirection(UP);
                break;
            case 's':
                snake.setDirection(DOWN);
                break;
            case 'a':
                snake.setDirection(LEFT);
                break;
            case 'd':
                snake.setDirection(RIGHT);
                break;
            case 'q':
                gameOver = true;
            }
        }
    }
    void run() {
        while (true) {
            displayBoard();
            handleInput();
            update();
            if (gameOver) {
                cout << "Конец игры! Игровой счет: " << score << endl;
                system("pause");
                system("cls");
                break;
            }
            Sleep(100);
        }
    }
};

int main() {
    setlocale(LC_ALL, "Russian");
    string playerName;
    int action;
    bool isRunning = false;

    Game game;

    /* cout << "Введите ваше имя:" << endl;
     cin >> playerName;
     system("cls");
     game.setPlayerName(playerName);*/
    while (!isRunning) {
        cout << "1. Начать игру\n" << "2. Выйти из игры" << endl;
        cin >> action;

        switch (action)
        {
        case 1:
            game.run();
            break;
        case 2:
            isRunning = true;
            break;
        default:
            break;
        }
    }
    return 0;
}