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

    cout<<"Selecciona una opcion (1-6): ";
    
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
                case 8:
                    cout << "Saliendo del programa..."<<endl;
                    getchar();
                    UI::enterToContinue();
                    break;                    
                default:
                    cout << "Opcion invalida. Intenta de nuevo."<<endl;
                    UI::enterToContinue();
                    break;

        }
    }while (opc !=8);
}


void Menu::insertSong(){
    char otherSong;
    do{  
        system("cls");
        UI::displayAllSongs(*songsList);

        if (songsList->isFull()){
            cout << "\nLa lista esta llena. No se pueden agregar mas canciones";
            UI::enterToContinue();
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
        int numSongs = songsList->getLastPos() + 1; 
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

        int internalPos= position -1; //Convierte la posicion a el indice base 0 (0,1,2...) 

        try {
            songsList->insertData(internalPos, newSong);    //inserta una nueva song en la posicion interna 
            cout << "Cancion agregada exitosamente."<<endl;
        } catch (const List<Song>::Exception& e) { 
            cerr << "Error: " << e.what() << endl;          //cerr se usa especificamente para msg de error
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
    system("cls");
    UI::displayAllSongs(*songsList);

    if (songsList->isEmpty()){
        system("cls");
        cout << "\nNo se puede eliminar. La lista de canciones esta vacia"<<endl;
        UI::enterToContinue();
        getchar();
        return; 
    }

    int position; 
    int maxPos = songsList->getLastPos() + 1; // se traduce los numeros a base 1 (en lugar de q sea 0,1,2 es 1,2,3)
    
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


    int internalPos = position - 1; //Convierte la posicion a el indice base 0 (0,1,2...) 

    // Se intenta eliminar se maneja excepciones por si hay algo inesperado.
    try {
        songsList->deleteData(internalPos);
        cout << "Cancion eliminada exitosamente\n";
    } catch(const List<Song>::Exception& e) {
        cerr << "\nError: " << e.what() << "\nPor favor ingresa una posicion valida\n";
    }
    UI::enterToContinue();
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
       
        /*songsList: Desreferencia el puntero songsList para obtener el objeto lista real
        'myFile <<' Escribe el objeto lista en el archivo usando el operador de insercion '<<'*/
        
        myFile << *songsList ; 
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

        UI::enterToContinue();
        cout<<"Lista recuperada!"<<endl;
        UI::displayAllSongs(*songsList);
    }
    else{
        cout<<"No se pudo abrir el archivo: "<< fileName<<" No existe."<<endl;
    }
    UI::enterToContinue();
    
}

void Menu::searchSong() {
    if(this-> songsList->isEmpty()){
        system("cls");
        cout<<"No se puede buscar en una lista vacia"<<endl; 
        UI:: enterToContinue();
        getchar();
    }
    else {

    int opc;
    do{
        system("cls");
        UI::displaySubMenu();

        cout<<"Selecciona una opcion (1-3): ";

        if (!(cin>> opc)){
            UI::handleInputError();
            continue;
        }

        string title;
        switch (opc)
        {
        case 1: //Titulo
            title = "Titulo"; 
            break;
        case 2: //Interprete
            title = "Interprete";
            break;
        
        case 3: 
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
            handleSearchCreateria(opc, title);
        }

    }while(opc != 3);
    }
}

void Menu::handleSearchCreateria(int& opc, string& title) {
    int metOpc;
    do{
        system("cls");
        UI::displaysearchMethodMenu();
        cout << "Selecciona una opcion (1-3): ";

        if (!(cin>> metOpc)){
            UI::handleInputError();
            continue;
        }

        switch (metOpc){
        case 1: //Busqueda lineal
        case 2: //Busqueda binaria
            performSearch(opc, metOpc, title);
            break;
        case 3: 
            cout<<"Regresando..."<<endl;
            getchar();
            UI::enterToContinue();
            break;
        
        default:
            cout << "\nOpcion invalida. Intenta de nuevo."<<endl;
            UI::enterToContinue();
            break;
        }
    }while(metOpc !=3);
}

void Menu::performSearch(int&opc, int& metOpc, string& title) {
    system("cls");
    string searchTxt;

    cout<<"\nIngresa el texto a buscar: ";
    cin.ignore();
    getline(cin, searchTxt);

    //Declaramos una variable que puede "contener" una función de comparacion
    int (*comparisonFunction)(const Song&, const Song&);
    Song searchSong;

    if(opc == 1){ //Por titulo 
        comparisonFunction = Song::compareByTitle;
        searchSong.setTitle(searchTxt);

    }else { //interprete
       comparisonFunction = Song::compareByInterprete;
       searchSong.setInterprete(searchTxt);
    }

    int pos = -1;

    //Como buscar el metodo por lineal o por binaria

    char res; 

    if(metOpc == 1) { //Titulo
        pos = songsList ->findDataLinear(searchSong, comparisonFunction);
    }else { //Interprete
        if (this-> songsList -> iSroted(comparisonFunction)){
            pos = songsList ->findDataBinary (searchSong, comparisonFunction);
        }else {
            cout<<"La lista no esta ordenada por "<< title <<endl; 
            
            cout<<"\nDeseas ordenar la lista por " << title << "(S/N)?: ";
                if (!(cin>> res)){
                UI::handleInputError();
            } else {
                res = toupper(res);
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                if (res == 'S'){
                    this-> songsList->shellSort(comparisonFunction);
                    cout<<"La lista se ordeno existosamente por " << title<< endl; 
                    pos = songsList ->findDataBinary (searchSong, comparisonFunction);
                }else {
                    cout << "La lista no se ordeno";
                }
            }
            
        }
    }

    //Muestra los resultados 
    if (pos != -1){
        system("cls");
        cout<<"Cancion encontrada en posicion " << pos + 1 << "!!" <<endl;

        try{
            Song foundSong = songsList->recover(pos);

        int width = 200; 
        string title = "   BUSQUEDA    ";
        UI::displayHeader(title, width);

            cout << setw(2) <<setfill(' ')<<pos + 1<<". "<<foundSong.toString() <<endl;
        }catch (const List<Song>::Exception&e){
            cout<<"Error al recuperar la cancion";
        }
    } else {
        cout<<"Cancion no encontrada"<<endl;
    }
    cout<<endl; 
    UI::enterToContinue();
}

void Menu::orderSong() {
    if(this-> songsList->isEmpty()){
        system("cls");
        cout<<"No se puede ordenar una lista vacia"<<endl; 
        UI:: enterToContinue();
        getchar();
    }else{

    int opc;
    do{
        system("cls");
        UI::displaySubMenu();

        cout<<"Selecciona una opcion (1-3): ";

        if (!(cin>> opc)){
            UI::handleInputError();
            continue;
        }

        switch (opc)
        {
        // No tiene break pq va a caer en el 2 y ahi va a llamar a otro subMenu
        case 1: //Titulo
        case 2: //Interprete
            //Pasa la opc del usuario a la siguiente funcion
            handleOrderCreateria(opc);
            break;
        
        case 3: 
            cout<<"Regresando..."<<endl;
            getchar();
            UI::enterToContinue();
            break;
        
        default:
            cout << "Opcion invalida. Intenta de nuevo."<<endl;
            UI::enterToContinue();
            break;
        }
    }while(opc != 3);
    }
}

void Menu::handleOrderCreateria(int& opc) {
    int metOpc;
    do{
        system("cls");
        UI::displayOrderMethodMenu();
        cout << "Selecciona una opcion (1-5): ";

        if (!(cin>> metOpc)){
            UI::handleInputError();
            continue;
        }

        switch (metOpc){
        case 1:
        case 2: 
        case 3:
        case 4: 
            performOrder(opc, metOpc);
            break; 
            case 5: 
            cout<<"Regresando..."<<endl;
            getchar();
            UI::enterToContinue();
            break;
        
        default:
            cout << "\nOpcion invalida. Intenta de nuevo."<<endl;
            UI::enterToContinue();
            break;
        }
    }while(metOpc !=5);
}

void Menu::performOrder(int&opc, int& metOpc) {
    //Declaramos una variable que puede "contener" una función de comparacion
    int (*comparisonFunction)(const Song&, const Song&);

    if(opc == 1){ //Por titulo 
        comparisonFunction = Song::compareByTitle;

    }else { //interprete
       comparisonFunction = Song::compareByInterprete;
    }

    string title; 
    switch (metOpc){
        case 1: 
            this-> songsList->bubbleSort(comparisonFunction);
            title = "Bubble Sort";
            break; 
        case 2: 
            this-> songsList->insertSort(comparisonFunction);
            title = "Insert Sort";
            break;
        case 3: 
            this-> songsList->selectSort(comparisonFunction);
            title = "Select Sort";
            break; 
        case 4: 
            this-> songsList->shellSort(comparisonFunction);
            title = "Shell Sort";
            break; 
        default: 
            cout << "\nOpcion invalida. Intenta de nuevo."<<endl;
            UI::enterToContinue();
            break; 
    }
    system("cls");

    if (this-> songsList -> iSroted(comparisonFunction)){
        cout<<"La lista se ordeno correctamente con: "<< title <<endl;
    }else {
        cout<<"La lista no se pudo ordenar correctamente con: "<< title <<endl;
    }
    UI::displayAllSongs(*songsList);

    UI::enterToContinue();
    getchar();

}



Menu::Menu(List<Song>&l) : songsList(&l){
    runMenu();
}
