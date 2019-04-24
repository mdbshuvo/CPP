#include <iostream>
#include <cstdlib>

using namespace std;

int main()
{
    cout<<"Choose from the options below :"<<endl
    <<"1. Build"<<endl
    <<"2. Rebuild"<<endl
    <<"3. Clean"<<endl
    <<"4. Cancel"<<endl
    <<endl<<"INPUT : ";

    int i;
    cin>>i;

    system("cls");

    if(i==1) system("mingw32-make all");
    else if(i==2) system("mingw32-make rebuild");
    else if(i==3) system("mingw32-make clean");
}
