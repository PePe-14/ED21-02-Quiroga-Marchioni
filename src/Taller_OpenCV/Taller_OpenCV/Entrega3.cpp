#include "opencv2/imgproc.hpp"
#include "opencv2/imgcodecs.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/objdetect.hpp"
#include <iostream>
#include <string>
#include <sstream>

using namespace cv;
using namespace std;

#ifndef UCN_TALLER_EDATOS_2021_1_BINARYSEARCHTREENODE_H
#define UCN_TALLER_EDATOS_2021_1_BINARYSEARCHTREENODE_H

/**
 * Clase que almacena la imagen y el identificador de la cara
 */
class BinarySearchTreeNode {
public:
    int key;
    Mat image; // Imagen de tamaño 25x25
    BinarySearchTreeNode* left;
    BinarySearchTreeNode* right;
};

#endif //UCN_TALLER_EDATOS_2021_1_BINARYSEARCHTREENODE_H


class FaceDetector {
public:
    /**
     * Detectar las caras en una imagen.
     * @param (Mat) imagen fuente para detectar caras
     * @return (vector) un listado de caras detectadas
     */
    FaceDetector() {
        face_cascade.load("haarcascade_frontalface_alt.xml");
    }

    /**
     * Ancho de la imange minima que se detectará
     */
    const int imageWidth_ = 50;
    /**
     * Alto de la imagen minima que se detectará
     */
    const int imageHeight_ = 50;
    /**
     * Factor de escala que se admitirá para detectar una cara
     */
    const double scaleFactor_ = 1.05;
    /**
     * Número de vecinos necesarios para verificar que existe una cara en ese lugar
     */
    const int minNeighbors_ = 8;

    /**
     * Atributo que contiene al clasificador de caras
     */
    CascadeClassifier face_cascade;

    vector<Rect> detectFaceRectangles(const Mat& frame) {

        vector<Rect> faces;
        Mat imageGray;

        // Detecto las caras (Se debe pasar la imagen a escala de grises
        cvtColor(frame, imageGray, COLOR_BGR2GRAY);
        // Aumento el constraste de una imagen
        equalizeHist(imageGray, imageGray);
        face_cascade.detectMultiScale(imageGray,faces,scaleFactor_,minNeighbors_,0 | CASCADE_SCALE_IMAGE,Size(imageWidth_, imageHeight_));

        return faces;
    }
};


class ImageCoding {
public:
    /**
     * Procesar imagen, convertirla en grises, es escalarla y ecualizarla (opcional)
     *
     * @param frame (Mat) imagen fuente para detectar caras
     * @param detections (Vector<Rect>) Vector con los rectangulos de las detecciones
     * @param equalize (bool) True - ecualizo la imagen, en caso contrario no se ecualiza
     * @param size (Size) Tamaño de las imágenes finales. (Todas tendrán ese tamaño)
     * @return (vector) un listado de caras detectadas
     */
    ImageCoding() {

    }

    /**
     * Imagen a ser procesada
     */
    Mat frame_;

    vector<Mat> codeGray(vector<Rect> detections, bool equalize, Size size) {
        Mat cropColor;
        Mat imageGray;
        Mat resizedDown;

        std::vector<Mat> cropFaces;
        for (const auto& det : detections) {
            // Recorto la imagen detectada
            cropColor = frame_(det);
            //Usamos solo imágenes en grises
            cvtColor(cropColor, imageGray, COLOR_BGR2GRAY);
            // Si se desea ecualizar la imagen (aumentar contraste)
            if (equalize) {
                equalizeHist(imageGray, imageGray);
            }
            // Reescalamos
            resize(imageGray, resizedDown, size, INTER_LINEAR);
            cropFaces.push_back(resizedDown.clone());
        }

        return cropFaces;
    }

    /**
    * Carga la imagen a ser procesada
    * @param frame (Mat) Imagen original para ser procesada
    */
    void setImage(Mat frame) {
        frame_ = frame;
    }
};



class BinarySearchTree {

    private:
        const int DIFFERENT = 1700;
        const int SIMILAR = 1300;
        /**
         * Contador para asignar identificadores a las caras
        */
        int counter;
        BinarySearchTreeNode* root;

    public:
        BinarySearchTree() {
            counter = 0;
            root = nullptr;
        }

    /**
     * Inserta la imagen en el arbol le asigna un identificador.
     *
     * @param image (Mat) imagen de tamaño 25x25 en gris
     */
    void insert(Mat image) {
        root = insert(root, image);
    }

    double euclideanDistance(Mat img1, Mat img2) {
        return norm(img1, img2, NORM_L2);
    }

    BinarySearchTreeNode* insert(BinarySearchTreeNode* node, Mat image) {
        // Tolerancia para considerar una imagen igual
        //Si el árbol no tiene hijos
        if (node == nullptr) {
            node = new BinarySearchTreeNode();
            node->key = ++counter;
            node->image = image;
            node->left = nullptr;
            node->right = nullptr;

            cout << "ID: " << node->key << endl;
            return node;
        }
        else if (SIMILAR < euclideanDistance(node->image, image)
            && DIFFERENT > euclideanDistance(node->image, image)) {
            node->left = insert(node->left, image);
        }
        else if (DIFFERENT <= euclideanDistance(node->image, image)) {
            node->right = insert(node->right, image);
        }
        else { //La cara es igual (menor a la distancia exigida para similar)
            cout << "Distancia euclidea (Igual): " << euclideanDistance(node->image, image) << endl;
            node->image = image; //Cambio la imagen por la nueva
            cout << "Cara igual" << endl;
        }
        cout << "Distancia euclidea: " << euclideanDistance(node->image, image) << endl;
        return node;
    }

    void preOrder(BinarySearchTreeNode* node) {
        if (node == nullptr) return;
        imshow("Detected Face", node->image);  //probar si esta guardadas las caras
        preOrder(node->left);
        preOrder(node->right);
    }

    BinarySearchTreeNode* getRoot() { return root; }

    void Destroy(BinarySearchTreeNode* node){

        if (node != NULL){
            Destroy(node->left);
            Destroy(node->right);
            delete node;
            node = NULL; 
        }
    }

    ~BinarySearchTree() {
        Destroy(root);
    }
};

int main()
{
    cout << "Para salir del programa presione ESC o q(uit)." << endl;

    vector<string> imagesStr;
    //TODO: Cargar todos los archivos del directorio automáticamente
    imagesStr.push_back("Resources/image-007.jpeg");
    imagesStr.push_back("Resources/image-008.jpeg");
    imagesStr.push_back("Resources/image-024.jpeg");
    imagesStr.push_back("Resources/image-025.jpeg");
    imagesStr.push_back("Resources/image-026.jpeg");
    imagesStr.push_back("Resources/image-046.jpeg");
    imagesStr.push_back("Resources/image-047.jpeg");

    // Leemos todas las caras de los archivos de imágenes y las insertamos en el árbol
    BinarySearchTree* abb = new BinarySearchTree();
    FaceDetector fdetector;
    ImageCoding icoding;
    Mat image;
    Scalar color(0, 0, 255);

    cout << "COLOR";
    for (string im : imagesStr) {
        cout << im << endl;
        image = imread(im, IMREAD_COLOR);
        auto facesMarkers = fdetector.detectFaceRectangles(image);

        // Codifico las caras detectadas
        icoding.setImage(image);
        auto faceCodingGray = icoding.codeGray(facesMarkers, true, Size(25, 25));
        // Muestro las caras codificadas
        Mat colorImage;
        Mat newSize;
        // Muestro las caras detectadas en la imagen original
        int widthImageInGrayColor = 40;
        int posX = 10;
        for (const auto& cf : faceCodingGray) {
            // Inserto la imagen en el arbol y obtengo el identificador
            abb->insert(cf);
            // Muestro la imagen codificada en la imagen original
            cvtColor(cf, colorImage, COLOR_GRAY2BGR);
            resize(colorImage, newSize, Size(widthImageInGrayColor, widthImageInGrayColor), INTER_LINEAR);
            newSize.copyTo(image(cv::Rect(posX, 10, newSize.cols, newSize.rows)));
            posX += widthImageInGrayColor + 10;
        }

        // Para ver caras detectadas
        //Muestro las caras encontradas en la imaggen original
        for (const auto& fm : facesMarkers) {
            rectangle(image, fm, color, 4);
        }
        // Mostrar la imagen con las marcas (rectángulos) indicando la posición de la cara
        imshow("Detected Face", image);

        waitKey(0);
    }

    //abb->preOrder(abb->getRoot());

    int opcion = 0;
    int op = 0;
    cout << "¿Como quiere iniciar sesion? (1-Guardia)(2-Administrador) "<< endl;
    cout << "Ingrese opcion(1-2):" << endl;
    cin >> opcion;

    switch (opcion)
    {
    case 1:
        cout << "***Bienvenido al Menu de Guardia***" << endl;
        cout << "1-Observar todas las caras detectadas por pantalla"<< endl;
        cout << "2-Observar las últimas 5 caras que mas tiempo fueron vistas en pantalla"<< endl;
        cout << "Ingrese opción(1-2):" << endl;
        cin >> op;
        break;

    case 2:
        cout << "***Bienvenido al Menu de Administrador***" << endl;
        cout << "1-Contar con un listado de todas las identidades mostrando cuantas veces salio en pantalla" << endl;
        cout << "2-Almacenar la secuencia de imagenes para tener evidencia en caso de problemas" << endl;
        cout << "3-Contar con un listado de todas las identidades mostrando el tiempo que salio en pantalla" << endl;
        cout << "Ingrese opción(1-2-3):" << endl;
        cin >> op;
        break;
    default:
        cout << "ERROR!! Ingrese opcion correcta (1-2):" << endl;
        cin >> opcion;
        break;
    }
    // Esperar hasta presionar la tecla ESC
    while (true) {
        int pressKey = waitKey(100);
        if (pressKey == 27 || pressKey == 113) break;
    }

    delete abb;
    destroyAllWindows();

    return 0;
}