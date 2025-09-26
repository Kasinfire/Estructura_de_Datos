#ifndef __LIST_HPP__
#define __LIST_HPP__

#include <string> // para cadenas 
#include <exception> // para la clase exception
#include <iostream> //Para los operadores >> y <<


//Definicion 

template <class T, int ARRAYSIZE>
class List {
 private:
    T data[ARRAYSIZE];
    int last;

    static const unsigned int gapSerie[];

    bool isValidPos(const int&) const;
    void copyAll(const List<T, ARRAYSIZE>&);
    void swapData(T&, T&);

    

 public:

    class Exception : public std:: exception{
        private: 
        std:: string msg;

        public:
            Exception() noexcept : msg ("Error indefinido"){ }
            Exception(const Exception& e) noexcept : msg( e.msg){}
            Exception (const std::string& ms) : msg(ms){}
            Exception& operator = (const Exception& e) noexcept{
                msg = e.msg; 
                return *this;
                }
            virtual ~Exception(){ };
            virtual const char* what() const noexcept {
                return msg.c_str();
            }
};


  List();                           // inicialización
  List(const List<T, ARRAYSIZE>&);  // inicialización

  bool isEmpty() const;
  bool isFull() const;
  bool iSroted() const;

  void insertData(const int&, const T&);  // posición , elemento
  void deleteData(const int&);            // posición

  int getFirstPos() const;
  int getLastPos() const;

  int getPrevPos(const int&) const;
  int getNexPos(const int&) const;

  const T& recover(const int&) const;
  int findDataLinear(const T&);
  int findDataBinary(const T&);

  void bubbleSort();
  void insertSort();
  void selectSort();
  void shellSort();

  std::string toString() const;

  void deleteAll();

  List<T, ARRAYSIZE>& operator=(const List<T, ARRAYSIZE>&);
   
  //Deserialización y serialización 
  template <class T2, int SIZE>
  friend std::ostream& operator << (std::ostream&, const List<T2, SIZE>&);
  
  template <class T3, int SIZE2>
  friend std::istream& operator >> (std:: istream&, List<T3,SIZE2>&);

//..............

    int findDataLinear(const T& , int(const T&, const T&)) const;
    int findDataBinary(const T& , int(const T&, const T&)) const;

    void bubbleSort(int(const T&, const T&));
    void insertSort(int(const T&, const T&));
    void selectSort(int(const T&, const T&));
    void shellSort(int(const T&, const T&));
    
    bool iSroted(int(const T&, const T&)) const;


};



// Implementación

using namespace std;

//privados

template <class T, int ARRAYSIZE>
const unsigned int List<T, ARRAYSIZE>:: gapSerie[] = {510774, 227011, 100894, 44842, 19930, 8858, 3937, 1750, 701, 301, 132, 57, 23, 10, 4, 1, 0};


template <class T, int ARRAYSIZE>
bool List<T, ARRAYSIZE>::isValidPos(const int& position) const {
  return position >= 0 and position <= this->last;
}

template <class T, int ARRAYSIZE>
void List<T, ARRAYSIZE>::copyAll(const List<T, ARRAYSIZE>& other) {
  int i(0);

  while (i <= other.last) {
    this->data[i] = other.data[i];
    i++;
  }
  this->last = other.last;
}

template <class T, int ARRAYSIZE>
void List<T, ARRAYSIZE>::swapData(T& x, T& y){
    T aux(x);
    x = y;
    y = aux;
}

//publicos

template <class T, int ARRAYSIZE>
List<T, ARRAYSIZE>::List() : last(-1) {}  // inicialización

template <class T, int ARRAYSIZE>
List<T, ARRAYSIZE>::List(const List<T, ARRAYSIZE>& other) {
  this->copyAll(other);
}

template <class T, int ARRAYSIZE>
bool List<T, ARRAYSIZE>::isEmpty() const {
    return this->last == -1;
}

template <class T, int ARRAYSIZE>
bool List<T, ARRAYSIZE>::isFull() const {
    return this -> last == (ARRAYSIZE-1);
}

template <class T, int ARRAYSIZE>
bool List<T, ARRAYSIZE>:: iSroted() const{
    int i(0);

    while (i < this-> last){
        if (this-> data[i] > this-> data[i+1]){
            return false;
        }
        i++;
    }
    return true; 
}

template <class T, int ARRAYSIZE>
void List<T, ARRAYSIZE>::insertData(const int& pos, const T& element) {

    if ( this-> isFull()){
        throw Exception ("Desbordamiento de datos, insertData");
    }

    int realPos = pos;
    if (realPos == -1){
        realPos = this-> last+1;
    }

    if (realPos< 0 or realPos > this-> last +1){
        throw Exception ("Posicion invalida, insertData");
    }
    
    for (int i= this-> last; i>= realPos; i--){
        this->data[i+1] = this->data[i];
        }
        this-> data[realPos]= element; 
        last++;
    }

template <class T, int ARRAYSIZE>
void List<T, ARRAYSIZE>::deleteData(const int& position) {
    if (!this ->isValidPos(position)){
        throw Exception ("Posicion invalida, deleteData");
    }

    int i(position);
    while (i < this ->last){
        this->data[i] = this ->data[i+1];
        i++;
    }
    this ->last--;
}

template <class T, int ARRAYSIZE>
int List<T, ARRAYSIZE>::getFirstPos() const {
    if (this-> isEmpty()){
        return -1;
    }
    return 0;
}


template <class T, int ARRAYSIZE>
int List<T, ARRAYSIZE>::getLastPos() const {
    return this-> last; 
}

template <class T, int ARRAYSIZE>
int List<T, ARRAYSIZE>::getPrevPos(const int& position) const {
    if (position == 0  or !this ->isValidPos (position)){
        return -1;
    }
    return position - 1; 
}

template <class T, int ARRAYSIZE>
int List<T, ARRAYSIZE>::getNexPos(const int& position) const {
    if (position == this->last or !this ->isValidPos (position)){
            return -1;
        }
        return position + 1; 
}



template <class T, int ARRAYSIZE>
const T& List<T, ARRAYSIZE>::recover(const int& position) const {
    if (!this-> isValidPos (position)){
       throw Exception("Posicion invalida, recover");
    }
    if (isEmpty()){
        throw Exception ("Insuficiencia de datos, recover");
    }

    return this ->data[position];
}

//BUSQUEDA 
//Busqueda linear 

template <class T, int ARRAYSIZE>
int List<T,ARRAYSIZE>::findDataLinear(const T& element){
    int i(0); 

    while (i <= this->last) {
        if (this->data[i] == element){
            return i;
        }
        i++;
    }
    return -1;
}

//Busqueda Binaria 

template <class T, int ARRAYSIZE>
int List<T, ARRAYSIZE>::findDataBinary(const T& element){
    int i = 0, j(last), middle; 


    while (i<=j){
        middle = (i+j)/2;

        if (this-> data[middle] == element){
            return middle;
        }
        if(this-> data[middle] > element){
            j = middle- 1;
        }else {
            i= middle + 1;
        }
    }
    return -1;
}

// ORDENAMINETOS
template <class T, int ARRAYSIZE>
void List<T, ARRAYSIZE>:: bubbleSort(){
    
    int i(last), j;
    bool  flag; 

    do{
        flag = false; 
        j = 0; 

        while(j < i){
            if (this-> data[j] > this-> data[j + 1]){
                this-> swapData(this-> data[j], this-> data[j + 1]);
                flag = true; 
            }
            j++;
        }
        i--;

    }while(flag == true);
}

template <class T, int ARRAYSIZE>
void List<T, ARRAYSIZE>:: insertSort(){
    int i(1), j; 
    T aux; 

    while(i <= last){
        j = i;
        aux = this-> data[i];
        while(j > 0 && aux < this-> data[j - 1]){
            this-> data[j] = this-> data[j - 1];
            j--;
        }
        if (i != j){
            this-> data[j] = aux;
        }
        i++;
    }
}

template <class T, int ARRAYSIZE>
void List<T, ARRAYSIZE>:: selectSort(){
    
    int i(0), j, lessThan;

    while(i < last){
        lessThan = i; 
        j = i + 1; 

        while(j <= last){
            if(this-> data[j] < this-> data[lessThan]){
                lessThan = j; 
            }
            j++;
        }
        if (lessThan != i){
            this-> swapData(this-> data[i], this-> data[lessThan]);
        }
        i++;
    }
}

template <class T, int ARRAYSIZE>
void List<T, ARRAYSIZE>:: shellSort(){
    
    unsigned gapPos(0), gap(this-> gapSerie[gapPos]), i, j;

    while (gap > 0){
        i = gap; 
        while (i <= last){
            j = i; 
        while( j >= gap && this-> data[j - gap] > this-> data[j]){
            this-> swapData(this-> data[j - gap], this-> data[j]);
            j -= gap; 
        }
        i++;
        }
    gap = gapSerie[++gapPos];
    }
}


//cadena 

template <class T, int ARRAYSIZE>
std::string List<T, ARRAYSIZE>::toString() const {
    string str;
    int i(0);

    while (i <= this ->last){
        str += this->data[i]. toString()+ "\n";
        i++;
    }
    return str;
}

template <class T, int ARRAYSIZE>
void List<T, ARRAYSIZE>::deleteAll() {
    this-> last = -1;
}

template <class T, int ARRAYSIZE>
List<T, ARRAYSIZE>& List<T, ARRAYSIZE>::operator= (const List<T, ARRAYSIZE>& other) {
  this->copyAll(other);
  return *this;  
}


/*Esta funcion recorre cada elemento de la lista y lo escribre en el flujo
de salida os separandolo con salto de linea.RETORNA FLUJO  */

template <class T2, int SIZE>
ostream& operator << (ostream& os, const List<T2,SIZE>& l){
    int i(0);
    while (i <= l.last) {
        os << l.data[i++]<<endl;
    }
    return os; 
}
  
/*Lee los elementos del flujo de ENTRADA is y los agrega a la lista mientras haya un espacio
Si ecurre un error se captura la excepcion y de finalizala lectura.*/

template <class T3, int SIZE2>
istream& operator >> (istream& is, List<T3,SIZE2>& l){

    T3 myObject;

    try{
    while(is>>myObject){
        if(!l.isFull()){
             l.data[++l.last] = myObject;
             }
        }
    }catch(const invalid_argument& e){
        
    }
    return is;

}


//................
/**
* Busca un elemento en la lista usando un criterio de comparación específico.
* EL parametro element es el elemento que se desea encontrar en la lista.
* El parametro compare es un Puntero a una función que define cómo comparar dos elementos.
* Debe devolver <0 si a<b, 0 si a==b, >0 si a>b.
* Devuelve la posición del elemento si se encuentra, de lo contrario -1. */

template <class T, int ARRAYSIZE>
int List<T, ARRAYSIZE>:: findDataLinear(const T& element, int(*compare) (const T&, const T&)) const {
    int i(0);
    while (i <= this->last) {
        if (compare(element, this-> data[i]) == 0 ){
            return i;
        }
        i++;
    }
    return -1;
}


template <class T, int ARRAYSIZE>
int List<T, ARRAYSIZE>:: findDataBinary(const T& element, int(*compare) (const T&, const T&)) const {
    int i = 0, j(last), middle; 


    while (i<=j){
        middle = (i+j)/2;
        
        if (compare(element,this-> data[middle]) == 0){
            return middle;
        }
        if(compare(element, this-> data[middle]) < 0 ){
            j = middle- 1;
        }else {
            i= middle + 1;
        }
    }
    return -1;
}

template <class T, int ARRAYSIZE>
void List<T, ARRAYSIZE>:: bubbleSort(int(*compare)(const T&, const T&)){
    int i(last), j;
    bool  flag; 

    do{
        flag = false; 
        j = 0; 

        while(j < i){
            if (compare(this-> data[j] , this-> data[j + 1]) > 0 ){
                this-> swapData(this-> data[j], this-> data[j + 1]);
                flag = true; 
            }
            j++;
        }
        i--;

    }while(flag == true);
}

template <class T, int ARRAYSIZE>
void List<T, ARRAYSIZE>:: insertSort(int(*compare)(const T&, const T&)){
    int i(1), j; 
    T aux; 

    while(i <= last){
        j = i;
        aux = this-> data[i];
        while(j > 0 && compare(aux, this-> data[j - 1]) < 0){
            this-> data[j] = this-> data[j - 1];
            j--;
        }
        if (i != j){
            this-> data[j] = aux;
        }
        i++;
    }
}

template <class T, int ARRAYSIZE>
void List<T, ARRAYSIZE>:: selectSort(int(*compare)(const T&, const T&)){
    int i(0), j, lessThan;

    while(i < last){
        lessThan = i; 
        j = i + 1; 

        while(j <= last){
            if(compare(this-> data[j], this-> data[lessThan])< 0){
                lessThan = j; 
            }
            j++;
        }
        if (lessThan != i){
            this-> swapData(this-> data[i], this-> data[lessThan]);
        }
        i++;
    }
}

template <class T, int ARRAYSIZE>
void List<T, ARRAYSIZE>:: shellSort(int(*compare)(const T&, const T&)){
    int gapPos(0), gap(this-> gapSerie[gapPos]),i, j;

    while (gap > 0){
        i = gap; 
        while (i <= last){
            j = i; 
        while( j >= gap && compare(this-> data[j - gap], this-> data[j])> 0){
            this-> swapData(this-> data[j - gap], this-> data[j]);
            j -= gap; 
        }
        i++;
        }
    gap = gapSerie[++gapPos];
    }
}

template <class T, int ARRAYSIZE>
bool List<T, ARRAYSIZE>:: iSroted(int(*compare)(const T&, const T&)) const{
    int i(0);

    while (i < this-> last){
        if (compare(this-> data[i], this-> data[i+1]) > 0){
            return false;
        }
        i++;
    }
    return true; 
}


#endif  // __LIST_HPP__