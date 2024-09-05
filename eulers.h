#ifndef _EULERS_H_
#define _EULERS_H_
class eulers{
public:
    void start(); //requests inputs and calls the calculate() function. takes return of that function and displays.
    void parse(string equation); // parses the f(x,y) function and give us a mathematical function for us to use.
    eulers(); // constructor. 
    double calculate(); //calculate the solution at some h domain/h times.

private:
    string equation;//y'
    double h;//step
    double x_initial, y_initial, x_upper_limit; //domain and y initial
};


#endif