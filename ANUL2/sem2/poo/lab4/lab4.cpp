#include <iostream>
#include <string>
#include <vector>

using namespace std;

// Clasa abstracta de bază
class InstitutieDeInvatamant {
public:
    virtual void descriere() const = 0; // Funcție virtuala pura pentru descrierea institutiei
    virtual ~InstitutieDeInvatamant() {} // Destructor virtual pentru clasele derivate
};

// Clasa pentru institutii de invatamant prescolar
class InstitutiePrescolara : public InstitutieDeInvatamant {
public:
    void descriere() const override {
        cout << "Aceasta este o institutie prescolara." << endl;
    }
};

// Clasa pentru institutii de invatamant mediu
class InstitutieMedie : public InstitutieDeInvatamant {
public:
    void descriere() const override {
        cout << "Aceasta este o institutie de invatamant mediu." << endl;
    }
};

// Clasa pentru institutii de invatamant superior
class InstitutieSuperioara : public InstitutieDeInvatamant {
public:
    void descriere() const override {
        cout << "Aceasta este o institutie de invatamant superior." << endl;
    }
};

int main() {
    // Cream obiecte pentru fiecare tip de institutie de invatamant
    InstitutiePrescolara prescolara;
    InstitutieMedie medie;
    InstitutieSuperioara superioara;

    // Cream un vector de pointeri la clasa abstractă de baza
    vector<InstitutieDeInvatamant*> institutii;

    // Adaugam adresele obiectelor la vectorul de pointeri
    institutii.push_back(&prescolara);
    institutii.push_back(&medie);
    institutii.push_back(&superioara);

    // Apelam functia descriere pentru fiecare obiect prin intermediul pointerilor
    for (int index = 0; index < institutii.size(); index++) {
        institutii[index]->descriere();
    }

    return 0;
}
