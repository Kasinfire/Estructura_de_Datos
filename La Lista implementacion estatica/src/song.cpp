#include "song.hpp"

#include <string>

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
    return "Titulo:"+ title + " | Autor:" + author + " | Interprete:"+ interprete+ " | Ranking:" + to_string(ranking);
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



Song& Song::operator = (const Song& s){
    title = s.title;
    author = s.author;
    interprete = s.interprete;
    ranking = s.ranking;
    
    return *this;
}
