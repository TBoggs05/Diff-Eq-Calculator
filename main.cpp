#include <iostream>
#include "eulers.h"
using namespace std;

char menu(){
    char x[2];
    cout<<"Main Menu:"<<endl;
    cout<<"1.)Euleurs Method Approximator"<<endl;
    cout<<"2.)Power Series Calculator"<<endl;
    cout<<"E.)Exit Application"<<endl;
    cin>>x[0];
    return x[0];
}

int main(){
    char input[2];
    while(input[0] != 'E' && input[0] != 'e'){
        input[0] = menu();
        switch(input[0]){
            case '1':{
            cout<<"Eulers Method Approximator!\n"<<endl;
            eulers approximator;
            approximator.start();
            break;
            }
                case '2':
                cout<<"SERIES Calculator!\n"<<endl;
                break;
                    case 'E':
                    case 'e':
                    cout<<"Exiting...\n"<<endl;
                    break;
                        default:
                        cout<<"invalid input.\n"<<endl;
                        break;
        }
    }
return 0;
}