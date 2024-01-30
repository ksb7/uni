#include <iostream>
using namespace std;

/* Să se creeze clasa Vector – vector. Clasa conţine pointer spre float, numărul de elemente şi o
variabilă – codul erorii. Să se definească constructorul fără parametri (constructorul implicit),
constructorul cu un parametru şi constructorul cu doi parametri. Să se definească funcţiile
membru de acces: returnarea şi setarea valorii elementului (i,j). Să se definească funcţiile de
adunare şi scădere a doi vectori; înmulţirea scalară unui vector cu un alt vector; înmulţirea unui
vector cu un număr. Să se testeze funcţionarea clasei. În caz de insuficienţă de memorie,
necorespondenţă a dimensiunilor vectorilor, depăşire a limitei memoriei utilizate să se
stabilească codul erorii.*/

typedef enum{
	E_OK = 0,
	E_NULL_PTR,
	E_INSUFFICIENT_MEMORY,
	E_VECTOR_UNMATCHED,
	E_MEMORY_OVERFLOW
} Error_Type;

class Vector{
public:
	float *vectorElement;
	int elementPosition;
	Error_Type errorCode;

	Vector() {
		vectorElement = NULL;
		elementPosition = 0;
		errorCode = E_NULL_PTR;
	}

	Vector(Error_Type error) {
		vectorElement = NULL;
		elementPosition = 0;
		errorCode = error;
	}

	Vector(int ptrSize, Error_Type error) {

		vectorElement = new float[2];
		if(vectorElement != NULL)
		{
			elementPosition = ptrSize;
			errorCode = E_OK;

			cin >> vectorElement[0];
			cin >> vectorElement[1];
		} else
		{
			elementPosition = 0;
			errorCode = E_INSUFFICIENT_MEMORY;
		}
	}

	void setElement(float i, float j, int position) {
		if(position == elementPosition)
		{
			vectorElement[0] = i;
			vectorElement[1] = j;
		}
		else
		{
			errorCode = E_VECTOR_UNMATCHED;
			cout<<"Invalid position"<<endl;
		}

	}

	float* getElement()
	{
		return vectorElement;
	}


	friend Vector operator *(const Vector &A, const Vector &B)
	{
		A.vectorElement[0] *= B.vectorElement[0];
		A.vectorElement[1] *= B.vectorElement[1];
		return A;
	}

	friend Vector operator *(const Vector &A, float factor)
	{
		A.vectorElement[0] *= factor;
		A.vectorElement[1] *= factor;
		return A;
	}

};
int main() {
	int numberOfElements;
	cout << "Numarul de elemente" << endl;
	cin >> numberOfElements;

	Vector vectorList[numberOfElements];

	cout << "Elementele: \ni j\n";
	for(int i = 0; i < numberOfElements; i++)
	{
		Vector temp(i, E_OK);
		vectorList[i] = temp;
		cout << (temp * 3).getElement()[0];
	}


	cout << vectorList[2].getElement()[0] << " " << vectorList[2].getElement()[1];
	return 0;
}
