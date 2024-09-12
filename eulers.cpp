#include "eulers.h"
//SUPLEMENTAL FUNCTIONS.
double sec(double x){
    return 1/cos(x);
}
double csc(double x){
    return 1/sin(x);
}
double cot(double x){
    return 1/tan(x);
}
double sech(double x){
    return 1/cosh(x);
}
double csch(double x){
    return 1/sinh(x);
}
double coth(double x){
    return 1/tanh(x);
}
double asec(double x){
    return acos(1/x);
}
double acsc(double x){
    return asin(1/x);
}
double acot(double x){
    return atan(1/x);
}
double asech(double x){
    return 1/cosh(x);
}
double acsch(double x){
    return 1/sinh(x);
}
double acoth(double x){
    return 1/tanh(x);
}
double log_base(double x, double b){
    return log(x) / log(b); //use change of base formula.
}
/*Default Constructor*/
eulers::eulers(){
// Initialize the map with standard math functions. uses static_cast<double(*)(double)> to handle 
// ambiguity between different math sin functions, forcing the compiler to see this as a function pointer 
// passed and returning a double.

    //trig.
    mathFunctions["sin"] = static_cast<double(*)(double)>(sin);
    mathFunctions["cos"] = static_cast<double(*)(double)>(cos);
    mathFunctions["tan"] = static_cast<double(*)(double)>(tan);
    //inverse trig.
    mathFunctions["asin"] = static_cast<double(*)(double)>(asin);
    mathFunctions["acos"] = static_cast<double(*)(double)>(acos);
    mathFunctions["atan"] = static_cast<double(*)(double)>(atan);
    //hyperbolic trig.
    mathFunctions["sinh"] = static_cast<double(*)(double)>(sinh);
    mathFunctions["cosh"] = static_cast<double(*)(double)>(cosh);
    mathFunctions["tanh"] = static_cast<double(*)(double)>(tanh);
    //inverse hyperbolic trig.
    mathFunctions["asinh"] = static_cast<double(*)(double)>(asinh);
    mathFunctions["acosh"] = static_cast<double(*)(double)>(acosh);
    mathFunctions["atanh"] = static_cast<double(*)(double)>(atanh);

    //sqrt, logarithms, absolute value, and exponential functions.
    mathFunctions["sqrt"] = static_cast<double(*)(double)>(sqrt);// Square Root (sqrt)
    mathFunctions["ln"] = static_cast<double(*)(double)>(log);// Natural log (ln)
    mathFunctions["log"] = static_cast<double(*)(double)>(log10);// Logarithm base 10
    mathFunctions["exp"] = static_cast<double(*)(double)>(exp);// Exponential function
    mathFunctions["abs"] = static_cast<double(*)(double)>(abs);// Absolute value (floating point)
    
    //special log cases of base 2 and base 5 (if u have a weirder case just convert it urself and stfu.)
    //lambda expression notation: our map for value 1 = [capture](parameters) -> return type { function body}
    //essentially creating a mini function capturing(copying) nothing, passed a double to it, and return a call to our custom log function as a double.
    mathFunctions["log2"] = [](double x) -> double { return log_base(x, 2); };
    mathFunctions["log5"] = [](double x) -> double { return log_base(x, 5); };

    //sec, cos, cot (Since its our custom functions, theres no ambiguity therefore we cast as MathFunction.)
     mathFunctions["sec"] = static_cast<MathFunction>(sec);
     mathFunctions["csc"] = static_cast<MathFunction>(csc);
     mathFunctions["cot"] = static_cast<MathFunction>(cot);

     //asec, acos, acot
     mathFunctions["asec"] = static_cast<MathFunction>(asec);
     mathFunctions["acsc"] = static_cast<MathFunction>(acsc);
     mathFunctions["acot"] = static_cast<MathFunction>(acot);

     //hyperbolic sec, cos, cot
     mathFunctions["sech"] = static_cast<MathFunction>(sech);
     mathFunctions["csch"] = static_cast<MathFunction>(csch);
     mathFunctions["coth"] = static_cast<MathFunction>(coth);

     //inverse hyperbolic sec, cos, cot
     mathFunctions["asech"] = static_cast<MathFunction>(asech);
     mathFunctions["acsch"] = static_cast<MathFunction>(acsch);
     mathFunctions["acoth"] = static_cast<MathFunction>(acoth);
}   


/*Default Destructor*/
eulers::~eulers(){}
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
bool eulers::handle_implicit_multiplication(){
return true;
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
    else if(equation[i]){

    }
}



equation = postfix;
if(parentheses_stack.empty() && termBalanceCount == 0)
return true;
else{
std::cout<<"Invalid Equation. Make sure parentheses are balanced and every two terms is separated by an operator."<<std::endl;
return false;
}

}
/*
Find Derivative Function
-plugs in our current x and y values
-calculates solution for y'
@RETURN DOUBLE
*/
double eulers::find_derivative(std::string postfix){
double dy = 0;
std::stack<double> operandStack;
for(int i = 0; i < postfix.size(); i++){
    if(postfix[i] == ' '){/*do nothing. Whitespace.*/}
        //pushes x value onto stack
        else if(postfix[i] == 'x' || postfix[i] == 'X'){
            operandStack.push(this->x_initial); 
        }
            //pushes y value onto stack
            else if(postfix[i] == 'y' || postfix[i] == 'Y'){
                operandStack.push(this->y_initial); 
            }
                // will push the value of e^1 onto stack. 
                else if(postfix[i] == 'e'){
                    operandStack.push(std::exp(1.0)); 
                }
                    //handles converting multi digit values from string to double, including decimals.
                    else if(std::isdigit(postfix[i]) || postfix[i] == '.'){ 
                        double value = 0;
                        while(std::isdigit(postfix[i])){
                        value*=10 + (postfix[i]-'0');
                        i++;
                        }
                        //POTENTIAL ISSUE: if there is a weird input after the decimal place or just before (i.e x.17 or 1.x or 1.  71),
                        //We could potentially have very weird or breaking outputs here. THIS SHOULD BE HANDLED IN THE VALIDATION CHECKS WHEN CONVERTING TO POSTFIX <3
                        if(postfix[i] == '.'){ 
                            i++;//move past decimal.
                            int placecount = 1;
                            while(std::isdigit(postfix[i])){
                                value += (1/(10*placecount++)) * (postfix[i] - '0');
                                i++;
                            }
                        }
                        operandStack.push(value); i--; //decrement to stop weird behaviour.
                    }
                        else if(postfix[i] == 'p' || postfix[i] == 'P'){ //push pi onto thing.
                            if(i+1 < postfix.size()){
                                if(postfix[i+1] == 'i' || postfix[i+1] == 'I'){
                                    operandStack.push(M_PI);
                                }
                                else{
                                    return -1; //error case. should be handled by other functions, if not I will implement some try/catches if that idea changes.
                                }
                            }
                        }
                            else if(std::isalpha(postfix[i])){//valid alpha that isnt above cases, so must be function.
                                std::string s = " ";
                                    while(i < postfix.size() && std::isalpha(postfix[i])){
                                        s+=postfix[i++];
                                    }
                                    //TODO: IMPLEMENT MAP.


                            }   //operator. Do the calculation
                                else if(postfix[i] == '+' || postfix[i] == '-' || postfix[i] == '/' || postfix[i] == '*' || postfix[i] == '^'){
                                    double term1;
                                    double term2;
                                    switch(postfix[i]){
                                        case '+':
                                            term1 = operandStack.top();
                                                operandStack.pop();
                                            term2 = operandStack.top();
                                                operandStack.pop();
                                            operandStack.push(term1+term2);
                                                break;
                                        case '-':
                                            term1 = operandStack.top();
                                                operandStack.pop();
                                            term2 = operandStack.top();
                                                operandStack.pop();
                                            operandStack.push(term2-term1);
                                                break;
                                        case '/':
                                            term1 = operandStack.top();
                                                operandStack.pop();
                                            term2 = operandStack.top();
                                                operandStack.pop();
                                            operandStack.push(term2/term1);
                                                break;
                                        case '*':
                                            term1 = operandStack.top();
                                                operandStack.pop();
                                            term2 = operandStack.top();
                                                operandStack.pop();
                                            operandStack.push(term1*term2);
                                                break;
                                        case '^':
                                             term1 = operandStack.top();
                                                operandStack.pop();
                                             term2 = operandStack.top();
                                                operandStack.pop();
                                            operandStack.push(pow(term2, term1));
                                                break;
                                        default:
                                            break;
                                    }
                                }

}
dy = operandStack.top();
    operandStack.pop();
if(!operandStack.empty()){
    //throw error
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
            y_initial = y_initial + h * find_derivative(equation);
            std::cout<<"Y("<<x_initial<<") = "<<y_initial<<std::endl;
            x_initial+=h;
            return 0;//return eulers_calculate();
    }
}