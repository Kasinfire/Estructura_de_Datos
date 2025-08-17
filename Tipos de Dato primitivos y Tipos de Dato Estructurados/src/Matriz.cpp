#include "Matriz.hpp"

Matriz::Matriz() : tam(0) {}

Matriz::Matriz(int tamaño)
    : tam(tamaño), datos(tamaño, vector<float>(tamaño, 0)) {}

void Matriz::llenado_aleatorio() {
  random_device rand;
  default_random_engine generador(rand());
  uniform_real_distribution<float> distribucion_mia(-100.0f, 100.0f);

  for (int y = 0; y < tam; y++) {
    for (int x = 0; x < tam; x++) {
      datos[y][x] = distribucion_mia(generador);
    }
  }
}

// Aqui sobrecargo el operador para multiplicacion
Matriz Matriz::operator*(const Matriz& C) const {
  Matriz resultado(tam);

  for (int y = 0; y < tam; y++) {
    for (int x = 0; x < tam; x++) {
      resultado.datos[y][x];
      for (int z = 0; z < tam; z++) {
        resultado.datos[y][x] += datos[y][z] * C.datos[z][x];
      }
    }
  }
  return resultado;
}
// igual sobrecargo pero con la suma
Matriz Matriz::operator+(const Matriz& D) const {
  Matriz resultado(tam);

  for (int y = 0; y < tam; y++) {
    for (int x = 0; x < tam; x++) {
      resultado.datos[y][x] = datos[y][x] + D.datos[y][x];
    }
  }
  return resultado;
}

void Matriz::imprimir(const string& nombre) const {
  cout << "\n Matriz " << nombre << ":\n";
  for (int y = 0; y < tam; y++) {
    for (int x = 0; x < tam; x++) {
      cout << fixed << setprecision(2) << setw(10) << datos[y][x];
    }
    cout << endl;
  }
}
