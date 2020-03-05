#include "MLSuiteClassifierSVM.h"

#include <opencv2/ml.hpp>
#include <opencv2/core/types.hpp>

mlsuite::ClassifierSVM::ClassifierSVM()
{

}

mlsuite::ClassifierSVM::~ClassifierSVM()
{

}

void mlsuite::ClassifierSVM::Train(
    cv::Mat& samples, 
    cv::Mat& responses, 
    YAML::Node configuration, 
    std::string outputModelPath)
{
    // TODO

    // ---- Find kernel ----

    // Defining a kernel for the SVM is mandatory
    if (!configuration["kernel"])
    {
        throw std::invalid_argument("No kernel defined for the SVM in the YAML config");
    }

    std::string kernel = configuration["kernel"].as<std::string>();

    // ---- Settle hyperparameters ----

    // SVMs have various hyperparameters depending on the kernel
    // C is one of them. Support for the other will have to be here too

    double c = 1; // if C is not defined, assume =1

    if (configuration["c"])
    {
        c = configuration["c"].as<double>();
    }

    // TODO: The same for more hyperparameters

    // ---- Settle extra options ----

    // There are more options that OpenCV provides for SVMs
    // that are not just "train with that kernel and those hyperparameters".
    // Some of these are "train_auto" which does cross-validation internally
    // to find the optimal hyperparameters, grid search is another one,
    // which tests various pre-defined values to judge which hyperparameters
    // are the best, balanced subsamples etc
    
    // It should be noted though, that all of these + the hyperparameters
    // are a looot of stuff but not everything is necessarily needed or will be 
    // used. Linear and RBF are the most important kernels. 
    // train_auto is also important, but just with the default paramgrids

    // ---- Actual training ----

    // OpenCV expects samples + responses in the same mat
    cv::Ptr<cv::ml::TrainData> trainData = cv::ml::TrainData::create(
        samples, cv::ml::ROW_SAMPLE, responses
    );

    // The classifier
    auto clf = cv::ml::SVM::create();

    if (kernel == "linear")
    {
        // General options
        clf->setKernel( cv::ml::SVM::KernelTypes::LINEAR );
        clf->setType( cv::ml::SVM::C_SVC ); // we don't really care about the other types
        clf->setTermCriteria( cv::TermCriteria(cv::TermCriteria::MAX_ITER, 100, 1e-6) );
        //clf->setClassWeights(mWeightsMat); // big story, look into this. should be optional.
        
        // Classic options (if no cross-validation etc)
        clf->setC(c);
        // ...

        // Advanced options
        // ...
    }

    // ---- Actual training ----
    bool res = false;
    try
    {
        // if train and not train_auto
        res = clf->train(trainData);
    }
    catch (cv::Exception ex) {
        std::cerr << ex.what();
        throw std::invalid_argument("Failed to train SVM model with the input provided");
    }

    // Save model
    clf->save(outputModelPath);
}