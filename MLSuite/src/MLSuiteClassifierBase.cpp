#include "MLSuiteClassifierBase.h"

mlsuite::ClassifierBase::ClassifierBase()
{
    std::cerr << "ClassifierBase methods are not "
              << "supposed to be invoked directly.\n";
}

mlsuite::ClassifierBase::~ClassifierBase()
{
    std::cerr << "ClassifierBase methods are not "
              << "supposed to be invoked directly.\n";
}

void mlsuite::ClassifierBase::Train(
    cv::Mat& samples, 
    cv::Mat& responses, 
    YAML::Node configuration, 
    std::string outputModelPath)
{
    std::cerr << "ClassifierBase methods are not "
              << "supposed to be invoked directly.\n";
}