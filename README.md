# TinyML PCB Defect Detection

## Overview

This project presents a TinyML-based visual defect detection and microcontroller health monitoring system using the ESP32-S3. The system combines camera-based image acquisition, machine learning-based PCB defect detection, and microcontroller health monitoring for real-time edge inspection.

The PCB defect detection model is trained using PCB images and is capable of identifying six different defect classes: Missing Hole, Mouse Bite, Open Circuit, Short, Spur, and Spurious Copper.

In addition to PCB inspection, the project includes an ESP32-S3 health monitoring system that monitors the microcontroller condition using temperature and system parameters and generates a health score from 0–100.

## Features

- PCB defect detection using machine learning
- Six-class PCB defect classification
- ESP32-S3 camera-based image acquisition
- TinyML / Edge AI implementation
- Microcontroller health monitoring
- Temperature monitoring
- Health score generation (0–100)
- Real-time defect localization using bounding boxes
- Model performance evaluation using standard detection metrics

## PCB Defect Classes

The model detects the following PCB defects:

1. Missing Hole
2. Mouse Bite
3. Open Circuit
4. Short
5. Spur
6. Spurious Copper

## Machine Learning Model

The PCB defect detection model was trained using a YOLO-based object detection approach.

### Model Results

- **mAP@0.5:** 0.89
- **Overall Recall:** ~0.91
- **Number of Classes:** 6
- **Class-wise AP:** 0.792 – 0.985

The model was evaluated using Precision-Recall curves, Recall-Confidence curves, and a normalized Confusion Matrix.

## Results and Metrics

### 1. Confusion Matrix

The normalized confusion matrix was used to evaluate the detection performance of the trained model across the six PCB defect classes: **Missing Hole, Mouse Bite, Open Circuit, Short, Spur, and Spurious Copper**.

![Confusion Matrix](Metrics/Confusion%20Matrix.png)

The diagonal values represent correctly detected defect classes, while the off-diagonal values indicate misclassification and background predictions. The results show that the model is able to distinguish the major PCB defect categories, with some confusion occurring for visually similar defects and background regions.

### 2. Precision-Recall Curve

The Precision-Recall curve was used to evaluate the detection performance of the model at different confidence levels. The model achieved an overall **mAP@0.5 of 0.890**, demonstrating effective detection performance across the six PCB defect classes.

![Precision Recall Curve](Metrics/precision%20recall%20curve%20.png)

The class-wise Average Precision values obtained were **0.985 for Missing Hole, 0.832 for Mouse Bite, 0.886 for Open Circuit, 0.946 for Short, 0.792 for Spur, and 0.897 for Spurious Copper**. These results indicate that the model can detect and localize different types of PCB defects with varying levels of accuracy.

### 3. PCB Detection Output

The trained model was tested on PCB images to verify its ability to identify and localize defects. The model generates bounding boxes around detected defects along with the predicted defect class and confidence score.

![PCB Detection Result](Metrics/PCB%20DETECTED%20FINAL%20RESULT.png)

The detection results demonstrate successful identification of defects such as **Missing Hole, Mouse Bite, Open Circuit, Short, Spur, and Spurious Copper** in PCB images. The bounding-box outputs provide the location of the detected defect, making the system suitable for automated visual inspection.

### 4. Overall Discussion

The experimental results demonstrate that the developed machine learning model provides effective multi-class PCB defect detection. The **0.890 mAP@0.5** and class-wise AP values show that the model is capable of detecting different defect patterns from PCB images. The model outputs were further considered for integration with the ESP32-S3-based edge system, along with microcontroller temperature and health monitoring.

The results also indicate that performance can be further improved by increasing the diversity of the training dataset, optimizing image preprocessing, and tuning the detection confidence threshold. The developed system provides a foundation for integrating machine learning-based PCB inspection with embedded edge intelligence.

## ESP32-S3 Health Monitoring

The ESP32-S3 is used as the embedded platform for the project. A camera is used for image acquisition, while temperature and system parameters are monitored to evaluate the operating condition of the microcontroller.

The health monitoring system combines these parameters with the defect detection output to generate a health score between 0 and 100.

## System Workflow

```text
PCB Image
     ↓
Image Acquisition
     ↓
Image Preprocessing
     ↓
ML-Based Defect Detection
     ↓
Defect Classification
     ↓
Confidence Score
     ↓
ESP32-S3 Integration
     ↓
MCU Health Monitoring
     ↓
Health Score (0–100)



### Technologies Used
Python
YOLO
Machine Learning
Computer Vision
TinyML
ESP32-S3
ESP32 Camera
TensorFlow Lite Micro
Arduino IDE
Kaggle


### Future Work
Optimize the trained model for efficient ESP32-S3 deployment
Increase the PCB dataset and add more defect classes
Improve model accuracy and inference speed
Apply model quantization for TinyML deployment
Integrate IoT-based remote monitoring and alerts
Improve microcontroller health monitoring using additional parameters
