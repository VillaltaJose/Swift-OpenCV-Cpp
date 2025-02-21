#include "LBPDescriptor.hpp"
#include <iostream>

LBPDescriptor::LBPDescriptor() {}

LBPDescriptor::~LBPDescriptor() {}

bool LBPDescriptor::loadClassifier(const std::string& classifierPath) {
    if (!cascade_.load(classifierPath)) {
        std::cerr << "Error al cargar el clasificador" << std::endl;
        return false;
    } else {
        std::cerr << "Clasificador cargado con éxito" << std::endl;
        return true;
    }
}

cv::Mat LBPDescriptor::detectObjects(const cv::Mat& frame) {
    cv::Mat gray, resizedGray, outputFrame;

    // Convertir a escala de grises
    cv::cvtColor(frame, gray, cv::COLOR_BGR2GRAY);

    // Redimensionar la imagen para mejorar la detección
    cv::resize(gray, resizedGray, cv::Size(gray.cols / 2, gray.rows / 2));

    std::vector<cv::Rect> objects;

    // Detección optimizada
    cascade_.detectMultiScale(resizedGray, objects, 1.2, 3, cv::CASCADE_SCALE_IMAGE, cv::Size(30, 30));

    // Asegurar que la imagen de salida tenga 3 canales (BGR)
    if (frame.channels() == 1) {
        cv::cvtColor(frame, outputFrame, cv::COLOR_GRAY2BGR);
    } else if (frame.channels() == 4) {
        cv::cvtColor(frame, outputFrame, cv::COLOR_BGRA2BGR);
    } else {
        outputFrame = frame.clone();
    }

    // Ajustar coordenadas de detección
    for (auto& obj : objects) {
        obj.x *= 2;
        obj.y *= 2;
        obj.width *= 2;
        obj.height *= 2;
    }

    // Dibujar rectángulos con borde rojo sin relleno
    cv::Scalar rectColor(0, 0, 255); // Rojo brillante
    for (const auto& obj : objects) {
        cv::rectangle(outputFrame, obj, rectColor, 2, cv::LINE_AA); // Borde más delgado y antialiasing
    }

    return outputFrame;
}
