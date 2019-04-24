#include<iostream>
#include<fstream>
#include<string>
#include<iomanip>
#include<cstdlib>
#include<string>
#include<cstring>
#include<ctime>
#include<conio.h>
#define _WIN32_WINNT 0x0500         //for resizing console window
#include<windows.h>
#include "class.h"
#include "title.h"
#define PASS_START_X 53
#define PASS_START_Y 8

namespace winEdit
{
void gotoxy(int x,int y)
{
    COORD coord;
    coord.X=x;
    coord.Y=y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),coord);
}

void resizeConsole()
{
    RECT r;
    GetWindowRect(GetConsoleWindow(),&r);

    MoveWindow(GetConsoleWindow(),r.left,r.top,933,520,TRUE);       //(933*520)==(112,30)
}

void takeUpDown()
{
    std::ofstream fout("files\\upDown.dat");
    std::string check,check2,check3;

    system("cls");
    std::cout<<"Press the up (arrow) button carefully.";

    char dummy;
    dummy=getch();
    check.push_back(dummy);
    dummy=getch();
    check.push_back(dummy);

    fout<<check<<" ";

    system("cls");
    std::cout<<"Press the down (arrow) button carefully.";

    dummy=getch();
    check2.push_back(dummy);
    dummy=getch();
    check2.push_back(dummy);

    fout<<check2<<" ";

    system("cls");
    std::cout<<"Press the enter button carefully.";

    dummy=getch();
    check3.push_back(dummy);

    fout<<check3;
}
}
