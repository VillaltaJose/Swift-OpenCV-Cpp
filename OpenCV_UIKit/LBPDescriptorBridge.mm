#import <opencv2/opencv.hpp>
#import <opencv2/imgcodecs/ios.h>
#import <Foundation/Foundation.h>
#import "LBPDescriptorBridge.h"
#include "LBPDescriptor.hpp"

@implementation LBPDescriptorBridge {
    LBPDescriptor *descriptor; // Instancia de la clase LBPDescriptor
}

- (instancetype)init {
    self = [super init];
    if (self) {
        descriptor = new LBPDescriptor();
    }
    return self;
}

- (UIImage *)applyFilter:(UIImage *)image {
    cv::Mat matImage;
    UIImageToMat(image, matImage, true);

    if (!matImage.empty()) {
        cv::Mat result = descriptor->detectObjects(matImage);
        return MatToUIImage(result);
    }
    return image; // Devolver la imagen original si hay un error
}

- (void *)loadClassifier:(NSString *)classifierPath {
    std::string path = [classifierPath UTF8String];
    if (descriptor->loadClassifier(path)) {
        return static_cast<void *>(descriptor);
    }
    return NULL;
}

- (UIImage *)detectObjectsInImage:(UIImage *)image withClassifier:(void *)classifier {
    cv::Mat matImage;
    UIImageToMat(image, matImage, true);

    if (!matImage.empty()) {
        cv::Mat result = static_cast<LBPDescriptor *>(classifier)->detectObjects(matImage);
        return MatToUIImage(result);
    }
    return image; // Devolver la imagen original si hay un error
}

- (void)dealloc {
    delete descriptor;
}

@end
