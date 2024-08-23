#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <conio.h> 
#include <thread>  
#include <chrono>  
using namespace std;

const char WALL = '#';
const char PATH = ' ';
const char START = 'S';
const char END = 'E';
const char MONEY = 'm';
const char PLAYER = 'P';

struct Position {
    int x, y;
};

void clearScreen() {
    cout << "\033[2J\033[1;1H";
}

void printMaze(const vector<vector<char>>& maze, const Position& playerPos) {
    for (int i = 0; i < maze.size(); ++i) {
        for (int j = 0; j < maze[i].size(); ++j) {
            if (i == playerPos.x && j == playerPos.y) {
                cout << PLAYER;
            }
            else {
                cout << maze[i][j];
            }
        }
        cout << endl;
    }
}

bool isValidMove(const vector<vector<char>>& maze, const Position& newPos) {
    return newPos.x >= 0 && newPos.x < maze.size() &&
        newPos.y >= 0 && newPos.y < maze[0].size() &&
        maze[newPos.x][newPos.y] != WALL;
}

void playLevel(vector<vector<char>> maze, Position startPos, Position endPos, int& totalScore) {
    Position playerPos = startPos;
    int moneyCount = 0;

    clearScreen();
    printMaze(maze, playerPos);

    while (true) {
        if (_kbhit()) {
            char move = _getch();

            Position newPos = playerPos;
            if (move == 'w' || move == 'W') newPos.x--;
            if (move == 's' || move == 'S') newPos.x++;
            if (move == 'a' || move == 'A') newPos.y--;
            if (move == 'd' || move == 'D') newPos.y++;

            if (isValidMove(maze, newPos)) {
                playerPos = newPos;

                clearScreen();
                printMaze(maze, playerPos);

                if (maze[newPos.x][newPos.y] == MONEY) {
                    moneyCount++;
                    maze[newPos.x][newPos.y] = PATH;
                    cout << "Money collected: " << moneyCount << endl;
                }
                if (newPos.x == endPos.x && newPos.y == endPos.y) {
                    totalScore += moneyCount * 10;
                    cout << "You reached the end! Score for this level: " << moneyCount * 10 << endl;
                    cout << "Press any key to continue to the next level..." << endl;
                    _getch();
                    break;
                }
            }
        }

        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }
}

int main() {
    srand(static_cast<unsigned int>(time(0)));
    int totalScore = 0;

    vector<vector<vector<char>>> levels = {
        {
            { '#', '#', '#', '#', '#', '#', '#', '#', '#', '#'},
            { '#', 'S', ' ', ' ', '#', 'm', ' ', ' ', ' ', '#'},
            { '#', '#', '#', ' ', '#', ' ', '#', '#', ' ', '#'},
            { '#', ' ', '#', ' ', ' ', ' ', ' ', '#', ' ', '#'},
            { '#', ' ', '#', '#', '#', '#', ' ', '#', ' ', '#'},
            { '#', ' ', ' ', ' ', ' ', ' ', ' ', '#', ' ', '#'},
            { '#', '#', '#', '#', '#', '#', ' ', '#', ' ', '#'},
            { '#', ' ', ' ', 'm', ' ', '#', ' ', ' ', 'E', '#'},
            { '#', ' ', '#', '#', ' ', '#', '#', '#', '#', '#'},
            { '#', '#', '#', '#', '#', '#', '#', '#', '#', '#'},
        },
        {
            { '#', '#', '#', '#', '#', '#', '#', '#', '#', '#'},
            { '#', 'S', ' ', ' ', '#', ' ', ' ', 'm', ' ', '#'},
            { '#', '#', '#', ' ', '#', ' ', '#', '#', ' ', '#'},
            { '#', ' ', '#', ' ', ' ', ' ', ' ', '#', ' ', '#'},
            { '#', ' ', '#', '#', '#', '#', '#', '#', ' ', '#'},
            { '#', ' ', ' ', ' ', ' ', '#', ' ', ' ', ' ', '#'},
            { '#', '#', '#', '#', ' ', '#', '#', '#', ' ', '#'},
            { '#', ' ', ' ', 'm', ' ', ' ', ' ', ' ', 'E', '#'},
            { '#', ' ', '#', '#', '#', '#', '#', '#', '#', '#'},
            { '#', '#', '#', '#', '#', '#', '#', '#', '#', '#'},
        },
        {
            { '#', '#', '#', '#', '#', '#', '#', '#', '#', '#'},
            { '#', 'S', ' ', ' ', '#', 'm', ' ', ' ', ' ', '#'},
            { '#', ' ', '#', ' ', '#', ' ', '#', '#', '#', '#'},
            { '#', ' ', '#', ' ', ' ', ' ', '#', '#', ' ', '#'},
            { '#', ' ', '#', '#', '#', '#', ' ', '#', ' ', '#'},
            { '#', ' ', ' ', ' ', ' ', ' ', ' ', '#', 'm', '#'},
            { '#', '#', '#', '#', '#', '#', ' ', '#', ' ', '#'},
            { '#', ' ', ' ', 'm', ' ', '#', ' ', ' ', 'E', '#'},
            { '#', ' ', '#', '#', ' ', '#', '#', '#', '#', '#'},
            { '#', '#', '#', '#', '#', '#', '#', '#', '#', '#'},
        },
        {
            { '#', '#', '#', '#', '#', '#', '#', '#', '#', '#'},
            { '#', 'S', ' ', ' ', '#', ' ', ' ', ' ', ' ', '#'},
            { '#', ' ', '#', ' ', '#', ' ', '#', '#', ' ', '#'},
            { '#', ' ', '#', ' ', '#', ' ', ' ', '#', ' ', '#'},
            { '#', ' ', '#', '#', '#', '#', ' ', '#', ' ', '#'},
            { '#', ' ', ' ', ' ', ' ', ' ', ' ', '#', 'm', '#'},
            { '#', '#', '#', '#', '#', '#', ' ', '#', ' ', '#'},
            { '#', ' ', ' ', 'm', ' ', '#', ' ', ' ', 'E', '#'},
            { '#', ' ', '#', '#', ' ', '#', '#', '#', '#', '#'},
            { '#', '#', '#', '#', '#', '#', '#', '#', '#', '#'},
        }
    };

    vector<Position> startPositions = { {1, 1}, {1, 1}, {1, 1}, {1, 1} };
    vector<Position> endPositions = { {7, 8}, {7, 8}, {7, 8}, {7, 8} };

    for (int i = 0; i < levels.size(); ++i) {
        cout << "Starting level " << i + 1 << "..." << endl;
        playLevel(levels[i], startPositions[i], endPositions[i], totalScore);
    }

    cout << "Game over! Total score: " << totalScore << endl;
    return 0;
}
