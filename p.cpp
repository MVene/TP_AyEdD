// test_p.cpp
#include <iostream>
#include <vector>
#include <cassert>
#include <algorithm>

using namespace std;

struct Paquete {
    int id;
};

void bubbleSort(vector<Paquete>& paquetes) {
    for (size_t i = 0; i < paquetes.size(); i++) {
        for (size_t j = 0; j < paquetes.size() - i - 1; j++) {
            if (paquetes[j].id > paquetes[j + 1].id) {
                swap(paquetes[j], paquetes[j + 1]);
            }
        }
    }
}

void test_bubbleSort() {
    vector<Paquete> paquetes = {{3}, {1}, {4}, {1}, {5}, {9}, {2}, {6}, {5}, {3}};
    //imprimir vector antes del ordenamiento
    cout << "Vector antes del ordenamiento: ";
    for (size_t i = 0; i < paquetes.size(); i++) {
        cout << paquetes[i].id << " ";
    }
    bubbleSort(paquetes);
    cout << "\n";
    cout << "Vector despues del ordenamiento: ";
    //imprimir vector despues del ordenamiento
    for (size_t i = 0; i < paquetes.size(); i++) {
        cout << paquetes[i].id << " ";
    }
}


int main() {
    test_bubbleSort();
    return 0;
}