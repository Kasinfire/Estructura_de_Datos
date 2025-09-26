#ifndef __MENU_HPP__
#define __MENU_HPP__

#include <fstream> // para crear archivos 
#include <iostream> // para cout y cin 
#include <string> // para cadenas 

#include "list.hpp"
#include "song.hpp"
#include "ui.hpp"



class Menu{
    private:
    List<Song,6000>*songsList; //songsList es un puntero

    void runMenu();

    void insertSong();
    void deleteSong();
    void deleteAllSongs();

    void writeToDisk();
    void readFromDisk();

    void searchSong();
    void handleSearchCreateria(int&, string&);
    void performSearch(int&, int&, string&);

    void orderSong();
    void handleOrderCreateria(int&);
    void performOrder(int&, int&);


    public: 
    
    Menu(List<Song,6000>&);

    
};

#endif // __MENU_HPP__