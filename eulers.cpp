#include "eulers.h"
/*
Default Constructor
*/
eulers::eulers(){ }
/*
Start Function
Function used to start running the calculator
@VOID
*/
void eulers::start(){ 
read_input(); 
var_search();
check_valid();
eulers_calculate();
}
/*
Read_Input Function
-takes inputs from the user
-makes sure inputs are of the correct data type.
@VOID
*/
void eulers::read_input()
{
    std::cin.ignore();
    std::cout << "Please input your f(x,y) equation!" << std::endl;
    std::getline(std::cin, equation);
                std::cout << "Now enter your step size (h)" << std::endl;
                    while(!(std::cin >> h)){
                        std::cout << "bad input. Retry." <<std::endl;//prompt user for re-entry.
                        std::cin.clear(); //clears the error flag
                        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');//ignore the rest of the line since its all bad vals.
                    }
                std::cout<<"Now enter initial x (Xo)"<<std::endl;
                    while(!(std::cin >> x_initial)){
                    std::cout << "bad input. Retry." <<std::endl;//prompt user for re-entry.
                    std::cin.clear(); //clears the error flag
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');//ignore the rest of the line since its all bad vals.
                    }
                std::cout<<"Now enter initial y (Y(Xo))"<<std::endl;
                    while(!(std::cin >> y_initial)){
                    std::cout << "bad input. Retry." <<std::endl;//prompt user for re-entry.
                    std::cin.clear(); //clears the error flag
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');//ignore the rest of the line since its all bad vals.
                    }
                std::cout<<"Lastly, enter the upper domain for which to approximate.(X1)"<<std::endl;
                    while(!(std::cin >> h)){
                    std::cout << "bad input. Retry." <<std::endl;//prompt user for re-entry.
                    std::cin.clear(); //clears the error flag
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');//ignore the rest of the line since its all bad vals.
                    }
}
/*
var_search function
-stores indexes of variables in equation string.
*/
void eulers::var_search(){
    for(int i = 0; i < equation.length();i++){
        if(equation[i] == 'X' || equation[i] == 'x'){ //replace X
            x_indexes.push_back(i);
        }
        else if(equation[i] == 'Y' || equation[i] == 'y'){ //replace Y
            y_indexes.push_back(i);
        }
    }
}
/*
Check Valid Function
-checks that everything in the inputs are valid
-Xinitial <= XFinal
-Step will not intersect XFinal
-Equation includes no invalid characters, terms, etc.
@RETURN BOOL
*/
bool eulers::check_valid(){
if(x_initial >= x_upper_limit){
    std::cout<<"Invalid. Upper limit must be greater than x.";
    return false;
}
else if(h == 0 || ((x_upper_limit - x_initial) / h != 0)){
    std::cout<<"Step value not valid for domain. Must solve for final X"<<std::endl;
    return false;
}
//TODO: search string for invalid values.
//maybe use string set or hashp map for this task.

return true;
}
/*
Find Derivative Function
-just plugs in our current x and y values, then returns a double representing y'.
@RETURN DOUBLE
*/
double eulers::find_derivative(){
double dy = 0;
std::stack<double> operandStack;
std::stack<char> operatorStack;
return dy;
}
/*
Eulers Calculate Function
-calculates the numerical solution of the Diff EQ recursively for the domain.
@RETURNS DOUBLE
*/
double eulers::eulers_calculate(){
    std::cout<<"calculating.."<<std::endl;
if(x_initial > x_upper_limit){
    std::cout<<"The numerical solution of Y("<<x_upper_limit<<") is "<<y_initial<<std::endl;
    return y_initial;
}    
else{
    std::string tempEquation = equation;
        y_initial = y_initial + h * find_derivative();
        std::cout<<"Y("<<x_initial<<") = "<<y_initial<<std::endl;
        x_initial+=h;
        return 0;
}
}