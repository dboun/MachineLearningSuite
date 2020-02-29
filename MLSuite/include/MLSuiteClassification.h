#ifndef MLSuiteClassification_h
#define MLSuiteClassification_h

#include <opencv2/opencv.hpp>

#include <string>

namespace mlsuite
{
/** \class Classification
 * \brief Entry point for machine learning operations.
 * 
 * The operations are described by a YAML configuration
 * and are performed on input opencv matrices
 */
class Classification
{
public:
    Classification();
    ~Classification();

    /** \brief Train a model defined by the configuration
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
    void Train(
        cv::Mat& samples, 
        cv::Mat& responses, 
        YAML::Node configuration, 
        std::string outputModelPath
    );

    /** \brief Make predictions using a trained model
     * 
     * \param samples the input samples matrix, rows are samples,
     *  columns are features
     * \param modelPath where to find the input model
     * \return 1-d column matrix, has the same
     *  rows as samples; every row is the prediction to the 
     *  input features 
     */
    cv::Mat Inference(
        cv::Mat& samples,
        std::string modelPath
    );

    // TODO: Cross-validation
    
    // TODO: Split train/test
};
}

#endif // ! MLSuiteClassification_h