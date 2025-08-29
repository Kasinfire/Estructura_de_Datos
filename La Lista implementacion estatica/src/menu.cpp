#include "menu.hpp"
#include <iostream>
#include <iomanip>
#include <limits>

using namespace std; 

void Menu::runMenu(){
    int option;
    do {
        displaySongs();      
        displayMenu();         
        
        cout << "\nSelecciona una opcion: ";
        
        if (!(cin >> option)) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Error: Entrada invalida. Debes ingresar un numero\n";
            cout << "[ENTER] para continuar";
            cin.ignore();
            cin.get();
            continue;
        }
        
        switch(option) {
            case 1:
                insertSong();
                break;
            case 2:
                deleteSong();
                break;
            case 3:
                deleteAllSongs();
                break;
            case 4:
                cout << "Saliendo del programa...\n";
                break;
            default:
                cout << "Opcion invalida. Intenta de nuevo.\n";
                cout << "[ENTER] para continuar";
                cin.ignore();
                cin.get();
                break;
        }
    } while (option != 4);
}

void Menu::displayMenu(){
    int width = 25;

    string title = "MENU DE OPCIONES";
    int titleLenght = title.length();

    int filler = (width - titleLenght) / 2;

    cout <<"\n" << setw(width) << setfill('-') << "" << setfill(' ') << endl;
    cout << setw(filler + titleLenght) << right << title
         << setw(width - filler - titleLenght) << "" << endl;
    cout << setw(width) << setfill('-') << "" << setfill(' ') << endl;

    cout << "1. Insertar nueva cancion\n";
    cout << "2. Eliminar cancion\n";
    cout << "3. Eliminar todas las canciones\n";
    cout << "4. Salir\n";
    cout << setw(width) << setfill('=') << "" << setfill(' ') << endl;
}

void Menu::insertSong(){
   char otherSong;
   do{  
        displaySongs();

        if (songsList.isFull()){
            cout << "\nLa lista esta llena. No se pueden agregar mas canciones";
            cout << "[ENTER] para continuar";
            cin.ignore();
            cin.get();
            return;
        }

        SongParams params; 
        cout << "\nIngresa el titulo de la cancion: ";
        cin.ignore();
        getline(cin, params.title);
        
        cout << "Ingresa el autor: ";
        getline(cin, params.author);
        
        cout << "Ingresa el interprete: ";
        getline(cin, params.interprete);
        
        cout << "Ingresa el ranking: ";
        cin >> params.ranking;

        Song newSong(params);

        int numSongs = songsList.getLastPos()+1;
        int maxPos = numSongs +1;

        int position;
        cout << "\nIngresa la posicion donde deseas insertar la cancion (1-" << maxPos << "): ";
        if (!(cin >> position)) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Error: Entrada invalida. Debes ingresar un numero\n";
            cout << "[ENTER] para continuar";
            cin.ignore();
            cin.get();
            return;
        }

        if (position < 1 || position > maxPos) {
            cout << "Error: La posicion debe estar entre 1 y " << maxPos << endl;
            cout << "[ENTER] para continuar";
            cin.ignore();
            cin.get();
            return;
        }

        int internalPos= position -1; 

        try {
            songsList.insertData(internalPos, newSong);
            cout << "Cancion agregada exitosamente.\n";
        } catch (const List<Song, 50>::Exception& e) {
            cerr << "Error: " << e.what() << endl;
        }
        if (!songsList.isFull()) {
                cout << "Deseas agregar otra cancion? (s/n): ";
                cin >> otherSong;
            } else {
                otherSong = 'n';
                cout << "La lista esta llena. No se pueden agregar mas canciones\n";
            }
    }while (otherSong == 's'|| otherSong =='S');
    
    cout << "[ENTER] para continuar";
    cin.ignore();
    cin.get();
}


void Menu::deleteSong(){
    if (songsList.isEmpty()){
        cout << "\nNo se puede eliminar. La lista de canciones esta vacia\n";
        cout << "[ENTER] para continuar";
        cin.ignore();
        cin.get();
        return; 
    }

    int position; 
    int maxPos = songsList.getLastPos() + 1; 
    cout << "\nIngresa el numero de cancion a eliminar: (1-" << maxPos << "): ";
    
    if (!(cin >> position)) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Error: Entrada invalida. Debes ingresar un numero\n";
        cout << "[ENTER] para continuar";
        cin.ignore();
        cin.get();
        return;
    }

    if (position < 1 || position > maxPos) {
        cout << "Error: La posicion debe estar entre 1 y " << maxPos << endl;
        cout << "[ENTER] para continuar";
        cin.ignore();
        cin.get();
        return;
    }

    int internalPos = position - 1;

    try {
        songsList.deleteData(internalPos);
        cout << "Cancion eliminada exitosamente\n";
    } catch(const List<Song,50>::Exception& e) {
        cerr << "\nError: " << e.what() << "\nPor favor ingresa una posicion valida\n";
    }
    
    cout << "[ENTER] para continuar";
    cin.ignore();
    cin.get();
}

void Menu::deleteAllSongs(){
    if (songsList.isEmpty()){
        cout << "\nNo se puede eliminar. La lista de canciones esta vacia\n";
        cout << "[ENTER] para continuar";
        cin.ignore();
        cin.get();
        return; 
    } else {
        char confirmacion;
        cout << "\nEstas seguro de que deseas eliminar TODAS las canciones? (s/n): ";
        cin >> confirmacion;
        
        if (confirmacion == 's' || confirmacion == 'S') {
            songsList.deleteAll(); 
            cout << "Todas las canciones han sido eliminadas exitosamente\n";
        } else {
            cout << "Operacion cancelada\n";
        }
    }
    
    cout << "[ENTER] para continuar";
    cin.ignore();
    cin.get();
}

void Menu::displaySongs(){
    if (songsList.isEmpty()){
        cout << "\nLa lista de canciones esta vacia\n";
    } else {
        int width = 50;
        string title = "LISTA DE EXITOS";
        int titleLenght = title.length();
        int filler = (width - titleLenght) / 2;

        cout << "\n" << setw(width) << setfill('=') << "" << setfill(' ') << endl;
        cout << setw(filler + titleLenght) << right << title
             << setw(width - filler - titleLenght) << "" << endl;
        cout << setw(width) << setfill('=') << "" << setfill(' ') << endl;

        for (int i = 0; i <= songsList.getLastPos(); i++) {
            cout << (i + 1) << ". " << songsList.recover(i).toString() << endl; 
        }
    }
}