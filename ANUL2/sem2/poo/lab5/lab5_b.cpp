#include <iostream>

using namespace std;

template <typename T>
class Queue {
private:
    T* elements; // Pointer catre tabloul de elemente
    int capacity; // Capacitatea cozi
    int front; // Indicele primului element din coada
    int rear; // Indicele ultimului element din coada
    int length; // Lungimea actuala a cozi

public:
    // Constructor
    Queue(int size = 10)
    {
        capacity = size;
        front = 0;
        rear = -1;
        length = 0;
        elements = new T[capacity];
    }

    // Destructor
    ~Queue() 
    {
        delete[] elements;
    }

    // Functia pentru adaugarea unui element in coada
    void add(const T& element) 
    {
        if (length < capacity) 
        {
            rear = (rear + 1) % capacity; // Urmatorul element va fi ultimul din coada
            elements[rear] = element;
            length++;
        } else 
        {
            cout << "Coada plina! Elementul nu a fost adaugat." << endl;
        }
    }

    // Functia pentru extragerea unui element din coada
    T get() 
    {
        if (!isEmpty()) 
        {
            T element = elements[front];
            front = (front + 1) % capacity; // Primul element existent va iesi 
            length--;
            return element;
        } else 
        {
            cout << "Coada goala! Nu exista elemente de extras." << endl;
            return T();
        }
    }

    // Functia pentru a obtine primul element din coada fara a-l sterge
    T peek() const 
    {
        if (!isEmpty()) 
        {
            return elements[front];
        } else 
        {
            cerr << "Coada goala! Nu exista elemente de extras." << endl;
            return T();
        }
    }

    // Functia pentru a verifica daca coada este goala
    bool isEmpty() const 
    {
        return (0 == length);
    }

    // Functia pentru a obtine lungimea curenta a cozii
    int getLength() const 
    {
        return length;
    }

    // Supraincarcarea operatorului []
    T& operator[](int index) 
    {
        if (index >= 0 && index < length) 
        {
            return elements[(front + index) % capacity]; // Elementul la pozitia index de la front
        } else 
        {
            cout << "Index invalid!" << endl;
            exit(1);
        }
    }

    // Supraincarcarea operatorului de afisare
    friend ostream& operator<<(ostream& out, const Queue<T>& q) 
    {
        out << "Elementele cozi:" << endl;
        if (!q.isEmpty()) 
        {
            for (int i = 0; i < q.length; i++) 
            {
                out << q.elements[(q.front + i) % q.capacity] << " "; // Trece prin fiecare pozitie i de la front
            }
        } else 
        {
            out << "Coada goala!";
        }
        return out;
    }
};

int main() 
{
    Queue<int> q(5);
    q.add(1);
    q.add(2);
    q.add(3);
    q.add(4);
    q.add(5);
    cout << "Coada initiala:" << endl;
    cout << q << endl;

    cout << "Primul element al cozii: " << q.peek() << endl;
    cout << "Extragere element din coada: " << q.get() << endl;
    cout << "Elementele cozii dupa extragere:" << endl;
    cout << q << endl;

    cout << "Elementul de pe pozitia 2: " << q[1] << endl;

    return 0;
}
