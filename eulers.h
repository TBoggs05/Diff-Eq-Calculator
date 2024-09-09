#ifndef _EULERS_H_
#define _EULERS_H_
#define _USE_MATH_DEFINES
#include <iostream>
#include <string>
#include <vector>
#include <stack>
#include <math.h>
#include <cmath>
class eulers{
public:
    void start(); //calls all the other functions into place.
    eulers(); // constructor. 
    ~eulers();// destructor.
private:
    std::string equation;//y'
    double h;//step
    double x_initial, y_initial, x_upper_limit; //domain and y initial
    //Internal/Helper Functions
    bool handle_implicit_multiplication();//function will return true when completed. loops thru string and inserts multiplciation operators.
    void read_input(); //read input from the user
    bool convert_to_postfix();//checks for valid equation, converts to postfix
    double find_derivative(std::string postfix); //calculate y' after substituting variables.
    double eulers_calculate();//recursively finds the numerical solution using eulers method. returns value at upper limit of discreted domain.
};


#endif