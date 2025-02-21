![Swift-OpenCV-Cpp](https://socialify.git.ci/VillaltaJose/Swift-OpenCV-Cpp/image?font=Bitter&language=1&name=1&owner=1&pattern=Plus&stargazers=1&theme=Light)

# **Final Report: Computer Vision Integrative Project**
## **Detection of STOP and Pedestrian Crossing Signs Using LBP and Cascade Classifier**
This project implements a traffic sign detection system, specifically **STOP** and **Pedestrian Crossing** signs, using the **Local Binary Patterns (LBP)** technique and training an **OpenCV Cascade Classifier**. A supervised learning model was developed to detect these symbols in real time from images or video.

Traffic sign recognition is a crucial task in computer vision, with applications in autonomous driving and assistive technologies. This project focuses on detecting **STOP** and **Pedestrian Crossing** signs using a **Cascade Classifier trained with Local Binary Patterns (LBP)**. 

The methodology involves:
- Dataset preparation using labeled images.
- Feature extraction with LBP.
- Training a cascade classifier with OpenCV.
- Real-time object detection with a webcam.

The goal is to develop a **lightweight and efficient model** that can detect these symbols in real-time under various conditions.

## Authors

- José Villalta - [@VillaltaJose](https://www.github.com/VillaltaJose)
- Daniel Collaguazo - [@DanielCollaguazo2003](https://www.github.com/DanielCollaguazo2003)


## Prerequisites

To run this project, you will need the following:

1. **OpenCV Framework for iOS and Swift:** OpenCV is required for image processing. You can download the appropriate version for iOS from the [OpenCV SourceForge page](https://sourceforge.net/projects/opencvlibrary/). Make sure to verify the compatibility of the version you select with your development environment.

1. **MobileVLCKit Framework:** MobileVLCKit is necessary for capturing RTSP streams. You can find the desired release version on the [MobileVLCKit artifacts page](https://artifacts.videolan.org/VLCKit/MobileVLCKit/). Ensure the version you choose aligns with your project requirements.## How It Works
### Swift Code Overview
The Swift code is located in the main view `OpenCV_UIKit/ViewController.swift`.

#### Key UI Elements  
The UI contains the following key components:  
  
- **Segment**: Determines whether the processed frame comes from the device's camera or the RTSP camera.  
- **TextField**: Used to input the URL for the RTSP camera stream.  
- **ImageViews**:  
  - `imageView`: Dedicated to displaying frames from the RTSP camera. Due to the functionality of the MobileVLCKit library, this `imageView` is used to render the RTSP stream (explained further below).  
  - `processedImageView`: Displays the frame processed by the OpenCV filter.  

#### Important Functions  
The following functions must be modified if you want to apply a different filter. At the end of each function, the frame is processed using OpenCV:  

1. **`captureOutput`**:  
   Processes frames from the device's camera.  

2. **`processCapturedFrame`**:  
   Processes frames from the RTSP camera.  
   Since MobileVLCKit does not provide a direct method to access frames, the RTSP content is first rendered in the `imageView`. The frame is then captured from this `imageView`, passed to OpenCV for processing, and the result is displayed in the `processedImageView`.
---

### **Dataset Used**
For training, we collected a total of **8,000 images**:
- **4,000 positive images** containing STOP and Pedestrian Crossing symbols, generated using **RoboFlow** and exported in **YOLO Darknet** format.
- **4,000 negative images** with various environments that do not include the target symbols.

### **Theoretical Background**
#### **Local Binary Patterns (LBP)**
LBP is a **texture descriptor** widely used in image classification and object detection. It encodes the **local structure of an image** by comparing each pixel with its surrounding neighbors.

##### **LBP Calculation:**
1. Select a **central pixel** in a `3×3` neighborhood.
2. Compare it with its 8 surrounding pixels.
3. Assign `1` if the neighbor is greater than or equal to the center, otherwise `0`.
4. Convert the binary sequence into a **decimal value**.

Example for a `3×3` window:


```

Thresholding: 120 135 150 115 130 140 → (Threshold with 130) 100 105 110

Binary Code: 0 1 1 0 (130) 1 → (01110100)₂ = 116 0 0 0

```

This process is repeated across the entire image to generate an **LBP feature map**, which is then used for classification.

#### **Cascade Classifier**
A **cascade classifier** is a machine learning algorithm based on **Haar-like features or LBP**. It works in **stages**, where simple classifiers are applied sequentially. If an object fails at any stage, it is immediately **discarded**, making the model **efficient**.

##### **Training Process:**
1. Extract features using **LBP** from **positive (signs) and negative (random scenes) images**.
2. Train weak classifiers using **Adaboost**.
3. Combine classifiers in a **cascade**, filtering out negatives progressively.
4. The final classifier is a **strong ensemble model** capable of real-time detection.

### **Dataset Preparation**
The dataset consists of **8,000 images**, split into:
- **4,000 positive samples** (STOP and Pedestrian Crossing signs).
- **4,000 negative samples** (random backgrounds without signs).

#### **Image Collection and Annotation**
- Positive images were generated using **RoboFlow** and exported in **YOLO Darknet** format.
- Negative images were manually collected from various environments.

#### **Sample Images**
Below are sample images from each category:

| **STOP Sign** | **Pedestrian Crossing Sign** |
|--------------|-----------------------------|
| ![STOP Sign Sample](./stop1.jpg) | ![Pedestrian Crossing Sample](./zebra1.jpg) |
| ![STOP Sign Sample](./stop2.jpg) | ![Pedestrian Crossing Sample](./zebra2.jpg) |

| **Negative Samples (No Signs)** |
|--------------------------------|
| ![Negative Sample](./neg1.jpg) |
| ![Negative Sample](./neg2.jpg) |

#### **Conversion to OpenCV Format**
Since OpenCV requires a specific format for training, we **converted YOLO annotations** into an OpenCV-compatible `.txt` file.

Command used to convert positive samples:
```
opencv_createsamples -info positives.txt -num 3900 -w 24 -h 24 -vec positives.vec
```

Command used for negative samples:

```
find ./DatasetNegative/ -iname "*.jpg" > dataset.txt
```

### **Training the Cascade Classifier**

The model was trained using `opencv_traincascade` with **LBP features**:

```
opencv_traincascade -data cascade/ -vec positives.vec -bg dataset.txt -numPos 3700 -numNeg 4000 -numStages 20 -w 24 -h 24 -featureType LBP

```

#### **Training Parameters**

-   `numPos 3700`: Number of positive samples used.
-   `numNeg 4000`: Number of negative samples used.
-   `numStages 20`: Number of training stages.
-   `featureType LBP`: Used LBP instead of Haar features.
-   `w 24 -h 24`: Resized all images to `24x24` pixels.

#### **Training Results**

-   The training reached **19 stages**, with a high **hit rate (HR)** and decreasing **false alarm rate (FA)**.
-   Achieved **>99% accuracy** on training data.

##### **Training Evolution Graphs**

-   **Detection Rate Evolution**  
    ![Detection Rate](./evi1.png)
    
-   **False Alarm Rate Evolution**  
    ![False Alarm Rate](./evi2.png)
    

## **Results and Evaluation**

The final system was tested under different lighting conditions and angles. **Detection results:**

-   **High accuracy in controlled environments**.
-   **Reduced false positives** due to **LBP robustness**.
-   **Real-time performance with low computational cost**.

### **Example Detection**

Below are two examples of object detection using the implemented system:

#### **Example 1**
![Detection Example 1](path/to/your/image1.png)

#### **Example 2**
![Detection Example 2](path/to/your/image2.png)

> *Figure 6.1: Examples of detected objects with bounding boxes.*

