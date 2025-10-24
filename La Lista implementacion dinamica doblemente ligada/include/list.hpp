#ifndef __LIST_HPP__
#define __LIST_HPP__

#include <string>
#include <exception>
#include "exception.hpp"


//Definicion

template <class T> 
class List {
class Node;

    public: 
    typedef Node* Position; 

    private: 
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

                void setDataPtr(const T*);
                void setData(const T&);

                void setPrev(const Position&);
                void setNext(const Position&);
        };
        Position header = nullptr;
        bool isValidPos(const Position&) const; 
        void add(const List<T>&);

    public: 

        List();
        List(const List<T>&);
        ~List();

        bool isEmpty() const;
        void insertData(const Position&, const T&);
        void deleteData(const Position&);

        Position getFirstPos() const; 
        Position getLastPos() const;
        Position getPrevPos(const Position&) const;
        Position getNextPos(const Position&) const;

        Position findData(const T&) const; 

        T& retrieve(const Position&);
        const T& retrieve(const Position&) const;

        std:: string toString() const; 

        void sortedData();
        void deleteAll();


        List<T>& operator = (const List<T>&);
        List<T>& operator+=(const List<T>&);
        List<T> operator+(const List<T>&) const;

    //---------------------------------------------

    Position findData(const T& , int(*)(const T&, const T&)) const;
    void sortedData(int(*)(const T&, const T&)); 

};

//Implementacion

using namespace std; 

//Nodo
//Publico
template<class T>
List<T>::Node::Node() { }

template<class T>
List<T>::Node::Node(const T& element) : dataPtr(new T(element)) { 
    if(dataPtr == nullptr){
        throw Exception ("Memoria no disponible, Node");
    }
}

template<class T>
List<T>::Node::~Node(){
    delete this-> dataPtr; 
 }

//Privado
template<class T>
T* List<T>::Node::getDataPtr() {
    return this-> dataPtr; 
}

template<class T>
T& List<T>::Node::getData() {
    if(this-> dataPtr == nullptr){
        throw Exception("Dato inexistente, getData");
    }
    return *this-> dataPtr; 
}

template<class T>
typename List<T>:: Position List<T>::Node::getPrev() const {
    return this-> prev;
}

template<class T>
typename List<T>:: Position List<T>::Node::getNext() const {
    return this-> next;
}

template<class T>
void List<T>::Node::setDataPtr(const T* element) {
    this-> dataPtr = element; 
}

template<class T>
void List<T>::Node::setData(const T& element) {
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
void List<T>::Node::setPrev(const typename List<T>:: Position& pointer) {
    this->prev = pointer;
}

template<class T>
void List<T>::Node::setNext(const typename List<T>:: Position& pointer) {
    this->next = pointer;
}

//Lista

//Privado

template<class T>
bool List<T>::isValidPos(const typename List<T>:: Position& pos) const {
    Position aux(this-> header->getNext()); 

    while(aux != header){
        if ( aux == pos){
            return true; 
        }
        aux = aux->getNext();
    }
    return false; 
}


template<class T>
void List<T>:: add(const List<T>& other) {
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

//Publico

template<class T>
List<T>::List(): header(new Node) { 
    if(this-> header == nullptr) {
        throw Exception("Memoria no disponible, List");
    }

    this->header->setPrev(this->header);
    this->header->setNext(this->header);

}

template<class T>
List<T>::List(const List<T>& other) : header(new Node) { 
     if(this-> header == nullptr) {
        throw Exception("Memoria no disponible, List");
    }

    this->header->setPrev(this->header);
    this->header->setNext(this->header);

    this-> add(other);
}

template<class T>
List<T>::~List(){
    this-> deleteAll();
    delete this-> header; 
 }


template<class T>
bool List<T>::isEmpty() const {
    return this-> header-> getNext() == this-> header;
}

template<class T>
void List<T>::insertData(const typename List<T>::Position& pos, const T& element){
    if(pos != nullptr && !isValidPos(pos)){
        throw Exception("Posicion Invalida, insertData");
    }

    Position newNode;
    try {
        newNode = new Node(element);
    } catch (const bad_alloc&e){
        throw Exception("Memoria no disponible, insertData");
    }

    Position insertedPos(pos == nullptr ? header : pos);

    newNode->setPrev(insertedPos);
    newNode->setNext(insertedPos->getNext());

    insertedPos->getNext()->setPrev(newNode); 
    insertedPos->setNext(newNode);
}

template<class T>
void List<T>::deleteData(const typename List<T>::Position&  pos) {
    if(!this->isValidPos(pos)){
        throw Exception("Posicion invalida, deleteData");
    }
    
    pos->getPrev()->setNext(pos->getNext());
    pos->getNext()->setPrev(pos->getPrev());

    delete pos; 
}

template<class T>
typename List<T>:: Position List<T>:: getFirstPos() const{
    if(this-> isEmpty()){
        return nullptr; 
    }
     return this-> header->getNext(); 
}
template<class T>
typename List<T>:: Position List<T>::getLastPos() const {
    if(this-> isEmpty()){
        return nullptr;
    }
    return this-> header->getPrev();
}

template<class T>
typename List<T>:: Position List<T>::getPrevPos(const typename List<T>::Position& pos) const {
    if(pos == this->header->getNext() || !this->isValidPos(pos)){
        return nullptr;
    }
    return pos-> getPrev();
}

template<class T>
typename List<T>:: Position List<T>::getNextPos(const typename List<T>::Position& pos) const{
    if(pos == this->header->getPrev() || !this->isValidPos(pos)){
        return nullptr;
    }
    return pos-> getNext();
}

template<class T>
typename List<T>:: Position List<T>::findData(const T& element) const{
    Position aux(this->header->getNext());

    while(aux != this->header){
        if(aux->getData() == element){
            return aux;
        }
        aux = aux->getNext();
    }
    return nullptr;
}

template<class T>
T& List<T>::retrieve(const typename List<T>:: Position& pos) {
    if(!this->isValidPos(pos) || pos == nullptr){
        throw Exception("Posicion invalida, retrieve");
    }
    return pos->getData();
}

template<class T>
const T& List<T>::retrieve(const typename List<T>::Position& pos) const {
    if(!isValidPos(pos) || pos == nullptr){
        throw Exception("Posicion invalida, retrieve");
    }
    return pos->getData();
}

template<class T>
string List<T>::toString() const {
    string myStr; 
    Position aux(this->header->getNext());

    while(aux != header){
        myStr += aux ->getData().toString() + "\n";
        aux = aux->getNext();
    }
    return myStr;
}

template<class T>
void List<T>::sortedData() {
    if (this->isEmpty() || this->header->getNext()->getNext() == this->header) {
        return;
    }

    Position i = this->header->getNext()->getNext();
    
    while (i != this->header) { 
        T aux = i->getData();   
        Position j = i;       
        
        while (j != this->header->getNext() && aux < j->getPrev()->getData()) {

            j->setData(j->getPrev()->getData());
            j = j->getPrev();
        }
        
        if (j != i) {
            j->setData(aux);
        }
        
        i = i->getNext();
    }
}


template<class T>
void List<T>::deleteAll() {
    Position aux; 

    while (this->header->getNext() != header) {
        aux = this->header->getNext(); 

        this->header->setNext(aux->getNext());
        delete aux; 
    }

    this->header->setPrev(this->header);
}

template<class T>
List<T>& List<T>::operator = (const List<T>& other) {
    if (this != &other) {
        this->deleteAll();
        this->add(other);
    }
    return *this;
}

template<class T>
List<T>& List<T>::operator+=(const List<T>& other) {
    if (this == &other) { 
        List<T> temp(other);
        this->add(temp);
    } else {
        this->add(other);
    }
    return *this;
}

template<class T>
List<T> List<T>::operator+(const List<T>& other) const {
    List<T> result(*this);
    result += other;        
    return result;
}

//--------------------------------------------------------

template<class T>
typename List<T>::Position List<T>::findData(const T& element, int(*compare)(const T&, const T&)) const {
    Position aux(header->getNext());

    while(aux != header  && compare(aux ->getData(),element) != 0){
        aux = aux->getNext();
    }
    if (aux != header) {
    return aux;
    } else {
    return nullptr;
    }
}

template<class T>
void List<T>::sortedData(int(*compare)(const T&, const T&)) {
    if (this->isEmpty() || this->header->getNext()->getNext() == this->header) {
        return;
    }

    Position i = this->header->getNext()->getNext();
    
    while (i != this->header) { 
        T aux = i->getData();   
        Position j = i;       
        
        while (j != this->header->getNext() && compare(aux, j->getPrev()->getData()) < 0) {

            j->setData(j->getPrev()->getData());
            j = j->getPrev();
        }
        
        if (j != i) {
            j->setData(aux);
        }
        
        i = i->getNext();
    }
}

#endif  // __LIST_HPP__