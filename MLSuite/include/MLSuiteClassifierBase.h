#ifndef ClassifierBase_h
#define ClassifierBase_h

#include <opencv2/opencv.hpp>
#include <yaml-cpp/yaml.h>

#include <string>

namespace mlsuite
{
/** \class ClassifierBase
 * \brief Base class to provide a unified way to run
 *  different ML classifiers. 
 * 
 * Every ML classifier is supposed to inherit from this.
 * Methods in here are intenionally not pure virtual 
 * (i.e. ClassifierBase() = 0;) to avoid making
 * the class abstract. If the class is not abstract
 * we can have variables with that class as the type. 
 * That way we can do something like:
 * ClassifierBase* clf = new MLSuiteClassifierSVM();
 * clf->Train(...); // This will call the SVM training.
 * If this doesn't make sense, it might make sense later!
 */
class ClassifierBase
{
public:
    ClassifierBase();
    ~ClassifierBase();

    /** \brief Train a model defined by the configuration
     * 
     * This is a virtual method meant to be overriden by
     * classes that inherit this base class.
     * 
     * \param samples the input samples matrix, rows are samples,
     *  columns are features
     * \param responses 1-column matrix, has the same rows as
     *  samples; every row is the response to the input 
     *  corresponding features
     * \param configuration YAML data structure holding the details
     *  on which model to invoke and with what parameters
     * \param outputModelPath where to save the output model
     */
    virtual void Train(
        cv::Mat& samples, 
        cv::Mat& responses, 
        YAML::Node configuration, 
        std::string outputModelPath
    );

    // TODO: Inference etc
};
}

#endif // ! ClassifierBase_h