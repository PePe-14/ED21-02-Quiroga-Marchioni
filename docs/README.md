![UCN](Imagenes/60x60-ucn-negro.png)


# Informe Técnico 
## Curso: Estructura de datos
### Detección y reidentificación de caras en secuencias de imágenes o video

**Alumnos:**

* Thomas Quiroga Espinoza (Bitacora)
* José Marchioni Clavería (Coordinador)

## Resumen 

>El Taller al que damos comienzo nos pide un sistema de vigilancia en base a reconocimiento de rostros. Para esta entrega en particular se solicita un programa que con ayuda de la biblioteca OpenCV podamos detectar los rostros en pantalla sea en una imagen, video o la cámara del ordenador, marcando esta en un rectángulo de color rojo, con el objetivo de que un guardia o administrador tengan acceso a los datos recopilados. 
>Para lograr este objetivo instalamos la IDE Visual Studio Community 2019 junto a OpenCV e hicimos uso de las librerías que nos permiten usar los archivos que reconocen caras y sus distintas herramientas; estas herramientas se tuvieron que aprender a usar con tutoriales y algunos foros en los que se nos indico que tuvimos que descargar un archivo de extensión .XML para la detección de los rostros. Una vez que obtuvimos todo lo necesario hicimos el código a partir de lo aprendido en los videos y sacamos imágenes de internet para hacer pruebas las cuales resultaron con éxito.

## 1. Introducción

En los últimos años, tecnologías como el reconocimiento automático de rostros y de otras figuras a partir de las cámaras esta cada vez mas presente en la vida diaria por lo que aprender a manipular y comprender estas nuevas tecnologías dará ventaja y nuevo conocimiento a los que se dispongan a estudiarlas. Para dar estos pasos se necesita de alguna necesidad de la que se pueda construir un proyecto, como lo es el caso de este taller que hará mejorar las habilidades y familiarizar conceptos que hasta ahora eran desconocidos

Este taller trata de aprender a usar programas junto con herramientas que facilitan el reconocimiento facial para lograr un objetivo que se define en los puntos posteriores
que tiene que ver con el poder de observar personas por las cámaras con el fin de llevar un registro de sus movimientos dentro de algún lugar. Para llevar a cabo los objetivos que planteamos más adelante se tendrá que recurrir a foros e investigar en detalle como usar las herramientas que nos proporcionan para trabajar de una manera eficiente.
### 1.1 Descripción del problema

Se presenta el desafío de construir un programa que reconozca los rostros de personas en imagenes o videos con el fin de identificarlos con un rectángulo para que un guardia tenga la certeza del correcto funcionamiento del código.

### 1.2 Objetivos 

**Objetivo General**

Construir un programa que detecte en una imagen los rostros de las personas y los identifique en un rectángulo rojo.

**Objetivos específicos**

- [x] :+1: Creación del repositorio en Github
- [x] :+1: Instalación de Visual Studio 2019 y OpenCV
- [x] :+1: Investigar como se reconocen rostros
- [x] :+1: Código de identificacion facial

Los objetivos específicos son acciones específicas que son desarrolladas para lograr cumplir el objetivo general, por ejemplo:

1. La creación de un repositorio en Github para poder ver en tiempo real el avance del taller.
2. Descargar e instalar los programas que nos proporcionan.
3. Investigar la configuración de los programas entre si para su correcto funcionamiento.
4. Plantearse la metodología a seguir durante el proyecto. 
5. Averiguar como funciona el reconocimiento facial y las herramientas necesarias para hacer un uso correcto.
6. Aplicar lo aprendido construyendo un código que reconozca los rostros.

### 1.3 Solución propuesta

Construir un código que permita reconocer rostros a partir de un archivo de extensión .XML que tiene en su implementación cumplir este objetivo y luego de esto mostrarle al usuario la imagen con los rostros señalados con el rectángulo rojo para probar que el algoritmo funciona.

## 2. Materiales y métodos

* IDE Visual Studio Community 2019 
* Biblioteca OpenCV
* Archivo haarcascade_frontalface_default.xml 
* Imagen de rostros

Configurando adecuandamente la IDE con OpenCV se logrará el primer paso para hacer uso de las librerias de esta y junto a la orientacion a objetos buscar y manipular los archivos necesarios para el analisis de las imágenes que se usarán. 
Luego haremos uso del archivo .XML que tiene como objetivo reconocer las caras en las imágenes y asi podremos saber donde ubicar los rectángulos.

### 2.1 Instalación

* IDE Visual Studio Community 2019: Es una IDE que tendrá todo el código del taller en el que se harán las pruebas de código hasta completar el objetivo.  
* Biblioteca OpenCV: Líbrería libre de visión artificial que cuenta con la mayoria de las herramientas y líbrerias para una correcta compatibilidad con la IDE.
* Archivo haarcascade_frontalface_default.xml: Archivo clasificador pre entrenado que es capaz de reconocer rostros y otras formas.

### 2.2 Diseño 

La manera en que diseñamos el taller para la primera historia es simple porque no contiene muchas clases, así que procedere a nombrarlas y explicar su rol en el código
* Clase Mat: Puede guardar matrices de varias dimesiones por lo que nosotros la usamos para guardar las imagenes.
* Clase CascadeClassifier: Crea objetos de tipo clasificadores de cascada que en resumen se necesitan muchas imagenes para entrenar a esta función para saber identificar objetos. Esto sera utilizado para cargar el archivo que reconoce los rostros.
* Clase Rect:  Puede declarar un tipo de variable que permite dibujar zonas rectangulares. Claramente esta clase nos servirá para crear los rectángulos rojos en las imágenes.

### 2.3 Implementación
 

#### Detector de rostros

El archivo detector de caras utilizado fue haarcascade_frontalface_default.xml. Para utilizarlo se debe crear un objeto que contenga este archivo, por lo que la clase que lo puede contener es CascadeCalssifier;
El código para detectar una cara en una imagen se muestra a continuación:

    CascadeClassifier faceCascade;
    faceCascade.load("haarcascade_frontalface_default.xml");

    vector<Rect> faces;
    faceCascade.detectMultiScale(img,faces,1.1,10);

En estas cuatro líneas se observa que el archivo .XML se carga a su correspondiente objeto y luego se crea una lista de rectangulos en la que con la ultima linea de codigo todas las caras que fueron detectadas tendran asignado un objeto tipo rectangulo.

#### Creacion de los rectangulos
    
    for (int i = 0; i < faces.size(); i++)
    {
        rectangle(img, faces[i].tl(), faces[i].br(), Scalar(0, 0,255),3);
    }
   El primero parametro de la funcion rectangulo es la image analisada, luego los 2 parametros siguientes son las escalas del rectangulo y por ultimo el color que en este caso sería rojo como se pidío.


## 3. Resultados obtenidos

Una vez terminada la ejecución del programa esta nos arroja la imagen que habiamos preseleccionado cuyo contenido eran cinco personas pero con la diferencia de que ahora estarían identificadas por el código, mostrando asi cinco rectángulos rojos en cada rostro.

## 4. Conclusiones

Analisando los resultados como grupo podemos decir que nuestra investigacion, comunicación como equipo y metodología usadas han sido exitosas ya que se obtuvieron los resultados esperados queriendo decir que se cumplio el objetivo general planteado anteriormente. Además recalcar que la interaccion entre la IDE y OpenCV facilita en gran parte el poder desarrollar nuestro taller, lo que da un avance en la materia de aprendizaje de nuevas tecnologías. 

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
