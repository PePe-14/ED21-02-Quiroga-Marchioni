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

La primera función de un reporte técnico es plasmar la información necesaria para que otras personas puedan reproducir el sistema propuesto o puedan entender su fucnionamiento . Para cumplir anterior se debe diferenciar claramente entre los artefactos de diseño e implementación. En el caso de un desarrollo tecnológico los algoritmos son importantes como componente de diseño y los programas generalmente son irrelevantes y deben resumidos o agregados en anexos en el documento. Los programas no son importantes en el documento, salvo si se quiere explicar conceptos expecíficos del lenguaje o del algoritmo implementado.

La redacción debe ser formal y de modo impersonal. No se debe utlizar primera persona del singular o plural. Se debe evitar el uso de cualquier calificativo sustituyéndolo siempre utilizando datos concretos y rastreables en documentos o publicaciones a través de referencias bibliográficas. Por ejemplo, no calificar algo como: "muy importante", "sustancial", "muy usadoo" o "mucho mejor".

Las comparaciones deben concretarse con hechos y datos, sin frases ambiguas o términos generales. Por ejemplo, nunca se debe redactar frases como "el método es mejor que el método B". Lo correcto es decir, el error promedio de el método A es de 5 %, correspondiendo a la mitad del error de 10% obtenido utilizando el método B". El tiempo verbal es usualmente presente. No se debe perder de vista que se está explicando ”como hacer algo”, en vez de ”qué se hizo”. Todo aspecto circunstancial es irrelevante para el documento. Por ejemplo, si se ha desarrollado en el laboratorio X, o en el curso Y, con el profesor Z, etc.

### 1.1 Descripción del problema

Se nos presenta el desafío de construir un programa que reconozca los rostros de personas en imagenes o videos con el fin de identificarlos con un rectangulo rojo para que un guardia tenga la certeza del correcto funcionamiento del código.

### 1.2 Objetivos 

**Objetivo General**

Construir un programa que detecte en una imagen los rostros de las personas y los identifique en un rectángulo rojo.

**Objetivos específicos**

- [x] :+1: Creación del repositorio en github
- [x] :+1: Instalación de Visual Studio 2019 y OpenCV
- [x] :+1: Código de identificacion facial

Los objetivos específicos son acciones específicas que son desarrolladas para lograr cumplir el objetivo general, por ejemplo:

1. Investigar  el  estado  del  arte  de  visión  por  computador  y  audio  para  resolver  tareas de  clasificación unimodal y multimodal aplicado  al  problema  de  reconocimiento  de emociones.
2.  Seleccionar  uno  o  dos  métodos  estudiados  en  el  estado  del  arte  para  la  estimación  de  laemoción utilizando datos unimodales o multimodales.
3.  Implementar los métodos seleccionados utilizando el lenguaje de programación Python y laslibrerías suministradas por Pytorch.
4.  Validar  los  resultados  por  medio  bases  de  datos  especializadas  para  el  desarrollo  deaplicaciones basadas en la estimación de la emoción y que incluyan varios modos de atributoscomo: imágenes, sonido y/o texto.
5.  Proponer  mejoras  a  los  modelos  implementados  para  mejorar  su  desempeño  en  futurasimplementaciones o proyectos de investigación.
6.  Difundir los resultados en medios científicos nacionales o internacionales.

### 1.3 Solución propuesta

Esbozo de la solución propuesta, se espera que esta vaya evolucionando a medida que se avanza en el proyecto.

## 2. Materiales y métodos

Explicar brevemente como se espera desarrollar el trabajo de implementación.

### 2.1 Instalación

Describir brevemente las librerías utilizadas para la instalación y programas utilizados para la ejecución del código. (Agregar una sección de anexo para describir como fueron instaladas las librerías de OpenCV y la IDE utilzada para el trabajo)

### 2.2 Diseño 

Explicar los componentes (módulos o clases) utilizados para resolver el problema. Indicar arquitectura propuesta, diagrama de clases u otro artefacto que estime conveniente para explicar el diseño de su implimentación.

### 2.3 Implementación

Explicar brevemente algunos aspectos de implementación: Por ejemplo, detector de caras utilizado. Se pueden realizar pequeñas reseñas al código para indicar elementos importantes en el trabajo.

Por ejemplo, 

#### Detector de caras

El detector de caras utilizado fue xxx. Para utilizarlo se debe.... El código para detectar una cara en una imagen se muestra a continuación:

```c++
 1. faceCascadePath = "./haarcascade_frontalface_default.xml";
 2. faceCascade.load( faceCascadePath )
 3. std::vector<Rect> faces;
 4. faceCascade.detectMultiScale(frameGray, faces);

 5. for ( size_t i = 0; i < faces.size(); i++ )
 6. {
 7.  int x1 = faces[i].x;
 8.  int y1 = faces[i].y;
 9.  int x2 = faces[i].x + faces[i].width;
10.  int y2 = faces[i].y + faces[i].height;
11. }
```
La primera linea carga el archivo de entrenamiento... etc

## 3. Resultados obtenidos

## 4. Conclusiones

# Anexos

## Anexo A: Instalación librerías OpenCV

## Anexo B: Instalación de IDE y configuración librerías OpenCV

# Referecia

Indicar los libros, páginas web, documentos, etc. Utilizados en el trabajo. Por ejemplo:

1. MONTERO, J.,Metodos matemáticos aplicados a la ganadería.3aed. Sevilla: Ediciones de la pradera,2007.
2. LVARADO,   J.   P.,¿Qué   debe   contener   un   artículo   científico?.http://www.ie.tec.ac.cr/palvarado/pmwiki/index.php/MSc/Art\%c3\%adculoCient\%c3\%adfico. Fe-cha de acceso:13/Nov/2018

