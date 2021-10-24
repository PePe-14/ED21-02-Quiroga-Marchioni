![UCN](Imagenes/60x60-ucn-negro.png)


# Informe Técnico 
## Curso: Estructura de datos
### Detección y reidentificación de caras en secuencias de imágenes o video

**Alumnos:**

* Thomas Quiroga Espinoza (Bitacora)
* José Marchioni Clavería (Coordinador)

## Resumen 

>Para la segunda entrega del taller se nos pide un sistema de vigilancia en base a reconocimiento de rostros. Para esta entrega en particular se solicita crear una lista enlazada y un programa utilizando OpenCV, para detectar los rostros en pantalla, ya sea en una imagen, video o la cámara del ordenador, esta  maracara el rostro en un rectángulo de color rojo, con el objetivo de que un guardia o administrador tengan acceso a los datos recopilados. 
>Para lograr este objetivo hicimos uso de la programacion orientada a objetos ya que necesitaremos almacenar los rostros de las personas y luego añadirlas a una LinkedList.Una vez que obtuvimos todo lo necesario debemos calcular el tiempo de cinco caras que aparezcan mas tiempo en el video.

## 1. Introducción

En los últimos años, tecnologías como el reconocimiento facial y de otras figuras a partir de las cámaras estan cada vez mas presente en la vida diaria, por lo que aprender a manipular y comprender estas nuevas tecnologías dará ventaja y nuevo conocimiento a los que se dispongan a estudiarlas. La mejor forma de aprender como reconocer rostros es con la investigacion, practica e implementacion de lo aprendido en codigo, como lo es el caso de este taller que hará perfeccionar las habilidades actuales y familiarizar conceptos que hasta ahora eran desconocidos.

En esta entrega aplicaremos los conseptos aprendidos de lo que es una lista enlazada, y se veran implementados dentro del codigo, ya que necesitamos almacenar los rostros que fueron correctamente detectado por el algoritmo, estos se veran diferenciados con un rectangulo rojo, a su vez al finalizar se veran las 5 identidades del video que estuvieron mas tiempo detectadas.

### 1.1 Descripción del problema

Se presenta el desafío de construir un programa que reconozca los rostros que se muestran con mayor tiempo en el video y los almacene en una Lista enlazada.

### 1.2 Objetivos 

**Objetivo General**

Construir un programa que almacene en una Linked List los cinco rostros que aparecen con mas tiempo en el video.

**Objetivos específicos**

- [x] :+1: Crear el código para reconocer rostros en videos.
- [x] :+1: Crear las clases Persona,Nodo y Linked_List.
- [x] :+1: Investigar como asociar un rostro capturado a un objeto persona.
- [x] :+1: Almacenar los rostros de las personas en la Linked_List.
- [x] :+1: Crear el código para que calcule el tiempo en pantalla de un rostro.

1. Un código esencial es el que detecta las matrices(rostros).
2. La clase persona deberá contener un atributo unico para identificarlo y además un atributo de tiempo.
3. Relacionar las clases con las librerias de OpenCV.
4. Investigar el formato en que estan los rostros capturados por OpenCV para poder asociarlos a la clase persona. 
5. Averiguar como calcular el tiempo que transcurre un rostro en el video.
6. Establecer un orden descendente de los rostros por el tiempo transcurrido en el video.

### 1.3 Solución propuesta

Construir una Linked List que almacene objetos tipo Persona que tendrán un atributo con el formato en que son reconocidos los rostros y una vez guardados comparar cuanto tiempo aparecen en el video y sumarle ese tiempo a otro atributo que medira el tiempo. Una vez terminado el video el programa tendra ordenado los rostros de manera descendente en relación a cuanto tiempo se mostraron en el video.

## 2. Materiales y métodos

* IDE Visual Studio Community 2019 
* Biblioteca OpenCV
* Archivo haarcascade_frontalface_default.xml 
* Video con rostros
* Clase Persona, Nodo_Persona y Linked_List.

Con el uso de la clase Mat de OpenCV podremos capturar la imagen del rostro con el archivo "haarcascade_frontalface_default.xml" y asignarlo como atributo (tipo Mat) a un objeto de tipo persona que se creara al momento de encontrar el rostro. Luego se agregará el objeto persona a la Linked List.

### 2.1 Instalación

* IDE Visual Studio Community 2019: Es una IDE que tendrá todo el código del taller en el que se harán las pruebas de código hasta completar el objetivo.  
* Biblioteca OpenCV: Líbrería libre de visión artificial que cuenta con la mayoria de las herramientas y líbrerias para una correcta compatibilidad con la IDE.
* Archivo haarcascade_frontalface_default.xml: Archivo clasificador pre entrenado que es capaz de reconocer rostros y otras formas.

### 2.2 Diseño 

La manera en que diseñamos el taller para la primera historia es simple porque no contiene muchas clases, así que procedere a nombrarlas y explicar su rol en el código
* Clase Mat: Puede guardar matrices de varias dimesiones por lo que nosotros la usamos para guardar las imagenes de las caras.
* Clase CascadeClassifier: Crea objetos de tipo clasificadores de cascada que en resumen se necesitan muchas imagenes para entrenar a esta función para saber identificar objetos. Esto sera utilizado para cargar el archivo que reconoce los rostros.
* Clase Rect:  Puede declarar un tipo de variable que permite dibujar zonas rectangulares. Claramente esta clase nos servirá para crear los rectángulos rojos en las imágenes.
* Clase Persona: Se guardará a la persona con un codigo unico, el tiempo que aparecio en el video y con la imagen del rostro de tipo Mat.
* Clase Nodo_Persona: Clase que contendrá como atributo una Persona y un puntero a el siguiente nodo.
* Clase ListaPersonas: Linked_List que almacenara objetos tipo persona cuando el código capture un rostro, además la lista estará ordenada de manera descendente de acuerdo al timepo que hayan sido detectadas por el programa.

### 2.3 Implementación
 
#### Almacenar rostros

La clase Personas fue creada con el objetivo de almacenar los rostros detectados en le video y guardar los segundos y el rostro de la persona.

#### Linked List

Esta clase fue necesaria para almacenar mas de un solo rostro y se apoya de la clase nodos que almacena una persona y además tiene una funcion que calcula las cinco personas que se muestran con mas frecuencia.
	
	void cincoPersonasMasTiempo() {
		int* tiempoPrimero = 0;
		Mat primero;
		int* tiempoSegundo = 0;
		Mat segundo;
		int* tiempoTercero = 0;
		Mat tercero;
		int* tiempoCuarto = 0;
		Mat cuarto;
		int* tiempoQuinto = 0;
		Mat quinto;

		Nodo* current = first;
		while (current != NULL) {
			int* tiempoCurrent = (*current).getPersona()->getTiempo();
			Mat codigoCurrent = (*current).getPersona()->getImagen();
			...(continua)

*Este codigo no se alcanzo a utilizar ya que no se pudo hacer una distinción de los rostros que se capturaban, por lo que todos los tiempos en la pantalla eran iguales. Practicamente lo que hacia era comparar los tiempos y luego asignar su correspondiente imagen tipo Mat.* 

#### Capturar rostro
El código a continuación captura las coordenadas donde se encontro el rostro y descompone la imagen en una matriz para poder asignarle el rectangulo rojo y despues agregar la captura a un archivo. 

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

#### Ingresa una persona a la Linked List
Esta clase tiene la funcion de verificar que el rostro detectado no haya sido detectado con anterioridad, si es un rostro nuevo es ingresado a la linked list, pero ya que el programa no distingue los rostros, todos son considerados nuevos.

	void add(Persona* persona) {
		Nodo* node = new Nodo(persona);

		if (first == NULL) {
			first = node;
		}
		else {
			Nodo* current = first;
			while (current->getNext() != NULL) {
				current = current->getNext();
			}
			current->setNext(node);
		}
		cout << "Se agrego: ";
	}
	
	
#### Detector de rostros

El archivo detector de caras utilizado fue haarcascade_frontalface_default.xml. Para utilizarlo se debe crear un objeto que contenga este archivo, por lo que la clase que lo puede contener es CascadeCalssifier;
El código para detectar una cara en una imagen se muestra a continuación:

    CascadeClassifier faceCascade;
    faceCascade.load("haarcascade_frontalface_default.xml");

    vector<Rect> faces;
    faceCascade.detectMultiScale(img,faces,1.1,10);

*En estas cuatro líneas se observa que el archivo .XML se carga a su correspondiente objeto y luego se crea una lista de rectangulos en la que con la ultima linea de codigo todas las caras que fueron detectadas tendran asignado un objeto tipo rectangulo.*

#### Creacion de los rectangulos
    
    Point pt1(faces[i].x, faces[i].y);
    Point pt2((faces[i].x + faces[i].height), (faces[i].y + faces[i].width));
    rectangle(img, pt1, pt2, Scalar(0, 0, 255), 2, 8, 0);
    
   *Modificamos la manera de hacer los rectángulos y ahora se uso la clase Point para fijar las medidas del rectangulo que se formará en la cara analizada y en el cuarto parametro ponemos el color que en este caso sería rojo como se pidío.*

## 3. Resultados obtenidos

Una vez terminada la ejecución del programa esta nos arroja el video donde señala a la mayoria de las caras que alli aparecen y además por consola se escribe el nombre de la imagen que acaba de ser capturada y con un mensaje de que un objeto persona que se ha creado a partir de esta captura ha sido ingresada a la Linked List de Personas. Las imágenes son capturadas en cada frame y no supimos como cambiar esta configuración.

## 4. Conclusiones

Analizando los resultados de nuestra investigación e implementación en el código, podemos llegar a la conclusión de que las estructuras de datos nos ayudan a almacenar de una forma comoda diversos datos que en estos casos fueron los rostros detectados por nuestro algoritmo utilizando OpenCV, esta vez no logramos todos los objetivos, pero si entendimos de mejor manera el funcionamiento de los conocimientos adquiridos. Además recalcar que la interacciÓn entre la IDE y OpenCV facilita en gran parte el poder desarrollar nuestro taller, lo que da un avance en la materia de aprendizaje de nuevas tecnologías. 

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
