#include <string>
#include <iostream>
#include <iomanip> 
#include <limits> 


#include "userinterface.hpp"

using namespace std; 


Queue<char, 444> UserInterface::stringToQueue(const std::string& str) { 
    Queue<char, 444> queue;
    for (char character : str){
        queue.enqueue(character);
    }
    return queue;
}

void UserInterface::printQueue(Queue<char, 444>& queue) {
    while (!queue.isEmpty()){
        cout<< queue.dequeue();
    } 
    cout<<endl; 
}


void UserInterface::displayMenu() {

    int width = 50;

    string title = "CONVERTIDOR DE INFIJO A POSFIJO";
    int titleLenght = title.length();

    int filler = (width - titleLenght) / 2;

    cout <<"\n" << setw(width) << setfill('-') << "" << setfill(' ') << endl; //Muestra linea de '=' caracteres
    cout << setw(filler + titleLenght) << right << title //muestra el titlulo (con el relleno a izquierda)
         << setw(width - filler - titleLenght) << "" << endl; // pone relleno a la derecha  para completar el ancho total
    cout << setw(width) << setfill('-') << "" << setfill(' ') << endl; //Muestra linea de '-' caracteres

    cout << "1. Insertar expresion infija" <<endl; 
    cout << "2. Salir" <<endl;

    cout << setw(width) << setfill('-') << "" << setfill(' ') << endl; //Muestra linea de '-' caracteres
}

void UserInterface::insertExpresion() {

    system("cls");
    std:: string infixExpression;
    cout << "Puedes usar: operandos A-Z, operadores ^,*,/,+,- y parentesis "<<endl;
    
    cout << "\nIngresa la expresion infija: ";
    getline (cin, infixExpression);
    try{
        if (!expressionConverter.isValid(infixExpression)){
            throw Exception ("La expresion contiene caracteres invalidos");
        }
        Queue<char,444> infixQueue = stringToQueue(infixExpression);
        postfixedExpression = expressionConverter.turnPostfixedQueue(infixQueue); 

    }catch(const Exception& e){
        cerr<<"Error: "<< e.what()<< endl;
    }
}

void UserInterface::printExpresion() {
    if (postfixedExpression.isEmpty()){
        cout<<"No hay expresion posfija"<<endl; 
        return; 
    }

    Queue<char, 444> tempQueue = postfixedExpression; 
    cout<<"Expresion Posfija: ";
    while (!tempQueue.isEmpty()){
        cout << tempQueue.dequeue();
    }
    cout<< endl; 
}


void UserInterface::enterToContinue() {
    cout<<"\n[ENTER] para continuar"<<endl;
    getchar();
}

UserInterface::UserInterface() { }

void UserInterface::run()
{
    int opc; 

    do{
        system("cls");
        displayMenu(); 

        cout<<"Selecciona una opcion (1-2): ";
    
        if (!(cin >> opc)) { // si la falla la lectura de la opc (no es un num):
            cin.clear(); // limpia el estado de error de cin
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); //Descarta todos los caracteres buffer hasta encontrar '\n'
            cout << "Error: Entrada invalida. Debes ingresar un numero"<<endl; 
            enterToContinue();
            continue;
        }

        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        switch(opc) {
                case 1:
                system("cls");
                insertExpresion();
                printExpresion();
                enterToContinue();
                break;

                case 2:
                system("cls");
                cout << "Saliendo del programa..."<<endl;
                    enterToContinue();
                break; 

                default:
                cout << "Opcion invalida. Intenta de nuevo."<<endl;
                    enterToContinue();
                break;

        }
    }while(opc!=2);
}


