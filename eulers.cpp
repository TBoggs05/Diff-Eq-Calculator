#include "eulers.h"
/*Default Constructor*/
eulers::eulers(){}
/*
Start Function
Function used to start running the calculator
@VOID
*/
void eulers::start()
{ 
std::cout<<"Eulers Method:"<<std::endl;
read_input(); 
if(convert_to_postfix()){
    eulers_calculate();
}
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
Implicit Multiplication Function
-Loops through string
-tokenizes operators, variables, numbers.

*/
bool eulers::implicit_multiplication(){

}

/*
Convert To Postfix Button
-Converts the problem to postifx form
-checks that everything in the inputs are valid
-Xinitial <= XFinal
-Step will not intersect XFinal
-valid parentheses
-balanced operators and operands (operators = operands-1)
-check the validity of individual terms, I.E valid functions, values, and variables.
-Handle implicit multiplication I.E converting 3(x) or 3x or 3(12) into a valid multiplication of values.
@RETURN BOOL
*/
bool eulers::convert_to_postfix(){
if(x_initial >= x_upper_limit){
    std::cout<<"Invalid. Upper limit must be greater than x."<<std::endl;
    return false;
}
else if(h == 0 || ((x_upper_limit - x_initial) / h != 0)){
    std::cout<<"Invalid. Must solve for final X"<<std::endl;
    return false;
}

//convert to postfix
std::string postfix = "";
std::stack<char> parentheses_stack;
int termBalanceCount = 0;
for(int i = 0; i < equation.size(); i++){
    //is whitespace
    if(equation[i] == ' '){
        //do nothing. whitespace.
    }
    //is digit
    else if(equation[i])
}



equation = postfix;
if(parentheses_stack.empty() && termBalanceCount == 0)
return true;
else{
std::cout<<"Invalid Equation. Make sure parentheses are balanced and every two terms is separated by an operator."
return false;
}

}
/*
Find Derivative Function
-plugs in our current x and y values
-calculates solution for y'
@RETURN DOUBLE
*/
double eulers::find_derivative(){
double dy = 0;
std::stack<double> operandStack;
for(int i = 0; i < equation.size(); i++){
    //if whitespace, do nothing

    //if term, loop thru and evaluate the term
    //I.E handle functions, variables, numbers, etc. 
}
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
            y_initial = y_initial + h * find_derivative();
            std::cout<<"Y("<<x_initial<<") = "<<y_initial<<std::endl;
            x_initial+=h;
            return 0;
    }
}