#include <stdio.h>
#include <iostream>
#include <unistd.h>
#include <iomanip>
#include <vector>
#include <ctype.h>
#include <cstdlib>
#include <time.h>

#include <stdbool.h>
#include <sys/ioctl.h>
#include <termios.h>
#include <termios.h> 
#include <fcntl.h>
struct termios orig_termios;
void Sleep(int a)
{
    usleep(1000 * a);
}
void get(){
    tcgetattr(STDIN_FILENO, &orig_termios);
}
void set(){
    tcsetattr(STDIN_FILENO, TCSANOW, &orig_termios);
}

using namespace std;

#define MOVE_CURSOR(x, y) cout << "\033[" << (x) << ";" << (y) << "H"

enum SnakeDirection
{
    Stop = 0,
    Up,
    Down,
    Left,
    Right
};
bool gameRunning = true;
int width, height;

SnakeDirection userInput(SnakeDirection direction)
{   struct termios oldt, newt;
    int ch;
    int oldf;

    tcgetattr(STDIN_FILENO, &oldt);
    newt = oldt;
    newt.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &newt);
    oldf = fcntl(STDIN_FILENO, F_GETFL, 0);
    fcntl(STDIN_FILENO, F_SETFL, oldf | O_NONBLOCK);

    ch = getchar();

    fcntl(STDIN_FILENO, F_SETFL, oldf);

    if (ch != EOF)
    {
        switch (tolower(ch))
        {
        case 'w':
            if (direction != Down)
                return Up;
            break;
        case 's':
            if (direction != Up)
                return Down;
            break;
        case 'a':
            if (direction != Right)
                return Left;
            break;
        case 'd':
            if (direction != Left)
                return Right;
            break;
        default:
            return direction;
            break;
        }
    }

    return direction;
}

void HideCursor()
{
    cout << "\033[?25l";
    cout.flush();
}

void ShowCursor()
{
    cout << "\033[?25h";
    cout.flush();
}

void getTerminalSize(int &width, int &height)
{
    struct winsize w;
    if (ioctl(STDOUT_FILENO, TIOCGWINSZ, &w) == -1 || w.ws_col == 0)
    {
        width = 80;
        height = 25;
    }
    else
    {
        width = w.ws_col;
        height = w.ws_row;
    }


}

void setSize()
{
    getTerminalSize(width, height);
    width = 3 * width / 4;
    height = 3 * height / 4;
}

void setColor(int color)
{
    cout << "\033[" << color << "m";
}

void resetchange()
{
    cout << "\033[0m";
}

void setbold()
{
    cout << "\033[1m";
}

class Snake
{
private:
    vector<pair<int, int>> body;
    int length, prevX, prevY;
    SnakeDirection direction = Up;

public:
    Snake()
    {
        body.push_back({height / 2, width / 2});
        prevX = body.at(0).first;
        prevY = body.at(0).second;
        length = 1;
    }
    ~Snake()
    {
        body.clear();
        length = 0;
    }
    int getLength()
    {
        return length;
    }
    SnakeDirection getdirection()
    {
        return direction;
    }
    void setdirection(SnakeDirection direction)
    {
        this->direction = direction;
    }
    void updateSnake()
    {
        prevX = body.at(0).first, prevY = body.at(0).second;

        for (int i = 1; i < body.size(); i++)
        {
            int temp = body.at(i).first;
            body.at(i).first = prevX;
            prevX = temp;

            temp = body.at(i).second;
            body.at(i).second = prevY;
            prevY = temp;
        }

        switch (direction)
        {
        case Up:
            body.at(0).first--;
            break;
        case Down:
            body.at(0).first++;
            break;
        case Left:
            body.at(0).second--;
            break;
        case Right:
            body.at(0).second++;
            break;
        }
    }
    void changeLength()
    {
        body.resize(++length);
    }
    void printSnake()
    {
        MOVE_CURSOR(prevX, prevY);
        cout << " ";

        setColor(33);
        MOVE_CURSOR(1, 1);
        cout << "*";
        resetchange();

        MOVE_CURSOR(body.at(0).first, body.at(0).second);
        setColor(32);
        setbold();
        cout << "o";
        resetchange();
    }
    pair<int, int> getHead()
    {
        return body.at(0);
    }
    void checkBodyCollision()
    {
        for (int i = 1; i < length; i++)
        {
            if (body.at(i) == body.at(0))
            {
                gameRunning = false;
                break;
            }
        }
    }
};

class food
{
private:
    int x, y;

public:
    food()
    {
        srand((unsigned)time(0));
        x = rand() % height;
        srand((unsigned)time(0));
        y = rand() % width;
        if (x == 1 || x == 0)
        {
            x = 2;
        }
        if (y == 1 || y == 0)
        {
            y = 2;
        }
    }
    int getX()
    {
        return x;
    }
    int getY()
    {
        return y;
    }
    void setCoordinates()
    {
        srand((unsigned)time(0));
        x = rand() % height;
        srand((unsigned)time(0));
        y = rand() % width;
        if (x == 1 || x == 0)
        {
            x = 2;
        }
        if (y == 1 || y == 0)
        {
            y = 2;
        }
    }
    void printFood()
    {
        setColor(31);
        MOVE_CURSOR(x, y);
        cout << "#";
        resetchange();
    }
};

int setDifficulty()
{
    int difficulty;
    cout << "Enter number to adjust difficulty level: " << endl;
    cout << "1. Easy" << endl;
    cout << "2. Medium" << endl;
    cout << "3. Hard" << endl;
    cout << "4. Expert" << endl;
    cout << "Difficulty level: ";
    cin >> difficulty;
    switch (difficulty)
    {
    case 4:
        return 50;
        break;
    case 3:
        return 100;
        break;
    case 2:
        return 200;
        break;
    case 1:
        return 400;
        break;
    default:
        return 200;
        break;
    }
}

void printBoard()
{
    cout << "\033[2J\033[H";
    cout.flush();
    setColor(33);
    for (int i = 0; i <= height; i++)
    {
        for (int j = 0; j <= width; j++)
        {
            if (i == 0 || i == height || j == 0 || j == width)
            {
                MOVE_CURSOR(i, j);
                cout << "*"; // Border
            }
        }
    }
    resetchange();
}

void gameResult(string playerName, int score)
{
    cout << setw(22) << playerName << ", you scored : " << score << endl;

}

int main()
{
        get();
    string playerName;
    cout << "Enter Your Name : ";
    cin >> playerName;
    int dfc = setDifficulty();
    int score = 0;
    HideCursor();
    setSize();
    printBoard();
    Snake s;
    food f;
    while (gameRunning)
    {
        s.setdirection(userInput(s.getdirection()));
        s.updateSnake();

        if (s.getHead().first <= 1 || s.getHead().first >= height || s.getHead().second <= 1 || s.getHead().second >= width)
        {
            gameRunning = false;
            continue;
        }
        s.checkBodyCollision();

        if (f.getX() == s.getHead().first && f.getY() == s.getHead().second)
        {
            s.changeLength();
            f.setCoordinates();
            score += 10;
        }
        s.printSnake();
        f.printFood();
        Sleep(dfc);
    }
    gameResult(playerName, score);
    ShowCursor();
        set();
    return 0;
}
