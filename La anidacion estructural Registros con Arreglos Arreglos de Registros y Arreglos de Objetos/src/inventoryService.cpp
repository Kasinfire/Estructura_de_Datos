#include "inventoryService.hpp"


using namespace std;

InventoryService::InventoryService(Collection& inv) : inventory(inv) {}

void InventoryService::addNewProduct(const string& barcode) {
  Product newProduct;
  string input;
  float floatValue;
  int intValue;

  cout << "\n AGREGANDO NUEVO PRODUCTO..." << endl;
  newProduct.setBarCode(barcode);

  // Obtener y validar el nombre
  while (true) {
    try {
      cout << "Nombre del producto: ";
      getline(cin, input);
      newProduct.setName(input);
      break;
    } catch (const invalid_argument& e) {
      cout << "Error: " << e.what() << endl;
    }
  }

  // Obtener y validar el Peso
  while (true) {
    try {
      cout << "Peso (kg): ";
      getline(cin, input);
      floatValue = stof(input);
      newProduct.setWeight(floatValue);
      break;
    } catch (const invalid_argument& e) {
      cout << "Error: Peso debe ser un numero valido." << endl;
    } catch (const exception& e) {
      cout << "Error: " << e.what() << endl;
    }
  }

  // Obtener y validar la fecha
  int year, month, day;
  while (true) {
    try {
      cout << "Fecha de entrada: " << endl;
      cout << "\tDia: ";
      getline(cin, input);
      day = stoi(input);

      cout << "\tMes: ";
      getline(cin, input);
      month = stoi(input);

      cout << "\tAnio: ";
      getline(cin, input);
      year = stoi(input);

      Date entryDate(year, month, day);
      newProduct.setEntryDate(entryDate);
      break;
    } catch (const invalid_argument& e) {
      cout << "Error: " << e.what() << " o formato de numero invalido." << endl;
    } catch (const exception& e) {
      cout << "Error: " << e.what() << endl;
    }
  }

  // Obtener y validar el precio de mayoreo
  while (true) {
    try {
      cout << "Precio de mayoreo: $";
      getline(cin, input);
      floatValue = stof(input);
      newProduct.setWholesalePrice(floatValue);
      break;
    } catch (const invalid_argument& e) {
      cout << "Error: Precio debe ser un numero valido." << endl;
    } catch (const exception& e) {
      cout << "Error: " << e.what() << endl;
    }
  }

  // Obtener y validar el precio de menudeo
  while (true) {
    try {
      cout << "Precio de menudeo: $";
      getline(cin, input);
      floatValue = stof(input);
      newProduct.setRetailPrice(floatValue);
      break;
    } catch (const invalid_argument& e) {
      cout << "Error: Precio debe ser un numero valido" << endl;
    } catch (const exception& e) {
      cout << "Error: " << e.what() << endl;
    }
  }

  // Obtener y validar la cantidad existente
  while (true) {
    try {
      cout << "Cantidad existente: ";
      getline(cin, input);

      if (input.find_first_not_of("0123456789") != string::npos) {
        throw invalid_argument("La cantidad debe ser un numero entero.");
      }
      intValue = stoi(input);
      newProduct.setCurrentExistenceProduct(intValue);
      break;
    } catch (const invalid_argument& e) {
      cout << "Error: " << e.what() << endl;
    } catch (const exception& e) {
      cout << "Error: " << e.what() << endl;
    }
  }

  // Agregar al inventario
  if (inventory.addProduct(newProduct)) {
    cout << "Producto agregado exitosamente!" << endl;
  } else {
    cout << "Error: No se pudo agregar el producto. Inventario lleno." << endl;
  }
}

Product* InventoryService::handleBarcodeOpt() {
  string barcode;
  bool validInput = false;

  while (!validInput) {
    cout << "Ingresa el codigo de barras (13 digitos) o '0' para cancelar: ";
    getline(cin, barcode);

    if (barcode == "0") {
      cout << "Operacion cancelada." << endl;
      return nullptr;
    }

    // Valida que solo contenga dígitos
    bool hasNonDigit = false;
    for (char c : barcode) {
      if (!isdigit(c)) {
        hasNonDigit = true;
        break;
      }
    }

    if (hasNonDigit) {
      cout << "Error: El codigo de barras debe contener solo numeros." << endl;
      continue;
    }

    // Valida longitud
    if (barcode.length() != 13) {
      cout << "Error: El codigo de barras debe tener exactamente 13 digitos."
           << endl;
      continue;
    }

    validInput = true;
    Product* product = inventory.searchProduct(barcode);

    if (product != nullptr) {
      cout << "Producto encontrado: " << product->getName() << endl;
      return product;
    } else {
      char res;

      cout << "Producto no encontrado " << endl;
      cout << "Deseas agregar este producto como nuevo? (s/n): ";

      cin >> res;
      cin.ignore();

      if (res == 's' || res == 'S') {
        addNewProduct(barcode);
        
        cout << "Volviendo al menu principal..." << endl;
        return nullptr;
    } else {
        cout << "Operacion cancelada " << endl;
        return nullptr;
      }
    }
  }
  return nullptr;
}

void InventoryService::addExistence(Product* product) {
  string input;
  int quantity;

  while (true) {
    try {
      cout << "\tCantidad a agregar: ";
      getline(cin, input);

      if (input.find_first_not_of("0123456789") != string::npos) {
        throw invalid_argument("La cantidad debe ser un numero entero.");
      }
      quantity = stoi(input);

      if (quantity <= 0) {
        cout << "Error: La cantidad debe ser un numero positivo." << endl;
        continue;
      }
      int current = product->getCurrentExistenceProduct();
      product->setCurrentExistenceProduct(current + quantity);

      cout << "Existencia agregada. Nueva existencia: "
           << product->getCurrentExistenceProduct() << endl;
      break;
    } catch (const invalid_argument& e) {
      cout << "Error: La cantidad debe ser un numero entero valido." << endl;
    } catch (const exception& e) {
      cout << "Error: " << e.what() << endl;
    }
  }
}

void InventoryService::removeProduct(Product* product) {
  string input;
  int quantity;

  while (true) {
    try {
      cout << "\tCantidad a retirar: ";
      getline(cin, input);

      if (input.find_first_not_of("0123456789") != string::npos) {
        throw invalid_argument("La cantidad debe ser un numero entero.");
      }

      quantity = stoi(input);

      int current = product->getCurrentExistenceProduct();

      if (quantity > current) {
        cout << "Error: No puede retirar mas de la existencia actual." << endl;
        continue;
      }
      if (quantity <= 0) {
        cout << "Error: La cantidad debe ser un numero positivo." << endl;
        continue;
      }

      product->setCurrentExistenceProduct(current - quantity);
      cout << "Producto retirado. Nueva existencia: "
           << product->getCurrentExistenceProduct() << endl;
      break;

    } catch (const invalid_argument& e) {
      cout << "Error: La cantidad debe ser un numero entero valido." << endl;
    } catch (const exception& e) {
      cout << "Error: " << e.what() << endl;
    }
  }
}

void InventoryService::showProductInfo(Product* product) {
  cout << product->toString() << endl;
}

Product* InventoryService::searchProduct(const std::string& barcode) {
  return inventory.searchProduct(barcode);
}