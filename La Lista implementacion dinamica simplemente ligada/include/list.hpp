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
List<T>::Node::Node(const T& element) : data(element) { }

//Privado
template<class T>
T& List<T>::Node::getData() {
    return this-> data; 
}

template<class T>
typename List<T>:: Position List<T>::Node::getNext() const {
    return this-> next;
}

template<class T>
void List<T>::Node::setData(const T& element) {
    this-> data = element; 
}

template<class T>
void List<T>::Node::setNext(const typename List<T>:: Position& pointer) {
    this->next = pointer;
}

//Lista

//Privado

template<class T>
bool List<T>::isValidPos(const typename List<T>:: Position& pos) const {
    Position aux(this-> anchor); 

    while( aux != nullptr){
        if ( aux == pos){
            return true; 
        }
        aux = aux->getNext();
    }
    return false; 
}


template<class T>
void List<T>:: add(const List<T>& other) {
    if (other.anchor == nullptr) {
        return;
    }

    Position aux(other.anchor), lastInserted(this->getLastPos()), newNode;

    while(aux != nullptr){
        try {
            newNode = new Node(aux->getData());

            if(lastInserted == nullptr) {
                this-> anchor = newNode;
            }else {
                lastInserted->setNext(newNode);
            }
            lastInserted = newNode;

        } catch ( const bad_alloc& e) {
            throw Exception("Memoria no disponible, add");
        }
        aux = aux->getNext();
    }
}

//Publico

template<class T>
List<T>::List(){ }

template<class T>
List<T>::List(const List<T>& other){ 
    this-> add(other);
}

template<class T>
List<T>::~List(){
    this-> deleteAll();
 }


template<class T>
bool List<T>::isEmpty() const {
    return this-> anchor == nullptr;
}

template<class T>
void List<T>::insertData(const typename List<T>::Position& pos, const T& element){
    if(pos != nullptr && !isValidPos(pos)){
        throw Exception("Posicion Invalida, InsertData");
    }
    Position newNode(new Node(element));

    if(newNode == nullptr){
        throw Exception ("Memoria no disponible, insertData");
    }

    if(pos == nullptr) {
        newNode ->setNext(this-> anchor);
        this->anchor = newNode;

    }else{
        newNode ->setNext(pos->getNext());
        pos ->setNext(newNode);
    }
}

template<class T>
void List<T>::deleteData(const typename List<T>::Position&  pos) {
    if(!this->isValidPos(pos)){
        throw Exception("Posicion invalida, deleteData");
    }
    if(pos == this->anchor){ 
        this->anchor = pos->getNext();
    }else{
        this->getPrevPos(pos) ->setNext(pos->getNext());
    }
    delete pos; 
}

template<class T>
typename List<T>:: Position List<T>:: getFirstPos() const{
     return this-> anchor; 
}
template<class T>
typename List<T>:: Position List<T>::getLastPos() const {
    if(this-> isEmpty()){
        return nullptr;
    }
    
    Position aux(this->anchor);

     while(aux->getNext() != nullptr){
        aux = aux->getNext();
     }
     return aux; 
}

template<class T>
typename List<T>:: Position List<T>::getPrevPos(const typename List<T>::Position& pos) const {
    if(this-> isEmpty() || pos == nullptr){
        return nullptr;
    }

    Position aux(this->anchor);

    while(aux != nullptr && aux->getNext() != pos) {
        aux = aux->getNext();
    }
    return aux; 
}

template<class T>
typename List<T>:: Position List<T>::getNextPos(const typename List<T>::Position& pos) const{
    if(this->isEmpty() || pos == nullptr){
        return nullptr;
    }
    return pos->getNext();
}

template<class T>
typename List<T>:: Position List<T>::findData(const T& element) const{
    Position aux(this->anchor);

    while(aux != nullptr && aux ->getData() != element){
        aux = aux->getNext();
    }
    return aux;
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
    Position aux(this->anchor);

    while(aux != nullptr){
        myStr += aux ->getData().toString() + "\n";
        aux = aux->getNext();
    }
    return myStr;
}


template<class T> //InsertSort
void List<T>::sortedData() {
    if(this-> isEmpty() || this-> anchor->getNext() == nullptr){
        return; 
    }

    Position sorted(nullptr), current(this->anchor);

    while(current != nullptr){
        Position next = current->getNext();

        if(sorted == nullptr || sorted->getData() >= current->getData()){
            current->setNext(sorted);
            sorted = current;
        }else {
            Position temp = sorted;

            while(temp->getNext() != nullptr && temp->getNext()->getData() < current->getData()){
                temp = temp->getNext();
            }
            current ->setNext(temp->getNext());
            temp ->setNext(current);
    }
    current = next;
    }
    this->anchor = sorted; 
}

template<class T>
void List<T>::deleteAll() {
    Position aux; 

    while (this->anchor != nullptr) {
        aux = this-> anchor; 

        this-> anchor = aux->getNext();
        delete aux; 
    }
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
    Position aux(this->anchor);

    while(aux != nullptr && compare(aux ->getData(),element) != 0){
        aux = aux->getNext();
    }
    return aux;
}

template<class T>
void List<T>::sortedData(int(*compare)(const T&, const T&)) {
   if(this-> isEmpty() || this-> anchor->getNext() == nullptr){
        return; 
    }

    Position sorted(nullptr), current(this->anchor);

    while(current != nullptr){
        Position next = current->getNext();

        if(sorted == nullptr || compare(sorted->getData(), current->getData()) >= 0 ){
            current->setNext(sorted);
            sorted = current;
        }else {
            Position temp = sorted;

            while(temp->getNext() != nullptr && compare(temp->getNext()->getData(),current->getData()) < 0){
                temp = temp->getNext();
            }
            current ->setNext(temp->getNext());
            temp ->setNext(current);
    }
    current = next;
    }
    this->anchor = sorted;
}



#endif  // __LIST_HPP__