
#include "product.hpp"

using namespace std;

Product::Product()
    : barCode("0000000000000"),
      name(""),
      weight(0.0),
      entryDate(),
      wholesalePrice(0.0),
      retailPrice(0.0),
      currentExistenceProduct(0) {}

Product::Product(const Product& p)
    : barCode(p.barCode),
      name(p.name),
      weight(p.weight),
      entryDate(p.entryDate),
      wholesalePrice(p.wholesalePrice),
      retailPrice(p.retailPrice),
      currentExistenceProduct(p.currentExistenceProduct) {}

std::string Product::getBarCode() const {
  return barCode;
}
std::string Product::getName() const {
  return name;
}
float Product::getWeight() const {
  return weight;
}
Date Product::getEntryDate() const {
  return entryDate;
}
float Product::getWholesalePrice() const {
  return wholesalePrice;
}
float Product::getRetailPrice() const {
  return retailPrice;
}
int Product::getCurrentExistenceProduct() const {
  return currentExistenceProduct;
}

void Product::setBarCode(const std::string& newBarCode) {
  if (newBarCode.length() != 13) {
    throw invalid_argument(
        "El codigo de barras debe de tener exactamente 13 digitos (0-9)");
  }

  for (char c : newBarCode) {
    if (!isdigit(static_cast<unsigned char>(c))) {
      throw invalid_argument(
          "El codigo de barras debe de tener solo digitos (0-9)");
    }
  }

  barCode = newBarCode;
}

void Product::setName(const std::string& newName) {
  if (newName.empty()) {
    throw invalid_argument("El nombre del producto no puede estar vacio");
  }
  name = newName;
}

void Product::setWeight(const float& newWeight) {
  if (newWeight <= 0.0) {
    throw invalid_argument("El peso no puede ser negativo (Se espera en kg)");
  }
  weight = newWeight;
}

void Product::setEntryDate(const Date& newDate) {
  entryDate = newDate;
}

void Product::setWholesalePrice(const float& newPrice) {
  if (newPrice <= 0.0) {
    throw invalid_argument("El precio de mayoreo no puede ser negativo ni 0");
  }
  wholesalePrice = newPrice;
}

void Product::setRetailPrice(const float& newPrice) {
  if (newPrice <= 0.0) {
    throw invalid_argument("El precio de menudeo no puede ser negativo ni 0");
  }
  retailPrice = newPrice;
}

void Product::setCurrentExistenceProduct(const int& newExistence) {
  if (newExistence < 0 ) {
    throw invalid_argument("La existencia no puede ser negativa");
  }
  currentExistenceProduct = newExistence;
}

bool Product::updateExistence(int quantity) {
  int newExistence = currentExistenceProduct + quantity;

  if (newExistence < 0) {
    currentExistenceProduct=0;
  }
  else {
    currentExistenceProduct=newExistence;
  }
  return true;
}

float Product::inventoryValue() const {
  return currentExistenceProduct * wholesalePrice;
}
float Product::potentialSalesValue() const {
  return currentExistenceProduct * retailPrice;
}

Product& Product::operator=(const Product& p) {
  if (this != &p) {
    barCode = p.barCode;
    name = p.name;
    weight = p.weight;
    entryDate = p.entryDate;
    wholesalePrice = p.wholesalePrice;
    retailPrice = p.retailPrice;
    currentExistenceProduct = p.currentExistenceProduct;
  }
  return *this;
}

std::string Product::toString() const {

   auto formatWithTwoDecimals = [](float value) -> std::string {
        string str = to_string(value);
        size_t dotPos = str.find('.');
        if (dotPos != string::npos && dotPos + 3 < str.length()) {
            return str.substr(0, dotPos + 3);
        }
        return str;
    };

  string str;

  str = "Codigo de barras: " + barCode + "\n" + "Nombre: " + name + "\n" +
        "Peso: " + formatWithTwoDecimals(weight) + " kg \n" +
        "Fecha de entrada: " + entryDate.toString() + "\n" +
        "Precio mayoreo: $" + formatWithTwoDecimals(wholesalePrice) + "\n" +
        "Precio menudeo: $" + formatWithTwoDecimals(retailPrice) + "\n" +
        "Existencia: " + to_string(currentExistenceProduct) + " unidades\n";

  return str;
}
