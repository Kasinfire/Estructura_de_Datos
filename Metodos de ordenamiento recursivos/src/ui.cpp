#include "ui.hpp"
#include "methodtime.hpp"
#include <iostream>
#include <iomanip>

using namespace std;

void UI::run() {
    MethodTime mt;

    MethodResults results[6];
    
    results[0] = mt.methodsTime("BubbleSort", &List<Int>::bubbleSort);
    results[1] = mt.methodsTime("InsertSort", &List<Int>::insertSort);
    results[2] = mt.methodsTime("SelectSort", &List<Int>::selectSort);
    results[3] = mt.methodsTime("ShellSort", &List<Int>::shellSort);
    results[4] = mt.methodsTime("MergeSort", &List<Int>::mergeSort);
    results[5] = mt.methodsTime("QuickSort", &List<Int>::quickSort);

    int width = 80;
    string title = "COMPARACION DE TIEMPOS DE ORDENAMIENTO";
    int titleLength = title.length();
    int filler = (width - titleLength) / 2;

    cout << "\n" << setw(width) << setfill('=') << "" << setfill(' ') << endl;
    cout << setw(filler + titleLength) << right << title 
         << setw(width - filler - titleLength) << "" << endl;
    cout << setw(width) << setfill('=') << "" << setfill(' ') << endl;

    cout << left 
         << setw(20) << "METODO"
         << setw(20) << "ANTES (ORDENADO?)"
         << setw(25) << "DESPUES (ORDENADO?)"
         << setw(20) << "TIEMPO (s)" 
         << endl;
    cout << setw(width) << setfill('-') << "" << setfill(' ') << endl;


    for (int i = 0; i < 6; i++) {
        cout << left << setw(20) << results[i].methodName;
        if (results[i].sortedBf){
            cout << setw(20) << "SI";
        } else {
            cout << setw(20) << "NO";
        }

        if(results[i].sortedAf){
            cout << setw(25) << "SI";
        } else {
            cout << setw(25) << "NO";
        }

        cout<<fixed << setprecision(6) << results[i].timeInSec;
        cout<<endl;
    } 

    cout << setw(width) << setfill('=') << "" << setfill(' ') << endl;

    getchar();
}