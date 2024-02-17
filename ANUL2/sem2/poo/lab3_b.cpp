#include <iostream>
#include <vector>
#include <string>
#include <cstdlib>
#include <ctime>

using namespace std;

// Clasa pentru o carte de joc
class CarteDeJoc 
{
protected:
    string grad;
    string culoare;
    bool esteDeschisa;

public:
    CarteDeJoc()
    {
        grad = "";
        culoare = "";
        esteDeschisa = false;
    }

    CarteDeJoc(const string& gradParam, const string& culoareParam)
    {
        grad = gradParam;
        culoare = culoareParam;
        esteDeschisa = false;
    }

    // Metoda pentru a deschide o carte
    void deschide() 
    {
        esteDeschisa = true;
    }

    // Metoda pentru a intoarce o carte
    void intoarce() 
    {
        esteDeschisa = false;
    }

    // Verifica daca cartea este deschisa
    bool esteCarteaDeschisa() const 
    {
        return esteDeschisa;
    }

    // Supraincarcarea operator afisare
    friend ostream& operator <<(ostream& out, const CarteDeJoc& carte) 
    {
        out << carte.grad << " de " << carte.culoare;
        return out;
    }
    
    // Supraincarcarea operator atribuire
    void operator =(const CarteDeJoc &carte)
    {
        grad = carte.grad;
        culoare = carte.culoare;
        esteDeschisa = carte.esteDeschisa;
    }
};

// Clasa pentru butuc de cărți
class ButucDeCarti {
protected:
    vector<CarteDeJoc> carti;

public:
    // Adauga o carte in butuc
    void adaugaCarte(const CarteDeJoc& carte) 
    {
        carti.push_back(carte);
    }

    // Metoda pentru a scoate ultima carte din butuc
    virtual CarteDeJoc scoateCarte() 
    {
        CarteDeJoc ultimaCarte;
        if(esteGol() == false)
        {
            ultimaCarte = carti.back();
            carti.pop_back();
        }
        return ultimaCarte;
    }

    // Verifica daca butucul este gol
    bool esteGol()
    {
        return carti.empty();
    }
};

// Clasa derivata pentru butucul de carti in care cartile trebuie scoase intr-o ordine specifica
class ButucOrdine : public ButucDeCarti 
{
private:
    int index;

public:
    ButucOrdine() 
    {
        index = 0;
    }

    // Supraincarcarea metodei de scoatere a cartii pentru a fi in ordine 
    CarteDeJoc scoateCarte() override 
    {
        CarteDeJoc carteOrdine;
        if (true == carti.empty()) 
        {
            cout << "Butucul de carti este gol!" << endl;
        }
        else
        {
            carteOrdine = carti[index];
            carti.erase(carti.begin() + index);
            if (index > 0) 
            {
                // decrementeaza pana la 0
                index--;
            }
        }
        return carteOrdine;
    }

};

// Clasa derivata pentru butucul de carti aleatorii
class ButucAleator : public ButucDeCarti 
{
public:
    // Supraincarcarea metodei de scoatere a cartii pentru a fi aleatorie
    CarteDeJoc scoateCarte() override 
    {
        CarteDeJoc carteAleatorie;
        if (carti.empty()) 
        {
            cout << "Butucul de carti este gol!" << endl;
        }
        else
        {
            srand(time(nullptr)); // Initializeaza generatorul de numere aleatoare
            int index = rand() % carti.size(); // Genereaza un index aleator
            carteAleatorie = carti[index];
            carti.erase(carti.begin() + index); // Sterge cartea scoasa din butuc
        }
        return carteAleatorie;
    }
};

int main() 
{
    // Exemplu de utilizare a claselor pentru butucurile de carti
    ButucOrdine butucOrdine;
    butucOrdine.adaugaCarte(CarteDeJoc("As", "Inima"));
    butucOrdine.adaugaCarte(CarteDeJoc("Rege", "Trefla"));
    butucOrdine.adaugaCarte(CarteDeJoc("Dama", "Romb"));
    butucOrdine.adaugaCarte(CarteDeJoc("Valet", "Pica"));

    cout << "Butucul cu ordine:\n";
    while (false == butucOrdine.esteGol()) 
    {
        cout << "Se scoate: " << butucOrdine.scoateCarte() << endl;
    }

    ButucAleator butucAleator;
    butucAleator.adaugaCarte(CarteDeJoc("10", "Inima"));
    butucAleator.adaugaCarte(CarteDeJoc("9", "Trefla"));
    butucAleator.adaugaCarte(CarteDeJoc("8", "Romb"));
    butucAleator.adaugaCarte(CarteDeJoc("7", "Pica"));

    cout << "\nButucul aleator:\n";
    while (false == butucAleator.esteGol()) 
    {
        cout << "Se scoate: " << butucAleator.scoateCarte() << endl;
    }

    return 0;
}
