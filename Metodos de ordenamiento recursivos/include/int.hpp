#ifndef __INT_H__
#define __INT_H__

#include <cstdint> //para el int64_t
#include <string> 
#include <sstream> 

class Int {
    private:
    int64_t value;

    public:
    //COSNTRUCTORES  
    Int();                                //Por defecto Inicializacion  
    Int(const Int&);                      //Copia
    explicit Int(const int64_t&);        //Converasion a un entero de 64 bits
    explicit Int(const std::string&);    //Conversion a string

    //GETTERS Y SETTERS 
    int64_t getValue() const; 
    std:: string toString() const; 
    static std:: string toString(const Int&); 

    void setValue(const int64_t&);

    //OPERADORES 
    Int& operator = (const Int&);
    Int& operator = (const std::string&);

    bool operator == (const Int&) const; 
    bool operator != (const Int&) const; 
    bool operator < (const Int&) const; 
    bool operator <= (const Int&) const; 
    bool operator > (const Int&) const; 
    bool operator >= (const Int&) const; 

    Int operator + (const Int&)const; 
    Int operator - (const Int&)const;
    Int operator / (const Int&)const;
    Int operator * (const Int&)const;
    Int operator % (const Int&)const;

    Int& operator ++();
    Int operator ++(int);
    Int& operator --();
    Int operator --(int);

    Int& operator += (const Int&);
    Int& operator -= (const Int&);
    Int& operator *= (const Int&);
    Int& operator /= (const Int&);
    Int& operator %= (const Int&);

    //COMPARACION
    int compare(const Int&) const; 
    static int compare(const Int&, const Int&);

    //FLUJO 
    friend std:: ostream& operator << (std:: ostream&, const Int&);
    friend std:: istream& operator >> (std:: istream&, Int&);
   
};

#endif // __INT_H__