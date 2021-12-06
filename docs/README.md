![UCN](Imagenes/60x60-ucn-negro.png)


# Informe Técnico 
## Curso: Estructura de datos
### Detección y reidentificación de caras en secuencias de imágenes o video

**Alumnos:**

* Thomas Quiroga Espinoza (Bitacora)
* José Marchioni Clavería (Coordinador)

## Resumen 

>Para la Tercera entrega del taller se nos pide un sistema de vigilancia en base a reconocimiento de rostros. Para esta entrega en particular se solicita establecer la hora de inicio y termino de la sesión por dia para poder contar las personas utilizando OpenCV, para detectar los rostros en pantalla, ya sea en una imagen, video o la cámara del ordenador, con el objetivo de que un guardia o administrador tengan acceso a los datos recopilados y almacenados en estructuras de datos. 
>Para lograr este objetivo hicimos uso de la programacion orientada a objetos ya que necesitaremos almacenar los rostros de las personas y luego ingresarlas en un Árbol Binario, ademas debemos almacenar el video o secuencia de imagenes para poder contar con él en caso de algun incidente. Una vez que obtuvimos todo lo necesario debemos contar los rostros en el video en un tiempo acotado.
## 1. Introducción

En los últimos años, tecnologías como el reconocimiento facial y de otras figuras a partir de las cámaras estan cada vez mas presente en la vida diaria, por lo que aprender a manipular y comprender estas nuevas tecnologías dará ventaja y nuevo conocimiento a los que se dispongan a estudiarlas. La mejor forma de aprender como reconocer rostros es con la investigacion, practica e implementacion de lo aprendido en codigo, como lo es el caso de este taller que hará perfeccionar las habilidades actuales y familiarizar conceptos que hasta ahora eran desconocidos.

En esta entrega aplicaremos los conceptos aprendidos sobre como implementar un Arbol binario, y a su vez como aplicar sus métodos en la captura y almacenamiento de rostros, ya que necesitamos almacenar los rostros que fueron correctamente detectado por el algoritmo, estos se veran diferenciados con un rectangulo rojo. Al finalizar podremos saber las identidades que pudieron ser identificadas en un periodo corto de tiempo.

### 1.1 Descripción del problema

Se presenta el desafío de construir un programa que reconozca los rostros que se muestran con mayor tiempo en el video o una secuencia de imagenes y los almacene en una estructura de Arbol Binario y ademas almacenar este video o secuencia de imágenes.

### 1.2 Objetivos 

**Objetivo General**

Construir un programa que almacene en un Árbol binario los rostros que aparecen en el video en un tiempo acotado y que guarde el video.

**Objetivos específicos**

- [x] :+1: Crear el código para reconocer rostros en videos.
- [x] :+1: Crear las clases ArbolBinario,NodoArbol, FaceDetector y ImageCoding .
- [x] :+1: Implementar dichas clases para un correcto almacenamiento de los rostros.
- [x] :+1: Almacenar los rostros de las distintas personas que se detectaron.
- [x] :+1: Crear el código para almacenar el video o las imagenes de la sesion diaria.

1. Un código esencial es el que detecta las matrices(rostros).
2. La clase NodoArbol deberá contener un atributo unico para identificarlo y además un atributo de tipo Image.
3. Habra que relacionar las clases con las librerias de OpenCV.
4. Investigar el formato en que estan los rostros capturados por OpenCV para poder asociarlos a la clase NodoArbol. 
5. Averiguar como calcular el tiempo que transcurre un rostro en el video.
6. Establecer una estructura de datos que almacene el video para la sésion o para la secuencia de imagenes.

### 1.3 Solución propuesta

Construir un Arbol Binario de busqueda que almacene objetos tipo NodoArbol que tendrán un atributo con el formato en que son reconocidos los rostros, estos son objetos de la calse Mat y ádemas un identificador. Con las clases FaceDetector y ImageCoding podremos hacer más facil el trabajo del reconocimiento de rostros y así una vez guardados comparar cuanto tiempo aparecen en el video. Una vez terminado el video el programa tendrá que almacenarlo para una posible revisión.

## 2. Materiales, métodos y clases

* IDE Visual Studio Community 2019 
* Biblioteca OpenCV
* Archivo haarcascade_frontalface_alt.xml 
* Video con rostros o secuencia de imágenes
* BinarySearchTree(), BinarySearchTreeNode() y FaceDetector() y ImageCoding().

Con el uso de la clase Mat de OpenCV podremos capturar la imagen del rostro con el archivo "haarcascade_frontalface_alt.xml" y asignarlo como atributo (tipo Mat) a un objeto de tipo BinarySearchTreeNode() que se creara al momento de encontrar el rostro. Luego se agregará el objeto persona al BinarySearchTree().

### 2.1 Instalación

* IDE Visual Studio Community 2019: Es una IDE que tendrá todo el código del taller en el que se harán las pruebas de código hasta completar el objetivo.  
* Biblioteca OpenCV: Líbrería libre de visión artificial que cuenta con la mayoria de las herramientas y líbrerias para una correcta compatibilidad con la IDE.
* Archivo haarcascade_frontalface_alt.xml: Archivo clasificador pre entrenado que es capaz de reconocer rostros y otras formas.

### 2.2 Diseño 

La manera en que diseñamos el taller para las historias 3 y 5 la mostraré a continuación junto a las clases que ádemas procedere a nombrarlas y explicar su rol en el código:
* Clase BinarySearchTree: Estructura de datos donde se almacenarán los objetos de tipo BinarySearchTreeNode() que corresponden a los rostros detectados.
* Clase CascadeClassifier: Crea objetos de tipo clasificadores de cascada que en resumen se necesitan muchas imagenes para entrenar a esta función para saber identificar objetos. Esto sera utilizado para cargar el archivo que reconoce los rostros.
* Clase BinarySearchTreeNode: Estructura de datos donde se crearán los los objetos nodos donde se almacenara a un rostro correspondiente a una persona, junto a atributos como su imagen respectiva y su identificador único que sera un número. Además de contar con los hijos left y right.
* Clase FaceDetector: Encargada de reconocer los rostros y enmarcarlos en un rectangulo rojo y retonar todos los rostros capturados en un vector tipo Rect.
* Clase ImageCoding: Encargada de recortar las imágenes para solo almacenar los rostros y retornarlos recortados.

### 2.3 Implementación
 
#### Almacenar rostros

La clase BinarySearchTreeNode fue creada con el objetivo de almacenar los rostros detectados en el video con una imagen de tipo MAT y asigarle un identificador al objeto nodo.

#### BinarySearchTree

Esta clase fue necesaria para almacenar mas de un solo rostro y se apoya de la clase BinarySearchTreeNode que serian los nodos que almacena la imagen de la persona y su identificador que es el "counter".
	
	class BinarySearchTree {

    private:
        const int DIFFERENT = 1700;
        const int SIMILAR = 1300;
        int counter;
        BinarySearchTreeNode* root;

    public:
        BinarySearchTree() {
            counter = 0;
            root = nullptr;
        }
    void insert(Mat image) {
        root = insert(root, image);
    }
    (continua...)

*Las variables const son parametros para saber si la imagen corresponde a algun rostro que ya esta ingresado o si es uno nuevo, estos se clasifican según lo que indique la distancia euclideana(ver su implementación abajo).* 

#### Distancia Euclideana
El código a continuación se encuentra en la clase del arbol binario como un método que se usa dentro del método insertar. El método euclideanDistance usa dos imagenes y la norma L2 que usa la menor distancia entre dos puntos.  

	double euclideanDistance(Mat img1, Mat img2) {
        	return norm(img1, img2, NORM_L2);
    	}
	
	BinarySearchTreeNode* insert(BinarySearchTreeNode* node, Mat image) {
	...
	else if (SIMILAR < euclideanDistance(node->image, image)
            && DIFFERENT > euclideanDistance(node->image, image)) {
            node->left = insert(node->left, image);
        }
        else if (DIFFERENT <= euclideanDistance(node->image, image)) {
            node->right = insert(node->right, image);
        }
        else { 
            cout << "Distancia euclidea (Igual): " << euclideanDistance(node->image, image) << endl;
            node->image = image; 
            cout << "Cara igual" << endl;
    
*Las variables que vimos arriba son la tolerancia que clasifica si una imagen es igual o distinta y aqui se ve su implementación junto a la funcion euclideanDistance que indica a que tipo de imagenes corresponde la imagen analizada respecto a la que contiene un nodo del Arbol.* 

#### CLASE BinarySearchTreeNode
Esta clase es la base para almacenar los rostros dado que la imagen capturada se guardara en image(tipo Mat) y la variable key sera su identificador correspondiente que sera un número entero.

	class BinarySearchTreeNode {
	public:
    		int key;
    		Mat image;
    		BinarySearchTreeNode* left;
    		BinarySearchTreeNode* right;
	}
	
	
#### Detector de rostros

El archivo detector de caras utilizado fue haarcascade_frontalface_alt.xml. Para utilizarlo se debe crear un objeto que contenga este archivo, por lo que la clase que lo puede contener es CascadeCalssifier;
El código para detectar una cara en una imagen se muestra a continuación:

   FaceDetector() {
        face_cascade.load("haarcascade_frontalface_alt.xml");
    }
    const int imageWidth_ = 50;
    const int imageHeight_ = 50;
    const double scaleFactor_ = 1.05;
    const int minNeighbors_ = 8;
    CascadeClassifier face_cascade;
    face_cascade.detectMultiScale("Todos los parametros necesarios");

*En estas líneas se observa que el archivo .XML se carga en el constructor de la clase y luego se detectan las imagenes con los parametros minimos que aparecen arriba como variables constantes.*

## 3. Resultados obtenidos

Una vez terminada la ejecución del programa esta nos arroja las imágenes una por una señalando las caras que alli aparecen y además por consola se escribe el nombre de la imagen que acaba de ser capturada, ademas de la distancia euclideana y con un mensaje del identificador de imagen corroborandose que se ha creado el nodo con esa imagen y se ingreso el nodo al Arbol Binario. Cabe destacar que al aparecer los mismos rostros estos no se guardan ya que ya estan reconocidos por la clase FaceDetector.

## 4. Conclusiones

Analizando los resultados de nuestra investigación e implementación en el código, podemos llegar a la conclusión de que las estructuras de datos nos ayudan a almacenar de una forma comoda diversos datos que en estos casos fueron los rostros detectados por nuestro algoritmo utilizando OpenCV, esta vez se logro el objetivo principal que era almacenar los rostros en una Arbol Binario de busqueda. Además recalcar que la interacción entre la IDE y OpenCV facilita en gran parte el poder desarrollar nuestro taller junto a los codigos dados por el profesor, lo que da un avance en la materia de aprendizaje de nuevas tecnologías. Ahora que se tienen las clases necesarias para almacenar correctamente las caras la finalizacion correcta del taller es cada vez más acertada. 

# Anexos

## Anexo A: Instalación librerías OpenCV
   >Se descargo he instalo OpenCV y la carpeta bin se agrego a las variables de entorno del sistema para que el sistema sepa donde ir a ejecutar los binarios referentes a      OpenCV.     

## Anexo B: Instalación de IDE y configuración librerías OpenCV
    >Se descargo he instalo Visual Studio Community 2019. Una vez creado el proyecto vamos a propiedades de este y configuramos las líbrerias de OpenCV en Visual Studio. 
    >Las líbrerias son las siguientes:
    * Del directorio de VC++ (opencv\build\include) y (opencv\build\x64\vc15\lib)
    * En la seccíon general de c++ agregamos el include siguiente (opencv\build\include\opencv2)
    * En dependencias adicionales de la opcion vinculador (opencv_world453d.lib)

# Referecia

1. Solano, G. (2020, 21 enero). Detección de Rostros con Haar Cascades. https://omes-va.com/deteccion-de-rostros-con-haar-cascades-python-opencv/.
2. Murtaza’s Workshop - Robotics and AI. (2020, 13 diciembre). LEARN OPENCV C++ in 4 HOURS [Vídeo]. Youtube. https://youtu.be/2FYm3GOonhk.
3. L.Team. (2021, 19 octubre). Image Resizing with OpenCV | LearnOpenCV #. LearnOpenCV – OpenCV, PyTorch, Keras, Tensorflow Examples and Tutorials. Recuperado 21 de octubre de 2021, de https://learnopencv.com/image-resizing-with-opencv/
