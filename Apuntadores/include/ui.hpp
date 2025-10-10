#ifndef __UI_HPP__
#define __UI_HPP__

#include <iomanip> //para el setw y setfill
#include <string> // para cadenas
#include <limits> // para limpiar buffer
#include <iostream> // para cout y cin 

#include "song.hpp" 
#include "list.hpp"


class UI{

    public:

    static void displayMenu();
    
    static void displayHeader(const std:: string&, int&);

    static void displayAllSongs(const List<Song>& songsList);

    static void displaySubMenu(); 
    
    static void displaysearchMethodMenu();
    static void displayOrderMethodMenu();

    static void enterToContinue();
    static void handleInputError();

};


#endif // __UI_HPP__