#include <cassert>
#include <cstdlib>
#include <iostream>
#include <vector>
#include <algorithm>
#include <fstream>

#include <mutex>
#include <atomic>
#include <thread>
#include <chrono>

#include "detect.h"
#include <opencv/cv.hpp>

#include <QJsonArray>
#include <QJsonObject>
#include <QJsonDocument>
#include <QCommandLineParser>

#include "globals.h"

void write_image(const std::string& imageName, const std::vector<std::string>& data, QJsonObject& meta) {
    const cv::Mat img = cv::imread("images/" + imageName + ".jpg");
    if (!img.data) return;
	const moldec md { img };

	md.write_images(meta, data, imageName);
}

void process_line(const std::string& line, QJsonObject& meta) {
	std::vector<std::string> data;
	std::stringstream ss(line);
	std::string entry;
	for (auto i = (size_t)0; i < 13; ++i) {
		std::getline(ss, entry, ';');
		data.push_back(entry);
	}
	std::getline(ss, entry, ';');//Hackathon download Link

	//read image names
	while (std::getline(ss, entry, ';')) {
		if (entry != "") {
			auto ss1 = std::stringstream(entry);
			std::string imageName;
			std::getline(ss1, imageName, '.');
			write_image(imageName, data, meta);
		}
	}
	
}

int main(int argc, char *argv[]) {

	QCoreApplication app(argc, argv);
    QCoreApplication::setApplicationName("mollex-ng");
    QCoreApplication::setApplicationVersion("1.0");

    // QCommandLineParser parser;
    parser.setApplicationDescription("Test helper");
    parser.addHelpOption();
    parser.addVersionOption();
    parser.addPositionalArgument("source", QCoreApplication::translate("main", "Source file to copy."));
    parser.addPositionalArgument("destination", QCoreApplication::translate("main", "Destination directory."));

    parser.addOptions({
        // A boolean option with a single name (-p)
        {{"p","progress"},
            QCoreApplication::translate("main", "Show progress during copy")},
        // A boolean option with multiple names (-f, --force)
        {{"f", "force"},
            QCoreApplication::translate("main", "Overwrite existing files.")},
        // An option with a value
        {{"t", "target-directory"},
            QCoreApplication::translate("main", "Save images into into <directory>. Default is <out>."),
            QCoreApplication::translate("main", "directory"),
			QCoreApplication::translate("main", "out")},
    });

    // Process the actual command line arguments given by the user
    parser.process(app);

    const QStringList args = parser.positionalArguments();
    // source is args.at(0), destination is args.at(1)

    bool showProgress = parser.isSet("progress");
    //bool force = parser.isSet(forceOption);
    //QString targetDir = parser.value(targetDirectoryOption);

	std::cout << "Save images to: " << parser.value("target-directory").toStdString() << std::endl;

	// ###################################

	std::ifstream oldMetaFile("species_list.csv");	
	std::string line;
    if (!oldMetaFile.is_open()) {
        std::cerr << "Can not open species_list.csv" << std::endl;
        return EXIT_FAILURE;
    }

	std::ofstream newMetaFile("out/meta_file.csv");
    if (!newMetaFile.is_open()) {
        std::cerr << "Can not create data/meta_file.csv" << std::endl;
        return EXIT_FAILURE;
    }

    newMetaFile << "Image;Color;Rotation;Ratio;OriginalImage;InventarNr;Class;Family;Genus;Species;Scientific Name;Fundort;Datum;Gebiet;Provinz;Land;Teilkontinent;Kontinent" << std::endl;

	std::getline(oldMetaFile, line);

	std::vector<std::string> lines;
	while (std::getline(oldMetaFile, line)) {
		lines.emplace_back(line);
	}

    long unsigned int lines_processed = 1;

	QJsonArray jsonMetaArray;
    
	//#pragma omp parallel for
    //for (long unsigned int i = 0; i < lines.size(); i++) {   
	
	//#pragma omp parallel for
	for (long unsigned int i = 0; i < 2; i++) {   
		QJsonObject jsonMetaObject;	    
        process_line(lines[i], jsonMetaObject);
		jsonMetaArray.push_back(jsonMetaObject);
		std::cout << lines_processed << "/" << lines.size() << std::endl;
        lines_processed += 1;		
	}

    //progress_thread.join();
	oldMetaFile.close();
	newMetaFile.close();

	QJsonDocument doc(jsonMetaArray);
    std::cerr << doc.toJson().toStdString();

    return EXIT_SUCCESS;
}
