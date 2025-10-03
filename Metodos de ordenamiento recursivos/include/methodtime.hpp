#ifndef __METHODTIME_H__
#define __METHODTIME_H__


#include "int.hpp"
#include "list.hpp"

#include <random>   // Para generar num aleatorios
#include <chrono>   // Para medir el tiempo
#include <ctime>    // Para la semilla del generador de numeros


struct MethodResults{
    std:: string methodName;
    bool sortedBf;
    bool sortedAf;
    double timeInSec; 
};


class MethodTime {
    private:
    List<Int> OGlist;    
    List<Int> fakelist; 

    const int NUM_ELEMENTS  = 100000;
    const int RANDOM_LIMIT = 1000000;

    void fillOGlist();

    public:
    
    MethodTime();    //Constructor 
    MethodResults methodsTime(const string&, void(List<Int>:: *)() );
};



#endif // __METHODTIME_H__