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

void write_image(const std::string& imageName, QJsonObject& meta) {
    const cv::Mat img = cv::imread(imageName);
    if (!img.data) return;
	const moldec md { img };

	md.write_images(meta, imageName);
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
        //{{"p","progress"},
        //    QCoreApplication::translate("main", "Show progress during copy")},
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

    //bool showProgress = parser.isSet("progress");
    //bool force = parser.isSet(forceOption);
    //QString targetDir = parser.value(targetDirectoryOption);

	std::cout << "Save images to: " << parser.value("target-directory").toStdString() << std::endl;
	QJsonObject jsonMetaObject;	    
    write_image(args.at(0).toStdString(), jsonMetaObject);

	QJsonDocument doc(jsonMetaObject);
    std::cerr << doc.toJson().toStdString();

    return EXIT_SUCCESS;
}
