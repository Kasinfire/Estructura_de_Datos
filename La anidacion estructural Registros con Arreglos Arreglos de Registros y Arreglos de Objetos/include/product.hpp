#ifndef PRODUCT_HPP__
#define PRODUCT_HPP__

#include "date.hpp"

#include <cctype>
#include <iomanip>
#include <string>
#include <sstream>

class Product {
 private:
  std::string barCode;
  std::string name;
  float weight;
  Date entryDate;
  float wholesalePrice;
  float retailPrice;
  int currentExistenceProduct;

 public:
  Product();
  Product(const Product&);

  std::string getBarCode() const;
  std::string getName() const;
  float getWeight() const;
  Date getEntryDate() const;
  float getWholesalePrice() const;
  float getRetailPrice() const;
  int getCurrentExistenceProduct() const;

  void setBarCode(const std::string&);
  void setName(const std::string&);
  void setWeight(const float&);
  void setEntryDate(const Date&);
  void setWholesalePrice(const float&);
  void setRetailPrice(const float&);
  void setCurrentExistenceProduct(const int&);

  bool updateExistence(int quantity);
  float inventoryValue() const;
  float potentialSalesValue() const;

  Product& operator=(const Product&);

  std::string toString() const;
};

#endif  // PRODUCT_HPP__