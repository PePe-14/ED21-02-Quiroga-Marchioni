#include "opencv2/imgproc.hpp"
#include "opencv2/imgcodecs.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/objdetect.hpp"
#include <iostream>
#include <string>

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

#ifndef FACEDETECTOR_H
#define FACEDETECTOR_H

using namespace cv;

class FaceDetector {
public:
    explicit FaceDetector();

    /**
     * Detectar las caras en una imagen.
     * @param (Mat) imagen fuente para detectar caras
     * @return (vector) un listado de caras detectadas
     */
    std::vector<Rect> detectFaceRectangles(const Mat& frame);

private:

    /**
     * Ancho de la imange minima que se detectará
     */
    const int imageWidth_;
    /**
     * Alto de la imagen minima que se detectará
     */
    const int imageHeight_;
    /**
     * Factor de escala que se admitirá para detectar una cara
     */
    const double scaleFactor_;
    /**
     * Número de vecinos necesarios para verificar que existe una cara en ese lugar
     */
    const int minNeighbors_;

    /**
     * Atributo que contiene al clasificador de caras
     */
    CascadeClassifier face_cascade;
};

#endif //FACEDETECTOR_H

#ifndef IMAGE_CODING_HPP
#define IMAGE_CODING_HPP

using namespace cv;

class ImageCoding {
public:
    explicit ImageCoding();

    /**
     * Procesar imagen, convertirla en grises, es escalarla y ecualizarla (opcional)
     *
     * @param frame (Mat) imagen fuente para detectar caras
     * @param detections (Vector<Rect>) Vector con los rectangulos de las detecciones
     * @param equalize (bool) True - ecualizo la imagen, en caso contrario no se ecualiza
     * @param size (Size) Tamaño de las imágenes finales. (Todas tendrán ese tamaño)
     * @return (vector) un listado de caras detectadas
     */
    std::vector<Mat> codeGray(std::vector<Rect> detections, bool equalize, Size size);

    /**
     * Carga la imagen a ser procesada
     * @param frame (Mat) Imagen original para ser procesada
     */
    void setImage(Mat frame);

private:
    /**
     * Imagen a ser procesada
     */
    Mat frame_;
};

#endif //IMAGE_CODING_HPP


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
    imagesStr.push_back("data/image-007.jpeg");
    imagesStr.push_back("data/image-008.jpeg");
    imagesStr.push_back("data/image-024.jpeg");
    imagesStr.push_back("data/image-025.jpeg");
    imagesStr.push_back("data/image-026.jpeg");
    imagesStr.push_back("data/image-046.jpeg");
    imagesStr.push_back("data/image-047.jpeg");

    cout << "imagesStr = { ";
    for (string n : imagesStr) {
        cout << n << ", ";
    }
    cout << "};" << endl;

    // Leemos todas las caras de los archivos de imágenes y las insertamos en el árbol
    BinarySearchTree abb;
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
            abb.insert(cf);
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

    //    // Comparar las distancias entre imágenes
    //    Mat img1 = faceCodingGray[0];
    //    int sum = 1;
    //    for(const auto &cf : faceCodingGray){
    //        double dist = norm(img1, cf,NORM_L2); // Calcular la distancia euclidia
    //        cout << "Comparación imagen 1 con imagen " << sum << ":" << dist << endl;
    //        sum++;
    //    }
    //


        // Esperar hasta presionar la tecla ESC
    while (true) {
        int pressKey = waitKey(100);
        if (pressKey == 27 || pressKey == 113) break;
    }

    destroyAllWindows();

    return 0;
}