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
    static void displayAllSongs(const List<Song,6000>& songsList);

    static void displaysearchMenu(); 
    static void displaysearchMethodMenu();

    static void enterToContinue();
    static void handleInputError();

};


#endif // __UI_HPP__