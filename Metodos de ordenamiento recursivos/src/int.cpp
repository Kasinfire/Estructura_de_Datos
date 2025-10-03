#include "int.hpp"

using namespace std;

//CONSTRUCTORES
Int::Int() : value(0) {}

Int::Int(const Int& other) : value(other.value) {}

Int::Int(const int64_t& value) : value(value) {}

Int::Int(const string& str) {
    try {
        //stoll es un string muy grandeeeeee pq usamos int64_t
        this-> value = stoll(str);
    } catch (const exception& e){
        //si hay un error al converir a str inicializamos en 0
        this-> value = 0; 
    }
}

//GETTER Y SETTER
int64_t Int::getValue() const {
    return this-> value;
}

string Int::toString() const {
    return to_string(this->value);
}

string Int::toString(const Int& i) {
    return i.toString();
}

void Int::setValue(const int64_t& newValue) {
    this-> value = newValue;
}


//OPERADORES
Int& Int::operator = (const Int& other) {
    this->value = other.value;
    return *this;
}

Int& Int::operator = (const string& str) {
    try {
        this->value = stoll(str);
    } catch(const exception& e) {
        this->value = 0;
    }
    return *this;
}


bool Int::operator == (const Int& other) const {
    return this-> value == other.value;
}

bool Int::operator != (const Int&other) const {
    return this-> value != other.value;
}

bool Int::operator < (const Int& other) const {
    return this-> value < other.value;
}

bool Int::operator <= (const Int& other) const {
    return value <= other.value; 
}

bool Int::operator > (const Int& other) const {
    return this-> value > other.value;
}

bool Int::operator >= (const Int& other) const {
    return this-> value >= other.value; 
}



Int Int::operator + (const Int& other) const {
    return Int(this->value + other.value);
}

Int Int::operator - (const Int& other) const {
    return Int(this->value - other.value);
}

Int Int::operator / (const Int& other) const {
    
    // Manejamos la division por cero
    if (other.value == 0) {
        return Int(0); 
    }
    return Int(this->value / other.value);
}

Int Int::operator * (const Int& other) const {
    return Int(this->value * other.value);
}

Int Int::operator % (const Int& other) const {
    
    // Manejamos la division por cero
    if (other.value == 0) {
        return Int(0);
    }
    return Int(this->value % other.value);
}


Int Int::operator ++ (int) {
    Int temp = *this;
    this->value++;
    return temp;
}

Int& Int::operator ++ () {
    this->value++;
    return *this;
}

Int& Int::operator -- () {
    this->value--;
    return *this;
}
Int Int::operator -- (int) {
    Int temp = *this;
    this->value--;
    return temp;
}


Int& Int::operator += (const Int& other) {
    this->value += other.value;
    return *this;
}

Int& Int::operator -= (const Int& other) {
    this->value -= other.value;
    return *this;
}

Int& Int::operator *= (const Int& other) {
    this->value *= other.value;
    return *this;
}

Int& Int::operator /= (const Int& other) {
    if (other.value != 0) {
        this->value /= other.value;
    } else {
        this->value = 0; 
    }
    return *this;
}

Int& Int::operator %= (const Int& other) {
    if (other.value != 0) {
        this->value %= other.value;
    } else {
        this->value = 0;
    }
    return *this;
}

//COMPARACION 
int Int::compare(const Int& other) const {
    if (this->value < other.value){
        return -1;
    } 
    if (this->value > other.value){
        return 1;
    } else {
        return 0; 
    }
}

int Int::compare(const Int& x, const Int& y) {
    return x.compare(y);
}


//FLUJO
ostream& operator<<(std::ostream& os, const Int& i) {
    os << i.value;
    return os;
}

istream& operator>>(std::istream& is, Int& i) {
    is >> i.value;
    return is;
}
