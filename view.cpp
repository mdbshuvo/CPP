#include<iostream>
#include<cstdlib>
#include<ctime>
#include<fstream>
#include<sstream>
#include<iomanip>
#include "class.h"
#include "search.h"
#include "title.h"

using namespace std;

void view(int indicator)
{
    string currentTime;
    system("cls");
    display(VIEW WINDOW);

    Account *ptr;
    Array<BasicInfo> bdarr(100);
    int i,j,choice,chosenId=indicator;

    ptr=new Account;

    ifstream bfile("files\\data");
    if(bfile.is_open()) //if the file opening is successfull.
    {
        j=0;
        while(!bfile.eof())
        {
            bdarr[j].loadBasic(bfile);
            j++;
        }
        j--;
        bfile.close();
    }
    else
    {
        cout<<"There is nothing on this server please input a new account first."<<endl;
        return;
    }
    if(chosenId==-1)
    {
        cout<<"What do you want to be done?"<<endl
            <<"1. View all the accounts."<<endl
            <<"2. Detailed information of single account."<<endl
            <<"3. Cancel."<<endl
            <<endl<<"INPUT: ";

        cin>>choice;

        while(choice!=1 && choice!=2 && choice!=3)
        {
            cout<<"Invalid selection !! Try again : ";
            cin>>choice;
        }

        if(choice==2)
        {
            cout<<"You need to find the account first.Choose a option below :"<<endl
                <<"1. Go to SEARCH WINDOW to search by name."<<endl
                <<"2. Enter the account ID."<<endl
                <<endl<<"INPUT : ";

            cin>>choice;

            while(choice!=1 && choice!=2)
            {
                cout<<"Invalid selection !! Try again : ";
                cin>>choice;
            }

            if(choice==1)
                chosenId=search_();
            else
            {
                cout<<"Enter the id you want to find : ";
                cin>>choice;
                for(i=0; i<j; i++)
                {
                    if(bdarr[i].getId()==choice)
                    {
                        chosenId=choice;
                        break;
                    }
                }

                if(i==j)
                {
                    cout<<"Id not found!"<<endl;
                    return;
                }
            }
        }
        else if(choice==1)
        {
            cout<<endl<<"There are "<<j<<" accounts stored in the server."<<endl<<endl;
            if(j>0)
                cout<<setw(10)<<"ID"<<setw(15)<<"NAME"<<endl;
            for(i=0; i<j; i++)
            {
                cout<<i+1<<"."<<setw(10)<<bdarr[i].getId()<<setw(15)<<bdarr[i].name<<endl;       //Formatted I/O
            }
            return;
        }
        else
        {
            cout<<"Process canceled."<<endl;
            return;
        }

    }
    if(chosenId==-1)
    {
        cout<<"Requested account couldnot be viewed!"<<endl;
    }
    else
    {
        system("cls");
        display(VIEW WINDOW);

        string path="files\\customers\\";
        stringstream str(path);
        str<<path<<chosenId;
        path=str.str();

        ifstream data(path.c_str());
        ptr->loadData(data);

        cout<<*ptr;  //operator overloading
    }

    delete ptr;
}
