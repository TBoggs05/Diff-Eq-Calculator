#ifndef _EULERS_H_
#define _EULERS_H_
#include <iostream>
#include <string>
#include <vector>
#include <stack>
class eulers{
public:
    void start(); //calls all the other functions into place.
    eulers(); // constructor. 
private:
    std::string equation;//y'
    double h;//step
    double x_initial, y_initial, x_upper_limit; //domain and y initial
    std::vector<int> x_indexes;//indexes of x in equation.
    std::vector<int> y_indexes;//indexes of y in equation
    //Internal/Helper Functions
    void var_search();//store indexes of variables in string.
    void read_input(); //read input from the user
    bool check_valid();//checks for valid equation, inputs and cases such as step passing upper limit and xinitial > upper_limit.
    double find_derivative(); //calculate y' after substituting variables.
    double eulers_calculate();//recursively finds the numerical solution using eulers method. returns value at upper limit of discreted domain.
};


#endif