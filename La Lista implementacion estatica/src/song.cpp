#include <iostream> //para operadores >> y <<
#include <iomanip> //para el setw y setfill
#include <string> // para cadenas
#include <limits> // para limpiar buffer

#include "song.hpp"

using namespace std;


Song::Song(){ 
    title = "";
    author = "";
    interprete = "";        
    ranking = 0;
    
}
Song::Song(const Song& other){ 
    title = other.title;
    author = other.author;
    interprete = other.interprete;
    ranking = other.ranking;

}
Song::Song(const SongParams&params){
    title = params.title;
    author = params.author;
    interprete = params.interprete;
    ranking = params.ranking;

}


std::string Song::getTitle() const{
    return title;
}

std::string Song::getAuthor() const{
    return author;
}

std::string Song::getInterprete() const{
    return interprete;
}

int Song::getRanking() const{
    return ranking;
}


std::string Song::toString() const{
    ostringstream oss; //flujo de cadena de salida 
    
    /*oss es una herramienta para construir strings formateados de manera similar a como se imprime en la consola,
     pero almacenando el resultado en una variable en lugar de mostrarlo en pantalla. (es un construcor de cadenas)*/
   
     oss << left 
        << setw(25) << title << " | "
        << setw(50) << author << " | "
        << setw(50) << interprete << " | "
        << right << setw(2) << setfill('0') << ranking << setfill(' ');

    return oss.str(); //retorna el contenido de oss como string para dar el resultado
}

void Song::setTitle(const std::string& newTitle){
    title = newTitle;
}

void Song::setAuthor(const std:: string& newAuthor){
    author = newAuthor;
}

void Song::setInterprete(const std:: string& newInterprete){
    interprete = newInterprete;
}

void Song::setRanking(const int& newRanking){
    ranking = newRanking;
}



Song& Song::operator = (const Song& other){
    title = other.title;
    author = other.author;
    interprete = other.interprete;
    ranking = other.ranking;
    
    return *this;
}


ostream& operator << (ostream& os, const Song& s){
    os <<  s.title << endl;
    os <<  s.author << endl;
    os <<  s.interprete << endl;
    os <<  s.ranking << endl;
    return os; 
}

istream& operator >> (istream& is, Song& s){
    string myStr;

    getline(is, s.title);
    getline(is, s.author);
    getline(is, s.interprete);
    getline(is, myStr);
    s.ranking = stoi(myStr);
    
    is.ignore(numeric_limits<streamsize>::max(), '\n'); /*Descarta todos los caracteres que puedan existir buffer hasta encontrar '\n' */

    return is;

}




 