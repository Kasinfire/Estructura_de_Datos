#include "ui.hpp"

void UI::displayMenu(){
    
    int width = 25;

    string title = "MENU DE OPCIONES";
    int titleLenght = title.length();

    int filler = (width - titleLenght) / 2;

    cout <<"\n" << setw(width) << setfill('-') << "" << setfill(' ') << endl; //Muestra linea de '=' caracteres
    cout << setw(filler + titleLenght) << right << title //muestra el titlulo (con el relleno a izquierda)
         << setw(width - filler - titleLenght) << "" << endl; // pone relleno a la derecha  para completar el ancho total
    cout << setw(width) << setfill('-') << "" << setfill(' ') << endl; //Muestra linea de '-' caracteres


    cout << "1. Insertar nueva cancion" <<endl; 
    cout << "2. Ordenar canciones" <<endl; 
    cout << "3. Buscar cancion" <<endl;
    cout << "4. Eliminar cancion" <<endl;
    cout << "5. Guardar al disco" <<endl;
    cout << "6. Leer el disco" <<endl; 
    cout << "7. Eliminar todas las canciones" <<endl<<endl;
    cout << "0. Salir" <<endl;

    cout << setw(width) << setfill('-') << "" << setfill(' ') << endl; //Muestra linea de '-' caracteres

}

void UI::displayHeader(const string& title, int& width) {

        int titleLenght = title.length();
        int filler = (width - titleLenght) / 2;

        cout << "\n" << setw(width) << setfill('=') << "" << setfill(' ') << endl;
        cout << setw(filler + titleLenght) << right << title  
             << setw(width - filler - titleLenght) << "" << endl; 
        cout << setw(width) << setfill('=') << "" << setfill(' ') << endl; 

        cout << left 
             << setw(32) << "TITULO" << " | "
             << setw(50) << "AUTOR" << " | "
             << setw(50) << "INTERPRETE" << " | "
             << setw(50) << "ARCHIVO MP3" << " | "
             << setw(2)  << "RANKING" << endl;
             cout << setw(width) << setfill('-') << "" << setfill(' ') << endl;

}

void UI::displayAllSongs(const List<Song>& songsList){
    if (songsList.isEmpty()){
        cout << "\nLa lista de canciones esta vacia\n";
    } else {
        int width = 200; 
        string title = "LISTA DE EXITOS";
        
        displayHeader(title, width);

        List<Song>::Position current = songsList.getFirstPos();
        int index = 1;
        
        while(current != nullptr) {
            try {
                const Song& song = songsList.retrieve(current);
                cout << setw(2) << setfill(' ') << index << ". " << song.toString() << endl;
                current = songsList.getNextPos(current);
                index++;
            } catch (const Exception& e) {
                cerr << "Error al recuperar canción: " << e.what() << endl;
                break;
            }
        }
    }
}


void UI::displaySubMenu() {
    int width = 25;

    string title = "MENU DE BUSQUEDA";
    int titleLenght = title.length();

    int filler = (width - titleLenght) / 2;

    cout <<"\n" << setw(width) << setfill('-') << "" << setfill(' ') << endl; 
    cout << setw(filler + titleLenght) << right << title 
         << setw(width - filler - titleLenght) << "" << endl; 
    cout << setw(width) << setfill('-') << "" << setfill(' ') << endl; 

    
    cout << "1. Titulo" <<endl; 
    cout << "2. Interprete" <<endl<<endl; 
    cout << "0. Regresar" <<endl;
    cout << setw(width) << setfill('-') << "" << setfill(' ') << endl; 


}

void UI::displaysearchMethodMenu() {
    int width = 25;
    string title = "CRITERIO DE BUSQUEDA";
    int titleLenght = title.length();
    int filler = (width - titleLenght) / 2;

    cout << "\n" << setw(width) << setfill('-') << "" << setfill(' ') << endl; 
    cout << setw(filler + titleLenght) << right << title 
         << setw(width - filler - titleLenght) << "" << endl; 
    cout << setw(width) << setfill('-') << "" << setfill(' ') << endl; 

    cout << "1. Por Titulo" << endl; 
    cout << "2. Por Interprete" << endl<<endl; 
    cout << "0. Regresar" << endl;
    cout << setw(width) << setfill('-') << "" << setfill(' ') << endl;
}

void UI::enterToContinue(){
    cout<<"[ENTER] para continuar ";
    getchar();
    
}

void UI::handleInputError() {
    cin.clear(); // limpia el estado de error de cin
    cin.ignore(numeric_limits<streamsize>::max(), '\n'); //Descarta todos los caracteres buffer hasta encontrar '\n'
    cout << "Error: Entrada invalida. Debes ingresar un numero"<<endl; 
    enterToContinue();
}