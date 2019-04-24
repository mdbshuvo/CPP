#include "new.h"
#include "view.h"
#include "search.h"
#include "delete.h"
#include "update.h"

class BasicInfo
{
protected:
    int accountId;
public:
    std::string name;

    void saveBasic(std::ofstream&);
    void loadBasic(std::ifstream&);
    void setId(int);
    int getId();
};


class Account : public BasicInfo
{
    std::string created;
    double accountBalance;

public:
    int age;
    std::string address;
    std::string email;
    std::string contactNo;

    Account()                                   //Constructor
    {
        time_t times;
        struct tm *timesinfo;
        time(&times);
        timesinfo=localtime(&times);

        created=asctime(timesinfo);
    }
    void firstExchange();
    void balanceExchange();
    std::string getDate();
    double getBalance();

    void saveData(std::ofstream&);
    void loadData(std::ifstream&);

    friend std::ostream& operator<<(std::ostream&,Account);         //Operator overloading
    //Friend Function
};

template <typename T>
class Array
{
    T *data;
    int size;

public:
    Array(int n)                                             //Constructor
    {
        data=new T[n];
        size=n;
    }

    Array(Array& oldba)                                //Copy constructor
    {
        size=oldba.size;
        data=new T[size];

        for(int i=0; i<size; i++)
            data[i]=oldba.data[i];                   //Deep copy
    }

    void operator=(Array& oldba)
    {
        size=oldba.size;

        if(data!=NULL)
            delete [] data;
        data=new T[size];

        for(int i=0; i<size; i++)
            data[i]=oldba.data[i];
    }

    T& operator[](int i)
    {
        if(i>=0 && i<size)
            return data[i];

        std::cout<<"Invalid request";

        exit(4);
    }

    ~Array()                                                //and Destructor
    {
        delete [] data;
    }
};

class Options
{
public:
    virtual int choice(int ind=-1)=0;
};

class New : public Options
{
public:
    int choice(int ind=-1)
    {
        new_();
        return 0;
    }
};

class Search : public Options
{
public:
    int choice(int ind=-1)
    {
        return search_();
    }
};

class View : public Options
{
public:
    int choice(int ind=-1)
    {
        view(ind);
        return 0;
    }
};

class Delete : public Options
{
public:
    int choice(int ind=-1)
    {
        delete_(ind);
        return 0;
    }
};

class Update : public Options
{
public:
    int choice(int ind=-1)
    {
        update(ind);
        return 0;
    }
};
