#include <opencv2/opencv.hpp>
#include <opencv2/objdetect.hpp>
#include <string>

class LBPDescriptor {
public:
    LBPDescriptor();
    ~LBPDescriptor();

    bool loadClassifier(const std::string& classifierPath);
    cv::Mat detectObjects(const cv::Mat& frame);

private:
    cv::CascadeClassifier cascade_;
};
