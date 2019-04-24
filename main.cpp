///To get better visual performance make sure the console screen size is (112*30)

#include "main.h"

using namespace std;
using namespace winEdit;


int main(int argc,char *argv[])
{
    //initialize section
    system("mkdir files\\customers\\pass");
    system("cls");
    resizeConsole();
    {
        ifstream fin("files\\upDown.dat");
        if(!fin.is_open())
            takeUpDown();
        else
            fin.close();
    }

    //password section
    string password,realPassword;
    int i,chosenId;

    ifstream pin("files\\customers\\pass\\password.dat");
    if(pin.is_open())
    {
        getline(pin,realPassword);
        pin.close();
    }
    else
    {
        ofstream pout("files\\customers\\pass\\password.dat");
        string dummy="0";
        realPassword=dummy;
        pout<<realPassword;
        pout.close();
    }

    for(;;)
    {
        system("cls");
        cout<<endl<<setw(13)<<" "<<"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"
            <<endl<<setw(13)<<" "<<"-"<<setw(84)<<"-"
            <<endl<<setw(13)<<" "<<"-"<<setw(84)<<"-"
            <<endl<<setw(13)<<" "<<"-"<<setw(84)<<"-"
            <<endl<<setw(13)<<" "<<"-"<<setw(84)<<"-"
            <<endl<<setw(13)<<" "<<"-"<<setw(14)<<" ";
        cout<<"Enter the authentication password to access the data base  "<<setw(10)<<" "<<"-"
            <<endl<<setw(13)<<" "<<"-"<<setw(84)<<"-"
            <<endl<<setw(13)<<" "<<"-"<<setw(28)<<" "<<"PASSWORD: "<<setw(45)<<" "<<"-"
            <<endl<<setw(13)<<" "<<"-"<<setw(84)<<"-"
            <<endl<<setw(13)<<" "<<"-"<<setw(84)<<"-"
            <<endl<<setw(13)<<" "<<"-"<<setw(84)<<"-"
            <<endl<<setw(13)<<" "<<"-"<<setw(84)<<"-"
            <<endl<<setw(13)<<" "<<"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~";
        gotoxy(PASS_START_X,PASS_START_Y);

        cin.sync();
        password.clear();
        for(i=0; i<20; i++)
        {
            char temp=getch();
            if(temp==10||temp==13)
            {
                break;
            }
            else if(temp==8)
            {
                if(i==0)
                {
                    i--;
                    continue;
                }
                password.erase(password.end()-1);
                cout<<"\b \b"<<flush;
                i-=2;
                continue;
            }
            password.push_back(temp);
            cout<<"*";
        }

        if(password!=realPassword)
        {
            int indicate=0;
            indicate=MessageBoxA(NULL,"Wrong password.","NOTE",5|MB_ICONEXCLAMATION);
            if(indicate!=4)
            {
                gotoxy(0,20);
                getch();
                return 0;
            }
        }
        else
        {
            MessageBoxA(NULL,"Welcome,Press enter to continue.","NOTE",MB_DEFAULT_DESKTOP_ONLY);
            break;
        }
    }

    gotoxy(53,27);
    cout<<"LOADING"<<endl;
    int printer;

    cout<<setw(6)<<" ";
    for(printer=0; printer<100; printer++)
        cout<<"_";

    CONSOLE_SCREEN_BUFFER_INFO cursor;
    GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE),&cursor);
    gotoxy(0,cursor.dwCursorPosition.Y);

    cout<<setw(6)<<" ";
    for(printer=0; printer<20; printer++)
    {
        char a=-37;
        for(int i=0; i<5; i++)
            cout<<a;
        Sleep(5);
    }
    Sleep(100);

    while(true)
    {
        string ind="*     ";
        int choice=1;
        string currentTime;
        while(true)
        {
            system("cls");
            display(MAIN MENU);

            cout<<"Please choose a option below:-"<<endl
                <<"["<<ind[0]<<"]  1. Find an account."<<endl
                <<"["<<ind[1]<<"]  2. Create a new account."<<endl
                <<"["<<ind[2]<<"]  3. Update information of an existing account."<<endl
                <<"["<<ind[3]<<"]  4. Delete an account."<<endl
                <<"["<<ind[4]<<"]  5. View details."<<endl
                <<"["<<ind[5]<<"]  6. Exit."<<endl;

            string check,pressedUp,pressedDown,pressedEnter;
            ifstream fin("files\\upDown.dat");
            fin>>pressedUp>>pressedDown;
            fin.close();
            //cin.ignore(100);

            cin.sync();
            check.push_back(getch());
            while(kbhit())
            {
                check.push_back(getch());
            }
            //taking button pressed;

            if(check==pressedUp)
            {
                if(choice==1)
                {
                    ind[5]='*';
                    ind[0]=' ';

                    choice=6;
                }
                else
                {
                    ind[choice-2]='*';
                    ind[choice-1]=' ';

                    choice--;
                }

            }
            else if(check==pressedDown)
            {
                if(choice==6)
                {
                    ind[0]='*';
                    ind[5]=' ';

                    choice=1;
                }
                else
                {
                    ind[choice]='*';
                    ind[choice-1]=' ';

                    choice++;
                }
            }
            else if(check[0]==13)
                break;
        }

        Options *bptr;
        New nOb;
        View vOb;
        Search sOb;
        Delete dOb;
        Update uOb;

        if(choice==1)
        {
            bptr=&sOb;
            chosenId=bptr->choice();
            if(chosenId!=-1)
            {
                cout<<"What do you want to do with this account?"<<endl
                    <<endl<<"1. Delete it."<<endl
                    <<endl<<"2. Update account information."<<endl
                    <<endl<<"3. View detailed information."<<endl
                    <<endl<<"4. Abort. "<<endl
                    <<endl<<"INPUT : ";

                int choice;
                cin>>choice;

                while(choice!=1 && choice!=2 && choice!=3 && choice!=4)
                {
                    cout<<"Invalid selection !! Try again : ";
                    cin>>choice;
                }

                if(choice==1)
                {
                    bptr=&dOb;
                }
                else if(choice==2)
                {
                    bptr=&uOb;
                }
                else if(choice==3)
                {
                    bptr=&vOb;
                }
                else
                {
                    cout<<"Aborted !!"<<endl;
                }
                bptr->choice(chosenId);
            }
        }
        else if(choice==2)
            bptr=&nOb;
        else if(choice==3)
            bptr=&uOb;
        else if(choice==4)
            bptr=&dOb;
        else if(choice==5)
            bptr=&vOb;
        else
            break;

        if(choice!=1)
            bptr->choice();

        cout<<endl<<"--Press \"Enter\" key to go to main menu.\n";
        getch();
    }

    return 0;
}

