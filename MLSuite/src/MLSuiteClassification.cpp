#include "MLSuiteClassification.h"

#include "MLSuiteClassifierBase.h"
#include "MLSuiteClassifierSVM.h"

#include <stdexcept>
#include <memory>

mlsuite::Classification::Classification()
{
    // constructor
}

mlsuite::Classification::~Classification()
{
    // destructor
}

void mlsuite::Classification::Train(
    cv::Mat& samples, 
    cv::Mat& responses, 
    YAML::Node configuration, 
    std::string outputModelPath)
{
    // TODO: Look in the configuration to see
    // which ML algorithm to invoke.
    // Here you don't care about the other parameters.
    // Just pass the input arguments to the correct algorithm.

    // Check if the model type is defined in the configuration
    if (!configuration["model_type"])
    {
        throw std::invalid_argument("No model_type defined in the YAML config");
    }

    // What type of ML model to train
    auto modelType = configuration["model_type"].as<std::string>();

    // This will hold the correct algorithm depending on modelType
    // Don't care too much about shared_ptr, it is just a smart pointer
    // that you don't need to delete. It gets automatically deleted
    // when all the blocks/instances that it gets used go out-of-scope/get deleted.
    std::shared_ptr<mlsuite::ClassifierBase> clf;

    // Initialize clf with the correct classifier
    if (modelType == "svm")
    {
        clf = std::make_shared<mlsuite::ClassifierBase>(
            mlsuite::ClassifierSVM()
        );
    }
    // TODO: else if ... // more classifiers like random forrest etc
    else
    {
        throw std::invalid_argument("Incorrect model_type defined in the YAML config");
    }

    // Do the actual training. clf will be the correct algorithm
    clf->Train(samples, responses, configuration, outputModelPath);
}

cv::Mat mlsuite::Classification::Inference(
    cv::Mat& samples,
    std::string modelPath)
{
    // TODO: Inference (Testing on a trained model)
    // I'm not sure if opencv has it abstracted enough that
    // you can tell it "here is the model and the samples, 
    // give me the predictions".
    // Also in the future you might need more arguments in
    // this function. One example I can think of is if it needs
    // to make class predictions (integers) or pseudo-probability
    // predictions (float in the range [0,1]). Anyway.. :P
}