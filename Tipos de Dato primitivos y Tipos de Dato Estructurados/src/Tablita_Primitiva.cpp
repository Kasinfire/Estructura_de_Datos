#include "Tablita_Primitiva.hpp"


void Tablita_Primitiva::ver_tablita() {
  int colum1 = 27;
  int colum2 = 15;
  int colum3 = 25;
  int colum4 = 18;
  int AnchoTColum = colum1 + colum2 + colum3 + colum4;

  // Sepaaracion
  cout << setfill('-') << setw(AnchoTColum) << "" << setfill(' ') << endl;

  // Encabezados
  cout << left << setw(colum1) << "Tipo de dato " << left << setw(colum2)
       << "Bits " << left << setw(colum3) << "Valor minimo " << left
       << setw(colum4) << "Valor maximo " << endl;

  // Sepaaracion
  cout << setfill('-') << setw(AnchoTColum) << "" << setfill(' ') << endl;

  // Fila 1: Caracter con signo
  cout << left << setw(colum1) << "Caracter con signo" << left << setw(colum2)
       << sizeof(char) * CHAR_BIT << left << setw(colum3)
       << static_cast<int>(numeric_limits<char>::min()) << left << setw(colum4)
       << static_cast<int>(numeric_limits<char>::max()) << endl;

  // Fila 2: Caracter sin signo
  cout << left << setw(colum1) << "Caracter sin signo" << left << setw(colum2)
       << sizeof(char) * CHAR_BIT << left << setw(colum3)
       << static_cast<int>(numeric_limits<unsigned char>::min()) << left
       << setw(colum4) << static_cast<int>(numeric_limits<unsigned char>::max())
       << endl;

  // separacion
  cout << setfill('-') << setw(AnchoTColum) << "" << setfill(' ') << endl;

  // Fila 3: Entero corto con signo
  cout << left << setw(colum1) << "Entero corto con signo" << left
       << setw(colum2) << sizeof(short) * CHAR_BIT << left << setw(colum3)
       << numeric_limits<short>::min() << left << setw(colum4)
       << numeric_limits<short>::max() << endl;

  // Fila 4: Entero sin signo
  cout << left << setw(colum1) << "Entero corto sin signo" << left
       << setw(colum2) << sizeof(short) * CHAR_BIT << left << setw(colum3)
       << numeric_limits<unsigned short>::min() << left << setw(colum4)
       << numeric_limits<unsigned short>::max() << endl;

  // Fila 5: Entero largo con signo
  cout << left << setw(colum1) << "Entero largo con signo" << left
       << setw(colum2) << sizeof(long) * CHAR_BIT << left << setw(colum3)
       << numeric_limits<long>::min() << left << setw(colum4)
       << numeric_limits<long>::max() << endl;

  // Fila 6: Entero sin signo
  cout << left << setw(colum1) << "Entero largo sin signo" << left
       << setw(colum2) << sizeof(long) * CHAR_BIT << left << setw(colum3)
       << numeric_limits<unsigned long>::min() << left << setw(colum4)
       << numeric_limits<unsigned long>::max() << endl;

  // Separacion
  cout << setfill('-') << setw(AnchoTColum) << "" << setfill(' ') << endl;

  // Fila 7: Real de presicion simple
  cout << left << setw(colum1) << "Real de presicion simple" << left
       << setw(colum2) << sizeof(float) * CHAR_BIT << left << setw(colum3)
       << numeric_limits<float>::lowest() << left << setw(colum4)
       << numeric_limits<float>::max() << endl;

  // Fila 8: Real de doble presicion
  cout << left << setw(colum1) << "Real de doble precision" << left
       << setw(colum2) << sizeof(double) * CHAR_BIT << left << setw(colum3)
       << numeric_limits<double>::lowest() << left << setw(colum4)
       << numeric_limits<double>::max() << endl;

  // Separacion
  cout << setfill('-') << setw(AnchoTColum) << "" << setfill(' ') << endl;
}
