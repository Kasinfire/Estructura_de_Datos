#ifndef __MENU_HPP__
#define __MENU_HPP__

#include <iomanip>
#include <iostream>
#include <limits>
#include "inventoryService.hpp"

class Menu {
 private:
  Collection inventory;
  InventoryService inventoryService;

  void displayMenu();
  void displayMenuOPC(Product* product);

 public:
  Menu();
  void runMenu();
};

#endif  // __MENU_HPP__