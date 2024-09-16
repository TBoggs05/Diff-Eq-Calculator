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

bool isValidDomain(std::string functionName, double x){
const double PI = 3.141592653589793;
const double EPSILON = 1e-7;
    if (functionName == "log" || functionName == "log10") {
        // Logarithmic functions are undefined for x <= 0
        return x > 0;
    } else if (functionName == "sqrt") {
        // Square root is undefined for x < 0
        return x >= 0;
    } else if (functionName == "tan" || functionName == "sec") {
        // tan and sec are undefined at odd multiples of pi/2
        double multiple = x / (PI / 2);
        return std::abs(std::round(multiple) - multiple) >= EPSILON;
    } else if (functionName == "csc" || functionName == "cot") {
        // csc and cot are undefined at multiples of pi
        double multiple = x / PI;
        return std::abs(std::round(multiple) - multiple) >= EPSILON;
    } else if (functionName == "acosh") {
        // acosh(x) is only valid for x >= 1
        return x >= 1;
    } else if (functionName == "atanh") {
        // atanh(x) is only valid for -1 < x < 1
        return x > -1 && x < 1;
    }
    // Default case for other functions (assume valid domain)
    return true;
}
bool isOperator(char x){
    if(x == '+' || x =='-' || x =='/' || x == '*' || x == '^'){
        return true;
    }
    else{
        return false;
    }
}
int operatorPriority(char x){
    if(x == '^')
        return 3;
    if(x == '*' || x == '/')
        return 2;
    if(x == '+' || x == '-')
        return 1;
    throw InvalidInputException("Invalid Input at Operator Detection.");
    return -1;
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
    mathFunctions["abs"] = static_cast<double(*)(double)>(abs);// Absolute value

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
if(convert_to_postfix(this->equation)){
    eulers_calculate(this->equation);
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
                    while(!(std::cin >> x_upper_limit)){
                    std::cout << "bad input. Retry." <<std::endl;//prompt user for re-entry.
                    std::cin.clear(); //clears the error flag
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');//ignore the rest of the line since its all bad vals.
                    }
}
/*
Implicit Multiplication Function
-Loops through string
-inserts 
@RETURN BOOL
*/
bool eulers::handle_implicit_multiplication(std::string eq){
return true;
}

/*
Convert To Postfix Function
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
bool eulers::convert_to_postfix(std::string& eq){
//checks x vs step and upper limit
if(x_initial >= x_upper_limit){
    std::cout<<"Invalid. Upper limit must be greater than x."<<std::endl;
    return false;
}
else if(h == 0 || floor(((x_upper_limit - x_initial) / h)) - ((x_upper_limit-x_initial)/h) >= 0.0001){
    std::cout<<"Invalid. Must solve for final X"<<std::endl;
    return false;
}
//handle implicit multiplication
if(!handle_implicit_multiplication(eq)){
    return false;
}
//convert to postfix
std::string postfix = "";
std::stack<char> parentheses_stack;
std::stack<char> operator_stack;
try{
for(int i = 0; i < eq.size();){
    //is whitespace
    if(eq[i] == ' '){
        //do nothing. whitespace.
        i++;
    }
    //is open parentheses
        else if(eq[i] == '('){
            std::cout<<"openParentheses"<<std::endl;
            //magage parentheses balance
            parentheses_stack.push(eq[i]);
            operator_stack.push(eq[i]);
            i++;
        }           //is digit
                    else if(std::isdigit(eq[i])){ 
                        std::cout<<"digit"<<std::endl;
                        postfix+=eq[i++];
                        while(i < eq.size() && std::isdigit(eq[i])){
                            postfix+=eq[i++];
                        }
                        if(i < eq.size() && eq[i] == '.'){ //Handle Decimal
                            postfix+=eq[i++];
                                while(i < eq.size() && std::isdigit(eq[i])){
                                    postfix+=eq[i++];
                                }
                        }
                        postfix += " ";//space to separate postfix terms.
                    }
                    //is alphanumeric(will be validated later)
                    else if(std::isalpha(eq[i])){
                        
                        if(std::tolower(eq[i]) == 'x' || tolower(eq[i]) == 'y' || tolower(eq[i]) == 'e'){
                            std::cout<<"variable"<<std::endl;
                        postfix+=eq[i];
                        i++;
                        }
                        else{
                            std::string s = "";
                            while(i<eq.size() && std::isalpha(eq[i])){
                                s+=eq[i++];
                            }
                            if(s.size() == 2 && std::tolower(s[0]) == 'p' && std::tolower(s[1]) == 'i'){
                                std::cout<<"PI"<<std::endl;
                                postfix+=s;
                            }
                            else if(mathFunctions.find(s) != mathFunctions.end()){
                                postfix+=s;
                                std::cout<<"Function"<<std::endl;
                                if(i < eq.size() && eq[i] == '('){
                                    //start storing internal term, we cant skip it.
                                    int pc = 1;//parentheses count
                                    while(i < eq.size() && pc > 0){
                                        if(eq[i] == '(')
                                            pc++;
                                        else if(eq[i] == ')')
                                            pc--;
                                        postfix+=eq[i++];
                                    }
                                }
                                else{
                                    std::cerr<<"Invalid Function"<<std::endl;
                                    //throw error
                                    throw InvalidInputException("Invalid Input. Check your Functions");
                                }
                            }
                            else{
                                //throw error
                                std::cerr<<"You input something it thought was a function but isnt a function."<<std::endl;
                                throw InvalidInputException("Invalid Input. Check your functions for invalid notation. I.E cosx or cos^2(x) are invalid");
                            }
                        }
                        postfix+=" ";//space to separate postfix terms
                    }
                    //if closing parentheses(pop all from stack until open)
                    else if(eq[i] == ')'){
                        if(!parentheses_stack.empty())//manage parentheses balance
                        parentheses_stack.pop();
                        else//throw error
                        throw UnbalancedParenthesesException("Unbalanced Parentheses Detected In Equation During Postfix Conversion.");
                        while(!operator_stack.empty() && operator_stack.top() != '('){
                            postfix+=operator_stack.top();
                            operator_stack.pop();
                        }
                        if(!operator_stack.empty()){
                            operator_stack.pop();//discard (
                        }
                        else{
                            throw UnbalancedParenthesesException("Unbalanced Parentheses in Postfix Conversion.");
                        }
                        i++;
                    }
                    //operator. Push/Pop as necessary
                    else if(isOperator(eq[i])){
                        std::cout<<"operator"<<std::endl;
                        //pop all necessary out of stack before pushing
                        while(!operator_stack.empty() && operator_stack.top() != '(' && operatorPriority(eq[i]) <= operatorPriority(operator_stack.top())){
                            postfix+=operator_stack.top();
                            operator_stack.pop();
                        }
                        operator_stack.push(eq[i]);
                        i++;
                    }
                    //throw error
                    else{
                        std::cerr<<"ERR:331"<<std::endl;
                        throw InvalidInputException("Invalid Input. Typo?");
                    }
}
//empty out stack
while(!operator_stack.empty()){
    postfix += operator_stack.top();
    operator_stack.pop();
}
//set equation back to postfix
eq = postfix;
std::cout<<"POSTFIX: "<<eq<<std::endl;
if(parentheses_stack.empty())
return true;
else{
throw UnbalancedOperatorsException("Error. Unbalanced Parentheses Detected In Equation After Postfix Conversion.");
}
}
catch (const UnbalancedOperatorsException& e){
std::cerr<<"Unbalanced Operators in Postfix Conversion"<<std::endl;
return false;
}
catch (const UnbalancedParenthesesException& e){
    std::cerr<<"Unbalanced Parentheses in Postfix Conversion"<<std::endl;
return false;
}
catch (const InvalidInputException& e){
    std::cerr<<"Invalid Input Exception in Postfix Conversion"<<std::endl;
return false;
}
catch(...){
    std::cerr<<"General Error Found in Postfix Conversion."<<std::endl;
    return false;
}
}
/*
Calculate internal function
-helper for Find Derivative
-Will evaluate the internal function of a trig equation, may get called multiple times.
@returns void
*/
double eulers::calculate_internal_function(std::string& internalFunction){
    double internal = 0;
    try{
    if(internalFunction.size() <= 2){//invalid domain.
        throw InvalidDomainException("Invalid Domain. Did you Leave a function blank? I.E sin()");
    }
    if(convert_to_postfix(internalFunction)){ //try to convert to postfix
        std::cout<<"EVALUATING INTERNAL OF FUNCTION"<<std::endl;
       internal = find_derivative(internalFunction); //if successful, re-use find_derivative to calculate.
    }
    else{
        throw InvalidDomainException("Problem evaluating internal term of function.");
    }
    }
    catch(const InvalidDomainException& e){
        std::cerr<<"Invalid Domain. Did you leave a function blank? I.E sin()"<<std::endl;
        return std::numeric_limits<double>::quiet_NaN();
    }
    catch(...){
        std::cerr<<"PROBLEM IN CALCULATION OF INTERNAL FUNCTION." <<std::endl;
        return std::numeric_limits<double>::quiet_NaN();
    }

return internal;
}
/*
Find Derivative Function
-plugs in our current x and y values
-calculates solution for y'
@RETURN DOUBLE
*/
double eulers::find_derivative(std::string& postfix){
double dy = 0;
std::stack<double> operandStack;
for(int i = 0; i < postfix.size(); i++){
    try{
    if(postfix[i] == ' '){/*do nothing. Whitespace.*/}
        //pushes x value onto stack
        else if(std::tolower(postfix[i]) == 'x'){
            std::cout<<"substituting x for "<<x_initial<<std::endl;
            operandStack.push(this->x_initial); 
        }
            //pushes y value onto stack
            else if(std::tolower(postfix[i]) == 'y'){
                std::cout<<"substituting y for "<<y_initial<<std::endl;
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
                        value = value * 10 + (postfix[i]-'0');
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
                            if(std::isspace(postfix[i])){
                                //do nothing
                            }
                            else{
                                throw InvalidInputException("Invalid Decimal Input");
                            }
                        }
                        operandStack.push(value); i--; //decrement to stop weird behaviour.
                    }
                        
                        else if(postfix[i] == 'p' || postfix[i] == 'P'){ //push pi onto thing.
                            if(i+1 < postfix.size()){
                                if(postfix[i+1] == 'i' || postfix[i+1] == 'I'){
                                    i++;
                                    operandStack.push(M_PI);
                                }
                                else{
                                    //throw error
                                    throw InvalidFunctionException("Invalid Function or Term. Were you trying to type PI or pi?");
                                }
                            }
                        }
                            else if(std::isalpha(postfix[i])){//valid alpha that isnt above cases, so must be function.
                                std::string s = "";
                                    while(i < postfix.size() && std::isalpha(postfix[i])){
                                        s+=postfix[i++];
                                    }
                                    //if we find our equation, we evaluate the inner equation
                                    MathFunction func;
                                    std::map<std::string, MathFunction>::iterator location = mathFunctions.find(s);
                                    if(location != mathFunctions.end()){
                                        //STORE THE INTERIOR TERM OF FUNCTION
                                            std::string internal = "";
                                            int parenthesesCount = 0;
                                            if(postfix[i]=='('){
                                            internal+=postfix[i];
                                            i++;
                                            parenthesesCount++;
                                            }
                                            else{
                                                //throw error 
                                                throw InvalidFunctionException("Functions require their term to be stored in ().");
                                            }
                                            while(i< postfix.size() && parenthesesCount > 0){
                                                if(postfix[i] == ')'){
                                                    parenthesesCount--;
                                                }
                                                else if(postfix[i] =='('){
                                                    parenthesesCount++;
                                                }
                                                    //append to internal function string
                                                    internal+=postfix[i];
                                                    i++;
                                            }
                                            if(parenthesesCount != 0)
                                                throw UnbalancedParenthesesException("Unbalanced parentheses in internal term of function!");
                                            //Evaluate interior term of function.
                                            double internalValue = calculate_internal_function(internal);
                                            //once evaluated, apply function by dereferencing.
                                            //if real answer, great! push to stack
                                            func = location->second;
                                            if(!isValidDomain(location->first, internalValue)){ //VALIDATE DOMAIN
                                                std::cerr <<"Error: Invalid Function Domain.";
                                                throw InvalidDomainException("Domain of a Functin is Invalid.");
                                            }
                                            else{
                                            double result = func(internalValue);
                                                if (std::isnan(result)) {
                                                    throw DoesNotExistException("Error. Result is not a number");
                                                std::cerr << "Error: result is NaN (not a number)." << std::endl;
                                                } 
                                                else if (std::isinf(result)) {
                                                    throw DoesNotExistException("Error. Result is Infinite");
                                                std::cerr << "Error: result is infinite (undefined operation)." << std::endl;
                                                }
                                                else{
                                                    std::cout<<result<<" is pushed to stack"<<std::endl;
                                                operandStack.push(result);
                                                }
                                            }
                                    }
                                    ///else, throw an error
                                    else{
                                        std::cerr<<"Error. Invalid Function or Term." <<std::endl;
                                        throw InvalidFunctionException("Some Term or Function is Invalid. Check your Input.");
                                    }
                            } 
                              //operator. Do the calculation
                                else if(postfix[i] == '+' || postfix[i] == '-' || postfix[i] == '/' || postfix[i] == '*' || postfix[i] == '^'){
                                    if(operandStack.size() < 2){
                                        //handle error
                                        throw UnbalancedOperatorsException("There needs to be one operator for every two operands, in form (operand_operator_operand)");
                                    }
                                    
                                    double term1;
                                    double term2;
                                    switch(postfix[i]){
                                        case '+':
                                            term1 = operandStack.top();
                                                operandStack.pop();
                                            term2 = operandStack.top();
                                                operandStack.pop();
                                            std::cout<<term1<<"+"<<term2<<" Is pushed to stack"<<std::endl;
                                            operandStack.push(term1+term2);
                                                break;
                                        case '-':
                                            term1 = operandStack.top();
                                                operandStack.pop();
                                            term2 = operandStack.top();
                                                operandStack.pop();
                                            std::cout<<term1<<"-"<<term2<<" Is pushed to stack"<<std::endl;
                                            operandStack.push(term2-term1);
                                                break;
                                        case '/':
                                            term1 = operandStack.top();
                                                operandStack.pop();
                                            term2 = operandStack.top();
                                                operandStack.pop();
                                            if(term1 != 0){
                                            std::cout<<term1<<"/"<<term2<<" Is pushed to stack"<<std::endl;
                                            operandStack.push(term2/term1);
                                            }
                                            else{
                                                //throw error
                                                std::cerr<<" Dividing By Zero Not Allowed."<<std::endl;
                                                throw DivideByZeroException();
                                            }
                                                break;
                                        case '*':
                                            term1 = operandStack.top();
                                                operandStack.pop();
                                            term2 = operandStack.top();
                                                operandStack.pop();
                                                std::cout<<term1<<"*"<<term2<<" Is pushed to stack"<<std::endl;
                                            operandStack.push(term1*term2);
                                                break;
                                        case '^':
                                             term1 = operandStack.top();
                                                operandStack.pop();
                                             term2 = operandStack.top();
                                                operandStack.pop();
                                                std::cout<<term1<<"^"<<term2<<" Is pushed to stack"<<std::endl;
                                            operandStack.push(pow(term2, term1));
                                                break;
                                        default:
                                            break;
                                    }
                                }
                                //fringe case, throw error
                                else{
                                    throw InvalidInputException("Invalid Input. Retry Input");
                                }
    }
    //TODO:IMPLEMENT LOGGING IN CATCH CASES.
    //ALSO SEND ERROR TO FRONTEND USING FRAMEWORK
    catch(const DivideByZeroException& e){
        return std::numeric_limits<double>::quiet_NaN();
    }
    catch(const UnbalancedOperatorsException& e){
        return std::numeric_limits<double>::quiet_NaN();
    }
    catch(const InvalidDomainException& e){
        return std::numeric_limits<double>::quiet_NaN();
    }
    catch(const InvalidFunctionException& e){
        return std::numeric_limits<double>::quiet_NaN();
    }
    catch(const UnbalancedParenthesesException& e){
        return std::numeric_limits<double>::quiet_NaN();
    }
    catch(const InvalidInputException& e){
        return std::numeric_limits<double>::quiet_NaN();
    }
    catch(const DoesNotExistException& e){
        return std::numeric_limits<double>::quiet_NaN();
    }
    catch(...){
        std::cerr<<"GENERAL ERROR IN FIND_DERIVATIVE()"<<std::endl;
        return std::numeric_limits<double>::quiet_NaN();
    }
}
try{
    if(!operandStack.empty()){
        dy = operandStack.top();
        operandStack.pop();
    }
if(!operandStack.empty()){
    std::cerr << "Error: Too many values left on stack after evaluation." <<std::endl;
    //throw error
    throw UnbalancedOperatorsException("Too many operands! Must be in form Operand_Operator_Operand");
}
}
catch(const UnbalancedOperatorsException& e){
    return std::numeric_limits<double>::quiet_NaN();
}
catch(...){
        std::cerr<<"GENERAL ERROR IN FIND_DERIVATIVE() -X"<<std::endl;
        return std::numeric_limits<double>::quiet_NaN();
    }
std::cout<<dy<<" is the derivative of this iteration"<<std::endl;
return dy;
}
/*
Eulers Calculate Function
-calculates the numerical solution of the Diff EQ recursively for the domain.
@RETURNS DOUBLE
*/
double eulers::eulers_calculate(std::string& eq){
 std::cout<<"calculating.."<<std::endl;
 double epsilon = 0.0001;
    if(std::abs(this->x_upper_limit - this->x_initial) < epsilon){
        std::cout<<"The numerical solution of Y("<<this->x_upper_limit<<") is "<<this->y_initial<<std::endl;
        return this->y_initial;
    }    
    else{
            std::cout<<"Y("<<this->x_initial<<") = "<<this->y_initial<<std::endl;
            std::string temp = "="+std::to_string(this->y_initial)+"+"+std::to_string(h)+"*"+std::to_string(find_derivative(eq));
            this->y_initial = this->y_initial + h * find_derivative(eq);
            std::cout<<this->y_initial<<temp<<std::endl;
            if(std::abs(this->y_initial-std::numeric_limits<double>::quiet_NaN()) < epsilon){
                return y_initial;
            }
            this->x_initial+=this->h;
            return eulers_calculate(eq);
    }
}