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
#include <QDir>

#include "globals.h"

void write_image(QJsonObject& meta, const std::string& imageName, const std::string& dest) {
    const cv::Mat img = cv::imread(imageName);
    if (!img.data) return;
	const moldec md { img };

	md.write_images(meta, imageName, dest);
}

int main(int argc, char *argv[]) {

	QCoreApplication app(argc, argv);
    QCoreApplication::setApplicationName("mollex-ng");
    QCoreApplication::setApplicationVersion("1.0");

    // QCommandLineParser parser;
    parser.setApplicationDescription("Extract snails from images.");
    parser.addHelpOption();
    parser.addVersionOption();
    parser.addPositionalArgument("source", QCoreApplication::translate("main", "Source image to process."));
    parser.addPositionalArgument("destination", QCoreApplication::translate("main", "Destination directory."));

    parser.addOptions({        
        {"verbose", QCoreApplication::translate("main", "Show debug information.")},
        {"json", QCoreApplication::translate("main", "Write metadata as JSON to stdout.")},
        // A boolean option with multiple names (-f, --force)
        //{{"f", "force"},
        //    QCoreApplication::translate("main", "Overwrite existing files.")},
        // An option with a value
        //{{"t", "target-directory"},
        //    QCoreApplication::translate("main", "Save images into into <directory>. Default is <out>."),
        //    QCoreApplication::translate("main", "directory"),
		//	QCoreApplication::translate("main", "out")},
    });

    // Process the actual command line arguments given by the user
    parser.process(app);

    const QStringList args = parser.positionalArguments();
    if (args.count() < 2 ) parser.showHelp();

    const QString source = args.at(0);
    const QString dest = args.at(1);

    const QDir destDir(dest);
    if (!destDir.exists()) {
        std::cout << "Destination dir does not exists." << std::endl;
        return EXIT_FAILURE;
    }

    //bool showProgress = parser.isSet("progress");
    //bool force = parser.isSet(forceOption);
    //QString targetDir = parser.value(targetDirectoryOption);

	//std::cout << "Save images to: " << dest.toStdString() << std::endl;
	QJsonObject jsonMetaObject;	    
    write_image(jsonMetaObject, source.toStdString(), dest.toStdString());

    if (parser.isSet("json")) {
        QJsonDocument doc(jsonMetaObject);
        std::cout << doc.toJson().toStdString();
    }	    

    return EXIT_SUCCESS;
}
