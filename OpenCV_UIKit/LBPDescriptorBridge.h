#import <Foundation/Foundation.h>
#import <UIKit/UIKit.h>

@interface LBPDescriptorBridge : NSObject

- (UIImage *)applyFilter:(UIImage *)image;

- (void *)loadClassifier:(NSString *)classifierPath;

- (UIImage *)detectObjectsInImage:(UIImage *)image withClassifier:(void *)classifier;

@end
