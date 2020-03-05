#include "MLSuiteClassifierBase.h"

mlsuite::MLSuiteClassifierBase::MLSuiteClassifierBase()
{
    std::cerr << "MLSuiteClassifierBase methods are not "
              << "supposed to be invoked directly.\n";
}

mlsuite::MLSuiteClassifierBase::~MLSuiteClassifierBase()
{
    std::cerr << "MLSuiteClassifierBase methods are not "
              << "supposed to be invoked directly.\n";
}

void mlsuite::Train(
    cv::Mat& samples, 
    cv::Mat& responses, 
    YAML::Node configuration, 
    std::string outputModelPath)
{
    std::cerr << "MLSuiteClassifierBase methods are not "
              << "supposed to be invoked directly.\n";
}