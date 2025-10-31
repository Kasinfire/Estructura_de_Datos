#ifndef __EXPRESION_HPP__
#define __EXPRESION_HPP__

#include <string>

#include "stack.hpp"
#include "queue.hpp"


class Expresion{
    private:

    public:
    Queue<char> turnPostfixedQueue(Queue<char>&);

    int getOutsidePriorityS(char);
    int getInsidePriorityS(char);

    bool isOperando(char) const;
    bool isValid(const std:: string&) const;

};

#endif // __EXPRESION_HPP__