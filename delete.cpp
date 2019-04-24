#include<iostream>
#include<cstdlib>
#include<string>
#include<ctime>
#include<fstream>
#include<list>
#include<sstream>
#include<conio.h>
#include "class.h"
#include "search.h"
#include "title.h"

using namespace std;

void delete_(int indicator)
{
    string currentTime;
    system("cls");
    display(DELETE WINDOW);

    list<BasicInfo> base;
    list<BasicInfo> :: iterator it;
    int choice,chosenId=indicator;

    //read section.
    ifstream bfile("files\\data");
    if(bfile.is_open()) //if the file opening is successfull.
    {
        while(!bfile.eof())
        {
            BasicInfo dummy;
            dummy.loadBasic(bfile);
            base.push_back(dummy);
        }
        bfile.close();
        it=base.end();
        it--;
        base.erase(it);
    }
    else
    {
        cout<<"There is nothing on this server please input a new account first."<<endl;
        return;
    }

    if(indicator==-1)       //if no indicator value passed from search
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
        {
            chosenId=search_();
            if(chosenId==-1)       //if search was not finished properly.
            {
                cout<<"Couldnot find the item to delete!"<<endl;
                return;
            }
        }
        else
        {
            cout<<"Enter the id you want to find : ";
            cin>>chosenId;
        }
    }

    for(it=base.begin(); it!=base.end(); it++)
    {
        if((*it).getId()==chosenId)
            break;
    }

    if(it==base.end())
    {
        cout<<"The requested ID not found!!"<<endl<<endl;
        return;
    }

    system("cls");
    display(DELETE WINDOW);
    //starting the deleting.

    cout<<"Are you sure you want to delete the account \""<<(*it).name<<"\" ?(warning! this process cannot be undone.)"<<endl
        <<"1. YES."<<endl
        <<"2. NO."<<endl
        <<endl<<"INPUT : ";
    while(true)
    {
        cin>>choice;
        if(choice==1)
            break;
        else if(choice==2)
        {
            cout<<"Account deletion aborted."<<endl;
            return;
        }
        else
            cout<<"Please enter correct command : ";
    }

    base.erase(it);// problem
    //int nsize=base.size()-1;
    //base.resize(nsize);

    //write section
    ofstream data("files\\data",ios::trunc);
    if(data.is_open())
    {
        for(it=base.begin(); it!=base.end(); it++)
        {
            (*it).saveBasic(data);
        }

        data.close();

        string path="files\\customers\\";
        stringstream str(path);
        str<<path<<chosenId;
        path=str.str();

        remove(path.c_str());
    }
    else
    {
        cout<<"There was an severe error while encountering the operation."<<endl
            <<"Make sure every folder exists (like files\\customers)"<<endl;
        exit(1);
    }

    printf("Process ended successfully.\n");
}
