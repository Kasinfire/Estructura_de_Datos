#include <iostream> //para operadores >> y <<
#include <iomanip> //para el setw y setfill
#include <string> // para cadenas
#include <limits> // para limpiar buffer

#include "song.hpp"

using namespace std;


Song::Song(){                           //constructor por defecto
    title = "";
    author = "";
    interprete = "";   
    mp3FileName ="";     
    ranking = 0;

    
}
Song::Song(const Song& other){          //Constructor copia
    title = other.title;
    author = other.author;
    interprete = other.interprete;
    mp3FileName = other.mp3FileName;
    ranking = other.ranking;

}
Song::Song(const SongParams&params){    //Constuctor parametrizado
    title = params.title;
    author = params.author;
    interprete = params.interprete;
    mp3FileName = params.mp3FileName;
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

std::string Song::getMp3FileName() const {
    return mp3FileName;
}

int Song::getRanking() const{
    return ranking;
}


std::string Song::toString() const{
    ostringstream oss; //flujo de cadena de salida 
    
    /*oss es una herramienta para construir strings formateados de manera similar a como se imprime en la consola,
     pero almacenando el resultado en una variable en lugar de mostrarlo en pantalla. (es un construcor de cadenas)*/
   
     oss << left 
        << setw(28) << title << " | "
        << setw(50) << author << " | "
        << setw(50) << interprete << " | "
        << setw(50) << mp3FileName << " | "
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


void Song::setMp3FileName(const std:: string& newMp3FileName) {
    mp3FileName = newMp3FileName; 
}

void Song::setRanking(const int& newRanking){
    ranking = newRanking;
}

//Operador de asignacion

Song& Song::operator = (const Song& other){
    title = other.title;
    author = other.author;
    interprete = other.interprete;
    mp3FileName = other.mp3FileName;
    ranking = other.ranking;
    
    return *this;
}

//OPERADORES DE COMPARACION 

bool Song::operator == (const Song& s) const {
    return this->title == s.title;
}

bool Song::operator != (const Song& s) const {
    return !(*this == s);
}


bool Song::operator <  (const Song& s) const {
   return this->title < s.title;
}

bool Song::operator <= (const Song& s) const {
    return *this < s || *this == s; 
}

bool Song::operator >  (const Song& s) const {
    return !(*this <= s); 
}

bool Song:: operator >= (const Song& s) const {
    return *this > s || *this == s;
}

int Song::compareByTitle(const Song& x, const Song& y) {
    return x.title.compare(y.title);              //.compare es un metodo de string 
}

int Song::compareByInterprete(const Song& x, const Song& y) {
    return x.interprete.compare(y.interprete);   
}


// SERIALIZACIÓN Y DESERIALIZACIÓN 


void Song::serialize(ostream& os) const {
    ostringstream oss;
    oss << title << '\x1F' << author << '\x1F' << interprete << '\x1F' << mp3FileName << '\x1F' << ranking;
    os << oss.str() << endl;  // Cada cancion esta en una línea
}


void Song::deserialize(istream& is) {
    string myStr;
    getline(is, myStr);

    if (myStr.empty()) {
        return;
    }

    istringstream iss(myStr);
    string tempStr;

    getline(iss, title, '\x1F');
    getline(iss, author, '\x1F');
    getline(iss, interprete, '\x1F');
    getline(iss, mp3FileName, '\x1F');
    getline(iss, tempStr, '\x1F');

    try {
        ranking = stoi(tempStr);
    } catch (const exception& e) {
        throw Exception("Error al deserializar la canción: " + myStr);
    }
}






 