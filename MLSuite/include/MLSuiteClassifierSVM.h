#ifndef MLSuiteClassifierSVM_h
#define MLSuiteClassifierSVM_h

#include "MLSuiteClassifierBase.h"

namespace mlsuite
{
class ClassifierSVM : public ClassifierBase
{
public:
    ClassifierSVM();
    ~ClassifierSVM();

    void Train(
        cv::Mat& samples, 
        cv::Mat& responses, 
        YAML::Node configuration, 
        std::string outputModelPath
    ) override; // -> we override the virtual method
                //    from the base class
};
}

#endif // ! MLSuiteClassifierSVM_h