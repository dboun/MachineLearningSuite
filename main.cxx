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

    parser.addRequiredParameter("ir", "inputresponses", cbica::Parameter::STRING, 
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

    if ((argc == 1) || (parser.compareParameter("u", tempPosition))) {
		parser.echoUsage();
		return EXIT_SUCCESS;
	}

	if (parser.compareParameter("m", tempPosition)) {
		mode = argv[tempPosition + 1];
	}
    
	if (parser.compareParameter("is", tempPosition)) {
		inputSamplesPath = argv[tempPosition + 1];
	}

	if (parser.compareParameter("ir", tempPosition)) {
		inputResponsesPath = argv[tempPosition + 1];
	}

	if (parser.compareParameter("md", tempPosition)) {
		modelPath = argv[tempPosition + 1];
	}

	if (parser.compareParameter("c", tempPosition)) {
		configPath = argv[tempPosition + 1];
	}

    // ---- Parameters that are actually required depending on the mode ----

    if (mode == "train" && configPath == "")
    {
        std::cerr << "Please provide the configuration file.\n";
        return EXIT_FAILURE;
    }

    // etc...

    // ---- Invoke ----

    cv::Mat samples = readCsv(inputSamplesPath);

    if (mode == "train")
    {
        cv::Mat responses = readCsv(inputResponsesPath);
        YAML::Node config = YAML::LoadFile(configPath);

        mlsuite::Classification classification; 
        // I realized way too late that the above doesn't really need
        // to be a class, but anyway..

        try
        {
            classification->Train(samples, responses, config, modelPath);
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
    
    return EXIT_SUCCESS;
}

cv::Mat readCsv(const std::string& path)
{
    // This is definitely the wrong way to do it,
    // or at least it is very inelegant.
    // Please find the right one.

    CvMLData mlData;
    mlData.read_csv(path);
    const CvMat* tmp = mlData.get_values();
    cv::Mat img(tmp, true);

    return img;
}