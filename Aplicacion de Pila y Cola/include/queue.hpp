#ifndef __QUEUE_HPP__
#define __QUEUE_HPP__

#include "exceptions.hpp"

//Definicion

template <class T, int ARRAYSIZE>
class Queue {
private:
    T data[ARRAYSIZE];
    int frontPos;
    int endPos = ARRAYSIZE; 

    void copyAll(const Queue<T,ARRAYSIZE>&);
public: 
    Queue();
    Queue(const Queue<T,ARRAYSIZE>&);

    void enqueue(const T&);   //Insertar (Añade un elemento por el final de la cola)
    T dequeue();              //Retira/extrae el elemento frente de la cola  

    bool isEmpty() const;     // Comprueba si la cola no tiene elementos
    bool isFull() const;      // Compureba si la cola esta llena de element 

    T getFrontQ()const;       // Obtiene el elemento 1ero de la cola

    Queue<T, ARRAYSIZE>& operator = (const Queue<T, ARRAYSIZE>&);
    
};


//Implementacion 


template<class T, int ARRAYSIZE>
void Queue<T, ARRAYSIZE>::copyAll(const Queue<T,ARRAYSIZE>& other) {
   this -> frontPos = other.frontPos;  
   this -> endPos = other.endPos; 

   for (int i=0; i < ARRAYSIZE; i++){
    this->data[i] = other.data[i];
   }
}

template<class T, int ARRAYSIZE>
Queue<T, ARRAYSIZE>::Queue() : frontPos(0), endPos(ARRAYSIZE-1){ }

template<class T, int ARRAYSIZE>
Queue<T, ARRAYSIZE>::Queue(const Queue<T,ARRAYSIZE>& other) {
    this-> copyAll(other);
}

template<class T, int ARRAYSIZE>
void Queue<T, ARRAYSIZE>::enqueue(const T& element) {
    if (this-> isFull()){
        throw Exception ("Desbordamiento de datos, enqueue");
    }

    this->endPos++;
    if (this-> endPos == ARRAYSIZE){
        this-> endPos = 0;
    }

    data[endPos] = element;
}

template<class T, int ARRAYSIZE>
T Queue<T, ARRAYSIZE>::dequeue() {
    if(this->isEmpty()){
        throw Exception ("Insuficiencia de datos, dequeue");
    }

    T res (data[this-> frontPos]);
    this->frontPos++;
    if (this -> frontPos == ARRAYSIZE){
        this-> frontPos = 0;
    }
    return res; 
    
}

template<class T, int ARRAYSIZE>
bool Queue<T, ARRAYSIZE>::isEmpty() const {
   if (( this -> frontPos == this -> endPos + 1) || (this-> frontPos == 0 && endPos == ARRAYSIZE - 1)){
        return true;
   }
   return false; 
}

template<class T, int ARRAYSIZE>
bool Queue<T, ARRAYSIZE>::isFull() const {
    if ((this-> frontPos == this->endPos + 2) 
    || (this-> frontPos == 0 && this-> endPos == ARRAYSIZE - 2)
    || (this-> frontPos == 1 && this -> endPos == ARRAYSIZE -1)){
        return true;
    }
    return false; 
}

template<class T, int ARRAYSIZE>
T Queue<T, ARRAYSIZE>::getFrontQ() const {
    if(isEmpty()){
        throw Exception ("Insuficiencia de datos, getFrontQ ");
    }
    return data[frontPos];
}

template<class T, int ARRAYSIZE>
Queue<T, ARRAYSIZE>& Queue<T, ARRAYSIZE>::operator = (const Queue<T, ARRAYSIZE>& other) {
    this->copyAll(other);

    return *this;
}


#endif // __QUEUE_HPP__