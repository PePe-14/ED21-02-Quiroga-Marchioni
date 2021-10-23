#include "opencv2/imgproc.hpp"
#include "opencv2/imgcodecs.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/objdetect.hpp"
#include <iostream>
#include <string>

using namespace cv;
using namespace std;

void reconocer_Guardar(Mat img, CascadeClassifier face_cascade);

class Persona {
	Mat* imagen;
	int* tiempo;
public:
	Persona() {
	
	}
	Persona(Mat* imagen) {
		this->imagen = imagen;
	}
	Mat* getImagen() {
		return imagen;
	}

	int* getTiempo() {
		return tiempo;
	}
	void agregarTiempo(int* newTiempo) {
		tiempo += *newTiempo;
	}
	~Persona() {
		delete tiempo;
	}
};

class Nodo {
	Persona* persona;
	Nodo* next;
public:
	Nodo(Persona* persona, Nodo* next) {
		this->persona = persona;
		this->next = next;
	}
	Persona* getPersona() {
		return persona;
	}
	Nodo* getNext() {
		return next;
	}

	~Nodo() {
		delete persona;
		next = NULL;
	}
};

class ListaPersonas {
	Nodo* first;
public:
	ListaPersonas() {
		first = NULL;
	}
	void add(Persona* persona) {
		Nodo* existe = buscarPersona(persona->getImagen());

		if (existe == NULL) {//no existe
			Nodo* newNodo = new Nodo(persona, first);
			first = newNodo;
		}
		else {
			int* newTiempo;
			(*existe).getPersona()->agregarTiempo(newTiempo);
		}
	}
	Nodo* buscarPersona(Mat* imagen) {
		Nodo* current = first;
		while (current != NULL) {
			if ((*current).getPersona()->getImagen() == imagen) {
				return current;
			}
			current = (*current).getNext();
		}
		return NULL;
	}

	void cincoPersonasMasTiempo() {
		int* tiempoPrimero = 0;
		Mat* primero;
		int* tiempoSegundo = 0;
		Mat* segundo;
		int* tiempoTercero = 0;
		Mat* tercero;
		int* tiempoCuarto = 0;
		Mat* cuarto;
		int* tiempoQuinto = 0;
		Mat* quinto;

		Nodo* current = first;
		while (current != NULL) {
			int* tiempoCurrent = (*current).getPersona()->getTiempo();
			Mat* codigoCurrent = (*current).getPersona()->getImagen();//cambiar
			if (tiempoCurrent >= tiempoPrimero) {
				int* aux = tiempoPrimero;
				Mat* Caux = primero;
				tiempoPrimero = tiempoCurrent;
				primero = codigoCurrent;

				int* aux2 = tiempoSegundo;
				Mat* Caux2 = segundo;
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
				int* aux = tiempoSegundo;
				Mat* Caux = segundo;
				tiempoSegundo = tiempoCurrent;
				segundo = codigoCurrent;

				int* aux2 = tiempoTercero;
				Mat* Caux2 = tercero;
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
				int* aux = tiempoTercero;
				Mat* Caux = tercero;
				tiempoTercero = tiempoCurrent;
				tercero = codigoCurrent;

				int* aux2 = tiempoCuarto;
				Mat* Caux2 = cuarto;
				tiempoCuarto = aux;
				cuarto = Caux;

				tiempoQuinto = aux2;
				quinto = Caux2;
			}
			else if (tiempoCurrent >= tiempoCuarto) {
				int* aux = tiempoCuarto;
				Mat* Caux = cuarto;
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

	~ListaPersonas() {
		Nodo* current = this->first;
		while (current->getNext() != NULL) {
			Nodo* aux = current;
			current = current->getNext();
			delete aux;
		}
		delete current;
		this->first = NULL;
	}
};

string window_name = "Window";
int filenumber;
string filename;

void reconocer_Guardar(Mat img, CascadeClassifier face_cascade)
{
	vector<Rect> faces;
	Mat img_gray;
	Mat crop;
	Mat res;
	Mat gray;

	cvtColor(img, img_gray, COLOR_BGR2GRAY);
	equalizeHist(img_gray, img_gray);

	face_cascade.detectMultiScale(img_gray, faces, 1.1, 2, 0 | CASCADE_SCALE_IMAGE, Size(30, 30));

	Rect filas;
	Rect col;
	size_t j = 0;

	for (size_t i = 0; i < faces.size(); i++)
	{
		col.x = faces[i].x;
		col.y = faces[i].y;
		col.width = (faces[i].width);
		col.height = (faces[i].height);

		filas.x = faces[j].x;
		filas.y = faces[j].y;
		filas.width = (faces[j].width);
		filas.height = (faces[j].height);

		crop = img(filas);
		resize(crop, res, Size(128, 128), 0, 0, INTER_LINEAR);
		cvtColor(crop, gray, COLOR_BGR2GRAY);

		filename = "Resources/Imagenes";
		stringstream ssfn;
		ssfn << filename.c_str() << filenumber << ".jpg";
		filename = ssfn.str();
		imwrite(filename, res);
		filenumber++;


		Point pt1(faces[i].x, faces[i].y);
		Point pt2((faces[i].x + faces[i].height), (faces[i].y + faces[i].width));
		rectangle(img, pt1, pt2, Scalar(0, 0, 255), 2, 8, 0);
	}

	imshow("image", img);
}

void asociarRostroPersona() {}

int main(void)
{
	ListaPersonas* lp = new ListaPersonas();

	string path = "Resources/video.mp4";
	VideoCapture capture(path);
	Mat img;
	CascadeClassifier face_cascade;
	
	face_cascade.load("haarcascade_frontalface_default.xml");

	while (true)
	{
		capture.read(img);

		reconocer_Guardar(img,face_cascade);

		waitKey(10);
	}
	delete lp;
	return 0;
}