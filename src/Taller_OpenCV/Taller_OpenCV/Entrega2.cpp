#include "opencv2/imgproc.hpp"
#include "opencv2/imgcodecs.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/objdetect.hpp"
#include <iostream>
#include <string>

using namespace cv;
using namespace std;

class Persona {
	int codigo;
	int tiempo;
public:
	Persona() {
		this->codigo = 000000;
	}
	Persona(int codigo, int tiempo) {
		this->codigo = codigo;
		this->tiempo = tiempo;
	}
	int getCodigo() {
		return codigo;
	}
	int getTiempo() {
		return tiempo;
	}
	void agregarTiempo(int newTiempo) {
		tiempo += newTiempo;
	}
	~Persona() {
		cout << "Persona eliminada" << endl;
	}
};

class Nodo {
	Persona persona;
	Nodo* next;
public:
	Nodo(Persona persona, Nodo* next) {
		this->persona = persona;
		this->next = next;
	}
	Persona getPersona() {
		return persona;
	}
	Nodo* getNext() {
		return next;
	}
};

class ListaPersonas {
	Nodo* first;
	int size;
public:
	ListaPersonas() {
		first = NULL;
		size = 0;
	}
	void add(Persona persona) {
		Nodo* existe = buscarPersona(persona.getCodigo());

		if (existe == NULL) {//no existe
			Nodo* newNodo = new Nodo(persona, first);
			first = newNodo;
			size++;
		}
		else {
			(*existe).getPersona().agregarTiempo(persona.getTiempo());
		}
	}
	Nodo* buscarPersona(int codigo) {
		Nodo* current = first;
		while (current != NULL) {
			if ((*current).getPersona().getCodigo() == codigo) {
				return current;
			}
			current = (*current).getNext();
		}
		return NULL;
	}
	int getSize() {
		return size;
	}
	string cincoPersonasMasTiempo() {
		int tiempoPrimero = 0;
		int primero;
		int tiempoSegundo = 0;
		int segundo;
		int tiempoTercero = 0;
		int tercero;
		int tiempoCuarto = 0;
		int cuarto;
		int tiempoQuinto = 0;
		int quinto;

		Nodo* current = first;
		while (current != NULL) {
			int tiempoCurrent = (*current).getPersona().getTiempo();
			int codigoCurrent = (*current).getPersona().getCodigo();//cambiar
			if (tiempoCurrent >= tiempoPrimero) {
				int aux = tiempoPrimero;
				int Caux = primero;
				tiempoPrimero = tiempoCurrent;
				primero = codigoCurrent;

				int aux2 = tiempoSegundo;
				int Caux2 = segundo;
				tiempoSegundo = aux2;
				segundo = Caux2;

				aux = tiempoTercero;
				Caux = tercero;
				tiempoTercero = aux;
				tercero = Caux;

				aux2 = tiempoCuarto;
				Caux2 = cuarto;
				tiempoCuarto = aux;
				cuarto = Caux;

				tiempoQuinto = aux2;
				quinto = Caux2;
			}
			else if (tiempoCurrent >= tiempoSegundo) {
				int aux = tiempoSegundo;
				int Caux = segundo;
				tiempoSegundo = tiempoCurrent;
				segundo = codigoCurrent;

				int aux2 = tiempoTercero;
				int Caux2 = tercero;
				tiempoTercero = aux;
				tercero = Caux;

				aux = tiempoCuarto;
				Caux = cuarto;
				tiempoCuarto = aux2;
				cuarto = Caux2;

				tiempoQuinto = aux;
				quinto = Caux;
			}
			else if (tiempoCurrent >= tiempoTercero) {
				int aux = tiempoTercero;
				int Caux = tercero;
				tiempoTercero = tiempoCurrent;
				tercero = codigoCurrent;

				int aux2 = tiempoCuarto;
				int Caux2 = cuarto;
				tiempoCuarto = aux;
				cuarto = Caux;

				tiempoQuinto = aux2;
				quinto = Caux2;
			}
			else if (tiempoCurrent >= tiempoCuarto) {
				int aux = tiempoCuarto;
				int Caux = cuarto;
				tiempoCuarto = tiempoCurrent;
				cuarto = codigoCurrent;

				tiempoQuinto = aux;
				quinto = Caux;
			}
			else if (tiempoCurrent >= tiempoQuinto) {
				tiempoQuinto = tiempoCurrent;
				quinto = codigoCurrent;
			}
			current = (*current).getNext();
		}
	}
};

int main()
{

	VideoCapture cap(0);
	Mat img;

	while (true) {

		cap.read(img);

		CascadeClassifier faceCascade;
		faceCascade.load("haarcascade_frontalface_default.xml");

		vector<Rect> faces;
		faceCascade.detectMultiScale(img, faces, 1.1, 10);

		for (int i = 0; i < faces.size(); i++)
		{
			rectangle(img, faces[i].tl(), faces[i].br(), Scalar(0, 0, 255), 3);
		}

		imshow("image", img);
		waitKey(1);
	
	}
	return 0;
}