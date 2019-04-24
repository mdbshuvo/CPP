#include<iostream>
#include<cstdlib>
#include<ctime>
#include<string>
#include<fstream>
#include<sstream>
#include "class.h"
#include "title.h"

using namespace std;

void new_()
{
    string currentTime;
    system("cls");
    display(NEW ACCOUNT WINDOW);

    Account *ptr;
    int idChooser,choice;

    ptr=new Account;

    ifstream id("files\\nextId.dat");

    if(id.is_open())
    {
        id>>idChooser;
        id.close();
        ofstream id("files\\nextId.dat");
        id<<idChooser+1;
        id.close();
    }
    else
    {
        ofstream id("files\\nextId.dat");
        id<<20002;
        idChooser=20001;
        id.close();
    }

    ptr->setId(idChooser);
    cout<<"The account id for this account is : "<<ptr->getId()<<endl
        <<"\t[ This is given by the server and unchangable! ]"<<endl;

    cout<<"Enter the new customer name: ";
    cin.ignore();       //to avoid the problem of newline character left by scanf function.
    getline(cin,ptr->name);

    cout<<"Enter the age of \" "<<ptr->name<<" \": ";
    cin>>ptr->age;

    cout<<"Enter the address of \" "<<ptr->name<<" \": ";
    cin.ignore();
    getline(cin,ptr->address);

    ptr->firstExchange();

    cout<<"Enter the email address of the customer (if not any then enter a blank space) : ";
    cin.ignore();
    getline(cin,ptr->email);
    cout<<"Enter the phone number of this account: ";
    getline(cin,ptr->contactNo);

    cout<<"\n\t Confirm to add this account? [ some data are not rechangable ] "<<endl
        <<"1. YES"<<endl
        <<"2. NO"<<endl
        <<endl<<"INPUT : ";

    cin>>choice;

    while(choice!=1 && choice!=2)
    {
        cout<<"Invalid selection !! Try again : ";
        cin>>choice;
    }

    if(choice==2)
    {
        ofstream id("files\\nextId.dat");
        id<<idChooser;
        id.close();
        return;
    }

    //write section
    string path="files\\customers\\";
    stringstream str(path);
    str<<path<<ptr->getId();
    path=str.str();

    ofstream data(path.c_str());
    if(data.is_open())
    {
        ofstream subData("files\\data",ios::app);
        ptr->saveBasic(subData);
        subData.close();

        ptr->saveData(data);
    }
    else
    {
        cout<<"There was an severe error while encountering the operation."<<endl
            <<"Make sure every folder exists (like files\\customers)"<<endl;
        exit(1);
    }

    cout<<endl<<"\t\tProcess ended successfully."<<endl;

    delete ptr;
}
