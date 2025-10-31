#ifndef __QUEUE_HPP__
#define __QUEUE_HPP__

#include "exceptions.hpp"

//Definicion

template <class T>
class Queue {
    private: 
    class Node;
    typedef Node* Position;
        class Node {

            private:
                T* dataPtr= nullptr; 
                Position prev = nullptr;
                Position next = nullptr;

            public: 
                Node();
                Node(const T&);
                ~Node();

                T* getDataPtr();
                T& getData(); 
                 
                Position getPrev() const;
                Position getNext() const;

                void setDataPtr(T*);
                void setData(const T&);

                void setPrev(const Position&);
                void setNext(const Position&);
        };
        
        Position header = nullptr;
        void add(const Queue<T>&);
        void deleteAll();

public: 
    Queue();
    Queue(const Queue<T>&);
    ~Queue();

    void enqueue(const T&);   //Insertar (Añade un elemento por el final de la cola)
    T dequeue();              //Retira/extrae el elemento frente de la cola  

    bool isEmpty() const;     // Comprueba si la cola no tiene elementos

    T getFrontQ()const;       // Obtiene el elemento 1ero de la cola

    Queue<T>& operator = (const Queue<T>&);
    
};


//Implementacion

using namespace std; 

//Nodo
//Publico
template<class T>
Queue<T>::Node::Node() { }

template<class T>
Queue<T>::Node::Node(const T& element) : dataPtr(new T(element)) { 
    if(dataPtr == nullptr){
        throw Exception ("Memoria no disponible, Node");
    }
}

template<class T>
Queue<T>::Node::~Node(){
    delete this-> dataPtr; 
 }

//Privado
template<class T>
T* Queue<T>::Node::getDataPtr() {
    return this-> dataPtr; 
}

template<class T>
T& Queue<T>::Node::getData() {
    if(this-> dataPtr == nullptr){
        throw Exception("Dato inexistente, getData");
    }
    return *this-> dataPtr; 
}

template<class T>
typename Queue<T>:: Position Queue<T>::Node::getPrev() const {
    return this-> prev;
}

template<class T>
typename Queue<T>:: Position Queue<T>::Node::getNext() const {
    return this-> next;
}

template<class T>
void Queue<T>::Node::setDataPtr(T* element) {
    this-> dataPtr = element; 
}

template<class T>
void Queue<T>::Node::setData(const T& element) {
    if(this->dataPtr == nullptr){
        this-> dataPtr = new T(element);
        
        if(this->dataPtr == nullptr) {
            throw Exception("Memoria no disponible, setData");
        }
    }else {
        *this-> dataPtr = element; 
    }
}

template<class T>
void Queue<T>::Node::setPrev(const typename Queue<T>:: Position& pointer) {
    this->prev = pointer;
}

template<class T>
void Queue<T>::Node::setNext(const typename Queue<T>:: Position& pointer) {
    this->next = pointer;
}


//Queue

//Private
template<class T>
void Queue<T>:: add(const Queue<T>& other) {
    if (other.isEmpty()) {
        return;
    }

    Position aux(other.header->getNext());

    while(aux != other.header){
        try {
            Position newNode = new Node(aux->getData());
            
            newNode->setPrev(this->header->getPrev());
            newNode->setNext(this->header);

            this->header->getPrev()->setNext(newNode);
            this->header->setPrev(newNode);

        } catch ( const bad_alloc& e) {
            throw Exception("Memoria no disponible, add");
        }
        aux = aux->getNext();
    }
}

template<class T>
void Queue<T>::deleteAll() {
    Position aux; 
    while (this->header->getNext() != header) {
        aux = this->header->getNext(); 
        this->header->setNext(aux->getNext());
        aux->getNext()->setPrev(this->header); 
        delete aux; 
    }
    this->header->setPrev(this->header);
}

template<class T>
Queue<T>::Queue(): header(new Node){
    if(this-> header == nullptr) {
        throw Exception("Memoria no disponible, Queue");
    }
    header->setPrev(header);
    header->setNext(header);
 }

template<class T>
Queue<T>::Queue(const Queue<T>& other) : Queue() { 
    this-> add(other);
}

template<class T>
Queue<T>::~Queue(){
    this-> deleteAll();
    delete this->header;
}

template<class T>
void Queue<T>::enqueue(const T& element) {
    Position newNode;
    try{
    newNode = new Node(element);
    } catch (const bad_alloc& e){
        throw Exception("Memoria no disponible, enqueue");
    }

    newNode->setPrev(this->header->getPrev());
    newNode->setNext(header);

    this->header->getPrev()->setNext(newNode);
    this->header->setPrev(newNode);

}

template<class T>
T Queue<T>::dequeue() {
    if(this->isEmpty()){
        throw Exception("Insuficencia de datos, dequeue");
    }

    Position aux(this->header->getNext());
    T result(aux->getData());

    aux->getPrev()->setNext(aux->getNext());
    aux->getNext()->setPrev(aux->getPrev());
    delete aux; 

    return result; 
}

template<class T>
bool Queue<T>::isEmpty() const {
    return header->getNext() == header;
}


template<class T>
T Queue<T>::getFrontQ() const {
    if(this->isEmpty()){
        throw Exception("Insuficencia de datos, getFront");
    }
    return this->header->getNext()->getData();
}

template<class T>
Queue<T>& Queue<T>::operator = (const Queue<T>& other) {
    if (this != &other) {
        this->deleteAll();
        this->add(other);
    }
    return *this;
}


#endif // __QUEUE_HPP__