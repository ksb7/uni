#include <iostream>

template <typename T>
int cautare(const T* tablou, int lungime, const T& cheie) {
    for (int i = 0; i < lungime; ++i) {
        if (tablou[i] == cheie) {
            return i; // Returneaza pozitia primei aparitii a cheii in tablou
        }
    }
    return -1; // Returneaza codul de eroare daca cheia lipseste in tablou
}

int main() {
    // Test cu tipul de date int
    int tablouInt[] = {0, 2, 3, 4, 3, 6};
    int pozitieInt = cautare(tablouInt, 6, 2);
    if (pozitieInt != -1) {
        std::cout << "Cheia 2 se afla pe pozitia: " << pozitieInt << std::endl;
    } else {
        std::cout << "Cheia nu a fost gasita." << std::endl;
    }

    // Test cu tipul de date double
    double tablouDouble[] = {1.1, 2.2, 3.3, 4.4, 5.5};
    int pozitieDouble = cautare(tablouDouble, 5, 4.4);
    if (pozitieDouble != -1) {
        std::cout << "Cheia 4.4 se afla pe pozitia: " << pozitieDouble << std::endl;
    } else {
        std::cout << "Cheia nu a fost gasita." << std::endl;
    }

    return 0;
}
