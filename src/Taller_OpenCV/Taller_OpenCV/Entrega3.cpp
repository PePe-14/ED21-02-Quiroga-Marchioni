#include "opencv2/imgproc.hpp"
#include "opencv2/imgcodecs.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/objdetect.hpp"
#include <iostream>


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

#ifndef UCN_TALLER_EDATOS_2021_1_BINARYSEARCHTREE_H
#define UCN_TALLER_EDATOS_2021_1_BINARYSEARCHTREE_H

class BinarySearchTree {

private:
    const int DIFFERENT = 1700;
    const int SIMILAR = 1300;
    /**
     * Contador para asignar identificadores a las caras
     */
    int counter;
    struct BinarySearchTreeNode* root;
    BinarySearchTreeNode* insert(BinarySearchTreeNode* node, Mat);
    double euclideanDistance(Mat, Mat);

public:
    BinarySearchTree() {
        counter = 0;
        root = nullptr;
    }

    void insert(Mat);

    //TODO: Falta hacer el destructor para eliminar cualquier el arbol complementamente
};


#endif //UCN_TALLER_EDATOS_2021_1_BINARYSEARCHTREE_H


void BinarySearchTree::insert(int n) {
    root = insert(root, n);
}

BinarySearchTreeNode* BinarySearchTree::insert(BinarySearchTreeNode* node, int n) {
    //Si el árbol no tiene hijos
    if (node == nullptr) {
        node = new BinarySearchTreeNode();
        node->key = n;
        node->left = nullptr;
        node->right = nullptr;

        return node;
    }
    else if (n < node->key) {
        node->left = insert(node->left, n);
    }
    else if (n > node->key) {
        node->right = insert(node->right, n);
    }

    return node;

}

void BinarySearchTree::preOrder(void) { // Public
    preOrder(root);
}

void BinarySearchTree::preOrder(BinarySearchTreeNode* node) {
    if (node == nullptr) return;
    cout << node->key << "\t";
    preOrder(node->left);
    preOrder(node->right);
}

void BinarySearchTree::remove(int n) { // Public
    remove(root, n);
}

BinarySearchTreeNode* BinarySearchTree::remove(BinarySearchTreeNode* node, int n) {
    // El nodo no se encuentra en el árbol
    if (node == nullptr) {
        return node;
    }
    else if (n < node->key) { // Busco la clave por la izquierda
        node->left = remove(node->left, n);
    }
    else if (n > node->key) { // Busco la clave por la derecha
        node->right = remove(node->right, n);
    }
    else { //Encontré la clave y la borro
       //Si es nodo hoja
        if (node->left == nullptr && node->right == nullptr) {
            delete node;
            node = nullptr;
        }
        else if (node->left == nullptr) { //El nodo a eliminar tiene solo un hijo derecho
            BinarySearchTreeNode* aux = node;
            node = node->right;
            delete aux;
        }
        else if (node->right == nullptr) { //El nodo a eliminar tiene solo un hijo izquierdo
            BinarySearchTreeNode* aux = node;
            node = node->left;
            delete aux;
        }
        else {
            BinarySearchTreeNode* aux = findMinimum(node->right);
            node->key = aux->key;
            node->right = remove(node->right, aux->key);
        }
    }
    return node;
}


BinarySearchTreeNode* BinarySearchTree::findMinimum(BinarySearchTreeNode* node) {
    while (node->left != nullptr) {
        node = node->left;
    }
    return node;
}


using namespace std;
using namespace cv;

int main()
{

    cout << "Para salir del programa presione ESC o q(uit)." << endl;
    Mat image;
    image = imread("data/caras.jpg", IMREAD_COLOR);

    FaceDetector fdetector;
    ImageCoding icoding;

    // Detecto las caras
    auto facesMarkers = fdetector.detectFaceRectangles(image);

    // Codifico las caras detectadas
    icoding.setImage(image);
    auto faceCodingGray = icoding.codeGray(facesMarkers, true, Size(25, 25));

    // Muestro las caras codificadas
    for (const auto& cf : faceCodingGray) {
        imshow("Imagen Codificada", cf);
        waitKey(0);
    }

    // Comparar las distancias entre imágenes
    Mat img1 = faceCodingGray[0];
    int sum = 1;
    for (const auto& cf : faceCodingGray) {
        double dist = norm(img1, cf, NORM_L2); // Calcular la distancia euclidia
        cout << "Comparación imagen 1 con imagen " << sum << ":" << dist << endl;
        sum++;
    }

    Scalar color(0, 0, 255);
    //Muestro las caras encontradas en la imaggen original
    for (const auto& fm : facesMarkers) {
        rectangle(image, fm, color, 4);
    }

    // Mostrar la imagen con las marcas (rectángulos) indicando la posición de la cara
    imshow("Detected Face", image);

    // Esperar hasta presionar la tecla ESC
    while (true) {
        int pressKey = waitKey(100);
        if (pressKey == 27 || pressKey == 113) break;
    }

    destroyAllWindows();

    return 0;
}