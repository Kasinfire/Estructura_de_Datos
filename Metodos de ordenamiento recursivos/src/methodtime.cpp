#include "methodtime.hpp"

using namespace std;



void MethodTime::fillOGlist() {
    srand(time(0));  //Inicializamos los num aleatorios a la hora actual
    for (int i = 0; i < NUM_ELEMENTS; ++i) {
        //Se inserta al final el entero random y se usa el modulo para que 
        //nos de un rango de 0 a el millon 
        OGlist.insertData(-1, Int(rand() % (RANDOM_LIMIT + 1)));
    }
}


//CONSTRUCTOR 
MethodTime::MethodTime() {
    fillOGlist();
}


/** Lo que dice esta funcion en void(List<Int>:: *)() es que solo la funcion se va a 
 * fijar en apuntar a los metodos de la lista, ya que ahi es donde estan nuestros 6
 * metodos de sort */
MethodResults MethodTime::methodsTime(const string& methodNm, void(List<Int>:: *choseSortMethod)()) {
    MethodResults results; 
    results.methodName = methodNm;

    fakelist = OGlist;
    results.sortedBf = fakelist.iSorted();

    clock_t  start = clock();       //Capturamos el click del reloj antes de empezar con el ordenamiento 
    (fakelist.*choseSortMethod)();  //Aqui ejecuta el sort que quiere el user
    clock_t end = clock();          

    /**Aqui se ve si la lista si esta ordenada despues del proceso que se pidio
     * y se calcula la diferencia de ticks q viene del procesador, y se divide con
     * CLOCKS_PER_SEC para obtener los segundos que paso.
     * Al final solo se guarda en el struct */

    results.sortedAf = fakelist.iSorted();
    double timethatLasted = double (end - start)/CLOCKS_PER_SEC;
    results.timeInSec = timethatLasted;

    return results;

}

