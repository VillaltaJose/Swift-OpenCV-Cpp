# **Informe del Proyecto Integrador de Visión por Computador**
## **Detección de Símbolos de STOP y Paso de Cebra usando LBP y Clasificador en Cascada**

### **1. Introducción**
Este proyecto implementa un sistema de detección de señales de tránsito, específicamente **STOP** y **Paso de Cebra**, utilizando la técnica **Local Binary Patterns (LBP)** y el entrenamiento de un **Clasificador en Cascada de OpenCV**. Se desarrolló un modelo basado en aprendizaje supervisado con el objetivo de detectar estos símbolos en tiempo real a partir de imágenes o video.

---

### **2. Dataset Utilizado**
Para el entrenamiento, recopilamos un total de **8000 imágenes**:
- **4000 imágenes positivas** con los símbolos de STOP y Paso de Cebra, generadas con **RoboFlow** y exportadas en formato **YOLO Darknet**.
- **4000 imágenes negativas** que incluyen diversos entornos sin los símbolos objetivo.

Las imágenes positivas se convirtieron en el formato adecuado para el entrenamiento del clasificador en cascada.

```shell
opencv_createsamples -info positives.txt -num 3900 -w 24 -h 24 -vec positives.vec
