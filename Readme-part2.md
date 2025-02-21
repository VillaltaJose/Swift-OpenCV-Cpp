![Swift-OpenCV-Cpp](https://socialify.git.ci/VillaltaJose/Swift-OpenCV-Cpp/image?font=Bitter&language=1&name=1&owner=1&pattern=Plus&stargazers=1&theme=Light)

# **Final Report: Computer Vision Integrative Project**
## **Detection of STOP and Pedestrian Crossing Signs Using LBP and Cascade Classifier**
This project implements a traffic sign detection system, specifically **STOP** and **Pedestrian Crossing** signs, using the **Local Binary Patterns (LBP)** technique and training an **OpenCV Cascade Classifier**. A supervised learning model was developed to detect these symbols in real time from images or video.

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

Positive images were converted into the appropriate format for cascade classifier training.

```
opencv_createsamples -info positives.txt -num 3900 -w 24 -h 24 -vec positives.vec
```
