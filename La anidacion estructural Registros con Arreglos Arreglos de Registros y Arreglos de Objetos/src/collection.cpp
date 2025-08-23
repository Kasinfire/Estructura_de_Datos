#include "collection.hpp"

using namespace std;

Collection::Collection() : actualQuantity(0) {}

Collection::Collection(const Collection& other)
    : actualQuantity(other.actualQuantity) {
  for (int c = 0; c < actualQuantity; c++) {
    products[c] = other.products[c];
  }
}

int Collection::getActualQuantity() const {
  return actualQuantity;
}


Product* Collection::searchProduct(const std::string& barcode) {
  for (int i = 0; i < actualQuantity; i++) {
    if (products[i].getBarCode() == barcode) {
      return &products[i];
    }
  }
  return nullptr;
}

const Product* Collection::searchProduct(const std::string& barcode) const {
  for (int i = 0; i < actualQuantity; i++) {
    if (products[i].getBarCode() == barcode) {
      return &products[i];
    }
  }
  return nullptr;
}

bool Collection::addProduct(const Product& newProduct) {
  if (actualQuantity >= maxProducts) {
    return false;
  }

  string barcode = newProduct.getBarCode();
  Product* existing = searchProduct(barcode);

  if (existing != nullptr) {
    existing->updateExistence(newProduct.getCurrentExistenceProduct());
    return true;
  } else {
    products[actualQuantity] = newProduct;
    actualQuantity++;
    return true;
  }
}


Collection& Collection::operator=(const Collection& c) {
  if (this == &c) {
    return *this;
  }

  actualQuantity = c.actualQuantity;

  for (int i = 0; i < actualQuantity; i++) {
    products[i] = c.products[i];
  }

  return *this;
}

std::string Collection::toString() const {
  string results;
  for (int i = 0; i < actualQuantity; i++) {
    results += products[i].toString() + "\n";
  }
  return results;
}
