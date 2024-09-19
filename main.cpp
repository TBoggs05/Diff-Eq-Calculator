#include "eulers.h"
using namespace std;

char menu(){
    char x;
    cout<<"Select Method to Solve Differential Equation:"<<endl;
    cout<<"1.)Eulers Method(Numerical Solution/Approximation)"<<endl;
    cout<<"2.)Taylor's Method(Power Series Solution)"<<endl;
    cout<<"E.)Exit"<<endl;
    cin>>x;
    return x;
}

int main(){
    char input[2];
    while(std::tolower(input[0]) !='e'){
        input[0] = menu();
        switch(input[0]){
            case '1':{
            eulers approximator;
            approximator.start();
            break;
            }
                case '2':{
                cout<<"SERIES Calculator!\n"<<endl;
                cout<<"Will be implemented at a future date...\n"<<endl;
                break;
                }
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