#ifndef CUSTOMEXCEPTIONS_H_
#define CUSTOMEXCEPTIONS_H_

#include <stdexcept>//exception handling
#include <string>
#include <stdlib.h>

class InvalidDomainException : public std::runtime_error{
    public:
        //constructor takes an error message, and passes it to the std rutime_error to do heavy lifting
        InvalidDomainException(const std::string& message) : std::runtime_error("Invalid Domain: " + message){}
};
class DivideByZeroException : public std::runtime_error{
    public:
        //constructor takes an error message, and passes it to the std rutime_error to do heavy lifting
        DivideByZeroException() : std::runtime_error("Invalid. Can't Divide by Zero."){}
};
class InvalidFunctionException : public std::runtime_error{
    public:
        //constructor takes an error message, and passes it to the std rutime_error to do heavy lifting
        InvalidFunctionException(const std::string& message) : std::runtime_error("Invalid Function: " + message){}
};
class UnbalancedOperatorsException : public std::runtime_error{
    public:
        //constructor takes an error message, and passes it to the std rutime_error to do heavy lifting
        UnbalancedOperatorsException(const std::string& message) : std::runtime_error("Unbalanced Operators: " + message){}
};
class UnbalancedParenthesesException : public std::runtime_error{
    public:
        //constructor takes an error message, and passes it to the std rutime_error to do heavy lifting
        UnbalancedParenthesesException(const std::string& message) : std::runtime_error("Unbalanced Parentheses: " + message){}
};      
class InvalidInputException : public std::runtime_error{
    public:
        //constructor takes an error message, and passes it to the std rutime_error to do heavy lifting
        InvalidInputException(const std::string& message) : std::runtime_error("Invalid Input: " + message){}
};     
class DoesNotExistException : public std::runtime_error{
    public:
        DoesNotExistException(const std::string& message) : std::runtime_error("Answer is Non-Real or Infinite: " + message){}
};
class InvalidIntervalException : public std::runtime_error{
    public:
        InvalidIntervalException(const std::string& message) : std::runtime_error("Interval Entered is Not Valid: " + message){}
};

#endif