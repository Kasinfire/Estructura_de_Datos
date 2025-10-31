#ifndef __USERINTERFACE_HPP__
#define __USERINTERFACE_HPP__

#include <string>

#include "expresion.hpp"
#include "stack.hpp"
#include "queue.hpp"

class UserInterface{
    private: 
    Expresion expressionConverter;
    Queue<char> postfixedExpression;
    Queue<char> stringToQueue(const std::string&);
    
    void printQueue(Queue<char>&);
    void displayMenu();
    void insertExpresion();
    void printExpresion();
    void enterToContinue();

    public: 
    UserInterface();
    void run();

};

#endif // __USERINTERFACE_HPP__