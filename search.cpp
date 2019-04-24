#include<iostream>
#include<cstdlib>
#include<string>
#include<cstring>
#include<ctime>
#include<fstream>
#include<vector>
#include<iomanip>
#include<conio.h>
#include "class.h"
#include "title.h"

using namespace std;

class GiveLower
{
    public:
    string operator()(string);
};

int search_()
{
    string currentTime;
    system("cls");
    display(SEARCH WINDOW);

    vector<int> checkList;
    int choice;
    string finder;

    vector<BasicInfo> base;

    ifstream bfile("files\\data");
    if(bfile.is_open())                             //if the file opening is successful.
    {
        while(!bfile.eof())
        {
            BasicInfo dummy;
            dummy.loadBasic(bfile);
            base.push_back(dummy);
        }
        bfile.close();
    }
    else
    {
        cout<<"There is nothing on this server please input a new account first."<<endl;
        return -1;
    }

    cout<<"Choose a option below :"<<endl
        <<"1. Search by name ."<<endl
        <<"2. Cancel."<<endl
        <<endl<<"INPUT : ";

    cin>>choice;

    while(choice!=1 && choice!=2)
    {
        cout<<"Invalid selection !! Try again : ";
        cin>>choice;
    }

    if(choice==1)
    {
        cout<<"Enter the name or partial name you want to find : ";
        cin.ignore();
        getline(cin,finder);

        int i=0;
        GiveLower giveLower;

        for(vector<BasicInfo>::iterator it=base.begin(); it!=base.end(); it++,i++)
        {
            if(strstr((giveLower((*it).name)).c_str(),(giveLower(finder)).c_str())!=NULL)
            {
                checkList.push_back(i);
            }
        }
        cout<<"->Found "<<checkList.size()<<" results."<<endl;
        if(checkList.size()==0)
        {
            return -1;
        }

        for(unsigned int i=0; i<checkList.size(); i++)
        {
            cout<<i+1<<". "<<base[checkList[i]].name<<" ."<<endl;
        }

        printf("Enter the index you want to select -- ");
        cin>>choice;

        cout<<setw(25)<<"name"<<setw(30)<<"id"<<endl
            <<"selected"<<setw(12)<<" "<<"\""<<base[checkList[choice-1]].name<<"\""<<setw(30-base[checkList[choice-1]].name.size())<<" "<<base[checkList[choice-1]].getId()<<endl;
        cout<<"Press Enter to go back."<<endl;
        getch();

        return base[checkList[choice-1]].getId();
    }
    else
    {
        printf("Process canceled.\n");
        return -1;
    }
}

string GiveLower::operator()(string old)
{
    for(unsigned int i=0; i<old.size(); i++)
    {
        if(old[i]>='A' && old[i]<='Z')
        {
            old[i]+=('a'-'A');
        }
    }
    return old;
}
