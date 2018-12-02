#include <iostream>
#include <ctime>
#include <random>
#include <windows.h>
#include <vector>
#include <conio.h>

using namespace std;
#define sizee 15
#define initialSleep 400
int snake[sizee][sizee] = {0};
int score = 0, level;
struct point
{
    int x,y;
};
point head, fruit, tail, path, unit, prevFruit = {-1,-1}, prevTail;
vector <point> body;
vector <point> obs;

void gamePlay();
void slowDown(unsigned milliseconds);
void initial();
void obstacles(int num);
void ranfruit();
void print_matrix();
void shortesetPath();
void basicGamePlay();
void consumeFruit();
void clearScreen();
bool check_collision();
int unitDistance(int x);
void revObstacles();

int main()
{
    int mode;
    cout << "Enter the number of obstacles:" << endl;
    cin >> level;
    cout << "Enter 0 for Player mode and 1 for Computer mode" << endl;
    cin >> mode;
    if(mode == 1)
    {
        initial();
        point next;
        next.x = head.x + 1;
        next.y = head.y;
        body.push_back(next);
        tail = next;
        snake[next.x][next.y] = 7;
        ranfruit();
        obstacles(level);
        print_matrix();
        shortesetPath();
        basicGamePlay();
    }
    else if(mode == 0)
    {
        gamePlay();
    }
    else
    {
        cout << "Invalid Input" << endl;
    }
    return 0;
}

void print_matrix()
{
    cout << endl << endl;
    unsigned char hd = 2537, ft = 2792, br = 2736, os = 2558;
    //cout << fruit.x << " " << fruit.y << endl;
    int j=0;
    cout << "    " << br << br;
    for(int f = 1; f<=sizee; f++)
        cout << br << br;
    cout << br << endl;
    for(int i=0;i<sizee;i++)
        {
            cout << "    " << br << br;
            for(j=0;j<sizee-1;j++)
                {
                	if(snake[i][j] == 1)
                        cout << hd << " ";
                    else if(snake[i][j] == 7)
                        cout << "o ";
                	else if(snake[i][j] == 0)
                        cout <<"  ";
                    else if(snake[i][j] == 8)
                        cout << os <<" ";
                    else
                        cout << ft <<" ";
        		}
            if(snake[i][j] == 1)
                        cout << hd << br << br << endl;
                	else if(snake[i][j] == 7)
                        cout << "o" << br << br << endl;
                	else if(snake[i][j] == 0)
                        cout << " " << br << br << endl;
                    else if(snake[i][j] == 8)
                        cout << os << br << br << endl;
                    else
                        cout << ft << br << br << endl;
        }
    cout << "    " << br << br << br;
    for(int f = 1; f<=sizee; f++)
        cout << br << br;
    cout << endl;
    cout << "Score: " << score << endl;
    return;
}

void initial()
{
    srand(time(0));
    head.x = rand()%sizee;
    head.y = rand()%sizee;
    snake[head.x][head.y] = 1;
    tail = head;
    return;
}

int mod(int n)
{
    if(n<0)
        return -n;
    else
        return n;
}

void ranfruit()
{
    fruit.x = rand()%sizee;
    fruit.y = rand()%sizee;
    if(snake[fruit.x][fruit.y] == 0 && mod(fruit.x-head.x)>5 && mod(fruit.y-head.y)>5)
    {
        snake[fruit.x][fruit.y] = 9;
        return;
    }
    else
    {
        ranfruit();
    }
    return;
}

void shortesetPath()
{
    path.x = fruit.x - head.x;
    path.y = fruit.y - head.y;
    return;
}

void slowDown(unsigned milliseconds)
{
    Sleep(milliseconds);
}

void printBody()
{
    for(int i=0;i<body.size();i++)
    {
        snake[body[i].x][body[i].y] = 7;
    }
}

void snakeBody()
{
    for(int i=body.size()-1; i>0; i--)
        body[i] = body[i-1];
    body[0] = head;
    prevTail = tail;
    snake[tail.x][tail.y] = 0;
    tail = body[body.size()-1];
    for(int i=0;i<body.size();i++)
    {
        snake[body[i].x][body[i].y] = 7;
    }
}

void revObstacles()
{
    for(int i=0;i<obs.size()-1;i++)
    {
        snake[obs[i].x][obs[i].y] = 0;
    }
    obs.clear();
}

void consumeFruit()
{
    if(head.x == fruit.x && head.y == fruit.y)
    {
        prevFruit = fruit;
        ranfruit();
        shortesetPath();
        score += 1;
        revObstacles();
        obstacles(level-1);
        basicGamePlay();
    }
}

void obstacles(int num)
{
    point p;
    srand(time(0));
    //cout << fruit.x << " " << fruit.y << endl << endl;
    for(int i=0;i<=num;i++)
        {
            do
            {
                p.x = rand()%sizee;
            }while(p.x == fruit.x);
           // cout << p.x << " ";

            do
            {
                p.y = rand()%sizee;
            }while(p.y == fruit.y);
           // cout << p.y << endl;
           // slowDown(500);
	        snake[p.x][p.y] = 8;
	        obs.push_back(p);
        }
}

bool check_collision()
{
    int xflag = 0;
    for(int i=0;i<obs.size();i++)
    {
        if((head.x == obs[i].x) && (head.y == obs[i].y))
        {
            xflag = 1; break;
        }
    }
    return xflag;
}

void basicGamePlay()
{
    unit.x = unitDistance(path.x);
    if(snake[head.x + unit.x][head.y] != 7)
    {

    while(head.x != fruit.x)
    {
        check_collision();
        snakeBody();
        head.x += unit.x;
        snake[head.x][head.y] = 1;
        if(prevTail.x == prevFruit.x && prevTail.y == prevFruit.y)
        {
            body.push_back(prevFruit);
            //snake[prevFruit.x][prevFruit.y] = 7;
        }
        clearScreen();
        if(snake[head.x + unit.x][head.y] == 7 || snake[head.x + unit.x][head.y] == 8 || snake[head.x][head.y] == 7 || snake[head.x][head.y] == 8)
        {
            print_matrix();
            cout << "Gameover" << endl;
            cout << "Score: " << score;
            break;
        }
        print_matrix();
        slowDown(initialSleep);
    }
    unit.y = unitDistance(path.y);
    while(head.y != fruit.y)
    {
        check_collision();
        snakeBody();
        head.y += unit.y;
        snake[head.x][head.y] = 1;
        if(prevTail.x == prevFruit.x && prevTail.y == prevFruit.y)
        {
            body.push_back(prevFruit);
            //snake[prevFruit.x][prevFruit.y] = 7;
        }
        clearScreen();
        if(snake[head.x][head.y+unit.y] == 7 || snake[head.x][head.y+unit.y] == 8)
        {
            print_matrix();
            cout << "Gameover" << endl;
            cout << "Score: " << score;
            break;
        }
        print_matrix();
        slowDown(initialSleep);
    }
    while(head.x != fruit.x)
    {
        check_collision();
        snakeBody();
        head.x += unit.x;
        snake[head.x][head.y] = 1;
        if(prevTail.x == prevFruit.x && prevTail.y == prevFruit.y)
        {
            body.push_back(prevFruit);
            //snake[prevFruit.x][prevFruit.y] = 7;
        }
        clearScreen();
        if(snake[head.x + unit.x][head.y] == 7 || snake[head.x + unit.x][head.y] == 8)
        {
            print_matrix();
            cout << "Gameover" << endl;
            cout << "Score: " << score;
            break;
        }
        print_matrix();
        slowDown(initialSleep);
    }
    unit.y = unitDistance(path.y);
    while(head.y != fruit.y)
    {
        check_collision();
        snakeBody();
        head.y += unit.y;
        snake[head.x][head.y] = 1;
        if(prevTail.x == prevFruit.x && prevTail.y == prevFruit.y)
        {
            body.push_back(prevFruit);
            //snake[prevFruit.x][prevFruit.y] = 7;
        }
        clearScreen();
        if(snake[head.x][head.y+unit.y] == 7  || snake[head.x][head.y+unit.y] == 8)
        {
            print_matrix();
            cout << "Gameover" << endl;
            cout << "Score: " << score;
            break;
        }
        print_matrix();
        slowDown(initialSleep);
    }
    while(head.x != fruit.x)
    {
        check_collision();
        snakeBody();
        head.x += unit.x;
        snake[head.x][head.y] = 1;
        if(prevTail.x == prevFruit.x && prevTail.y == prevFruit.y)
        {
            body.push_back(prevFruit);
            //snake[prevFruit.x][prevFruit.y] = 7;
        }
        clearScreen();
        if(snake[head.x + unit.x][head.y] == 7 || snake[head.x + unit.x][head.y] == 8 || snake[head.x][head.y] == 7 || snake[head.x][head.y] == 8)
        {
            print_matrix();
            cout << "Gameover" << endl;
            cout << "Score: " << score;
            break;
        }
        print_matrix();
        slowDown(initialSleep);
    }
    unit.y = unitDistance(path.y);
    while(head.y != fruit.y)
    {
        check_collision();
        snakeBody();
        head.y += unit.y;
        snake[head.x][head.y] = 1;
        if(prevTail.x == prevFruit.x && prevTail.y == prevFruit.y)
        {
            body.push_back(prevFruit);
            //snake[prevFruit.x][prevFruit.y] = 7;
        }
        clearScreen();
        if(snake[head.x][head.y+unit.y] == 7 || snake[head.x][head.y+unit.y] == 8)
        {
            print_matrix();
            cout << "Gameover" << endl;
            cout << "Score: " << score;
            break;
        }
        print_matrix();
        slowDown(initialSleep);
    }
    while(head.x != fruit.x)
    {
        check_collision();
        snakeBody();
        head.x += unit.x;
        snake[head.x][head.y] = 1;
        if(prevTail.x == prevFruit.x && prevTail.y == prevFruit.y)
        {
            body.push_back(prevFruit);
            //snake[prevFruit.x][prevFruit.y] = 7;
        }
        clearScreen();
        if(snake[head.x + unit.x][head.y] == 7 || snake[head.x + unit.x][head.y] == 8)
        {
            print_matrix();
            cout << "Gameover" << endl;
            cout << "Score: " << score;
            break;
        }
        print_matrix();
        slowDown(initialSleep);
    }
    unit.y = unitDistance(path.y);
    while(head.y != fruit.y)
    {
        check_collision();
        snakeBody();
        head.y += unit.y;
        snake[head.x][head.y] = 1;
        if(prevTail.x == prevFruit.x && prevTail.y == prevFruit.y)
        {
            body.push_back(prevFruit);
            //snake[prevFruit.x][prevFruit.y] = 7;
        }
        clearScreen();
        if(snake[head.x][head.y+unit.y] == 7  || snake[head.x][head.y+unit.y] == 8)
        {
            print_matrix();
            cout << "Gameover" << endl;
            cout << "Score: " << score;
            break;
        }
        print_matrix();
        slowDown(initialSleep);
    }
    consumeFruit();
    }
    else
    {
    while(head.y != fruit.y)
    {
        check_collision();
        snakeBody();
        unit.y = unitDistance(path.y);
        head.y += unit.y;
        snake[head.x][head.y] = 1;
        if(prevTail.x == prevFruit.x && prevTail.y == prevFruit.y)
        {
            body.push_back(prevFruit);
            //snake[prevFruit.x][prevFruit.y] = 7;
        }
        clearScreen();
        if(snake[head.x][head.y+unit.y] == 7  || snake[head.x][head.y+unit.y] == 8)
        {
            print_matrix();
            cout << "Gameover" << endl;
            cout << "Score: " << score;
            break;
        }
        print_matrix();
        slowDown(initialSleep);
    }
    while(head.x != fruit.x)
    {
        check_collision();
        snakeBody();
        unit.x = unitDistance(path.x);
        head.x += unit.x;
        snake[head.x][head.y] = 1;
        if(prevTail.x == prevFruit.x && prevTail.y == prevFruit.y)
        {
            body.push_back(prevFruit);
            //snake[prevFruit.x][prevFruit.y] = 7;
        }
        clearScreen();
        if(snake[head.x + unit.x][head.y] == 7 || snake[head.x + unit.x][head.y] == 8)
        {
            print_matrix();
            cout << "Gameover" << endl;
            cout << "Score: " << score;
            break;
        }
        print_matrix();
        slowDown(initialSleep);
    }
    while(head.y != fruit.y)
    {
        check_collision();
        snakeBody();
        unit.y = unitDistance(path.y);
        head.y += unit.y;
        snake[head.x][head.y] = 1;
        if(prevTail.x == prevFruit.x && prevTail.y == prevFruit.y)
        {
            body.push_back(prevFruit);
            //snake[prevFruit.x][prevFruit.y] = 7;
        }
        clearScreen();
        if(snake[head.x][head.y+unit.y] == 7  || snake[head.x][head.y+unit.y] == 8)
        {
            print_matrix();
            cout << "Gameover" << endl;
            cout << "Score: " << score;
            break;
        }
        print_matrix();
        slowDown(initialSleep);
    }
    while(head.x != fruit.x)
    {
        check_collision();
        snakeBody();
        unit.x = unitDistance(path.x);
        head.x += unit.x;
        snake[head.x][head.y] = 1;
        if(prevTail.x == prevFruit.x && prevTail.y == prevFruit.y)
        {
            body.push_back(prevFruit);
            //snake[prevFruit.x][prevFruit.y] = 7;
        }
        clearScreen();
        if(snake[head.x + unit.x][head.y] == 7 || snake[head.x + unit.x][head.y] == 8)
        {
            print_matrix();
            cout << "Gameover" << endl;
            cout << "Score: " << score;
            break;
        }
        print_matrix();
        slowDown(initialSleep);
    }
    while(head.y != fruit.y)
    {
        check_collision();
        snakeBody();
        unit.y = unitDistance(path.y);
        head.y += unit.y;
        snake[head.x][head.y] = 1;
        if(prevTail.x == prevFruit.x && prevTail.y == prevFruit.y)
        {
            body.push_back(prevFruit);
            //snake[prevFruit.x][prevFruit.y] = 7;
        }
        clearScreen();
        if(snake[head.x][head.y+unit.y] == 7  || snake[head.x][head.y+unit.y] == 8)
        {
            print_matrix();
            cout << "Gameover" << endl;
            cout << "Score: " << score;
            break;
        }
        print_matrix();
        slowDown(initialSleep);
    }
    while(head.x != fruit.x)
    {
        check_collision();
        snakeBody();
        unit.x = unitDistance(path.x);
        head.x += unit.x;
        snake[head.x][head.y] = 1;
        if(prevTail.x == prevFruit.x && prevTail.y == prevFruit.y)
        {
            body.push_back(prevFruit);
            //snake[prevFruit.x][prevFruit.y] = 7;
        }
        clearScreen();
        if(snake[head.x + unit.x][head.y] == 7 || snake[head.x + unit.x][head.y] == 8)
        {
            print_matrix();
            cout << "Gameover" << endl;
            cout << "Score: " << score;
            break;
        }
        print_matrix();
        slowDown(initialSleep);
    }
    while(head.y != fruit.y)
    {
        check_collision();
        snakeBody();
        unit.y = unitDistance(path.y);
        head.y += unit.y;
        snake[head.x][head.y] = 1;
        if(prevTail.x == prevFruit.x && prevTail.y == prevFruit.y)
        {
            body.push_back(prevFruit);
            //snake[prevFruit.x][prevFruit.y] = 7;
        }
        clearScreen();
        if(snake[head.x][head.y+unit.y] == 7  || snake[head.x][head.y+unit.y] == 8)
        {
            print_matrix();
            cout << "Gameover" << endl;
            cout << "Score: " << score;
            break;
        }
        print_matrix();
        slowDown(initialSleep);
    }
    while(head.x != fruit.x)
    {
        check_collision();
        snakeBody();
        unit.x = unitDistance(path.x);
        head.x += unit.x;
        snake[head.x][head.y] = 1;
        if(prevTail.x == prevFruit.x && prevTail.y == prevFruit.y)
        {
            body.push_back(prevFruit);
            //snake[prevFruit.x][prevFruit.y] = 7;
        }
        clearScreen();
        if(snake[head.x + unit.x][head.y] == 7 || snake[head.x + unit.x][head.y] == 8)
        {
            print_matrix();
            cout << "Gameover" << endl;
            cout << "Score: " << score;
            break;
        }
        print_matrix();
        slowDown(initialSleep);
    }
    consumeFruit();
    }
}

int unitDistance(int x)
{
    if(x<0)
        return -1;
    else
        return 1;
}

void gamePlay();
void printmatrixplayer();
void initarray();
void move(int dirx, int diry);
void update();
void changeDirection(char key);
void clearScreen();
void ranfruitplayer();
void obstaclesPlayer();

char getarrayValue(int value);

const int arraywidth = sizee+2;
const int arrayheight = sizee+2;

const int size = arraywidth * arrayheight;

int array[size];


int headplayerx;
int headplayery;
int direction;
int fruitplayer = 2;
int zzz = 0;

bool gameIsOn;
vector <point> playerVect;


void gamePlay()
{

    initarray();
    gameIsOn = true;
    while (gameIsOn) {

        if (kbhit()) {

            changeDirection(getch());
        }

        update();


        clearScreen();


        printmatrixplayer();


        slowDown(initialSleep - 20*zzz);
    }


    cout << "Game over!" << endl << "Score: " << fruitplayer-2;


    cin.ignore();
}


void changeDirection(char key) {

    switch (key) {
    case 'w':
        if (direction != 2) direction = 0;
        break;
    case 'W':
        if (direction != 2) direction = 0;
        break;
    case '8':
        if (direction != 2) direction = 0;
        break;
    case 'd':
        if (direction != 3) direction = 1;
        break;
    case 'D':
        if (direction != 3) direction = 1;
        break;
    case '6':
        if (direction != 3) direction = 1;
        break;
    case 's':
        if (direction != 0) direction = 2;
        break;
    case 'S':
        if (direction != 0) direction = 2;
        break;
    case '5':
        if (direction != 0) direction = 2;
        break;
    case 'a':
        if (direction != 1) direction = 3;
        break;
    case 'A':
        if (direction != 1) direction = 3;
        break;
    case '4':
        if (direction != 1) direction = 3;
        break;
    }
}


void move(int dirx, int diry) {

    int newx = headplayerx + dirx;
    int newy = headplayery + diry;

    if (array[newx + newy * arraywidth] == -2) {

        fruitplayer++;
        ranfruitplayer();
    }


    else if (array[newx + newy * arraywidth] != 0) {
        gameIsOn = false;
    }


    headplayerx = newx;
    headplayery = newy;
    array[headplayerx + headplayery * arraywidth] = fruitplayer + 1;

}


void clearScreen() {

    system("cls");
}


void ranfruitplayer() {
    int x = 0;
    int y = 0;
    zzz++;
    do {

        x = rand() % (arraywidth - 2) + 1;
        y = rand() % (arrayheight - 2) + 1;


    } while (array[x + y * arraywidth] != 0);
    obstaclesPlayer();

    array[x + y * arraywidth] = -2;
}


void update() {

    direction = (direction+3)%4;
    switch (direction) {
    case 3: direction = (direction+1)%4;
        move(-1, 0);
        break;
    case 0: direction = (direction+1)%4;
        move(0, 1);
        break;
    case 1: direction = (direction+1)%4;
        move(1, 0);
        break;
    case 2: direction = (direction+1)%4;
        move(0, -1);
        break;

    }


    for (int i = 0; i < size; i++) {
        if (array[i] > 0) array[i]--;
    }
}


void initarray()
{

    headplayerx = arraywidth-2;
    headplayery = arrayheight-2;
    array[headplayerx + headplayery * arraywidth] = 1;


    for (int x = 0; x < arraywidth; ++x) {
        array[x] = -1;
        array[x + (arrayheight - 1) * arraywidth] = -1;
    }


    for (int y = 0; y < arrayheight; y++) {
        array[0 + y * arraywidth] = -1;
        array[(arraywidth - 1) + y * arraywidth] = -1;
    }
    ranfruitplayer();
}

void reverseObstacles()
{
    for(int i=0;i<playerVect.size();i++)
        array[playerVect[i].x + playerVect[i].y*arraywidth] = 0;
    playerVect.clear();
}

void obstaclesPlayer()
{
    reverseObstacles();
    point p;
    for(int i=0;i<level;i++)
    {
        do{
            p.x = rand()%sizee;
            p.y = rand()%sizee;
        }while(array[p.x + p.y*arraywidth] !=0);
        playerVect.push_back(p);
        array[p.x + p.y*arraywidth] = -3;
    }
}

void printmatrixplayer()
{
    cout << endl << endl;
    unsigned char hd = 2537, ft = 2792, br = 2736, os = 2558;
    int temp = array[headplayerx + headplayery*arraywidth];
    array[headplayerx + headplayery*arraywidth] = -4;
    cout << "     " << br;
    for(int f = 1; f<sizee+2; f++)
        cout << br << br;
    cout << br << endl;

    for (int x = 1; x < arraywidth-1; ++x) {
            cout << "     " << br << br;
        for (int y = 1; y < arrayheight-1; ++y) {

            cout << getarrayValue(array[x + y * arraywidth]) << " ";
        }

        cout << br << br <<endl;
    }
    cout << "     " << br;
    for(int f = 1; f<sizee+2; f++)
        cout << br << br;
    cout << br <<endl;
    cout << "Score: " << fruitplayer-2<<endl;
    array[headplayerx + headplayery*arraywidth] = temp;
}


char getarrayValue(int value)
{
    unsigned char hd = 2537, ft = 2792, br = 2736, os = 2558;

    if (value > 0) return 'o';

    switch (value) {

    case -1: return br;

    case -2: return ft;

    case -3: return os;

    case -4: return hd;
    }
}


