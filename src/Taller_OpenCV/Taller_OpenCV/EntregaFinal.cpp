#include "opencv2/imgproc.hpp"
#include "opencv2/imgcodecs.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/objdetect.hpp"
#include <iostream>
#include <string>
#include <sstream>
#include <ctime>

using namespace cv;
using namespace std;


class AVLNode {
public:
    int key;
    Mat image; 
    AVLNode* left;
    AVLNode* right;
    int altura;
    int veces;

    AVLNode(Mat image) {
        this->image = image;
        key = 0;
        left = right = NULL;
        altura = 0;
        veces = 0;
    }
};

class FaceDetector {
public:
    
    FaceDetector() {
        face_cascade.load("haarcascade_frontalface_alt.xml");
    }

   
    const int imageWidth_ = 50;
    
    const int imageHeight_ = 50;
   
    const double scaleFactor_ = 1.05;
   
    const int minNeighbors_ = 8;

    
    CascadeClassifier face_cascade;

    vector<Rect> detectFaceRectangles(const Mat& frame) {

        vector<Rect> faces;
        Mat imageGray;

        
        cvtColor(frame, imageGray, COLOR_BGR2GRAY);
        
        equalizeHist(imageGray, imageGray);
        face_cascade.detectMultiScale(imageGray, faces, scaleFactor_, minNeighbors_, 0 | CASCADE_SCALE_IMAGE, Size(imageWidth_, imageHeight_));

        return faces;
    }
};


class ImageCoding {
public:
   
    ImageCoding() {

    }

    Mat frame_;
    std::vector<Mat> FacesSaves;
    vector<Mat> codeGray(vector<Rect> detections, bool equalize, Size size) {
        Mat cropColor;
        Mat imageGray;
        Mat resizedDown;

        std::vector<Mat> cropFaces;
        for (const auto& det : detections) {
           
            cropColor = frame_(det);
           
            cvtColor(cropColor, imageGray, COLOR_BGR2GRAY);
           
            if (equalize) {
                equalizeHist(imageGray, imageGray);
            }
            
            resize(imageGray, resizedDown, size, INTER_LINEAR);
            cropFaces.push_back(resizedDown.clone());
            FacesSaves.push_back(cropColor);
        }

        return cropFaces;
    }

    vector<Mat> mostrarCaras()
    {
        return FacesSaves;
    }

    void setImage(Mat frame) {
        frame_ = frame;
    }
};


class AVL {

private:
    const int DIFFERENT = 1700;
    const int SIMILAR = 1300;
    int counter;
    AVLNode* root;

public:
    AVL() {
        counter = 0;
        root = NULL;
    }

    void insert(Mat image) {
        root = insert(root, image);
    }

    double euclideanDistance(Mat img1, Mat img2) {
        return norm(img1, img2, NORM_L2);
    }

    AVLNode* insert(AVLNode* n, Mat image) {
        if (n == nullptr) {
            n = new AVLNode(image);
            n->key = ++counter;
            n->veces = n->veces + 1;
        }

        else if (SIMILAR < euclideanDistance(n->image, image) && DIFFERENT > euclideanDistance(n->image, image)) {
            n->left = insert(n->left, image);

            if (!isBalanced(n)) { //ver si rota
                n = (SIMILAR < euclideanDistance(n->left->image, image)) ? rotacionDer(n) : dobleDer(n);
            }
        }
        else if (DIFFERENT <= euclideanDistance(n->image, image)) {
            n->right = insert(n->right, image);

            if (!isBalanced(n)) { //ver si rota
                n = (DIFFERENT <= euclideanDistance(n->right->image, image)) ? rotacionIzq(n) : dobleIzq(n);
            }
        }
        else { 
            cout << "Distancia euclidea (Igual): " << euclideanDistance(n->image, image) << endl;
            n->image = image; 
            cout << "Cara igual" << endl;
            n->veces = n->veces + 1;
        }
        calcularAlto(n);
        return n;
    }

    int altoArbol(AVLNode* n) {
        return n == nullptr ? 0 : n->altura;
    }

    void calcularAlto(AVLNode* n) {
        if (n != nullptr) {
            n->altura = 1 + max(altoArbol(n->left), altoArbol(n->right));
        }
    }

    bool isBalanced(AVLNode* n) {
        if (n != nullptr) {
            return abs(altoArbol(n->left) - altoArbol(n->right)) <= 1;
        }
    }

    AVLNode* rotacionIzq(AVLNode* n) {
        AVLNode* current = n->right;
        n->right = current->left;
        current->left = n;

        calcularAlto(current);
        calcularAlto(n);
        return current;
    }

    AVLNode* rotacionDer(AVLNode* n) {
        AVLNode* current = n->left;
        n->left = current->right;
        current->right = n;

        calcularAlto(current);
        calcularAlto(n);
        return current;
    }

    AVLNode* dobleIzq(AVLNode* n) {
        n->right = rotacionDer(n->right);
        return rotacionIzq(n);
    }

    AVLNode* dobleDer(AVLNode* n) {
        n->left = rotacionIzq(n->left);
        return rotacionDer(n);
    }


    void MostrarVeces(AVLNode* node) {
        if (node == NULL) return;
        cout << "ID: " << node->key << endl;
        cout << "Veces que aparecio: " << node->veces << endl;
        MostrarVeces(node->left);
        MostrarVeces(node->right);
    }

    AVLNode* getRoot() { return root; }

    void Destroy(AVLNode* node) {

        if (node != NULL) {
            Destroy(node->left);
            Destroy(node->right);
            delete node;
            node = NULL;
        }
    }

    ~AVL() {
        Destroy(root);
    }
};

int main()
{
    cout << "Para salir del programa presione ESC o q(uit)." << endl;

    vector<string> imagesStr;
    
    imagesStr.push_back("Resources/image-007.jpeg");
    imagesStr.push_back("Resources/image-008.jpeg");
    imagesStr.push_back("Resources/image-024.jpeg");
    imagesStr.push_back("Resources/image-025.jpeg");
    imagesStr.push_back("Resources/image-026.jpeg");
    imagesStr.push_back("Resources/image-046.jpeg");
    imagesStr.push_back("Resources/image-047.jpeg");

    AVL* avl = new AVL();
    FaceDetector fdetector;
    ImageCoding icoding;
    Mat image;
    Scalar color(0, 0, 255);
    unsigned t0, t1;
    vector<double> TimeSave;

    cout << "COLOR";
    for (string im : imagesStr) {
        cout << im << endl;
        image = imread(im, IMREAD_COLOR);
        auto facesMarkers = fdetector.detectFaceRectangles(image);

       
        icoding.setImage(image);
        auto faceCodingGray = icoding.codeGray(facesMarkers, true, Size(25, 25));
        
        Mat colorImage;
        Mat newSize;
        
        int widthImageInGrayColor = 40;
        int posX = 10;
        for (const auto& cf : faceCodingGray) {
           
            avl->insert(cf);
            
            cvtColor(cf, colorImage, COLOR_GRAY2BGR);
            resize(colorImage, newSize, Size(widthImageInGrayColor, widthImageInGrayColor), INTER_LINEAR);
            newSize.copyTo(image(cv::Rect(posX, 10, newSize.cols, newSize.rows)));
            posX += widthImageInGrayColor + 10;
        }

        for (const auto& fm : facesMarkers) {
            rectangle(image, fm, color, 4);
        }
        
        t0 = clock();
        imshow("Detected Face", image);

        waitKey(0);
        t1 = clock();
        double time = (double(t1 - t0) / CLOCKS_PER_SEC);
        TimeSave.push_back(time);
    }

    //avl->preOrder(avl->getRoot());

    int opcion = 0;
    int op = 0;
    cout << "¿Como quiere iniciar sesion? (1-Guardia)(2-Administrador)(3-Salir)" << endl;
    cout << "Ingrese opcion(1-2):" << endl;
    cin >> opcion;

    switch (opcion)
    {
    case 1:
        cout << "***Bienvenido al Menu de Guardia***" << endl;
        cout << "Observando todas las caras detectadas por pantalla y sus tiempos" << endl;
        cout << "NOTA: Haga click sobre la imagen pequena y luego presione cualquier letra para pasar las imagenes\n" << endl;
        cout << endl;
        if (op == 0) {
            vector<Mat> lista = icoding.mostrarCaras();
            for (Mat image : lista) {
                
                imshow("RostrosCapturados", image);
                double time = TimeSave.back();
                TimeSave.pop_back();
                cout << "Execution Time: " << time << endl;
                waitKey(0);
            }
        }
        break;

    case 2:
        cout << "***Bienvenido al Menu de Administrador***" << endl;
        cout <<"Contando con un listado de todas las identidades mostrando cuantas veces salio en pantalla"<< endl;
        cout <<"Almacenando la secuencia de imagenes para tener evidencia en caso de problemas" << endl;
        avl->MostrarVeces(avl->getRoot());
        cout << "Presione el cuadro con la imagen y luego presione la tecla Esc" << endl;
        break;

    case 3:
        cout <<"Saliendo del programa"<< endl;
        break;
    default:
        cout << "ERROR!! Ingrese opcion correcta (1-2):" << endl;
        cin >> opcion;
        break;
    }
    
    while (true) {
        int pressKey = waitKey(100);
        if (pressKey == 27 || pressKey == 113) break;
    }

    delete avl;
    destroyAllWindows();

    return 0;
}