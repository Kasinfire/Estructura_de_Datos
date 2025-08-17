#include <iostream>

#include "Matriz.hpp"
#include "Tablita_Primitiva.hpp"


int main() {
  char opc;

  Tablita_Primitiva objTablita_Primitiva;

  do {
    cout << "\nMenu\n" << endl;
    cout << "a. Tamaño y rangos de los Tipos de Dato Primitivos.\n"
         << "b. Ejemplo de uso de Tipo de dato Estructurado. \n"
         << "c. Salir. \n"
         << "Ingresa tu opcion: ";
    cin >> opc;
    cout << "\n";

    opc = tolower(opc);

    switch (opc) {
      case 'a':
        objTablita_Primitiva.ver_tablita();

        break;

      case 'b': {
        int tam;
        while (true) {
          cout << "Ingresa el tamaño de la matriz NxN (entre 3 y 10): ";

          if (cin >> tam) {
            if (tam >= 3 && tam <= 10) {
              break;
            } else {
              cout << "Error: El tamaño min es 3 y max 10.\n";
            }
          } else {
            cout << "Error: Debes ingresar un numero entero (Min 3 y Max 10)\n";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
          }
        }
        Matriz A(tam);
        Matriz B(tam);
        A.llenado_aleatorio();
        B.llenado_aleatorio();

        Matriz C = A * B;
        Matriz D = A + B;

        A.imprimir("A");
        B.imprimir("B");
        C.imprimir("C (A * B)");
        D.imprimir("D (A + B)");

        break;
      }

      case 'c':
        cout << "Saliendo... " << endl;
        break;

      default:
        cout << "Opcion no valida, vuelve a intentar. ";
    }

  } while (opc != 'c');


  return 0;
}
