#include "menu.hpp"

using namespace std;

Menu::Menu() : inventory(), inventoryService(inventory) {}

void Menu::displayMenu() {
    string message = "(Ten en mano el codigo de barras d el producto)";
    int width = message.length();

    string title = "SISTEMA DE INVENTARIO";
    int titleLenght = title.length();

    int filler = (width - titleLenght) / 2;

    cout << "\n" << setw(width) << setfill('=') << "" << setfill(' ') << endl;
    cout << setw(filler + titleLenght) << right << title
         << setw(width - filler - titleLenght) << "" << endl;
    cout << setw(width) << setfill('=') << "" << setfill(' ') << endl;

    cout << message << endl;

    cout << "\n\t1. Ingresar codigo de barras para operar";
    cout << "\n\t2. Mostrar inventario completo";
    cout << "\n\t3. Salir";
    cout << "\nSeleccione una opcion: ";
}

void Menu::displayMenuOPC(Product* product) {
    int opc;

    cout << "\nProducto: " << product->getName() << endl;
    cout << "Existencia actual: " << product->getCurrentExistenceProduct()
         << endl;

    do {
        cout << "\n OPCIONES PARA: " << product->getName() << endl;
        cout << "\t1. Agregar" << endl;
        cout << "\t2. Retirar prodctos" << endl;
        cout << "\t3. Ver informacion" << endl;
        cout << "\t4. Volver al menu principal" << endl;

        cout << "Selecione una opcion: ";
        cin >> opc;
        if (cin.fail()) {
            cout << "Entrada no valida. Por favor, ingrese un numero." << endl;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            continue;
        }
        cin.ignore();

        switch (opc) {
            case 1:
                inventoryService.addExistence(product);
                break;
            case 2:
                inventoryService.removeProduct(product);
                break;
            case 3:
                inventoryService.showProductInfo(product);
                break;
            case 4:
                cout << "Volviendo al menu principal..." << endl;
                break;
            default:
                cout << "Opcion no valida" << endl;
        }

    } while (opc != 4);
}

void Menu::runMenu() {
    int opc;

    do {
        displayMenu();
        cin >> opc;
        if (cin.fail()) {
            cout << "Entrada no valida. Por favor, ingrese un numero." << endl;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            continue;
        }
        cin.ignore();

        switch (opc) {
            case 1: {
                Product* product = inventoryService.handleBarcodeOpt();
                if (product != nullptr) {
                    displayMenuOPC(product);
                }
                break;
            }
            case 2:
                cout << "\n========== INVENTARIO COMPLETO ==========" << endl;
                if (inventory.getActualQuantity() == 0) {
                    cout << "El inventario esta vacio" << endl;
                } else {
                    cout << inventory.toString() << endl;
                }
                break;
            case 3:
                cout << "Saliendo..." << endl;
                break;
            default:
                cout << "Opcion no valida. Por favor, selecciona 1,2 o 3." << endl;
        }

        if (opc != 3) {
            cout << "\nPresione Enter para continuar..." << endl;
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
    } while (opc != 3);
}