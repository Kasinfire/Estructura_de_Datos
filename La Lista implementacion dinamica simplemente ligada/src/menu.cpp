#include <fstream> // para crear archivos
#include <iomanip> //para el setw y setfill
#include <limits> //para poder limpiar el buffer


#include "menu.hpp"



using namespace std; 


void Menu::runMenu(){
    int opc;

    do{

    system("cls");
    UI::displayAllSongs(*songsList);
    UI::displayMenu(); 

    cout<<"Selecciona una opcion: ";
    
    if (!(cin >> opc)) { // si la falla la lectura de la opc (no es un num):
            UI::handleInputError();
            continue;
        }
        
        switch(opc) {
                case 1:
                    this-> insertSong(); 
                    break;
                case 2:
                    this-> orderSong();
                    break; 
                case 3:
                    this-> searchSong();
                    break; 
                case 4:
                    this-> deleteSong();
                    break;
                case 5:
                    this-> writeToDisk();
                    break;
                case 6:
                    this-> readFromDisk();
                    break;
                case 7:
                    this ->deleteAllSongs();
                    break;
                case 0:
                    cout << "Saliendo del programa..."<<endl;
                    getchar();
                    UI::enterToContinue();
                    break;                    
                default:
                    cout << "Opcion invalida. Intenta de nuevo."<<endl;
                    UI::enterToContinue();
                    break;

        }
    }while (opc !=0);
}


void Menu::insertSong(){
    char otherSong;
    do{  
        system("cls");
        UI::displayAllSongs(*songsList);

        SongParams params;  //Estructura para los datos de la cancion (contenedor temp) 
        cout << "\nIngresa el titulo de la cancion: ";
        cin.ignore();
        getline(cin, params.title);
        
        cout << "Ingresa el autor: ";
        getline(cin, params.author);
        
        cout << "Ingresa el interprete: ";
        getline(cin, params.interprete);

        cout << "Ingresa el nombre del archvivo mp3 (sin el .mp3): ";
        string mp3Name;
        getline(cin,mp3Name);
        params.mp3FileName = mp3Name + ".mp3";  //puse el .mp3 asi siempre se va a cumplir con que sea archivo mp3    
        
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
        int numSongs = 0; 
        List<Song>::Position current = songsList->getFirstPos();
        while(current != nullptr) {
            numSongs++;
            current = songsList->getNextPos(current);
        }
        int maxPos = numSongs + 1;
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
                UI::handleInputError();
            }
        }

        /// AQUI TERMINAN LOS ERRORES VALIDACION DE RANGO Y ENTRADA 

        List<Song>::Position insertPos = nullptr;
        if (position == 1) {
            // Insertar al inicio (posicion nullptr)
            insertPos = nullptr;
        } else {
            // Buscar la posicion anterior
            insertPos = songsList->getFirstPos();
            for (int i = 1; i < position - 1; i++) {
                insertPos = songsList->getNextPos(insertPos);
            }
        }

        try {
            songsList->insertData(insertPos, newSong);    //inserta una nueva song en la posicion interna 
            cout << "Cancion agregada exitosamente."<<endl;
        } catch (const Exception& e) { 
            cerr << "Error: " << e.what() << endl;          //cerr se usa especificamente para msg de error
        }

        
        cout << "Deseas agregar otra cancion? (S/N): ";
        cin >> otherSong;
        otherSong = toupper(otherSong);
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
                
    }while (otherSong =='S');
}

void Menu::deleteSong(){
    system("cls");
    UI::displayAllSongs(*songsList);

    if (songsList->isEmpty()){
        system("cls");
        cout << "\nNo se puede eliminar. La lista de canciones esta vacia"<<endl;
        getchar();
        UI::enterToContinue();
        return; 
    }

    int position;
    int numSongs =0; 
    List<Song>::Position current = songsList->getFirstPos(); 
    while(current != nullptr) {
        numSongs++;
        current = songsList->getNextPos(current);
    }
    
    int maxPos = numSongs;



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
            UI::handleInputError();
        }
    }
    //AQUI TERMINA LAS VALIDACIONES DE ENTRADA Y RANGO 

     List<Song>::Position deletePos = songsList->getFirstPos();
    for (int i = 1; i < position; i++) {
        deletePos = songsList->getNextPos(deletePos);
    }


    // Se intenta eliminar se maneja excepciones por si hay algo inesperado.
    try {
        songsList->deleteData(deletePos);
        cout << "Cancion eliminada exitosamente\n";
        getchar();
        UI::enterToContinue();
    } catch(const Exception& e) {
        cerr << "\nError: " << e.what() << "\nPor favor ingresa una posicion valida\n";
    }
}

void Menu::deleteAllSongs(){
    system("cls");
    UI::displayAllSongs(*songsList);

    if (songsList->isEmpty()){
        system("cls");
        cout << "\nNo se pueden eliminar todas las canciones. La lista de canciones esta vacia"<<endl;
        UI::enterToContinue();
        getchar();
        return; 

    } else {
        char confirm;
        cout << "\nEstas seguro de que deseas eliminar TODAS las canciones? (S/N): ";
        cin >> confirm;
        confirm = toupper(confirm);
    
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        
        if (confirm == 'S') {
            system("cls");
            songsList->deleteAll(); 
            cout << "Todas las canciones han sido eliminadas exitosamente\n";
        } else {
            cout << "Operacion cancelada\n";
        }
    }
    UI::enterToContinue();
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
        
        // Serializar manualmente usando el método serialize de Song
        List<Song>::Position current = songsList->getFirstPos();
        while(current != nullptr) {
            songsList->retrieve(current).serialize(myFile);
            current = songsList->getNextPos(current);
        }
         
        myFile.close();   //se cierra el archivo despues de escribirse 
        cout<<"Archivo escrito correctamente. "<<endl;
    }else {
        cout <<"No se puede abrir el archivo para escritura";
    }
    UI::enterToContinue();
}   

void Menu::readFromDisk(){
    system("cls");
    string fileName;
    ifstream myFile; 

    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cout<<"\nRecuperando lista desde el archivo..."<<endl;
    cout<<"Nombre del archivo: ";
    getline(cin, fileName);

    myFile.open(fileName);
    if (myFile.is_open()){
        songsList->deleteAll();

        // Deserializar manualmente usando el metodo deserialize de Song
        Song tempSong;
        while(!myFile.eof()) {
            try {
                tempSong.deserialize(myFile);
                if(!myFile.fail()) {
                    songsList->insertData(songsList->getLastPos(), tempSong);
                }
            } catch(const Exception& e) {
                system("cls");
                cerr << "Error de deserialización: " << e.what() << endl;
                break;
            }
        }

        // Conteo de canciones cargadas manualmente
        int count = 0;
        List<Song>::Position current = songsList->getFirstPos();
        while(current != nullptr) {
            count++;
            current = songsList->getNextPos(current);
        }

        if (count == 0) {
            system("cls");
            cout << "El archivo se abrio pero no contenia datos validos." << endl;
        } else {
            system("cls");
            cout << "Lista recuperada exitosamente! Se cargaron " 
                 << count << " canciones." << endl;
        }

        UI::displayAllSongs(*songsList);
    } else {
        system("cls");
        cout<<"No se pudo abrir el archivo: "<< fileName << endl;
    }
    UI::enterToContinue();
}

void Menu::searchSong() {
    if(this-> songsList->isEmpty()){
        system("cls");
        cout<<"No se puede buscar en una lista vacia"<<endl; 
        getchar();
        UI:: enterToContinue();
        return; 
    }
    else {

    int opc;
    do{
        system("cls");
        UI::displaysearchMethodMenu();
        cout<<"Selecciona una opcion: ";

        if (!(cin>> opc)){
            UI::handleInputError();
            continue;
        }

        string criteria;
        switch (opc)
        {
        case 1: //Titulo
            criteria = "Titulo"; 
            break;
        case 2: //Interprete
            criteria = "Interprete";
            break;
        
        case 0: 
            cout<<"Regresando..."<<endl;
            getchar();
            UI::enterToContinue();
            break;
        
        default:
            cout << "Opcion invalida. Intenta de nuevo."<<endl;
            UI::enterToContinue();
            break;
        }
        if (opc == 1 || opc == 2){
            //Pasa la opc del usuario a la siguiente funcion 
            performSearch(opc, criteria);
        }

    }while(opc != 0);
    }
}

void Menu::performSearch(int& opc, string& criteria) {
    system("cls");
    string searchTxt;

    cout << "\nIngresa el " << criteria << " a buscar: ";
    cin.ignore();
    getline(cin, searchTxt);

    List<Song>::Position foundPos = nullptr;

    Song tempSong;
    if (opc == 1) {
        tempSong.setTitle(searchTxt);
        foundPos = songsList->findData(tempSong, Song::compareByTitle);
    } else if (opc == 2) {
        tempSong.setInterprete(searchTxt);
        foundPos = songsList->findData(tempSong, Song::compareByInterprete);
    }

    if (foundPos != nullptr) {
        system("cls");
    
        int index = 1;
        List<Song>::Position temp = songsList->getFirstPos();
        while(temp != foundPos) {
            index++;
            temp = songsList->getNextPos(temp);
        }
        
        cout << "Cancion encontrada en posicion " << index << "!!" << endl;

        try {
            Song foundSong = songsList->retrieve(foundPos);
            int width = 200; 
            string headerTitle = "   BUSQUEDA    ";
            UI::displayHeader(headerTitle, width);
            cout << setw(2) << setfill(' ') << index << ". " << foundSong.toString() << endl;
        } catch (const Exception& e) {
            cout << "Error al recuperar la cancion: " << e.what() << endl;
        }
    } else {
        cout << "Cancion no encontrada" << endl;
    }
    UI::enterToContinue();
}


void Menu::orderSong() {
    if(songsList->isEmpty()){
        system("cls");
        cout<<"No se puede ordenar una lista vacia"<<endl; 
        getchar();
        UI::enterToContinue();
        return;
    }

    int opc;
    do{
        system("cls");
        UI::displaySubMenu();
        cout<<"Selecciona una opcion : ";

        if (!(cin>> opc)){
            UI::handleInputError();
            continue;
        }

        switch (opc) {
            case 1: 
                system("cls");
                songsList->sortedData();
                cout << "Lista ordenada por titulo exitosamente." << endl;
                UI::displayAllSongs(*songsList);
                getchar();
                UI::enterToContinue();
                break;
            case 2:
                system("cls");
                songsList->sortedData(Song::compareByInterprete);
                cout << "Lista ordenada por interprete exitosamente." << endl;
                UI::displayAllSongs(*songsList);
                getchar();
                UI::enterToContinue();
                break;
            case 0: 
                cout<<"Regresando..."<<endl;
                getchar();
                UI::enterToContinue();
                break;
            default:
                system("cls");
                cout << "Opcion invalida. Intenta de nuevo."<<endl;
                UI::enterToContinue();
                break;
        }
    } while(opc != 0);
}


Menu::Menu(List<Song>&l) : songsList(&l){
    runMenu();
}
