#ifndef __MENU_HPP__
#define __MENU_HPP__

#include "list.hpp"
#include "song.hpp"


class Menu {
    private:
    List<Song,50>songsList;

    public: 
    
    void runMenu();
    void displayMenu();
    void insertSong();
    void deleteSong();
    void deleteAllSongs();
    void displaySongs();
    
};

#endif // __MENU_HPP__