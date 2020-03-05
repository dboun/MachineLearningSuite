#include <cbicaCmdParser.h>

#include "MLSuiteClassification.h"

#include <opencv2/ml.hpp>
#include <yaml-cpp/yaml.h>

#include <iostream>

/** \brief Populates a cv::Mat from a csv file */
cv::Mat readCsv(const std::string& path);

int main(int argc, char *argv[])
{
    // Initialize argument parser
    cbica::CmdParser parser = cbica::CmdParser(argc, argv, "MachineLearningSuite");

    // ---- Required parameters ----

    parser.addRequiredParameter("m", "mode", cbica::Parameter::STRING, 
        "text", "What operation to perform"
    );

    parser.addRequiredParameter("is", "inputsamples", cbica::Parameter::STRING, 
        "text", "Path to the input samples matrix"
    );

    // ---- Optional parameters ----

    parser.addOptionalParameter("ir", "inputresponses", cbica::Parameter::STRING, 
        "text", "Path to the input responses matrix"
    );

    parser.addOptionalParameter("md", "model", cbica::Parameter::STRING, 
        "text", "Path to the model (input for inference, output for training)"
    );

    parser.addOptionalParameter("c", "config", cbica::Parameter::STRING, 
        "text", "Path to the YAML configuration file"
    );

    // ---- Parameter parsing ----
    
    int parserPos; // parser populates this with the position of the argument

    std::string mode;
    std::string inputSamplesPath;
    std::string inputResponsesPath;
    std::string modelPath;
    std::string configPath;

    if ((argc == 1) || (parser.compareParameter("u", parserPos))) {
		parser.echoUsage();
		return EXIT_SUCCESS;
	}

	if (parser.compareParameter("m", parserPos)) {
		mode = argv[parserPos + 1];
	}
    
	if (parser.compareParameter("is", parserPos)) {
		inputSamplesPath = argv[parserPos + 1];
	}

	if (parser.compareParameter("ir", parserPos)) {
		inputResponsesPath = argv[parserPos + 1];
	}

	if (parser.compareParameter("md", parserPos)) {
		modelPath = argv[parserPos + 1];
	}

	if (parser.compareParameter("c", parserPos)) {
		configPath = argv[parserPos + 1];
	}

    // ---- Parameters that are actually required depending on the mode ----

    if (mode == "train" && configPath == "")
    {
        std::cerr << "Please provide the configuration file.\n";
        return EXIT_FAILURE;
    }

    if (mode == "train" && inputResponsesPath == "")
    {
        std::cerr << "Please provide a responses file.\n";
        return EXIT_FAILURE;
    }

    // etc...

    // ---- Invoke ----

    cv::Mat samples = readCsv(inputSamplesPath);

    if (mode == "train")
    {
        cv::Mat responses = readCsv(inputResponsesPath);
        responses.convertTo(responses, CV_32S); // make responses integer
                                                // in the future, you might want to
                                                // support probabilities (regression)
        YAML::Node config = YAML::LoadFile(configPath);

        mlsuite::Classification classification; 
        // I realized way too late that the above doesn't really need
        // to be a class, but anyway..

        try
        {
            classification.Train(samples, responses, config, modelPath);
        }
        catch(const std::exception& e)
        {
            std::cerr << e.what();
            return EXIT_FAILURE;
        }
    }
    // else if (mode == "inference")
    else
    {
        std::cerr << "Invalid mode\n";
        return EXIT_FAILURE;
    }
    
    std::cout << "Finished.\n";
    return EXIT_SUCCESS;
}

cv::Mat readCsv(const std::string& path)
{
    // This is definitely the wrong way to do it,
    // or at least it is very inelegant.
    // Please find the right one.
    // I think this is the correct one
    // https://docs.opencv.org/master/dc/d32/classcv_1_1ml_1_1TrainData.html#ab3264a32194126ff8d6821e76018cde3

    // -2 and 0 in the last 2 args means that everything will be read as train data and no response data.
    // Since we are reading them separately this is fine, we want to load the whole csv each time.
    cv::Ptr<cv::ml::TrainData> tdata = cv::ml::TrainData::loadFromCSV(path,0,-2,0);

    return tdata->getTrainSamples(); // not necessarily the train samples for us, we just 'em all
}