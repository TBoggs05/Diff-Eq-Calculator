#ifndef CUSTOMEXCEPTIONS_H_
#define CUSTOMEXCEPTIONS_H_

#include <stdexcept>//exception handling
#include <string>
#include <stdlib.h>

class InvalidDomainException : public std::runtime_error{
    public:
        std::string msg;
        //constructor takes an error message, and passes it to the std rutime_error to do heavy lifting
        InvalidDomainException(const std::string& message) : std::runtime_error("Invalid Domain: " + message){
            msg = message;
        }
};
class DivideByZeroException : public std::runtime_error{
    public:
    std::string msg;
        //constructor takes an error message, and passes it to the std rutime_error to do heavy lifting
        DivideByZeroException() : std::runtime_error("Invalid. Can't Divide by Zero."){msg = "Invalid. Can't Divide by Zero.";}
};
class InvalidFunctionException : public std::runtime_error{
    public:
    std::string msg;
        //constructor takes an error message, and passes it to the std rutime_error to do heavy lifting
        InvalidFunctionException(const std::string& message) : std::runtime_error("Invalid Function: " + message){msg = message;}
};
class UnbalancedOperatorsException : public std::runtime_error{
    public:
    std::string msg;
        //constructor takes an error message, and passes it to the std rutime_error to do heavy lifting
        UnbalancedOperatorsException(const std::string& message) : std::runtime_error("Unbalanced Operators: " + message){msg = message;}
};
class UnbalancedParenthesesException : public std::runtime_error{
    public:
    std::string msg;
        //constructor takes an error message, and passes it to the std rutime_error to do heavy lifting
        UnbalancedParenthesesException(const std::string& message) : std::runtime_error("Unbalanced Parentheses: " + message){msg = message;}
};      
class InvalidInputException : public std::runtime_error{
    public:
    std::string msg;
        //constructor takes an error message, and passes it to the std rutime_error to do heavy lifting
        InvalidInputException(const std::string& message) : std::runtime_error("Invalid Input: " + message){msg = message;}
};     
class DoesNotExistException : public std::runtime_error{
    public:
    std::string msg;
        DoesNotExistException(const std::string& message) : std::runtime_error("Answer is Non-Real or Infinite: " + message){msg = message;}
};
class InvalidIntervalException : public std::runtime_error{
    public:
    std::string msg;
        InvalidIntervalException(const std::string& message) : std::runtime_error("Interval Entered is Not Valid: " + message){msg = message;}
};

#endif