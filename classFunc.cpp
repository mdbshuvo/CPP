#include<iostream>
#include<ctime>
#include<cstdlib>
#include<fstream>
#include<sstream>
#include "class.h"

using namespace std;

void Account::firstExchange()
{
    cout<<"What type of transaction?"<<endl
        <<"1. Keep"<<endl
        <<"2. Borrow"<<endl<<endl
        <<"INPUT : ";

    int choice;
    cin>>choice;

    while(choice!=1 && choice!=2)
    {
        cout<<"Invalid selection !! Try again : ";
        cin>>choice;
    }

    cout<<"Enter the amount (1-10000): ";
    cin>>accountBalance;

    while(accountBalance<=0 || accountBalance>10000)
    {
        cout<<"Invalid input !! Try again : ";
        cin>>accountBalance;
    }

    if(choice==2)
        accountBalance*=-1;
}

void Account::balanceExchange()
{
    if(accountBalance>=0)
    {
        cout<<"    Current account balance is "<<accountBalance<<" tk."<<endl;

        cout<<"1. Money Withdrawal"<<endl
            <<"2. Money deposit"<<endl
            <<endl<<"INPUT: ";

        int choice;
        cin>>choice;

        while(choice!=1 && choice!=2)
        {
            cout<<"Invalid selection !! Try again : ";
            cin>>choice;
        }

        cout<<"Enter the amountf tk [1-10000]: ";
        double amount;
        cin>>amount;

        while(true)
        {
            if(amount>0 && amount<=10000)
            {
                if(choice==1 && accountBalance<amount)
                    cout<<"Check your balance and try again : ";
                else
                    break;
            }
            else
                cout<<"Invalid input !! Try again : ";
            cin>>amount;
        }

        if(choice==1)
        {
            accountBalance-=amount;
        }
        else
        {
            accountBalance+=amount;
        }
        cout<<"New balance is "<<accountBalance<<" tk."<<endl;
    }
    else if(accountBalance<0)
    {
        cout<<"    Current loan amount is "<<accountBalance*(-1)<<" tk.\n";
        cout<<"1. Borrow Again!"<<endl
            <<"2. Pay back."<<endl
            <<endl<<"INPUT: ";
        int choice;
        cin>>choice;

        while(choice!=1 && choice!=2)
        {
            cout<<"Invalid selection !! Try again : ";
            cin>>choice;
        }

        cout<<"Enter the amountf tk [1-10000]: ";
        double amount;
        cin>>amount;

        while(true)
        {
            if(amount>0 && amount<=10000)
            {
                if(choice==2 && accountBalance*(-1)<amount)
                {
                    cout<<"Check your balance and try again : ";
                }
                else
                    break;
            }
            else
            {
                cout<<"Invalid input !! Try again : ";
            }
            cin>>amount;
        }

        if(choice==1)
        {
            accountBalance-=amount;
        }
        else
        {
            accountBalance+=amount;
        }
        if(accountBalance==0)
            cout<<"New balance is "<<accountBalance<<" tk."<<endl;
        else
            cout<<"New loan amount is "<<accountBalance*(-1)<<" tk."<<endl;
    }
}

int BasicInfo::getId()             //Getter Setter
{
    return accountId;
}

void BasicInfo::setId(int accountId)
{
    this->accountId=accountId;          //this pointer
}

string Account::getDate()          //Getter Setter
{
    return created;
}

double Account::getBalance()       //Getter Setter
{
    return accountBalance;
}

void Account::saveData(ofstream& fout)
{
    fout<<"Account ID: "<<accountId<<endl;
    fout<<"Name: "<<name<<endl;
    fout<<"Creation Time: "<<created<<endl;
    if(accountBalance>=0)
        fout<<"Balance Amount: "<<accountBalance<<endl;
    else
        fout<<"Loan Amount: "<<accountBalance*(-1)<<endl;
    fout<<"Address: "<<address<<endl;
    fout<<"Email: "<<email<<endl;
    fout<<"ContactNo.: "<<contactNo<<endl;
}

void Account::loadData(ifstream& fin)
{
    string dummy;

    fin>>dummy>>dummy;
    fin.ignore();
    fin>>accountId;

    fin>>dummy;
    fin.ignore();
    getline(fin,name);

    fin>>dummy>>dummy;
    fin.ignore();
    getline(fin,created);

    bool isLoan=false;
    fin>>dummy;
    if(dummy=="Loan")
        isLoan=true;
    fin>>dummy;
    fin.ignore();
    fin>>accountBalance;
    if(isLoan==true)
        accountBalance*=-1;

    fin>>dummy;
    fin.ignore();
    getline(fin,address);

    fin>>dummy;
    fin.ignore();
    getline(fin,email);

    fin>>dummy;
    fin.ignore();
    getline(fin,contactNo);
}

void BasicInfo::saveBasic(ofstream& fout)
{
    fout<<accountId<<" "<<name<<endl;
}

void BasicInfo::loadBasic(ifstream& fin)
{
    fin>>accountId;
    fin.ignore();
    getline(fin,name);
}

ostream& operator<<(ostream& sout,Account ptr)
{
    sout<<"Account ID: "<<ptr.getId()<<endl;
    sout<<"Name: "<<ptr.name<<endl;
    sout<<"Creation Time: "<<ptr.getDate()<<endl;
    if(ptr.getBalance()>=0)
        sout<<"Balance Amount: "<<ptr.getBalance()<<endl;
    else
        sout<<"Loan Amount: "<<ptr.getBalance()*(-1)<<endl;
    sout<<"Address: "<<ptr.address<<endl;
    sout<<"Email: "<<ptr.email<<endl;
    sout<<"ContactNo.: "<<ptr.contactNo<<endl;

    return sout;
}
