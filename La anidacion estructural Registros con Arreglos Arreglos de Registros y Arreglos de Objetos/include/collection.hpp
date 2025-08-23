#ifndef COLLECTION_HPP__
#define COLLECTION_HPP__

#include <string>
#include <stdexcept>
#include "product.hpp"

class Collection{
    private: 
    static const int maxProducts = 500;
    Product products [maxProducts];
    int actualQuantity; 

    public:

    Collection();
    Collection(const Collection&);
    
    int getActualQuantity()const;  //no se le puse un set porque es una variable de control interna

    Product* searchProduct(const std:: string&); //para objetos no constantes que quiero modificaar 
    const Product* searchProduct( const std:: string & )const;  //Para objetos que si son constantes
    
    bool addProduct(const Product&);
    

    Collection& operator = (const Collection&); 
    std:: string toString() const; 

};


#endif // __COLLECTION_HPP__