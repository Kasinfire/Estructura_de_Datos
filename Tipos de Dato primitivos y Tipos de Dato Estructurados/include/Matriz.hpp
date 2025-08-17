#ifndef MATRIZ_HPP
#define MATRIZ_HPP

using namespace std;
#include <iomanip>
#include <iostream>
#include <random>
#include <vector>

class Matriz {
 private:
  int tam;
  vector<vector<float>> datos;

 public:
  Matriz();
  Matriz(int tamaño);
  void llenado_aleatorio();
  Matriz operator*(const Matriz& C) const;
  Matriz operator+(const Matriz& D) const;
  void imprimir(const string& nombre) const;
};

#endif