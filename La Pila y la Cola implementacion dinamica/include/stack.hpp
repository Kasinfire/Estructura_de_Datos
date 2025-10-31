#ifndef __STACK_HPP__
#define __STACK_HPP__

#include "exceptions.hpp"

//Definicion 

template <class T> 
class Stack { 
    private: 
    class Node;
    typedef Node* Position;

    private: 
         class Node {

            private:
                T data; 
                Position next = nullptr;

            public: 
                Node();
                Node(const T&);

                T& getData(); 
                Position getNext() const;

                void setData(const T&);
                void setNext(const Position&);
        };
        
        Position anchor = nullptr;
        void add(const Stack<T>&);
        void deleteAll();

public: 
    Stack();
    Stack(const Stack<T>&);
    ~Stack();

    void push(const T&);    // insertar (pone un dato en la pila)
    T pop();                // Quitar (Saca un dato dela pila)
    void clearStack();      // Limpiar pila (Quita todos los elementos de la pila) 

    bool isEmpty() const;   // Pila vacia (compureba si no tiene elementos)

    const T& getTopS()const; // Cima pila (obtiene el elemento de la cima de la pila)

    Stack<T>& operator = (const Stack<T>&);
};

//Implementacion 

using namespace std; 

//Nodo
//Publico
template<class T>
Stack<T>::Node::Node() { }

template<class T>
Stack<T>::Node::Node(const T& element) : data(element) { }

//Privado
template<class T>
T& Stack<T>::Node::getData() {
    return this-> data; 
}

template<class T>
typename Stack<T>:: Position Stack<T>::Node::getNext() const {
    return this-> next;
}

template<class T>
void Stack<T>::Node::setData(const T& element) {
    this-> data = element; 
}

template<class T>
void Stack<T>::Node::setNext(const typename Stack<T>:: Position& pointer) {
    this->next = pointer;
}

//Stack

//Privado

template<class T>
void Stack<T>:: add(const Stack<T>& other) {
    if (other.anchor == nullptr) {
        return;
    }

    Position aux(other.anchor), lastInserted(nullptr), newNode;

    while(aux != nullptr){
        try {
            newNode = new Node(aux->getData());

            if(lastInserted == nullptr) {
                this-> anchor = newNode;
            }else {
                lastInserted->setNext(newNode);
            }
            lastInserted = newNode;
            aux = aux->getNext();

        } catch (const bad_alloc& e) {
            throw Exception("Memoria no disponible, add");
        }
    }
}

template<class T>
void Stack<T>:: deleteAll(){
    Position aux; 

    while (this->anchor != nullptr) {
        aux = this-> anchor; 

        this-> anchor = aux->getNext();
        delete aux; 
    }
}

//Publico

template<class T>
Stack<T>:: Stack() { }

template<class T>
Stack<T>:: Stack(const Stack<T>& s) { 
    this->add(s);
}

template<class T>
Stack<T>::~Stack(){
    this-> deleteAll();
}


template<class T>
void Stack<T>::push(const T& element) {
    Position newNode(new (nothrow) Node(element));

    if(newNode == nullptr){
        throw Exception ("Memoria no disponible, push");
    }
    newNode ->setNext(this->anchor);
    this->anchor = newNode;
}

template<class T>
T Stack<T>::pop() {
    if(this->isEmpty()){
        throw Exception("Insuficiencia de datos, pop");
    }
    Position aux(this->anchor);
    T result(aux->getData());
    this->anchor = aux->getNext();
    delete aux; 
    return result;
}

template<class T>
void Stack<T>::clearStack() {
    this->deleteAll();
}

template<class T>
bool Stack<T>::isEmpty()const  {
    return this-> anchor == nullptr;
}

template<class T>
const T& Stack<T>::getTopS() const {
   if(this->isEmpty()){
    throw Exception("Insuficiencia de datos, getTop");
   }
   return this->anchor->getData();
}

template<class T>
Stack<T>& Stack<T>::operator = (const Stack<T>& other) {
    if (this != &other) {
        this->deleteAll();
        this->add(other);
    }
    return *this;
}


#endif // __STACK_HPP__