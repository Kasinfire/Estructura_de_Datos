#ifndef INVENTORYSERVICE_HPP__
#define INVENTORYSERVICE_HPP__

#include <iostream>
#include <limits>
#include "collection.hpp"

class InventoryService {
 private:
  Collection& inventory;

 public:
  InventoryService(Collection& inv);

  void addNewProduct(const std::string& barcode);
  Product* handleBarcodeOpt();

  void addExistence(Product* product);
  void removeProduct(Product* product);
  void showProductInfo(Product* product);

  Product* searchProduct(const std::string& barcode);
};

#endif  // INVENTORYSERVICE_HPP__