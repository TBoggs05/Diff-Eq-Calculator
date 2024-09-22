#ifndef _EULERS_H_
#define _EULERS_H_
#define _USE_MATH_DEFINES
#include <iostream>
#include <string>
#include <vector>
#include <stack>
#include <math.h>
#include <cmath>
#include <map>
#include <functional>
#include <iterator>
#include "customExceptions.h"

using MathFunction = std::function<double(double)>; //define namespace for our function map.
class eulers{
public:
    void start(); //calls all the other functions into place.
    bool start(std::string, double, double, double, double);//overloaded function for server
    eulers(); // constructor. 
    ~eulers();// destructor.
    double eulers_calculate(std::string& eq);//recursively finds the numerical solution using eulers method. returns value at upper limit of discreted domain.
    std::string equation;//y'
    std::vector<std::string> getSteps(){ //CALL AFTER RUNNING CALCULATE TO GET STEPS
        return answers;
    }
    std::string getErrString(){//returns the error message to be delivered to frontend
        return errString;
    }
private:
    std::vector<std::string> answers;
    double h;//step
    double x_initial, y_initial, x_upper_limit; //domain and y initial
    std::map<std::string, MathFunction> mathFunctions; //map of all allowed functions in y'.
    bool errorFlag;
    std::string errString;
    //Internal/Helper Functions
    bool handle_implicit_multiplication(std::string& eq);//function will return true when completed. loops thru string and inserts multiplciation operators.
    void read_input(); //read input from the user
    bool convert_to_postfix(std::string& eq);//checks for valid equation, converts to postfix
    double find_derivative(std::string& postfix); //calculate y' after substituting variables.
    double calculate_internal_function(std::string& internalFunction);


};


#endif