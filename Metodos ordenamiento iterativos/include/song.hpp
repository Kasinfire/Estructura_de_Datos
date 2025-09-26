#ifndef __SONG_HPP__
#define __SONG_HPP__

#include <string>    // para cadenas
#include <iostream>  // para operadores >> y <<

struct SongParams{
    std:: string title;  
    std:: string author; 
    std:: string interprete;
    std:: string mp3FileName;
    int ranking;  
    
};

class Song {
    private:
        std:: string title;  
        std:: string author; 
        std:: string interprete;
        std:: string mp3FileName;
        int ranking;  

    public:

    Song();                         //Constructor por defecto 
    Song(const Song&);              // Construcotr copia
    Song(const SongParams&params);  // constructor para crear obj ya con todos mis datos


    std::string getTitle()const; 
    std::string getAuthor() const; 
    std::string getInterprete() const; 
    std::string getMp3FileName() const; 
    int getRanking() const; 

    std::string toString() const; 

    void setTitle(const std::string&);
    void setAuthor(const std::string&);
    void setInterprete(const std::string&);
    void setMp3FileName(const std::string&);
    void setRanking(const int&);

    Song& operator = (const Song&);

    bool operator == (const Song&) const;
    bool operator != (const Song&) const;
    bool operator <  (const Song&) const; 
    bool operator <= (const Song&) const; 
    bool operator >  (const Song&) const; 
    bool operator >= (const Song&) const; 

    static int compareByTitle(const Song&, const Song&);
    static int compareByInterprete(const Song&, const Song&);

    friend std::ostream& operator << (std::ostream&,const Song&);
    friend std::istream& operator >> (std:: istream&, Song&);
    
};

#endif // __SONG_HPP__