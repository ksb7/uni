#include <iostream>
#include <string>

using namespace std;
class Om {
protected:
    string nume;
    string prenume;

public:
    Om(const string& numeParam, const string& prenumeParam)
    {
        nume = numeParam;
        prenume = prenumeParam;
    }

    // Supraincarcare operator pentru iesire
    friend ostream& operator<<(ostream& out, const Om& om) {
        out << "Nume: " << om.nume << ", Prenume: " << om.prenume;
        return out;
    }

    // Supraincarcare operator pentru intrare
    friend istream& operator>>(istream& in, Om& om) {
        cout << "Introduceti numele: ";
        in >> om.nume;
        cout << "Introduceti prenumele: ";
        in >> om.prenume;
        return in;
    }

    // Constructor de copiere
    Om(const Om& other)
    {
        nume = other.nume;
        prenume = other.prenume;
    }

    // Operator de atribuire
    Om& operator=(const Om& other) {
        if (this != &other) {
            nume = other.nume;
            prenume = other.prenume;
        }
        return *this;
    }

    virtual ~Om() {}
};

class Colaborator : public Om {
protected:
    string post;
    double salariu;

public:
    Colaborator(const string& numeParam, const string& prenumeParam, const string& postParam, double salariuParam): Om(numeParam, prenumeParam)
    {
        nume = numeParam;
        prenume = prenumeParam;
        post = postParam;
        salariu = salariuParam;
    }

    // Supraincarcare operator pentru iesire
    friend ostream& operator<<(ostream& out, const Colaborator& colaborator) {
        out << "Nume: " << colaborator.nume << ", Prenume: " << colaborator.prenume << ", Post: " << colaborator.post << ", Salariu: " << colaborator.salariu;
        return out;
    }

    // Supraincarcare operator pentru intrare
    friend istream& operator>>(istream& in, Colaborator& colaborator) {
        cout << "Introduceti numele: ";
        in >> colaborator.nume;
        cout << "Introduceti prenumele: ";
        in >> colaborator.prenume;
        cout << "Introduceti postul: ";
        in >> colaborator.post;
        cout << "Introduceti salariul: ";
        in >> colaborator.salariu;
        return in;
    }

    // Constructor de copiere
    Colaborator(const Colaborator& other) : Om(other.nume, other.prenume)
    {
        nume = other.nume;
        prenume = other.prenume;
        post = other.post;
        salariu = other.salariu;
    }

    // Operator de atribuire
    Colaborator& operator=(const Colaborator& other) {
        if (this != &other) {
            nume = other.nume;
            prenume = other.prenume;
            post = other.post;
            salariu = other.salariu;
        }
        return *this;
    }

    ~Colaborator() {}
};

int main() {
    Colaborator colaborator("Moraru", "Mihai", "Manager", 5000);
    cout << "Constructorul cu parametri: " << endl;
    cout << colaborator << endl;

    Colaborator colaborator2 = colaborator;
    cout << "Constructorul de copiere: " << endl;
    cout << colaborator2 << endl;

    Colaborator colaborator3("Ciobanu", "Petru", "Director", 7000);
    cout << "Obiectul initial: " << endl;
    cout << colaborator3 << endl;
    cout << "Obiectul dupa atribuire: " << endl;
    colaborator3 = colaborator;
    cout << colaborator3 << endl;

    return 0;
}
