#ifndef __STACK_HPP__
#define __STACK_HPP__

#include "exceptions.hpp"

//Definicion 

template <class T, int ARRAYSIZE> 
class Stack {
private: 
    T data[ARRAYSIZE];
    int top; 
    void copyAll(const Stack <T, ARRAYSIZE>&);

public: 
    Stack();
    Stack(const Stack<T, ARRAYSIZE>&);

    void push(const T&);    // insertar (pone un dato en la pila)
    T pop();                // Quitar (Saca un dato dela pila)
    void clearStack();      // Limpiar pila (Quita todos los elementos de la pila) 

    bool isEmpty() const;   // Pila vacia (compureba si no tiene elementos)
    bool isFull() const;    // Pila llena (comprueba si esta llena de elemnt)

    const T& getTopS()const; // Cima pila (obtiene el elemento de la cima de la pila)

    Stack<T, ARRAYSIZE>& operator = (const Stack<T, ARRAYSIZE>&);
};

//Implementacion 


template<class T, int ARRAYSIZE>
void Stack<T, ARRAYSIZE>::copyAll(const Stack <T, ARRAYSIZE>& other) {
    int i(0);
    while (i <= other.top) {
        this -> data[i] = other.data[i];
        i++;
    }
    this -> top= other.top;
}

template<class T, int ARRAYSIZE>
Stack<T, ARRAYSIZE>::Stack() :top(-1) { }

template<class T, int ARRAYSIZE>
Stack<T, ARRAYSIZE>::Stack(const Stack<T, ARRAYSIZE>& other) {
    copyAll(other);
}

template<class T, int ARRAYSIZE>
void Stack<T, ARRAYSIZE>::push(const T& element) {
    if (this-> isFull()){
        throw Exception ("Desbordamiento de datos, push");
    }
    this ->top++;
    this -> data[this->top] = element; 
}

template<class T, int ARRAYSIZE>
T Stack<T, ARRAYSIZE>::pop() {
    if (this -> isEmpty()){
        throw  Exception ("Insuficiencia de datos, pop");
    }
    T res(this -> data[this->top--]);
    return res;

}

template<class T, int ARRAYSIZE>
void Stack<T, ARRAYSIZE>::clearStack() {
    top = -1;
}

template<class T, int ARRAYSIZE>
bool Stack<T, ARRAYSIZE>::isEmpty()const  {
    return this->top == -1;
}

template<class T, int ARRAYSIZE>
bool Stack<T, ARRAYSIZE>::isFull() const {
    return this-> top == ARRAYSIZE - 1; 
}

template<class T, int ARRAYSIZE>
const T& Stack<T, ARRAYSIZE>::getTopS() const {
    if( this -> isEmpty()){
        throw Exception ("Insuficiencia de datos, getTop");
    }
    return this -> data[this-> top];
}

template<class T, int ARRAYSIZE>
Stack<T, ARRAYSIZE>& Stack<T, ARRAYSIZE>::operator = (const Stack<T, ARRAYSIZE>& other) {
    this-> copyAll(other);

    return *this; 
}


#endif // __STACK_HPP__