#include <fstream> // para crear archivos
#include <iomanip> //para el setw y setfill
#include <limits> //para poder limpiar el buffer


#include "menu.hpp"



using namespace std; 


void Menu::runMenu(){
    int opc;

    do{

    system("cls");
    displayAllSongs();
    displayMenu(); 

    cout<<"Selecciona una opcion (1-6): ";
    
    if (!(cin >> opc)) { // si la falla la lectura de la opc (no es un num):
            cin.clear(); // limpia el estado de error de cin
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); //Descarta todos los caracteres buffer hasta encontrar '\n'
            cout << "Error: Entrada invalida. Debes ingresar un numero"<<endl; 
            enterToContinue();
            continue;
        }
        
       
        switch(opc) {
                case 1:
                    this-> insertSong(); 
                    break;
                case 2:
                    this-> deleteSong();
                    break;
                case 3:
                    this-> writeToDisk();
                    break;
                case 4:
                    this-> readFromDisk();
                    break;
                case 5:
                    this ->deleteAllSongs();
                    break;
                case 6:
                    cout << "Saliendo del programa..."<<endl;
                    getchar();
                    enterToContinue();
                    break;                    
                default:
                    cout << "Opcion invalida. Intenta de nuevo."<<endl;
                    enterToContinue();
                    break;

        }
    }while (opc !=6);
}



void Menu::displayMenu(){
    
    int width = 25;

    string title = "MENU DE OPCIONES";
    int titleLenght = title.length();

    int filler = (width - titleLenght) / 2;

    cout <<"\n" << setw(width) << setfill('-') << "" << setfill(' ') << endl; //Muestra linea de '=' caracteres
    cout << setw(filler + titleLenght) << right << title //muestra el titlulo (con el relleno a izquierda)
         << setw(width - filler - titleLenght) << "" << endl; // pone relleno a la derecha  para completar el ancho total
    cout << setw(width) << setfill('-') << "" << setfill(' ') << endl; //Muestra linea de '-' caracteres


    cout << "1. Insertar nueva cancion" <<endl; 
    cout << "2. Eliminar cancion" <<endl;
    cout << "3. Guardar al disco" <<endl;
    cout << "4. Leer el disco" <<endl; 
    cout << "5. Eliminar todas las canciones" <<endl;
    cout << "6. Salir" <<endl;

    cout << setw(width) << setfill('-') << "" << setfill(' ') << endl; //Muestra linea de '=' caracteres

}



void Menu::insertSong(){
    char otherSong;
    do{  
        system("cls");
        displayAllSongs();

        if (songsList->isFull()){
            cout << "\nLa lista esta llena. No se pueden agregar mas canciones";
            enterToContinue();
            return;
        }

        SongParams params;  //Estructura para los datos de la cancion (contenedor temp) 
        cout << "\nIngresa el titulo de la cancion: ";
        cin.ignore();
        getline(cin, params.title);
        
        cout << "Ingresa el autor: ";
        getline(cin, params.author);
        
        cout << "Ingresa el interprete: ";
        getline(cin, params.interprete);
        
        while (true){
        cout << "Ingresa el ranking: ";   
        if (  cin >> params.ranking){
            break;
        }else {
            cout << "Error: Debes ingresar un numero valido para el rankign"<<endl; 
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
        }

        Song newSong(params); //se crea una cancion con los parametros 

        // se traducen los numeros a base 1 (en lugar de q sea 0,1,2 es 1,2,3)
        int numSongs = songsList->getLastPos()+1; 
        int maxPos = numSongs +1;

        
        int position;

        //ERRORES DE VALIDACION RANGO Y DE ENTRADA
        while (true) {
            cout << "\nIngresa la posicion donde deseas insertar la cancion (1-" << maxPos << "): ";
            
            if (cin >> position) {
                if (position >= 1 && position <= maxPos) {
                    break; // Entrada válida
                } else {
                    cout << "Error: La posicion debe estar entre 1 y " << maxPos << endl;
                }
            } else {
                cout << "Error: Entrada invalida. Debes ingresar un numero" << endl;
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
            }
        }
        /// AQUI TERMINAN LOS ERRORES VALIDACION DE RANGO Y ENTRADA 

        int internalPos= position -1;  //Convierte la posicion a el indice base 0 (0,1,2...) 

        try {
            songsList->insertData(internalPos, newSong);  //inserta una nueva song en la posicion interna 
            cout << "Cancion agregada exitosamente."<<endl;
        } catch (const List<Song, 50>::Exception& e) { 
            cerr << "Error: " << e.what() << endl; //cerr se usa especificamente para msg de error
        }


        if (!songsList->isFull()) {
                cout << "Deseas agregar otra cancion? (S/N): ";
                cin >> otherSong;
                otherSong = toupper(otherSong);
                cin.ignore(numeric_limits<streamsize>::max(), '\n');

            } else {
                otherSong = 'N'; // fuerza a otherSong a ser N para que termine el bucle do while
                cout << "La lista esta llena. No se pueden agregar mas canciones"<<endl;
            }
    }while (otherSong =='S');
}

void Menu::deleteSong(){
    displayAllSongs();

    if (songsList->isEmpty()){
        cout << "\nNo se puede eliminar. La lista de canciones esta vacia"<<endl;
        enterToContinue();
        return; 
    }

    int position; 
    int maxPos = songsList->getLastPos() + 1;  // se traduce los numeros a base 1 (en lugar de q sea 0,1,2 es 1,2,3)
    
    //VALIDACION DE ENTRADA Y RANGO 
    while (true) {
        cout << "\nIngresa el numero de cancion a eliminar (1-" << maxPos << "): ";
        
        if (cin >> position) {
            if (position >= 1 and position <= maxPos) {
                break; // Entrada válida
            } else {
                cout << "Error: La posicion debe estar entre 1 y " << maxPos << endl;
            }
        } else {
            cout << "Error: Entrada invalida. Debes ingresar un numero" << endl;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
    }
    //AQUI TERMINA LAS VALIDACIONES DE ENTRADA Y RANGO 


    int internalPos = position - 1; //Convierte la posicion a el indice base 0 (0,1,2...) 

    // Se intenta eliminar se maneja excepciones por si hay algo inesperado.
    try {
        songsList->deleteData(internalPos);
        cout << "Cancion eliminada exitosamente\n";
    } catch(const List<Song,50>::Exception& e) {
        cerr << "\nError: " << e.what() << "\nPor favor ingresa una posicion valida\n";
    }
    enterToContinue();
}

void Menu::deleteAllSongs(){
    displayAllSongs();

    if (songsList->isEmpty()){
        cout << "\nNo se puede eliminar. La lista de canciones esta vacia"<<endl;
        enterToContinue();
        return; 

    } else {
        char confirm;
        cout << "\nEstas seguro de que deseas eliminar TODAS las canciones? (S/N): ";
        cin >> confirm;
        confirm = toupper(confirm);
    
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        
        if (confirm == 'S') {
            songsList->deleteAll(); 
            cout << "Todas las canciones han sido eliminadas exitosamente\n";
        } else {
            cout << "Operacion cancelada\n";
        }
    }
    enterToContinue();
}

void Menu::displayAllSongs(){
   
    if (songsList->isEmpty()){
        cout << "\nLa lista de canciones esta vacia\n";
    } 
     else {
        int width = 150; 
        string title = "LISTA DE EXITOS";

        int titleLenght = title.length();
        int filler = (width - titleLenght) / 2;

        cout << "\n" << setw(width) << setfill('=') << "" << setfill(' ') << endl;
        cout << setw(filler + titleLenght) << right << title  
             << setw(width - filler - titleLenght) << "" << endl; 
        cout << setw(width) << setfill('=') << "" << setfill(' ') << endl; 

        cout << left 
             << setw(29) << "TITULO" << " | "
             << setw(50) << "AUTOR" << " | "
             << setw(50) << "INTERPRETE" << " | "
             << setw(2) << "RANKING" << endl;
             cout << setw(width) << setfill('-') << "" << setfill(' ') << endl;
        
        /* Itera a traves de todas las canciones y las muestra enumeradas (1., 2., ...) */
        for (int i = 0; i <= songsList->getLastPos(); i++) { 
            try {
            cout <<setw(2) <<setfill(' ')<<(i+1)<< ". " << songsList->recover(i).toString() << endl; 
        } catch (const List<Song,50>::Exception&e){
            cerr << "Error al recuperar canción en posicion " << i  << ": " <<e.what()<<endl;
            }
        }
    } 
}

void Menu::writeToDisk(){
    system("cls");
    string myStr;
    ofstream myFile;
    
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cout<<"Escribiendo a archivo..."<<endl;
    cout<<"\nNombre del archivo a escribir: "; 
    getline(cin,myStr);

    //abre el archivo en modo "trunc" osea que lo sobreescribe y si no existe se crea uno nuevo
    myFile.open(myStr, ios_base::trunc);
    if (myFile.is_open()){ //si se abre correctamente escribe la lista de canciones
       
        /*songsList: Desreferencia el puntero songsList para obtener el objeto lista real
        'myFile <<' Escribe el objeto lista en el archivo usando el operador de insercion '<<'*/
        
        myFile << *songsList ; 
        myFile.close();   //se cierra el archivo despues de escribirse 
        cout<<"Archivo escrito correctamente. "<<endl;
    }else {
        cout <<"No se puede abrir el archivo para escritura";
    }
    enterToContinue();
}   

void Menu::readFromDisk(){
    system("cls");
    string fileName;
    ifstream myFile; 

    
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cout<<"\nRecuperando lista desde el archivo..."<<endl;
    cout<<"Nombre del archivo: ";
    getline(cin,fileName);

    myFile.open(fileName);
    if (myFile.is_open()){
        songsList -> deleteAll();

        myFile >> *songsList; 

        if (songsList->isEmpty()) {
            cout << "El archivo se abrio pero no contenia datos validos." << endl;
        } else {
            cout << "Lista recuperada exitosamente! Se cargaron " 
                 << songsList->getLastPos() + 1 << " canciones." << endl;
        }

        cout<<"Lista recuperada!"<<endl;
        displayAllSongs();
    }
    else{
        cout<<"No se pudo abrir el archivo: "<< fileName<<" No existe."<<endl;
    }
    enterToContinue();
    
}

void Menu::enterToContinue(){
    cout<<"[ENTER] para continuar"<<endl;
    getchar();
    
}

Menu::Menu(List<Song,50>& l) : songsList(&l){
    runMenu();
}
