#include<iostream>
#include<iomanip>
#include<cstdlib>
#include<string>
#include<ctime>
#include<vector>
#include<fstream>
#include<sstream>
#include "class.h"
#include "search.h"
#include "title.h"

using namespace std;


void update(int indicator)
{
    string currentTime;
    system("cls");
    display(UPDATE WINDOW);

    int choice,chosenId=indicator;
    vector<BasicInfo> base;
    Account sampleAccount;

    ifstream bfile("files\\data");
    if(bfile.is_open()) //if the file opening is successful.
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
                cout<<"Could not find the account!"<<endl;
                return;
            }
        }
        else
        {
            cout<<"Enter the id you want to find : ";
            cin>>choice;
            unsigned int i;
            for(i=0; i<base.size(); i++)
            {
                if(base[i].getId()==choice)
                {
                    chosenId=choice;
                    break;
                }
            }

            if(i==base.size())
            {
                cout<<"Id not found!"<<endl;
                return;
            }
        }
    }

    system("cls");
    display(UPDATE WINDOW);

    //Starting updating.

    string path="files\\customers\\";
    stringstream str(path);
    str<<path<<chosenId;
    path=str.str();

    ifstream data(path.c_str());
    sampleAccount.loadData(data);
    data.close();


    cout<<"Name : "<<setw(20)<<left<<sampleAccount.name<<"ID : "<<sampleAccount.getId()<<endl<<endl;       //Formatted I/O

    cout<<"1. Updating Balance"<<endl
        <<"2. Updating Other Information"<<endl
        <<"3. Cancel."<<endl
        <<endl<<"INPUT: ";

    cin>>choice;

    while(choice!=1 && choice!=2 && choice!=3)
    {
        cout<<"Invalid selection !! Try again : ";
        cin>>choice;
    }

    if(choice==1)
    {
        sampleAccount.balanceExchange();
    }
    else if(choice==2)
    {


        cout<<"Select the index from the following list to upgrade information-- "<<endl
            <<"1.Present address. "<<endl
            <<"2.Email address. "<<endl
            <<"3.Contact Number. "<<endl
            <<"4.Enter zero (0) to cancel "<<endl
            <<"[N.B: Some informations like name,age etc are not changable] "<<endl;

        cin>>choice;
        cin.ignore();

        while(choice!=1 && choice!=2 && choice!=3 && choice!=4)
        {
            cout<<"Invalid selection !! Try again : ";
            cin>>choice;
            cin.ignore();
        }

        switch (choice)
        {
        case 1:
            cout<<"Your current address: "<<sampleAccount.address<<endl;
            cout<<"Enter the new address: ";
            getline(cin,sampleAccount.address);
            break;
        case 2:
            cout<<"Your current E-mail address: "<<sampleAccount.email<<endl;
            cout<<"Enter the new E-mail address: ";
            getline(cin,sampleAccount.email);
            break;
        case 3:
            cout<<"Your current Contact Number: "<<sampleAccount.contactNo<<endl;
            cout<<"Enter the new Contact Number: ";
            getline(cin,sampleAccount.contactNo);
            break;
        default:
            cout<<"Process canceled."<<endl;
            return;
        }
        cout<<"Information updated successfully."<<endl;
    }
    else
    {
        cout<<"Process canceled."<<endl;
        return;
    }

    ofstream data2(path.c_str());
    sampleAccount.saveData(data2);
    data2.close();
}
