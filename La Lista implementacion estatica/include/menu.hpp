#ifndef __MENU_HPP__
#define __MENU_HPP__

#include <fstream> // para crear archivos 
#include <iostream> // para cout y cin 
#include <string> // para cadenas 

#include "list.hpp"
#include "song.hpp"




class Menu{
    private:
    List<Song,50>*songsList; //songsList es un puntero

    void runMenu();
    void displayMenu();

    void insertSong();
    void deleteSong();
    void deleteAllSongs();
    void displayAllSongs();

    void writeToDisk();
    void readFromDisk();
    void enterToContinue();

    public: 
    
    Menu(List<Song,50>&);

    
};

#endif // __MENU_HPP__