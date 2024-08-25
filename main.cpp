#include <iostream>

using namespace std;

char menu(){
    char x[2];
    cout<<"Main Menu:"<<endl;
    cout<<"1.)Euleurs Approximation Calculator"<<endl;
    cout<<"2.)Power Series Calculator"<<endl;
    cout<<"E.)Exit Application"<<endl;
    cout<<endl;
    cin>>x[0];
    return x[0];
}



int main(){
    char input[2];
    while(input[0] != 'E' && input[0] != 'e'){
        input[0] = menu();
        switch(){
            case 1:
            
            case 2:

            case E:
            case e:
            cout<<"Exiting..."<<endl;
            break;
            default:
            cout<<"invalid input."<<endl;
            break;
        }
    }




return 0;
}