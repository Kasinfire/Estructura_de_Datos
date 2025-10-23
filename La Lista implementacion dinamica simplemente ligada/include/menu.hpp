#ifndef __MENU_HPP__
#define __MENU_HPP__

#include <fstream> // para crear archivos 
#include <iostream> // para cout y cin 
#include <string> // para cadenas 

#include "list.hpp"
#include "song.hpp"
#include "ui.hpp"
#include "exception.hpp"



class Menu{
    private:
    List<Song>*songsList;

    void runMenu();

    void insertSong();
    void deleteSong();
    void deleteAllSongs();

    void writeToDisk();
    void readFromDisk();

    void searchSong();
    void performSearch(int&, string&);
    void orderSong();
    public: 
    
    Menu(List<Song>&);  
};

#endif // __MENU_HPP__